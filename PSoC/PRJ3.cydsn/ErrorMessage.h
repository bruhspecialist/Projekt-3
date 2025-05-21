#pragma once

#include "project.h"

#include "stdbool.h"
#include <stdint.h>

const char* ErrorMessage(int8_t err_index) {
    switch (err_index) {
        case (-1) : return "Failed to initialize Color Sensor";
        case (-2) : return "Failed to read Color Sensor";
        case (-3) : return "Failed to validate weight (cup size)";
        case (-4) : return "No cup size selected";
        case (-5) : return "Not enough contrast to determine color";
    }
    return "Unknown error";
}

void PrintError(int8_t err_index) {
    UART_USB_PutString("Error: ");
    UART_USB_PutString(ErrorMessage(err_index));
    UART_USB_PutString("\r\n");
}