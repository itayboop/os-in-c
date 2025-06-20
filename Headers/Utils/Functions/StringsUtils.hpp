#pragma once

#define MAX_DIGITS 62

#include <stdarg.h>
#include <stddef.h>

namespace StringsUtils
{
    constexpr void itoa(int num, char* str)
    {
        int i = 0;
        int is_negative = 0;

        if (0 > num)
        {
            is_negative = 1;
            num = 0 - num;
        }

        do
        {
            str[i++] = num % 10 + '0';
            num /= 10;
        } while (num && MAX_DIGITS > i); // 62 since we add may add '-' and null terminator at the end.


        if (is_negative)
        {
            str[i++] = '-';
        }

        str[i] = '\0';

        for (int j = 0; j < i / 2; j++)
        {
            char temp = str[j];
            str[j] = str[i - j - 1];
            str[i - j - 1] = temp;
        }
    }

    constexpr size_t strlen(const char* str)
    {
        size_t string_length = 0;

        while(str[string_length])
        {
            string_length++;
        }

        return string_length;
    }
};
