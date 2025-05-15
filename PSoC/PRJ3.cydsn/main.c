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
#include <stdio.h>
#include "stdbool.h"

#define MAX_STR_SIZE 10

#define COLOR_MEASUREMENTS 100  // Antal målinger
#define COLOR_SENSING_TIME 1000 // ms

typedef enum {
    STATE_IDLE,
    STATE_DROPPING,
    STATE_SENSING,
    STATE_ERROR
} State;

State currentState = STATE_IDLE;

int8_t setup() {
    int8_t err = 0;
    CyGlobalIntEnable;
    UART_Initialize();
    //if (!ColorSensor_Initialize()) err = -1;
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
            else if (strcmp(cmd, "test1") == 0) currentState = STATE_DROPPING;
            break;
        }
        case STATE_DROPPING: {
            UART_USB_PutString("Dropping die!\n");
            SetAngle(180, 100);
            SetAngle(0, 100);
            CyDelay(1000); // Tiden det tager terningen at nå til bunds
            currentState = STATE_SENSING;
            break;
        }
        case STATE_SENSING:{
            uint16_t colorFrequency[COLOR_MEASUREMENTS] = {0};
            for (uint8_t i = 0; i < COLOR_MEASUREMENTS; ++i) {
                uint8_t color_index;
                //if (!ColorSensor_Read(&color_index)) PrintError(-2);
                if (!SimulateColorSensor(&color_index)) PrintError(-2);
                else colorFrequency[i]++;
                CyDelay(COLOR_SENSING_TIME/COLOR_MEASUREMENTS);
            }
            
            uint8_t mostFrequentColor = MostFrequent(colorFrequency);
            
            UART_USB_PutString("Detected color: \r\n");
            UART_USB_PutString(ColorToString(mostFrequentColor));
            UART_USB_PutString("\r\n");
            break;
        }
        case STATE_ERROR: {
            UART_USB_PutString("In ERROR state\n");
            break;
        }
        default: {
            currentState = STATE_IDLE;
            break;
        }
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