/*
    Implementationsfil for TCS37073M
                                        */

#include "ColorSensor.h"

uint8_t address = 0x39; // I2C adresse for farvesensoren

void ColorSensor_ReadRegister(uint8_t REG, uint8_t dataBytes, uint8_t* bytes) {
    I2C_MasterSendStart(address, 0);
    I2C_MasterWriteByte(REG); // Register at starte aflæsning ved
    I2C_MasterSendRestart(address, 1);
    for (uint8_t i = 0; i < dataBytes; ++i) { // Loop for hver efterfølgende byte der skal læses
        bool isLastByte = (i == dataBytes - 1); // Sikrer NACK ved sidste byte, i stedet for ACK
        bytes[i] = I2C_MasterReadByte(isLastByte?I2C_NAK_DATA:I2C_ACK_DATA);
    }
    I2C_MasterSendStop();
}

void ColorSensor_WriteRegister(uint8_t REG, uint8_t data) {
    I2C_MasterSendStart(address, 0);
    I2C_MasterWriteByte(REG);
    I2C_MasterWriteByte(data);
    I2C_MasterSendStop();
}

void ColorSensor_ReadColorData(uint16_t* colorData) {
    uint8_t dataBytes = DATA_REG_END_ADDR - DATA_REG_START_ADDR; // Antal af bytes at læse i ALS data registre
    uint8_t data[dataBytes];
    
    ColorSensor_ReadRegister(DATA_REG_START_ADDR, dataBytes, data);
    
    uint16_t red = (data[3] << 8) + data[2];    // Rød (0x97 - 0x98)
    uint16_t green = (data[5] << 8) + data[4];  // Grøn (0x99 - 0x9A)
    uint16_t blue = (data[7] << 8) + data[6];   // Blå (0x9B - 0x9C)
    
    colorData[0] = red;
    colorData[1] = green;
    colorData[2] = blue;
}

void ColorSensor_Initialize() {
    ColorSensor_WriteRegister(0x80, 0b00000011); // Enable AEN & PON bits
}