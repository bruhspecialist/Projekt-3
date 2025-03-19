/*
    Implementationsfil for SP2575M0206-A
                                            */


#include "project.h"
#include "Motor.h"
#include <stdint.h>

/* Statorenes step sekvenser for de forskellige drive modes */
const uint8_t MOTOR_WAVE_DRIVE_SEQUENCE[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};
const uint8_t MOTOR_FULL_DRIVE_SEQUENCE[4][4] = {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {1, 0, 0, 1}
};
const uint8_t MOTOR_HALF_DRIVE_SEQUENCE[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

/* Tilstand for slukkede statore */
const uint8_t MOTOR_STOPPED_DRIVE[4] = {0, 0, 0, 0};

// Variabler
static bool currentState = false; // Slukket som standard
static driveModes currentMode = MOTOR_MODE_FULL_STEP; // I Full Step som standard
static driveDirections currentDirection = MOTOR_DIRECTION_FORWARD; // Kører fremad som standard
static uint8_t currentSpeed = 50; // 50% hastighed som standard

// Sætter tilstande af statore
void SetStators(const uint8_t states[4]) {
    STEP_1a_Write(states[0]);
    STEP_2a_Write(states[1]);
    STEP_1b_Write(states[2]);
    STEP_2b_Write(states[3]);
}

// Kalkulerer tiden (ms) til næste stator-skift
uint16_t CalculateDelay() {
    uint16_t delayLimitDiff = MAX_SPEED_DELAY - MIN_SPEED_DELAY;
    uint16_t speedDiff = 100 - currentSpeed;
    uint16_t delay = MIN_SPEED_DELAY + (delayLimitDiff * speedDiff * speedDiff) / (100 * 100);
    return delay;
}

// Kører én step sekvens
void RunDriveSequence(const uint8_t sequence[][4], uint8_t steps){
    uint8_t init_direction = currentDirection;
    uint8_t i = (init_direction == MOTOR_DIRECTION_FORWARD)?(0):(steps-1);
    int8_t step_inc = (init_direction == MOTOR_DIRECTION_FORWARD)?(1):(-1);
    for (; (i < steps && i >= 0); i += step_inc) {
        
        if (
            currentState == true
            && currentDirection == init_direction
        ) {
            SetStators(sequence[i]);
            CyDelay(CalculateDelay());
        }
        else break;
    }
}

// Sætter kørsel: tændt/slukket
void Motor_SetDriveState(bool newState) {
    currentState = newState;
    if (newState == false) {
        SetStators(MOTOR_STOPPED_DRIVE);
    }
}

// Sætter Drive Mode
void Motor_SetDriveMode(driveModes newMode) {
    currentMode = newMode;
}

// Sætter kørselsretning: fremad/bagud
void Motor_SetDriveDirection(driveDirections newDirection) {
    currentDirection = newDirection;
}

// Sætter kørselshastighed: Mellem 0 tom. 100. Kan forstås som procent
uint8_t Motor_SetDriveSpeed(uint8_t newSpeed) {
    uint8_t speed = (newSpeed >= 0 && newSpeed <= 100)?newSpeed:currentSpeed;
    currentSpeed = speed;
    return speed;
}

// Returnerer kørselsretning
driveDirections Motor_GetDriveDirection() {
    return currentDirection;
}

// Returnerer kørselshastighed
uint8_t Motor_GetDriveSpeed() {
    return currentSpeed;
}

// Opdaterer step sekvensen, baseret på aktuel drive mode
void Motor_UpdateState() {
    switch (currentMode) {
        case MOTOR_MODE_WAVE_DRIVE :  RunDriveSequence(MOTOR_WAVE_DRIVE_SEQUENCE, 4); break;
        case MOTOR_MODE_FULL_STEP  :  RunDriveSequence(MOTOR_FULL_DRIVE_SEQUENCE, 4); break;
        case MOTOR_MODE_HALF_STEP  :  RunDriveSequence(MOTOR_HALF_DRIVE_SEQUENCE, 8); break;
        default : break;
    }
}