#include "project.h"
#include "Pump.h"

void Pump(int color)
{
    if (color >= 1 && color <= 6)
    {
        switch(color)
        {
            case 1:
                PUMP_1_Write(1);
                CyDelay(5000);
                PUMP_1_Write(0);
                break;
            case 2:
                PUMP_2_Write(1);
                CyDelay(5000);
                PUMP_2_Write(0);
                break;
            case 3:
                PUMP_3_Write(1);
                CyDelay(5000);
                PUMP_3_Write(0);
                break;
            case 4:
                PUMP_4_Write(1);
                CyDelay(5000);
                PUMP_4_Write(0);
                break;
            case 5:
                PUMP_5_Write(1);
                CyDelay(5000);
                PUMP_5_Write(0);
                break;
            case 6:
                PUMP_6_Write(1);
                CyDelay(5000);
                PUMP_6_Write(0);
                break;
        }


    }
}