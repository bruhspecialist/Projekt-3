#pragma once

#include <stdint.h>
#include <stddef.h>

uint8_t MostFrequent(const uint16_t *frequency) {
    uint8_t most_frequent = 0;
    uint16_t max_count = 0;

    for (int i = 0; i < 256; i++) {
        if (frequency[i] > max_count) {
            max_count = frequency[i];
            most_frequent = (uint8_t)i;
        }
    }

    return most_frequent;
}