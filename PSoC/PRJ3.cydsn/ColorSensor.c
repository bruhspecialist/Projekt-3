#include "project.h"
#include "ColorSensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const uint16_t rgb_ref[3] = {R_REF, G_REF, B_REF}; // Med udgangspunkt i hvid skærm fra iPhone 15 Pro

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
    
    rgbData[0] = (data[3] << 8) | data[2];    // Rød (0x97 - 0x98)
    rgbData[1] = (data[5] << 8) | data[4];  // Grøn (0x99 - 0x9A)
    rgbData[2] = (data[7] << 8) | data[6];   // Blå (0x9B - 0x9C)
    
    return true;
}

uint16_t FindMaxColor(const uint16_t rgb[3]) {
    uint16_t max = rgb[0] > rgb[1] ? rgb[0] : rgb[1];
    return max > rgb[2] ? max : rgb[2];
}

void CalibrateColor(const uint16_t *rgb, uint16_t *rgbNorm) {
    uint16_t maxRef = FindMaxColor(rgb_ref);
    for (uint8_t i = 0; i < 3; ++i) {
        uint32_t norm = ((uint32_t)rgb[i] * maxRef) / rgb_ref[i];
        rgbNorm[i] = (norm > MAX_VALUE) ? MAX_VALUE : norm;
    }
}

const char* DetectColor(const uint16_t* rgb) {
    const double tol = 0.20;
    if (rgb[0] > rgb[1]*(1+tol) && rgb[0] > rgb[2]*(1+tol)) return "red";
    if (rgb[1] > rgb[0]*(1+tol) && rgb[1] > rgb[2]*(1+tol)) return "green";
    if (rgb[2] > rgb[0]*(1+tol) && rgb[2] > rgb[1]*(1+tol)) return "blue";
    if (rgb[0] > rgb[2] && rgb[1] > rgb[2]) return "yellow";
    if (rgb[0] > rgb[1] && rgb[2] > rgb[1]) return "magenta";
    if (rgb[1] > rgb[0] && rgb[2] > rgb[0]) return "cyan";
    if (rgb[0] >= rgb[1] && rgb[0] >= rgb[2]) return "red";
    if (rgb[1] >= rgb[0] && rgb[1] >= rgb[2]) return "green";
    return "blue";
}

bool TCS37073M_Read(const char** color) {
    uint16_t rgbData[3];
    uint16_t rgbNorm[3];
    if (!ReadColorDataRegisters(rgbData)) return false;
    CalibrateColor(rgbData, rgbNorm);
    *color = DetectColor(rgbNorm);
    return true;
}

bool TCS37073M_Initialize()
{
    I2C_Start();
    if (!WriteRegister(0x81, 0x1D)) return false; // ?
    if (!WriteRegister(0xCA, 0x57)) return false; // ?
    if (!WriteRegister(0xCB, 0x02)) return false; // ?
    if (!WriteRegister(0x80, 0b00000011)) return false; // Enable AEN & PON bits
    return true;
}