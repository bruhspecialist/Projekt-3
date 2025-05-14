#include "project.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ColorSensor.h"
#include "Motor.h"
#include "Pump.h"

CY_ISR_PROTO(UART_USB_RX_ISR_handler);
CY_ISR_PROTO(UART_PI_RX_ISR_handler);
void HandleStringReceived(char* stringReceived);

#define MAX_MSG_BUFFER_SIZE 128 // Maksimal størrelse af besked der kan printes (bytes)
#define MAX_PARAMS 2 // Maksimalt antal af parametre til en funktion (2 er fint i vores tilfælde)

int main(void)
{
    CyGlobalIntEnable;
    UART_USB_RX_ISR_StartEx(UART_USB_RX_ISR_handler);
    UART_PI_RX_ISR_StartEx(UART_PI_RX_ISR_handler);
    UART_USB_Start();
    UART_PI_Start();
    
    TCS37073M_Initialize();

    for(;;)
    {
        // Farvesensor test
//        const char* color = TCS37073M_Read();
//        UART_USB_PutString(color);
//        UART_USB_PutString("\r\n");
        
        // Pumpt test
            //for (int i = 1; i <= 6; ++i) Pump(i);
    }
}

/* UART Interrupt, sker ved modtagelse af seriel data fra USB */
CY_ISR(UART_USB_RX_ISR_handler)
{
    static char UART_USB_rx_buf[MAX_MSG_BUFFER_SIZE] = {0};
    static uint8_t buf_index = 0;

    while (UART_USB_GetRxBufferSize() > 0) {
        uint8_t byteReceived = UART_USB_ReadRxData();
        
        // Ignorér ekstra 'linebreaks' som kan føre til ekstra kald
        if (byteReceived == '\n' && buf_index == 0) continue;

        // Gem karakter i buffer, hvis den ikke er fyldt
        if (buf_index < MAX_MSG_BUFFER_SIZE - 1) {
            UART_USB_rx_buf[buf_index++] = byteReceived;
        }

        // Check for slutning af besked
        if (byteReceived == '\n' || byteReceived == '\r') {
            UART_USB_rx_buf[buf_index] = '\0'; // Null-terminering
            HandleStringReceived(UART_USB_rx_buf);
            buf_index = 0;
            break;
        }
    }
}

/* UART Interrupt, sker ved modtagelse af seriel data fra Raspberry Pi */
CY_ISR(UART_PI_RX_ISR_handler)
{
    static char UART_PI_rx_buf[MAX_MSG_BUFFER_SIZE] = {0};
    static uint8_t buf_index = 0;

    while (UART_PI_GetRxBufferSize() > 0) {
        uint8_t byteReceived = UART_PI_ReadRxData();
        
        // Ignorér ekstra 'linebreaks' som kan føre til ekstra kald
        if (byteReceived == '\n' && buf_index == 0) continue;

        // Gem karakter i buffer, hvis den ikke er fyldt
        if (buf_index < MAX_MSG_BUFFER_SIZE - 1) {
            UART_PI_rx_buf[buf_index++] = byteReceived;
        }

        // Check for slutning af besked
        if (byteReceived == '\n' || byteReceived == '\r') {
            UART_PI_rx_buf[buf_index] = '\0'; // Null-terminering
            HandleStringReceived(UART_PI_rx_buf);
            buf_index = 0;
            break;
        }
    }
}

/* Håndtering af data fra UART */
void HandleStringReceived(char* receivedString)
{
    char msg[MAX_MSG_BUFFER_SIZE];
    
    int i = 0;
    char* token = strtok(receivedString, "\r\n ");
    char* params[MAX_PARAMS]; // Er pt. ubrugt: Årsag til warning
    
    char* command = token;
    token = strtok(NULL, "\r\n ");
    while (token != NULL)
    {
        params[i++] = token;
        token = strtok(NULL, "\r\n ");
    }
    
    snprintf(msg, MAX_MSG_BUFFER_SIZE, "Received command: %s\r\n", command);
    
    if (command == NULL) return;

    if (strcmp(command, "test1") == 0) {
        UART_USB_PutString("Running function test1\r\n");
        LED_BUILTIN_Write(1);
    }
    else if (strcmp(command, "test2") == 0) {
        UART_USB_PutString("Running function test2\r\n");
        LED_BUILTIN_Write(0);
    }
    
    UART_USB_PutString(msg);
}