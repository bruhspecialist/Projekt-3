#include "project.h"
#include "Motor.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const uint8_t FULL_DRIVE_SEQUENCE[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1}
};
const uint8_t STOPPED_DRIVE[4] = {0, 0, 0, 0};

static uint16_t currentStep = 0; // 0 - 47 (0° - 352.5°)

// Sætter tilstande af statore
void SetStators(const uint8_t states[4]) {
    STEP_1a_Write(states[0]);
    STEP_2a_Write(states[1]);
    STEP_1b_Write(states[2]);
    STEP_2b_Write(states[3]);
}

// Kalkulerer tiden (ms) til næste stator-skift
uint16_t CalculateDelay(uint8_t speed) {
    uint16_t delayLimitDiff = MAX_SPEED_DELAY - MIN_SPEED_DELAY;
    uint16_t speedDiff = 100 - speed;
    uint16_t delay = MIN_SPEED_DELAY + (delayLimitDiff * speedDiff * speedDiff) / (100 * 100);
    return delay;
}

// Kalkulerer ny 'step-værdi', som er proportional med vinklen
uint16_t CalculateNewStep(uint16_t step, int16_t stepDiff) {
    int16_t newStep = (step + stepDiff) % TOTAL_STEPS;
    if (newStep < 0) newStep += TOTAL_STEPS;
    return newStep;
}

// Indstil vinkel af motoren
void SetAngle(int16_t newAngle, uint8_t speed) {
    newAngle = ((newAngle % 360) + 360) % 360; // Sikrer 0–359

    uint16_t newStep = (TOTAL_STEPS * newAngle) / 360;
    
    if (newStep == currentStep) return;

    int16_t stepDiff = newStep - currentStep;
    int16_t altDiff = (stepDiff > 0) ? stepDiff - TOTAL_STEPS : stepDiff + TOTAL_STEPS;

    int16_t chosenDiff = (abs(stepDiff) <= abs(altDiff)) ? stepDiff : altDiff;
    int8_t stepInc = (chosenDiff > 0) ? 1 : -1;
    int16_t stepsRemaining = abs(chosenDiff);
    
    while (stepsRemaining--) {
        currentStep = CalculateNewStep(currentStep, stepInc);

        char msg[64];
        snprintf(msg, 64, "currentStep: %d\r\n", currentStep);
        UART_USB_PutString(msg);

        SetStators(FULL_DRIVE_SEQUENCE[currentStep % 4]);
        CyDelay(CalculateDelay(speed));
    }
}

// Slukker statore
void Deactivate() {SetStators(STOPPED_DRIVE);}