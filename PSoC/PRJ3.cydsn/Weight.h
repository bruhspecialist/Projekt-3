#pragma once

#include "project.h"

#include "UART.h"

#include "stdbool.h"

// Maksimal afvigelse
#define WEIGHT_TOLERANCE 20

// Kalibreringsværdier (Med 100g preload)
#define ADC_M1      903     // @ 0 gram
#define ADC_M2      1536    // @ 400 gram

#define M1_WEIGHT   0
#define M2_WEIGHT   415

enum cupSizes {shot = 1, medium = 2, large = 3};

// Værdier for glas
#define SHOT_WEIGHT 46
#define MEDIUM_WEIGHT 67
#define LARGE_WEIGHT 89

// Værdier for glas, når de er fyldt helt op (100%)
#define SHOT_FULL_WEIGHT 91
#define MEDIUM_FULL_WEIGHT 142
#define LARGE_FULL_WEIGHT 199

int16_t ADC_zeroOffset = 0;

uint16_t CupWeight(enum cupSizes cupSize) {
    switch (cupSize) {
        case (shot) : return SHOT_WEIGHT;
        case (medium) : return MEDIUM_WEIGHT;
        case (large) : return LARGE_WEIGHT;
        default : return 0;
    }
}

uint16_t CupFullWeight(enum cupSizes cupSize) {
    switch (cupSize) {
        case (shot) : return SHOT_FULL_WEIGHT;
        case (medium) : return MEDIUM_FULL_WEIGHT;
        case (large) : return LARGE_FULL_WEIGHT;
        default : return 0;
    }
}

const char* CupSizeToString(enum cupSizes cupSize) {
    switch (cupSize) {
        case (shot) : return "shot";
        case (medium) : return "medium";
        case (large) : return "large";
        default : return "\0";
    }
}

uint8_t StringToCupSize(const char* cupSizeString) {
    if (strcmp(cupSizeString, "shot") == 0)
        return shot;
    else if (strcmp(cupSizeString, "medium") == 0)
        return medium;
    else if (strcmp(cupSizeString, "large") == 0)
        return large;
    else
        return 0;
}

uint16_t ConvertToGram(uint16_t adc_count) {
    int32_t diff = (int32_t)adc_count - ADC_M1; // Relativ forskel
    uint16_t gramRange = M2_WEIGHT - M1_WEIGHT;
    uint16_t adcRange = ADC_M2 - ADC_M1;
    int32_t grams = M1_WEIGHT + ((diff * gramRange) / adcRange); // Konvertering til gram
    if (grams < 0) grams = 0; // Clamp til 0, hvis negativ værdi
    return grams;
}

uint16_t Weight_ADC_Read() {
    if (WEIGHT_ADC_IsEndConversion(WEIGHT_ADC_WAIT_FOR_RESULT)) { // OBS. Kan hænge her
        UART_USB_PutString("ADC_zeroOffset: ");
        UART_USB_PutInt(ADC_zeroOffset);
        UART_USB_PutString("\r\n");
        return WEIGHT_ADC_GetResult16() - ADC_zeroOffset;
    }
    else return 0; // Fejl?
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
    if (
        (weight >= CupWeight(cupSize) - WEIGHT_TOLERANCE)
        && (weight <= CupWeight(cupSize) + WEIGHT_TOLERANCE)
    ) {
        return true;
    }
    else return false;
}

bool Weight_IsCupFull(enum cupSizes cupSize) {
    uint16_t weight = Weight_Read();
    if (
        (weight >= CupFullWeight(cupSize) - WEIGHT_TOLERANCE)
        && (weight <= CupFullWeight(cupSize) + WEIGHT_TOLERANCE)
    ) {
        return true;
    }
    else return false;
}

void Weight_Tare() {
    ADC_zeroOffset = Weight_ADC_Read() - ADC_M1 ;
}

void Weight_Initialize() {
    WEIGHT_ADC_Start();
    WEIGHT_ADC_StartConvert();
    Weight_Tare();
}