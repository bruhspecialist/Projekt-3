#pragma once

#include "project.h"

#include "ColorSensor.h"
#include "CustomMath.h"
#include "SimulationTests.h"
#include "ErrorMessage.h"

#include "stdint.h"

#define COLOR_MEASUREMENTS 100  // Antal målinger
#define COLOR_SENSING_TIME 1000 // ms

void TestColorSensor() {
    uint16_t colorFrequency[COLOR_MEASUREMENTS] = {0};
    for (uint8_t i = 0; i < COLOR_MEASUREMENTS; ++i) {
        uint8_t color_index;
        //if (!ColorSensor_Read(&color_index)) PrintError(-2);
        if (!SimulateColorSensor(&color_index)) PrintError(-2);
        else colorFrequency[i]++;
        CyDelay(COLOR_SENSING_TIME/COLOR_MEASUREMENTS);
    }
    
    uint8_t mostFrequentColor = MostFrequent(colorFrequency);
    
    UART_USB_PutString("Detected color: \r\n");
    UART_USB_PutString(ColorToString(mostFrequentColor));
    UART_USB_PutString("\r\n");
}