#pragma once

#include <stdint.h>
#include <stddef.h>

uint8_t GetMaxIndex(const uint8_t* frequency, uint8_t size) {
    uint8_t maxIndex = 0;
    for (uint8_t i = 1; i < size; ++i) {
        if (frequency[i] > frequency[maxIndex]) maxIndex = i;
    }
    return maxIndex;
}