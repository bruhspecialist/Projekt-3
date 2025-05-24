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

void TestColorSensorRawRGB() {
    uint16_t rgb[3];
    char buffer[64];
    ColorSensor_ReadRawRGB(rgb);
    sprintf(
        buffer,
        "RGB = [%u, %u, %u]\r\n",
        rgb[0], rgb[1], rgb[2]
    );
    UART_USB_PutString(buffer);
}

void TestColorSensorRGB() {
    uint16_t rgb[3];
    char buffer[64];
    ColorSensor_ReadRGB(rgb);
    sprintf(
        buffer,
        "RGB = [%u, %u, %u]\r\n",
        rgb[0], rgb[1], rgb[2]
    );
    UART_USB_PutString(buffer);
}

void TestColorSensor() {
    uint8_t color_index;
    char buffer[64];
    ColorSensor_Read(&color_index);
    sprintf(
        buffer,
        "Detected color: %s\r\n",
        ColorToString(color_index)
    );
    UART_USB_PutString(buffer);
}