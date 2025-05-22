#pragma once

#include <cytypes.h>

#define MAX_MSG_BUFFER_SIZE 128
#define MAX_PARAMS 2

CY_ISR_PROTO(UART_USB_RX_ISR_handler);
CY_ISR_PROTO(UART_PI_RX_ISR_handler);

const char* UART_GetCommand();
const char* UART_GetParameter(uint8_t parameter_index);
void UART_ResetBuffer();
void UART_Initialize();
void UART_USB_PutInt(int num);