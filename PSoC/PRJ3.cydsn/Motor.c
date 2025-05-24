#include "project.h"
#include "Motor.h"

#include <stdlib.h> // til abs()

// Delaygrænser (i ms) mellem stator-skift
#define MIN_SPEED_DELAY 5
#define MAX_SPEED_DELAY 20

// Steps pr. omdrejning
#define TOTAL_STEPS 2048

// Sekvens til 4-trins full-step kørsel
const uint8_t DRIVE_SEQ[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1}
};

const uint8_t DRIVE_OFF[4] = {0, 0, 0, 0};

uint16_t currentStep = 0; // 0 - 2047

void SetStators(const uint8_t s[4]) {
    STEP_1a_Write(s[0]);
    STEP_2a_Write(s[1]);
    STEP_1b_Write(s[2]);
    STEP_2b_Write(s[3]);
}

uint16_t CalculateDelay(uint8_t speedPercent) {
    // Kvadratisk faldende delay med hastighed
    uint16_t range = MAX_SPEED_DELAY - MIN_SPEED_DELAY;
    uint16_t diff = 100 - speedPercent;
    return MIN_SPEED_DELAY + (range * diff * diff) / 10000;
}

uint16_t WrapStep(int32_t step) {
    step %= TOTAL_STEPS;
    return (step < 0) ? step + TOTAL_STEPS : step;
}

void Motor_SetAngle(int16_t angle, uint8_t speed) {
    angle = ((angle % 360) + 360) % 360; // Sikrer 0–359
    uint16_t targetStep = (TOTAL_STEPS * angle) / 360;

    if (targetStep == currentStep) return;

    int16_t delta = targetStep - currentStep;
    int16_t altDelta = (delta > 0) ? delta - TOTAL_STEPS : delta + TOTAL_STEPS;

    int16_t bestDelta = (abs(delta) <= abs(altDelta)) ? delta : altDelta;
    int8_t stepDir = (bestDelta > 0) ? 1 : -1;
    uint16_t steps = abs(bestDelta);
    uint16_t delay = CalculateDelay(speed);

    while (steps--) {
        currentStep = WrapStep(currentStep + stepDir);
        SetStators(DRIVE_SEQ[currentStep % 4]);
        CyDelay(delay);
    }
}

void Motor_Deactivate() {
    SetStators(DRIVE_OFF);
}