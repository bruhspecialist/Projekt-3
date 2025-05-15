#include "project.h"

#include "ColorSensor.h"
#include "Motor.h"
#include "Pump.h"
#include "UART.h"
#include "ErrorMessage.h"
#include "TempTests.h"

#include "stdbool.h"

int8_t setup() {
    int8_t err = 0;
    CyGlobalIntEnable;
    UART_Initialize();
    if (!TCS37073M_Initialize()) err = -1;
    return err;
}

void loop() {
    TestColorSensor();
    CyDelay(100);
}

int main() {
    int8_t err = setup();
    if (err != 0) {PrintError(err); return -1;} // Stop hvis setup fejler
    while (1) loop();
}