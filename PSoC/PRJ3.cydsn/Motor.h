#pragma once

#include <stdint.h>

// Delaygrænser (i ms) mellem stator-skift
#define MIN_SPEED_DELAY 5
#define MAX_SPEED_DELAY 20

// Steps pr. omdrejning
#define TOTAL_STEPS 2048

void SetAngle(int16_t angleDeg, uint8_t speedPercent);
void Deactivate(void);