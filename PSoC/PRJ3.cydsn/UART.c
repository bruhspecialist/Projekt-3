#include "project.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>

// Kommandotype
typedef void (*CommandFunc)(char*[]);

typedef struct {
    const char* name;
    CommandFunc func;
} CommandEntry;

// --- Kommando-implementeringer ---
void Cmd_Test1(char* params[]) {
    LED_BUILTIN_Write(1);
    UART_USB_PutString("LED: ON\r\n");
}

void Cmd_Test2(char* params[]) {
    LED_BUILTIN_Write(0);
    UART_USB_PutString("LED: OFF\r\n");
}

// --- Kommandotabel ---
static const CommandEntry commandTable[] = {
    {"test1", Cmd_Test1},
    {"test2", Cmd_Test2},
    {NULL, NULL} // Terminator
};

void HandleStringReceived(char* receivedString)
{
    char msg[MAX_MSG_BUFFER_SIZE];
    char* params[MAX_PARAMS] = {0};
    int i = 0;

    char* token = strtok(receivedString, "\r\n ");
    if (!token) return;

    char* command = token;
    token = strtok(NULL, "\r\n ");
    while (token && i < MAX_PARAMS) {
        params[i++] = token;
        token = strtok(NULL, "\r\n ");
    }

    snprintf(msg, MAX_MSG_BUFFER_SIZE, "Received command: %s\r\n", command);
    UART_USB_PutString(msg);

    for (int j = 0; commandTable[j].name != NULL; ++j) {
        if (strcmp(command, commandTable[j].name) == 0) {
            commandTable[j].func(params);
            return;
        }
    }

    UART_USB_PutString("Unknown command\r\n");
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