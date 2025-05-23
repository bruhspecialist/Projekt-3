#include "project.h"
#include <stdio.h>

uint16_t ConvertToGram(uint16_t adc_count);

// Kalibreringsværdier (Med 100g preload)
#define ADC_M1      292
#define ADC_M2      500
#define ADC_M3      663
#define ADC_M4      842
#define ADC_M5      1037

#define M1_WEIGHT   0
#define M2_WEIGHT   116
#define M3_WEIGHT   203
#define M4_WEIGHT   300
#define M5_WEIGHT   400

int main(void)
{
    char uartBuffer[256];

    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();

    UART_1_PutString("Scale application started\r\n");

    for(;;)
    {
        if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT))
        {
            uint16_t result = ADC_SAR_1_GetResult16();
            snprintf(uartBuffer, sizeof(uartBuffer), "ADC Count: %d\r\nWeight: %dg\r\n\r\n", result, ConvertToGram(result));
            UART_1_PutString(uartBuffer);
        }
        CyDelay(100);
    }
}

uint16_t ConvertToGram(uint16_t adc_count) {
    typedef struct {
        uint16_t adc;
        uint16_t gram;
    } CalibrationPoint;

    CalibrationPoint points[] = {
        {ADC_M1, M1_WEIGHT},
        {ADC_M2, M2_WEIGHT},
        {ADC_M3, M3_WEIGHT},
        {ADC_M4, M4_WEIGHT},
        {ADC_M5, M5_WEIGHT}
    };

    int num_points = sizeof(points) / sizeof(points[0]);

    if (adc_count <= points[0].adc)
        return points[0].gram;
    if (adc_count >= points[num_points - 1].adc)
        return points[num_points - 1].gram;

    for (int i = 0; i < num_points - 1; i++) {
        if (adc_count >= points[i].adc && adc_count <= points[i + 1].adc) {
            int32_t adc_diff = points[i + 1].adc - points[i].adc;
            int32_t gram_diff = points[i + 1].gram - points[i].gram;
            int32_t adc_offset = adc_count - points[i].adc;

            return points[i].gram + ((adc_offset * gram_diff) / adc_diff);
        }
    }

    return 0; // fallback – burde aldrig ske
}
