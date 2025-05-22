#include "project.h"

#include "ColorSensor.h"
#include "Motor.h"
#include "Pump.h"
#include "Weight.h"
#include "UART.h"
#include "ErrorMessage.h"
#include "MockupTests.h"
#include "SimulationTests.h"
#include "CustomMath.h"

#include "time.h"
#include "stdio.h"
#include "stdbool.h"

#define MAX_STR_LENGTH 32

typedef enum {
    STATE_IDLE,
    STATE_DROPPING,
    STATE_COLOR_READING,
    STATE_PUMPING,
    STATE_RESET,
    STATE_ERROR
} State;

State currentState = STATE_IDLE;

int8_t setup() {
    int8_t err = 0;
    CyGlobalIntEnable;
    UART_Initialize();
    if (!ColorSensor_Initialize()) err = -1;
    InitializeSimulationConditions(); // Midlertidig
    return err;
}

char selectedCupSize[7] = "\0";
void UpdateState() {
    const char* cmd = UART_GetCommand();
    const char* param1 = UART_GetParameter(1);
    const char* param2 = UART_GetParameter(2);
    if (cmd != NULL) UART_ResetBuffer();
    (void)param1; // Fjerner warning at de potentielt er ubrugt
    (void)param2;

    switch (currentState) {
        case STATE_IDLE: {
            if (
                strcmp(cmd, "shot") == 0 ||
                strcmp(cmd, "medium") == 0 ||
                strcmp(cmd, "large") == 0
            ) {
                if (ValidateCupSize()) {
                    UART_PI_PutString("ok");
                    strncpy(selectedCupSize, cmd, 7); // 7 pga. medium er længst + nul-terminering
                    selectedCupSize[sizeof(selectedCupSize) - 1] = '\0';
                    UART_USB_PutString("Cup size set to ");
                    UART_USB_PutString(selectedCupSize);
                    UART_USB_PutString("\r\n");
                }
                else {
                    UART_PI_PutString("err");
                    PrintError(-3);
                    currentState = STATE_ERROR;
                }
                
            }
            else if (strcmp(cmd, "test1") == 0) {
                if (strcmp(selectedCupSize, "\0") != 0) currentState = STATE_DROPPING;
                else PrintError(-4);
            }
            break;
        }
        case STATE_DROPPING: {
            UART_USB_PutString("Dropping die!\n");
            SetAngle(-115, 100);
            SetAngle(0, 100);
            CyDelay(1000); // Tiden det tager terningen at nå til bunds
            currentState = STATE_COLOR_READING;
            break;
        }
        case STATE_COLOR_READING: {
            uint8_t color;
            ColorSensor_ReadAverage(&color, 200);
            char msg[MAX_STR_LENGTH];
            snprintf(msg, MAX_STR_LENGTH, "Detected color: %s\r\n", ColorToString(color));
            UART_USB_PutString(msg);
            if (color != tone) {
                memset(msg, 0, MAX_STR_LENGTH); // Rydder bufferen i msg
                snprintf(msg, MAX_STR_LENGTH, "result %s", ColorToString(color));
                UART_PI_PutString(msg);
                currentState = STATE_PUMPING;
            }
            else {
                PrintError(-5);
                currentState = STATE_ERROR;
            }
            break;
        }
        case STATE_PUMPING: {
            /*  Pseudo-kode:
                * Tænd pumpe én gang
                * Vent indtil vægt er nået 80% af kendt grænse
                * Sluk pumpe
                                                                */
            break;
        }
        case STATE_RESET: {
            memset(selectedCupSize, 0, 7);
            selectedCupSize[0] = '\0';
            currentState = STATE_IDLE;
            break;
        }
        case STATE_ERROR: {
            UART_USB_PutString("In ERROR state\r\n");
            currentState = STATE_RESET;
            break;
        }
        default: {
            currentState = STATE_ERROR; // Bør aldrig ske
            break;
        }
    }
}

//void TestLoop() {
//    TestSimpleColorSensor();
//    CyDelay(1000);
//}

int main() {
    int8_t err = setup();
    if (err == 0) UART_USB_PutString("PSoC has booted and successfully completed setup\r\n");
    else {PrintError(err); return -1;} // Stop hvis setup fejler
    while (1) UpdateState();
}