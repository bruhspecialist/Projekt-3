#include "project.h"
#include "Pump.h"

void Pump(uint8_t color)
{
    if (color < 1 || color > 6) return; // Ugyldig farve-tal --> Returnér

    void (*pumpWrite[])(uint8_t) = {
        PUMP_1_Write,
        PUMP_2_Write,
        PUMP_3_Write,
        PUMP_4_Write,
        PUMP_5_Write,
        PUMP_6_Write
    };

    pumpWrite[color - 1](1); // Tænd pumpen
    CyDelay(5000);
    pumpWrite[color - 1](0); // Sluk pumpen
}