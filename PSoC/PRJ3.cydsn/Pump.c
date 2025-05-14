void Pump(int color)
{
    if (color >= 1 && color <= 6)
    {
        switch(color)
        {
            case 1:
                Pump_Pin_1_Write(1);
                CyDelay(5000);
                Pump_Pin_1_Write(0);
                break;
            case 2:
                Pump_Pin_2_Write(1);
                CyDelay(5000);
                Pump_Pin_2_Write(0);
                break;
            case 3:
                Pump_Pin_3_Write(1);
                CyDelay(5000);
                Pump_Pin_3_Write(0);
                break;
            case 4:
                Pump_Pin_4_Write(1);
                CyDelay(5000);
                Pump_Pin_4_Write(0);
                break;
            case 5:
                Pump_Pin_5_Write(1);
                CyDelay(5000);
                Pump_Pin_5_Write(0);
                break;
            case 6:
                Pump_Pin_6_Write(1);
                CyDelay(5000);
                Pump_Pin_6_Write(0);
                break;
        }


    }
}


/* [] END OF FILE */
