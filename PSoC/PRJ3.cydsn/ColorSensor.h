#pragma once

#include <stdbool.h>
#include <stdint.h>

#define DATA_REG_START_ADDR 0x95
#define DATA_REG_END_ADDR 0xA0

#define ATIME 29 // Antal af integrations-steps fra 1-256
#define ASTEP 599 // ASTEP (Bits 15:0 - Integrations-tid mellem steps)
#define AGAIN 2 // Sensitivitet af sensoren
#define MAX_VALUE (ATIME * ASTEP + ATIME + ASTEP)

// Referenceværdier fra hvid skærm på iPhone 15 Pro (MAX_VALUE=17999)
#define R_REF 17506
#define G_REF 17156
#define B_REF 15056

#define ADDRESS 0x39

#define LED_ENABLE_DELAY 100 // ms

enum Colors {tone, red, green, blue, yellow, cyan, magenta};

const char* ColorToString(uint8_t color);
bool ColorSensor_ReadRGB(uint16_t* rgbNorm);
//bool ColorSensor_ReadAverage(uint8_t* color, uint16_t measurements);
bool ColorSensor_Read(uint8_t* color);
bool ColorSensor_Initialize();