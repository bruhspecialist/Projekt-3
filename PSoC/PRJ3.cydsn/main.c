#include "project.h"

#include "ColorSensor.h"
#include "Motor.h"
#include "Pump.h"
#include "Weight.h"
#include "UART.h"
#include "ErrorMessage.h"
#include "TempTests.h"

#include "stdbool.h"

#define MAX_STR_SIZE 10

typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} State;

State currentState = STATE_IDLE;

int8_t setup() {
    int8_t err = 0;
    CyGlobalIntEnable;
    UART_Initialize();
    //if (!TCS37073M_Initialize()) err = -1;
    return err;
}

char cupSize[MAX_STR_SIZE] = "\0";

void UpdateState() {
    const char* cmd = GetCmd();
    if (cmd == NULL) return;

    switch (currentState) {
        case STATE_IDLE: {
            if (
                strcmp(cmd, "shot") == 0 ||
                strcmp(cmd, "medium") == 0 ||
                strcmp(cmd, "large") == 0
            ) {
                if (ValidateCupSize()) {
                    UART_PI_PutString("ok");
                    UART_USB_PutString("'ok' sent to pi\r\n");
                    strncpy(cupSize, cmd, MAX_STR_SIZE);
                    cupSize[sizeof(cupSize) - 1] = '\0';
                    UART_USB_PutString("Cup size set to ");
                    UART_USB_PutString(cupSize);
                    UART_USB_PutString("\r\n");
                }
                else {
                    UART_PI_PutString("err");
                    UART_USB_PutString("'err' sent to pi\r\n");
                }
                ResetCmd();
            }
            else if (strcmp(cmd, "test1") == 0) currentState = STATE_RUNNING;
            break;
        }
        case STATE_RUNNING:
            UART_USB_PutString("In RUNNING state\n");
            break;
        case STATE_ERROR:
            UART_USB_PutString("In ERROR state\n");
            break;
        default:
            currentState = STATE_IDLE;
            break;
    }
}


//void loop() {
//    TestColorSensor();
//    CyDelay(100);
//}

int main() {
    int8_t err = setup();
    if (err == 0) UART_USB_PutString("PSoC has booted and successfully completed setup\r\n");
    else {PrintError(err); return -1;
    } // Stop hvis setup fejler
    while (1) {UpdateState(); CyDelay(100);}
}