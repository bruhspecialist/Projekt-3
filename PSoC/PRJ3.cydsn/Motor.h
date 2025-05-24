#pragma once

#include <stdint.h>

void Motor_SetAngle(int16_t angleDeg, uint8_t speedPercent);
void Motor_Deactivate();