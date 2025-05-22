#include "project.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>

char* latestCmd = NULL;
char* latestParams[MAX_PARAMS] = {0};

const char* UART_GetCommand() {
    return latestCmd;
}
const char* UART_GetParameter(uint8_t parameter) {
    return latestParams[parameter - 1];
}

void UART_ResetBuffer() {
    latestCmd = NULL;
    memset(latestParams, 0, sizeof(latestParams));
}

void HandleStringReceived(char* receivedString)
{
    UART_ResetBuffer(); // Nulstil først
    
    const char* delimiters = "\r\n ";

    char* token = strtok(receivedString, delimiters);
    if (token == NULL) return;

    latestCmd = token;
    
    uint8_t i = 0;
    while ((token = strtok(NULL, delimiters)) && i < MAX_PARAMS) latestParams[i++] = token;
    
//    char msg[MAX_MSG_BUFFER_SIZE];
//    snprintf(msg, MAX_MSG_BUFFER_SIZE, "Received command: %s\r\n", latestCmd ? latestCmd : "(null)");
//    UART_USB_PutString(msg);
//    for (uint8_t j = 0; j < MAX_PARAMS; ++j) {
//        if (latestParams[j]) {
//            snprintf(msg, MAX_MSG_BUFFER_SIZE, "Received parameter: %s\r\n", latestParams[j]);
//            UART_USB_PutString(msg);
//        }
//    }
}


static void UART_HandleRxByte(uint8_t byteReceived, char* buffer, uint8_t* index)
{
    if (byteReceived == '\n' && *index == 0) return;

    if (*index < MAX_MSG_BUFFER_SIZE - 1) {
        buffer[(*index)++] = byteReceived;
    }

    if (byteReceived == '\n' || byteReceived == '\r') {
        buffer[*index] = '\0';
        HandleStringReceived(buffer);
        *index = 0;
    }
}

CY_ISR(UART_USB_RX_ISR_handler)
{
    static char buf[MAX_MSG_BUFFER_SIZE] = {0};
    static uint8_t idx = 0;

    while (UART_USB_GetRxBufferSize() > 0) {
        UART_HandleRxByte(UART_USB_ReadRxData(), buf, &idx);
    }
}

CY_ISR(UART_PI_RX_ISR_handler)
{
    static char buf[MAX_MSG_BUFFER_SIZE] = {0};
    static uint8_t idx = 0;

    while (UART_PI_GetRxBufferSize() > 0) {
        UART_HandleRxByte(UART_PI_ReadRxData(), buf, &idx);
    }
}

void UART_Initialize() {
    UART_USB_RX_ISR_StartEx(UART_USB_RX_ISR_handler);
    UART_PI_RX_ISR_StartEx(UART_PI_RX_ISR_handler);
    UART_USB_Start();
    UART_PI_Start();
}

void UART_USB_PutInt(int num) {
    char msg[12]; // -2147483648\0
    int i = 11;
    unsigned int n;

    msg[i--] = '\0';

    if (num < 0) {
        n = -num;
    } else {
        n = num;
    }

    do {
        msg[i--] = '0' + (n % 10);
        n /= 10;
    } while (n > 0);

    if (num < 0)
        msg[i--] = '-';

    UART_USB_PutString(&msg[i + 1]);
}