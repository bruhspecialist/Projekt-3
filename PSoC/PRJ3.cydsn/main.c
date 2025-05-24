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
    STATE_REPLACE_DIE,
    STATE_RESET,
    STATE_ERROR
} State;

State currentState = STATE_IDLE;

int8_t setup() {
    int8_t err = 0;
    CyGlobalIntEnable;
    UART_Initialize();
    if (!ColorSensor_Initialize()) err = -1;
    //Weight_Initialize();
    InitializeSimulationConditions(); // Midlertidig
    return err;
}

uint8_t selectedCupSize = 0;
uint8_t detectedColor = 0;
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
                selectedCupSize = StringToCupSize(cmd);
                if (
                    (selectedCupSize >= shot && selectedCupSize <= large)
                    && ValidateCupSize(selectedCupSize)
                ) {
                    UART_USB_PutString("Cup size set to ");
                    UART_USB_PutString(CupSizeToString(selectedCupSize));
                    UART_USB_PutString("\r\n");
                }
                else {
                    UART_PI_PutString("err_badCup\n");
                    PrintError(-3);
                }
            }
            else if (strcmp(cmd, "start") == 0) {
                if (selectedCupSize >= shot && selectedCupSize <= large) currentState = STATE_DROPPING;
                else {
                    UART_PI_PutString("err_noCup\n");
                    PrintError(-4);
                }
            }
            break;
        }
        case STATE_DROPPING: {
            UART_USB_PutString("Dropping die!\n");
            Motor_SetAngle(-115, 100);
            Motor_SetAngle(0, 100);
            currentState = STATE_COLOR_READING;
            break;
        }
        case STATE_COLOR_READING: {
            ColorSensor_Read(&detectedColor);
            char msg[MAX_STR_LENGTH];
            snprintf(msg, MAX_STR_LENGTH, "Detected color: %s\r\n", ColorToString(detectedColor));
            UART_USB_PutString(msg);
            if (detectedColor >= red && detectedColor <= magenta) {
                memset(msg, 0, MAX_STR_LENGTH); // Rydder bufferen i msg
                snprintf(msg, MAX_STR_LENGTH, "result %s", ColorToString(detectedColor));
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
            ActivatePump(detectedColor);
            UART_USB_PutString("Pump activated!\r\n");
            while (!isCupFull(shot)) {}; // Wait
            //CyDelay(1000);
            DeactivatePump(detectedColor);
            UART_USB_PutString("Pump deactivated!\r\n");
            currentState = STATE_REPLACE_DIE;
            break;
        }
        case STATE_REPLACE_DIE: {
            // kode
            break;
        }
        case STATE_RESET: {
            //memset(selectedCupSize, 0, 7);
            //selectedCupSize[0] = '\0';
            selectedCupSize = 0;
            detectedColor = 0;
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

void TestLoop() {
    TestColorSensorRGB();
    TestColorSensor();
    CyDelay(1000);
    
//    EnablePump(1);
//    CyDelay(1000);
//    DisablePump(1);
//    CyDelay(1000);
}

int main() {
    int8_t err = setup();
    if (err == 0) UART_USB_PutString("PSoC has booted and successfully completed setup\r\n");
    else {PrintError(err); return -1;} // Stop hvis setup fejler
    while (1) TestLoop();
}