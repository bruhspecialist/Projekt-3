#pragma once

#include <stdbool.h>
#include <stdint.h>

enum Colors {
    red     = 1,
    green   = 2,
    blue    = 3,
    yellow  = 4,
    cyan    = 5,
    magenta = 6
};

const char* ColorToString(enum Colors color);
bool ColorSensor_ReadRGB(uint16_t* rgbNorm);
bool ColorSensor_Read(uint8_t* color);
bool ColorSensor_Initialize();