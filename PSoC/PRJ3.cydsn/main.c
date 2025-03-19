#include "project.h"

/* Indbyggede headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Egne headers */
#include "ColorSensor.h"
#include "Motor.h"
#include "StringToInteger.h"

/* Definitioner */
#define MAX_MSG_BUFFER_SIZE 128 // Maksimal størrelse af besked der kan printes (bytes)
#define MAX_PARAMS 2            // Maksimalt antal af parametre til en funktion (2 er fint i vores tilfælde)
#define MAX_REGISTER_READ 12    // Maksimalt tilladt at læse 12 bytes på én gang

/* Prototyper */
CY_ISR_PROTO(ISR_UART_rx_handler);
void HandleStringReceived(char* stringReceived);

/* Variabler */
bool motorRotating = false; // Midlertidig til test



int main(void)
{
    CyGlobalIntEnable;
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_Start();
    I2C_Start();
    
    Motor_SetDriveState(motorRotating); // Sikrer at motor er stoppet i starten
    Motor_SetDriveSpeed(100); // 100%
    
    UART_PutString("Program has started!\r\n");
    
    for(;;) {
        Motor_UpdateState();
    }
}

/* UART Interrupt, sker ved modtagelse af seriel data */
CY_ISR(ISR_UART_rx_handler)
{
    static char UART_rx_buf[MAX_MSG_BUFFER_SIZE] = {0};
    static uint8_t buf_index = 0;

    while (UART_GetRxBufferSize() > 0) {
        uint8_t byteReceived = UART_ReadRxData();
        
        // Ignorér ekstra 'lineb breaks' som kan føre til ekstra kald
        if (byteReceived == '\n' && buf_index == 0)
            continue;

        // Gem karakter i buffer, hvis den ikke er fyldt
        if (buf_index < MAX_MSG_BUFFER_SIZE - 1)
            UART_rx_buf[buf_index++] = byteReceived;

        // Check for slutning af besked
        if (byteReceived == '\n' || byteReceived == '\r') {
            UART_rx_buf[buf_index] = '\0'; // Null-terminering
            HandleStringReceived(UART_rx_buf);
            buf_index = 0;
            break;
        }
    }
}

/* Håndtering af data fra UART */
void HandleStringReceived(char* receivedString) {
    char msg[MAX_MSG_BUFFER_SIZE];
    
    int i = 0;
    char* token = strtok(receivedString, "\r\n ");
    char* params[MAX_PARAMS];
    
    char* command = token;
    token = strtok(NULL, "\r\n ");
    while (token != NULL) {
        params[i++] = token;
        token = strtok(NULL, "\r\n ");
    }
    
    if (command == NULL)
        return;
    else if (strcmp(command, "read_color") == 0) { // Midlertidigt til testing
        if (i != 0) {
            UART_PutString("No arguments should be passed!\r\n");
            return;
        }
        
        uint16_t colorData[3];
        ColorSensor_ReadColorData(colorData);
        
        snprintf(
            msg, MAX_MSG_BUFFER_SIZE,
            "ColorData:\n   R: %d\n   G: %d\n   B: %d\n",
            colorData[0], colorData[1], colorData[2]
        );
        UART_PutString(msg);
    }
    else if (strcmp(command, "toggle_motor") == 0) {
        motorRotating = !motorRotating;
        Motor_SetDriveState(motorRotating);
        UART_PutString("Motor state has been toggled!\r\n");
    }
}