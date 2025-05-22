#pragma once

#include <stdbool.h>
#include <stdint.h>

enum Colors {tone, red, green, blue, yellow, cyan, magenta};

const char* ColorToString(enum Colors color);
bool ColorSensor_ReadRGB(uint16_t* rgbNorm);
//bool ColorSensor_ReadAverage(uint8_t* color, uint16_t measurements);
bool ColorSensor_Read(uint8_t* color);
bool ColorSensor_Initialize();