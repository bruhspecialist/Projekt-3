#pragma once

#include <stdbool.h>
#include <stdint.h>

#define DATA_REG_START_ADDR 0x95
#define DATA_REG_END_ADDR 0xA0

#define MAX_VALUE 17999

// Referenceværdier fra hvid skærm på iPhone 15 Pro
#define R_REF 17506
#define G_REF 17156
#define B_REF 15056

#define ADDRESS 0x39

enum Colors {tone, red, green, blue, yellow, cyan, magenta};

const char* ColorToString(uint8_t color);
bool ColorSensor_Read(uint8_t* color);
bool ColorSensor_Initialize();