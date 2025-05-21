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
    uint8_t colorFrequency[7] = {0};
    for (uint8_t i = 0; i < COLOR_MEASUREMENTS; ++i) {
        uint8_t color_index;
        if (!ColorSensor_Read(&color_index)) PrintError(-2);
        else colorFrequency[color_index]++;
    }
    uint8_t mostFrequentColor = GetMaxIndex(colorFrequency, 7);
    UART_USB_PutString("colorFrequency: ");
    for (uint8_t i = 0; i < sizeof(colorFrequency); ++i) {
        UART_USB_PutInt(colorFrequency[i]);
        if (i != sizeof(colorFrequency) - 1) UART_USB_PutString(", ");
    }
    UART_USB_PutString("\r\n");
    
    UART_USB_PutString("mostFrequentColor: ");
    UART_USB_PutInt(mostFrequentColor);
    UART_USB_PutString("\r\n");
    
    UART_USB_PutString("Detected color: ");
    UART_USB_PutString(ColorToString(mostFrequentColor));
    UART_USB_PutString("\r\n");
}