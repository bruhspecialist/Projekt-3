#pragma once

#include <cytypes.h>

#define MAX_MSG_BUFFER_SIZE 128
#define MAX_PARAMS 2

CY_ISR_PROTO(UART_USB_RX_ISR_handler);
CY_ISR_PROTO(UART_PI_RX_ISR_handler);

void HandleStringReceived(char* stringReceived);
void UART_Initialize();