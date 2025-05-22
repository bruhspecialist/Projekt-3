#pragma once

#include "project.h"

#include "ColorSensor.h"
#include "CustomMath.h"
#include "SimulationTests.h"
#include "ErrorMessage.h"
#include "UART.h"

#include "stdio.h"
#include "stdint.h"

#define COLOR_MEASUREMENTS 100  // Antal målinger
#define COLOR_SENSING_TIME 1000 // ms

//void TestColorSensorRGB() {
//    uint16_t rgb[3];
//    char buffer[64];
//    ColorSensor_ReadRGB(rgb);
//    sprintf(buffer, "RGB = [%u, %u, %u]\r\n", rgb[0], rgb[1], rgb[2]);
//    UART_USB_PutString(buffer);
//}
//
//void TestAverageColorSensor() {
//    uint8_t color_index;
//    ColorSensor_ReadAverage(&color_index, 100);
//    CyDelay(10);
//    
//    UART_USB_PutString("Detected color: ");
//    UART_USB_PutString(ColorToString(color_index));
//    UART_USB_PutString("\r\n");
//}

void TestColorSensor() {
    uint16_t rgb[3];
    uint8_t color_index;
    char buffer[64];
    ColorSensor_ReadRGB(rgb);
    ColorSensor_Read(&color_index);
    sprintf(
        buffer,
        "RGB = [%u, %u, %u]    Detected color: %s\r\n",
        rgb[0], rgb[1], rgb[2],
        ColorToString(color_index)
    );
    UART_USB_PutString(buffer);
}