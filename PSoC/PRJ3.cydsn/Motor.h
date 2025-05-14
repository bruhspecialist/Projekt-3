#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Grænser for 'speed' (i form af delay)
#define MIN_SPEED_DELAY 1 // Minimum delay (ms) mellem stator-skift
#define MAX_SPEED_DELAY 10 // Maksimum delay (ms) mellem stator-skift

// Antal af mulige positioner
#define TOTAL_STEPS 2048 // 7.5° pr. step (360/7.5=48)

// Prototyper
void SetAngle(int16_t newAngle, uint8_t speed);
void Deactivate();