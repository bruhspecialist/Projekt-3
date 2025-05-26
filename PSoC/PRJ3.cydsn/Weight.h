#pragma once
#include "project.h"
#include "UART.h"
#include <stdbool.h>
#include <string.h>

// Internal reference er godt for første vægt (Omer), external skal bruges ved anden vægt

// Med 3D printet kopholder som preload
#define WEIGHT_TOLERANCE 10
#define ADC_M1      32
#define ADC_M2      256 // Anden vægt: 1802
#define M1_WEIGHT   0
#define M2_WEIGHT   515 // Anden vægt: 750

enum cupSizes { none = 0, shot = 1, medium = 2, large = 3 };

#define SHOT_WEIGHT 39 // Faktisk: 46g
#define MEDIUM_WEIGHT 65 // Faktisk: 67g
#define LARGE_WEIGHT 84 // Faktisk: 89g
#define SHOT_FULL_WEIGHT 87 - 20 // Faktisk: 91g
#define MEDIUM_FULL_WEIGHT 143 - 20 // Faktisk: 142g
#define LARGE_FULL_WEIGHT 194 - 20 // Faktisk: 199g

static const uint16_t cup_weights[]      = { 0, SHOT_WEIGHT, MEDIUM_WEIGHT, LARGE_WEIGHT };
static const uint16_t cup_full_weights[] = { 0, SHOT_FULL_WEIGHT, MEDIUM_FULL_WEIGHT, LARGE_FULL_WEIGHT };
static const char*    cup_names[]        = { "none", "shot", "medium", "large" };

int16_t ADC_zeroOffset = 0;

uint16_t CupWeight(enum cupSizes cupSize) { return cup_weights[cupSize]; }
uint16_t CupFullWeight(enum cupSizes cupSize) { return cup_full_weights[cupSize]; }
const char* CupSizeToString(enum cupSizes cupSize) { return cup_names[cupSize]; }

enum cupSizes StringToCupSize(const char* cupSizeString) {
    for (int i = shot; i <= large; i++) {
        if (strcmp(cup_names[i], cupSizeString) == 0)
            return (enum cupSizes)i;
    }
    return 0;
}

uint16_t ConvertToGram(uint16_t adc_count) {
    if(adc_count <= ADC_M1) return M1_WEIGHT;
    if(adc_count >= ADC_M2) return M2_WEIGHT;
    uint32_t num = (uint32_t)(adc_count - ADC_M1) * (M2_WEIGHT - M1_WEIGHT);
    uint32_t denom = (ADC_M2 - ADC_M1);

    return (int16_t)(num / denom);
}

uint16_t Weight_ADC_Read() {
    if (WEIGHT_ADC_IsEndConversion(WEIGHT_ADC_WAIT_FOR_RESULT)) {
        uint16_t rawADC = WEIGHT_ADC_GetResult16();
        //UART_USB_PutString("ADC: ");
        //UART_USB_PutInt(rawADC);
        //UART_USB_PutString("\r\n");
        return rawADC - ADC_zeroOffset;
    }
    else return 0;
}

uint16_t Weight_Read() {
    uint16_t adcCount = Weight_ADC_Read();
    uint16_t weight = ConvertToGram(adcCount);
    UART_USB_PutString("Weight: ");
    UART_USB_PutInt(weight);
    UART_USB_PutString("g\r\n");
    return weight;
}

bool Weight_ValidateCupSize(enum cupSizes cupSize) {
    if (cupSize != none) {
        uint16_t weight = Weight_Read();
        uint16_t target = CupWeight(cupSize);
        return (weight >= target - WEIGHT_TOLERANCE) && (weight <= target + WEIGHT_TOLERANCE);
    }
    else return false;
}

bool Weight_IsCupFull(enum cupSizes cupSize) {
    if (cupSize != none) {
        uint16_t weight = Weight_Read();
        uint16_t target = CupFullWeight(cupSize);
        return (weight >= target - WEIGHT_TOLERANCE) && (weight <= target + WEIGHT_TOLERANCE);
    }
    else return false;
}

void Weight_Tare() {
    
    uint32_t sum = 0;
    uint16_t reading;
    for (uint16_t i = 0; i < 100; ++i) {
        reading = Weight_ADC_Read();
        sum += reading;
        CyDelay(10); // 10ms delay
    }
    uint16_t avg = (uint16_t)(sum / 100);
    ADC_zeroOffset = avg - ADC_M1;
    UART_USB_PutString("ADC_zeroOffset: ");
    UART_USB_PutInt(ADC_zeroOffset);
    UART_USB_PutString("\r\n");
}

void Weight_Initialize() {
    WEIGHT_ADC_Start();
    WEIGHT_ADC_StartConvert();
    Weight_Tare();
}