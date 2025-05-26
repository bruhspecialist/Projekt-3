#include "project.h"

#include "ColorSensor.h"
#include "Motor.h"
#include "Pump.h"
#include "Weight.h"
#include "UART.h"
#include "ErrorMessage.h"

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
uint8_t selectedCupSize = 0;
uint8_t detectedColor = 0;

int8_t setup() {
    int8_t err = 0;
    CyGlobalIntEnable;
    UART_Initialize();
    if (!ColorSensor_Initialize()) err = -1;
    Weight_Initialize(); // Vægten nulstilles ved opstart, så ingen vægt på der!
    return err;
}

void UpdateState() {
    const char* cmd = UART_GetCommand();
    if (cmd != NULL) UART_ResetBuffer();

    switch (currentState) {
        case STATE_IDLE: {
            if (
                strcmp(cmd, "shot") == 0 ||
                strcmp(cmd, "medium") == 0 ||
                strcmp(cmd, "large") == 0
            ) {
                uint8_t cupSize = StringToCupSize(cmd);
                if (
                    (cupSize >= shot && cupSize <= large)
                    && Weight_ValidateCupSize(cupSize)
                ) {
                    selectedCupSize = cupSize;
                    UART_USB_PutString("Cup size set to ");
                    UART_USB_PutString(cmd);
                    UART_USB_PutString("\r\n");
                }
                else {
                    UART_PI_PutString("err_badCup\n");
                    UART_USB_PutString("err_badCup sent to PI\n");
                    PrintError(-3);
                }
            }
            else if (strcmp(cmd, "start") == 0) {
                if (selectedCupSize >= shot && selectedCupSize <= large)
                    currentState = STATE_DROPPING;
                    //currentState = STATE_PUMPING;
                else {
                    UART_PI_PutString("err_noCup\n");
                    UART_USB_PutString("err_noCup sent to PI\n");
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
            //detectedColor = green; // MIDLERTIDIGT
            if (detectedColor >= red && detectedColor <= magenta) {
                memset(msg, 0, MAX_STR_LENGTH); // Rydder bufferen i msg
                snprintf(msg, MAX_STR_LENGTH, "result %s", ColorToString(detectedColor));
                //UART_PI_PutString(msg);
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
            while (!Weight_IsCupFull(selectedCupSize)) {}; // Vent til koppen er fyldt
            DeactivatePump(detectedColor);
            UART_USB_PutString("Pump deactivated!\r\n");
            currentState = STATE_RESET;
            break;
        }
        case STATE_RESET: {
            selectedCupSize = 0;
            detectedColor = 0;
            currentState = STATE_IDLE;
            break;
        }
        case STATE_ERROR: {
            UART_USB_PutString("Fatal error has occured, restarting system!\r\n");
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
    uint16_t rgb[3];
    char buffer[64];
    ColorSensor_ReadRawRGB(rgb);
    sprintf(
        buffer,
        "RGB = [%u, %u, %u]\r\n",
        rgb[0], rgb[1], rgb[2]
    );
    UART_USB_PutString(buffer);
    
    uint8_t color;
    ColorSensor_Read(&color);
    sprintf(
        buffer,
        "Color = %s\r\n",
        ColorToString(color)
    );
    UART_USB_PutString(buffer);
    
    
    
    //Weight_Read();
    
    CyDelay(100);
}

int main() {
    int8_t err = setup();
    if (err == 0) UART_USB_PutString("PSoC has booted and successfully completed setup\r\n");
    else {PrintError(err); return -1;} // Stop hvis setup fejler
    while (1) UpdateState();
}