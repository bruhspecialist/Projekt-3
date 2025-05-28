#include "project.h"
#include "ColorSensor.h"

#include <stdio.h>
#include <stdlib.h>

/* TCS37073M indstillinger */
#define ADDRESS 0x39

#define DATA_REG_START_ADDR 0x95
#define DATA_REG_END_ADDR 0xA0

#define ATIME 29 // Antal af integrations-steps fra 1-256
#define ASTEP 599 // ASTEP (Bits 15:0 - Integrations-tid mellem steps)
#define AGAIN 4 // Sensitivitet af sensoren

// Referenceværdier fra hvidt papir (MAX_VALUE=17999)
const uint16_t rgb_ref[3] = {8685, 8716, 5886};

// Tiden før farveaflæsning, at lysioden skal tænde
#define LED_ENABLE_DELAY 100 // ms

// Tolerance-værdier for farveaflæsning
#define SEC_TOL 0.20 // 20% tolerance for at farve afgøres som sekundær farve
#define UNDEF_TOL 0.05 // 5% tolerance for at farve afgøres som udefineret

bool ReadRegister(uint8_t REG, uint8_t dataBytes, uint8_t* bytes)
{
    if (I2C_MasterSendStart(ADDRESS, 0)   != I2C_MSTR_NO_ERROR) return false;
    if (I2C_MasterWriteByte(REG)          != I2C_MSTR_NO_ERROR) return false;
    if (I2C_MasterSendRestart(ADDRESS, 1) != I2C_MSTR_NO_ERROR) return false;
    for (uint8_t i = 0; i < dataBytes; ++i) { // Loop for hver efterfølgende byte der skal læses
        bool isLastByte = (i == dataBytes - 1); // Sikrer NACK ved sidste byte, i stedet for ACK
        bytes[i] = I2C_MasterReadByte(isLastByte?I2C_NAK_DATA:I2C_ACK_DATA);
    }
    I2C_MasterSendStop();
    return true;
}

bool WriteRegister(uint8_t REG, uint8_t data)
{
    if (I2C_MasterSendStart(ADDRESS, 0) != I2C_MSTR_NO_ERROR) return false;
    if (I2C_MasterWriteByte(REG)        != I2C_MSTR_NO_ERROR) return false;
    if (I2C_MasterWriteByte(data)       != I2C_MSTR_NO_ERROR) return false;
    I2C_MasterSendStop();
    return true;
}

bool ReadColorDataRegisters(uint16_t* rgbData) {
    uint8_t dataBytes = DATA_REG_END_ADDR - DATA_REG_START_ADDR; // Antal af bytes at læse i ALS data registre
    uint8_t data[dataBytes];
    
    if (!ReadRegister(DATA_REG_START_ADDR, dataBytes, data)) return false;
    
    rgbData[0] = (data[3] << 8) | data[2]; // Rød  (0x97 - 0x98)
    rgbData[1] = (data[5] << 8) | data[4]; // Grøn (0x99 - 0x9A)
    rgbData[2] = (data[7] << 8) | data[6]; // Blå  (0x9B - 0x9C)
    
    return true;
}

uint16_t GetDominatingColor(const uint16_t rgb[3]) {
    uint16_t max = rgb[0] > rgb[1] ? rgb[0] : rgb[1];
    return max > rgb[2] ? max : rgb[2];
}

void CalibrateColor(const uint16_t* rgb, uint16_t *rgbNorm) {
    uint16_t maxRef = GetDominatingColor(rgb_ref);
    uint16_t maxValue = ATIME * ASTEP + ATIME + ASTEP;
    for (uint8_t i = 0; i < 3; ++i) {
        uint32_t norm = ((uint32_t)rgb[i] * maxRef) / rgb_ref[i];
        rgbNorm[i] = (norm > maxValue) ? maxValue : norm;
    }
}

uint8_t DetectColor(const uint16_t* rgb) {
    uint16_t r = rgb[0], g = rgb[1], b = rgb[2];

    uint16_t max = r;
    if (g > max) max = g;
    if (b > max) max = b;

    uint16_t min = r;
    if (g < min) min = g;
    if (b < min) min = b;

    if (max - min <= max * UNDEF_TOL) return no_color; // For lidt kontrast til at afgøre farve

    if (r > g * (1 + SEC_TOL) && r > b * (1 + SEC_TOL)) return red;
    if (g > r * (1 + SEC_TOL) && g > b * (1 + SEC_TOL)) return green;
    if (b > r * (1 + SEC_TOL) && b > g * (1 + SEC_TOL)) return blue;
    if (r > b && g > b) return yellow;
    if (g > r && b > r) return cyan;
    if (r > g && b > g) return magenta;
    return no_color; // Hvis alt andet skulle fejle (Bør ikke ske)
}

uint8_t GetOpposingColor(enum Colors color) {
    switch (color) {
        case red       : return yellow;
        case green     : return magenta;
        case blue      : return cyan;
        case yellow    : return red;
        case cyan      : return blue;
        case magenta   : return green;
        default        : return no_color;
    }
}

const char* ColorToString(enum Colors color) {
    switch (color) {
        case red       : return "red";
        case green     : return "green";
        case blue      : return "blue";
        case yellow    : return "yellow";
        case cyan      : return "cyan";
        case magenta   : return "magenta";
        default        : return "error";
    }
}

bool ColorSensor_ReadRawRGB(uint16_t* rgbData) {
    COLOR_SENSOR_LED_Write(1);
    CyDelay(LED_ENABLE_DELAY);
    if (!ReadColorDataRegisters(rgbData)) return false;
    COLOR_SENSOR_LED_Write(0);
    return true;
}

bool ColorSensor_ReadRGB(uint16_t* rgbNorm) {
    COLOR_SENSOR_LED_Write(1);
    CyDelay(LED_ENABLE_DELAY);
    uint16_t rgbData[3];
    if (!ReadColorDataRegisters(rgbData)) return false;
    CalibrateColor(rgbData, rgbNorm);
    COLOR_SENSOR_LED_Write(0);
    return true;
}

bool ColorSensor_Read(uint8_t* color) {
    COLOR_SENSOR_LED_Write(1);
    CyDelay(LED_ENABLE_DELAY);
    uint16_t rgbData[3];
    uint16_t rgbNorm[3];
    if (!ReadColorDataRegisters(rgbData)) return false;
    CalibrateColor(rgbData, rgbNorm);
    *color = GetOpposingColor(DetectColor(rgbNorm));
    COLOR_SENSOR_LED_Write(0);
    return true;
}

bool ColorSensor_Initialize()
{
    I2C_Start();
    uint8_t ASTEP_MSB = ASTEP >> 8;
    if (!WriteRegister(0x81, ATIME)) return false;
    if (!WriteRegister(0xCA, ASTEP - ASTEP_MSB)) return false;
    if (!WriteRegister(0xCB, ASTEP_MSB)) return false;
    if (!WriteRegister(0xAA, AGAIN)) return false;
    if (!WriteRegister(0x80, 0b00000011)) return false; // Enable AEN & PON bits
    return true;
}