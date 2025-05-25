#include "project.h"
#include "Pump.h"

void (*PumpWrite[])(uint8_t) = {
        PUMP_1_Write,
        PUMP_2_Write,
        PUMP_3_Write,
        PUMP_4_Write,
        PUMP_5_Write,
        PUMP_6_Write
};

void ActivatePump(uint8_t color)
{
    if (color < 1 || color > 6) return; // Ugyldig farve-tal --> Returnér
    PumpWrite[color - 1](1); // Tænd pumpen
}

void DeactivatePump(uint8_t color)
{
    if (color < 1 || color > 6) return; // Ugyldig farve-tal --> Returnér
    PumpWrite[color - 1](0); // Sluk pumpen
}