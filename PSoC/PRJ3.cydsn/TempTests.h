#pragma once

#include "project.h"

#include "ColorSensor.h"
#include "ErrorMessage.h"

void TestColorSensor() {
    const char* color;
    if (!TCS37073M_Read(&color)) PrintError(-2);
    else {
        UART_USB_PutString("Detected color: \r\n");
        UART_USB_PutString(color);
        UART_USB_PutString("\r\n");
    }
}