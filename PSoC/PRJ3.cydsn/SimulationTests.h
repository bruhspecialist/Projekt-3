#pragma once

#include "project.h"
#include "ColorSensor.h"

#include "stdbool.h"
#include "stdlib.h"
#include "time.h"

void InitializeSimulationConditions() {
    srand(time(NULL));
}

bool SimulateColorSensor(uint8_t* color) {
    *color = rand() % 7;
    return true;
}