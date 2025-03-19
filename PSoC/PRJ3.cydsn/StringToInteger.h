#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t ConvertToInteger(char* string) {
    if (strncmp(string, "0x", 2) == 0 || strncmp(string, "0X", 2) == 0) { // Hex
        return (uint8_t)strtol(string, NULL, 16);
    }
    else if (strncmp(string, "0b", 2) == 0 || strncmp(string, "0B", 2) == 0) { // Binær
        char* string_p = string;
        uint8_t value = 0;
        while (*string_p) { // Inkremenér pointer: næste bit
            value <<= 1;
            if (*string_p++ == '1') value ^= 1;
        }
        return value;
    }
    else { // Decimal
        return atoi(string);
    }
}