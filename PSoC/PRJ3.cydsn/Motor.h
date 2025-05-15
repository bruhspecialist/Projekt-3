#pragma once

#include <stdint.h>

// Grænser for 'speed' (i form af delay)
#define MIN_SPEED_DELAY 1 // Minimum delay (ms) mellem stator-skift
#define MAX_SPEED_DELAY 10 // Maksimum delay (ms) mellem stator-skift

// Antal af steps for én omdrejning
#define TOTAL_STEPS 2048

// Prototyper
void SetAngle(int16_t newAngle, uint8_t speed);
void Deactivate();