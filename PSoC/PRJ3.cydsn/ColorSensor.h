/*
    Header-fil for TCS37073M
                                */

#pragma once

#include "project.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_REG_START_ADDR 0x95
#define DATA_REG_END_ADDR 0xA0

#define MAX_VALUE 999

void ColorSensor_ReadRegister(uint8_t REG, uint8_t bytesAmount, uint8_t* bytes);
void ColorSensor_WriteRegister(uint8_t REG, uint8_t data);

uint16_t ColorSensor_ReadClearData();
void ColorSensor_ReadColorData(uint16_t* colorData);

void ColorSensor_Initialize();