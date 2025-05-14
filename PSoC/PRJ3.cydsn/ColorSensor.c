#include "ColorSensor.h"

const uint16_t rgb_ref[3] = {17506, 17156, 15056}; // Med udgangspunkt i hvid skærm fra iPhone 15 Pro
const uint8_t address = 0x39;

void TCS37073M_ReadRegister(uint8_t REG, uint8_t dataBytes, uint8_t* bytes)
{
    I2C_MasterSendStart(address, 0);
    I2C_MasterWriteByte(REG); // Register at starte aflæsning ved
    I2C_MasterSendRestart(address, 1);
    for (uint8_t i = 0; i < dataBytes; ++i) { // Loop for hver efterfølgende byte der skal læses
        bool isLastByte = (i == dataBytes - 1); // Sikrer NACK ved sidste byte, i stedet for ACK
        bytes[i] = I2C_MasterReadByte(isLastByte?I2C_NAK_DATA:I2C_ACK_DATA);
    }
    I2C_MasterSendStop();
}

void TCS37073M_WriteRegister(uint8_t REG, uint8_t data)
{
    I2C_MasterSendStart(address, 0);
    I2C_MasterWriteByte(REG);
    I2C_MasterWriteByte(data);
    I2C_MasterSendStop();
}

void TCS37073M_ReadColorData(uint16_t* rgbData) {
    uint8_t dataBytes = DATA_REG_END_ADDR - DATA_REG_START_ADDR; // Antal af bytes at læse i ALS data registre
    uint8_t data[dataBytes];
    
    TCS37073M_ReadRegister(DATA_REG_START_ADDR, dataBytes, data);
    
    uint16_t red = (data[3] << 8) + data[2];    // Rød (0x97 - 0x98)
    uint16_t green = (data[5] << 8) + data[4];  // Grøn (0x99 - 0x9A)
    uint16_t blue = (data[7] << 8) + data[6];   // Blå (0x9B - 0x9C)
    
    rgbData[0] = red;
    rgbData[1] = green;
    rgbData[2] = blue;
}

uint16_t FindMaxColor(const uint16_t rgb[3]) {
    uint16_t max = rgb[0] > rgb[1] ? rgb[0] : rgb[1];
    return max > rgb[2] ? max : rgb[2];
}

void CalibrateColor(const uint16_t *rgb, uint16_t *rgbNorm) {
    uint16_t maxRef = FindMaxColor(rgb_ref);
    for (uint8_t i = 0; i < 3; ++i) {
        //rgbNorm[i] = (rgb[i] * maxRef) / rgb_ref[i];
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

const char* Read() {
    // code
    return "amogus";
}

void TCS37073M_Initialize()
{
    TCS37073M_WriteRegister(0x81, 0x1D); // ?
    TCS37073M_WriteRegister(0xCA, 0x57); // ?
    TCS37073M_WriteRegister(0xCB, 0x02); // ?
    
    TCS37073M_WriteRegister(0x80, 0b00000011); // Enable AEN & PON bits
}