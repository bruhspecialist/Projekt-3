#pragma once
#include "project.h"
#include "UART.h"
#include <stdbool.h>
#include <string.h>

#define WEIGHT_TOLERANCE 20
#define ADC_M1      903
#define ADC_M2      1536
#define M1_WEIGHT   0
#define M2_WEIGHT   415

enum cupSizes { shot = 1, medium = 2, large = 3 };

#define SHOT_WEIGHT 46
#define MEDIUM_WEIGHT 67
#define LARGE_WEIGHT 89
#define SHOT_FULL_WEIGHT 91
#define MEDIUM_FULL_WEIGHT 142
#define LARGE_FULL_WEIGHT 199

static const uint16_t cup_weights[]      = { 0, SHOT_WEIGHT, MEDIUM_WEIGHT, LARGE_WEIGHT };
static const uint16_t cup_full_weights[] = { 0, SHOT_FULL_WEIGHT, MEDIUM_FULL_WEIGHT, LARGE_FULL_WEIGHT };
static const char*    cup_names[]        = { "", "shot", "medium", "large" };

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
    int32_t diff = (int32_t)adc_count - ADC_M1;
    int32_t adcRange = ADC_M2 - ADC_M1;
    if (adcRange == 0) return 0;
    int32_t grams = M1_WEIGHT + ((diff * (M2_WEIGHT - M1_WEIGHT)) / adcRange);
    if (grams < 0) grams = 0;
    return grams;
}

uint16_t Weight_ADC_Read() {
    if (WEIGHT_ADC_IsEndConversion(WEIGHT_ADC_WAIT_FOR_RESULT))
        return WEIGHT_ADC_GetResult16() - ADC_zeroOffset;
    else
        return 0;
}

uint16_t Weight_Read() {
    uint16_t adcCount = Weight_ADC_Read();
    uint16_t weight = ConvertToGram(adcCount);
    UART_USB_PutString("Weight: ");
    UART_USB_PutInt(weight);
    UART_USB_PutString("\r\n");
    return weight;
}

bool Weight_ValidateCupSize(enum cupSizes cupSize) {
    uint16_t weight = Weight_Read();
    uint16_t target = CupWeight(cupSize);
    return (weight >= target - WEIGHT_TOLERANCE) && (weight <= target + WEIGHT_TOLERANCE);
}

bool Weight_IsCupFull(enum cupSizes cupSize) {
    uint16_t weight = Weight_Read();
    uint16_t target = CupFullWeight(cupSize);
    return (weight >= target - WEIGHT_TOLERANCE) && (weight <= target + WEIGHT_TOLERANCE);
}

void Weight_Tare() { ADC_zeroOffset = Weight_ADC_Read() - ADC_M1; }

void Weight_Initialize() {
    WEIGHT_ADC_Start();
    WEIGHT_ADC_StartConvert();
    Weight_Tare();
}