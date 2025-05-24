#pragma once

#include <stdint.h>

void Motor_SetAngle(
    int16_t angle, // Vinkel i grader
    uint8_t speed  // Drejningshastighed i procent
);
void Motor_Deactivate();