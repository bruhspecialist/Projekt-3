/*
    Header-fil for SP2575M0206-A
                                    */

#include <stdio.h>
#include <stdbool.h>

// Mulige drive modes
typedef enum {
    MOTOR_MODE_WAVE_DRIVE,
    MOTOR_MODE_FULL_STEP,
    MOTOR_MODE_HALF_STEP
} driveModes;

// Mulige omdrejningsretninger
typedef enum {
    MOTOR_DIRECTION_FORWARD,
    MOTOR_DIRECTION_BACKWARD
} driveDirections;

// Grænse for 'speed' (i form af delay)
#define MIN_SPEED_DELAY 10 // Minimum delay (ms) mellem stator-skift
#define MAX_SPEED_DELAY 1000 // Maksimum delay (ms) mellem stator-skift

// Prototyper
void Motor_SetDriveState(bool newState);
void Motor_SetDriveMode(driveModes newMode);
void Motor_SetDriveDirection(driveDirections newDirection);
uint8_t Motor_SetDriveSpeed(uint8_t newSpeed);
driveDirections Motor_GetDriveDirection();
uint8_t Motor_GetDriveSpeed();

//void SetStators(const uint8_t states[4]);
//uint16_t CalculateDelay();
//void RunDriveSequence(const uint8_t sequence[][4], uint8_t steps);
void Motor_UpdateState();