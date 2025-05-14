#pragma once

#include "project.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_REG_START_ADDR 0x95
#define DATA_REG_END_ADDR 0xA0

#define MAX_VALUE 17999

void TCS37073M_ReadRegister(uint8_t REG, uint8_t bytesAmount, uint8_t* bytes);
void TCS37073M_WriteRegister(uint8_t REG, uint8_t data);

void TCS37073M_ReadColorData(uint16_t* rgbData);

uint16_t FindMaxColor(const uint16_t rgb[3]);

void CalibrateColor(const uint16_t *rgb, uint16_t *rgbNorm);
const char* DetectColor(const uint16_t* rgb);

const char* Read();

void TCS37073M_Initialize();