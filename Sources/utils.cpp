#define MAX_DIGITS 62

#include <stdarg.h>
#include "stddef.h"

#include "vga_buffer.hpp"

void printk(const char* formatted_str, ...)
{
	va_list arg;
	char formatted_str_char = 0;

	va_start(arg, formatted_str);

	while ((formatted_str_char = *formatted_str++))
	{
		if(formatted_str_char != '%')
		{
			terminal_putchar(formatted_str_char);
		} else
		{
			formatted_str_char = *formatted_str++;

			switch (formatted_str_char)
			{
				case 'd':
				{
					int number_to_print = va_arg(arg, int);
					terminal_print_int(number_to_print);
				}
					break;
				case 's':
				{
					char* string_to_print = va_arg(arg, char *);
					terminal_print_string(string_to_print);
				}
					break;
				case 'c':
				{
					char char_to_print = va_arg(arg, int); // 'char' is promoted to 'int' when passed through '...'
					terminal_putchar(char_to_print);
				}
					break;
				case 'x':
				{
					int hex_to_print = va_arg(arg, int);
					terminal_print_hex(hex_to_print);
				}
					break;
				default:
					break;
			}
		}
	}

	va_end(arg);
}

void itoa(int num, char* str)
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

size_t strlen(const char* str)
{
	size_t string_length = 0;

	while(str[string_length])
	{
		string_length++;
	}

	return string_length;
}

/* 
	TODO: maybe convert to template like:
	```
	template<typename T>
	T* memset(T* ptr, char c, size_t size)
	{
		unsigned char byte_value = (unsigned char)c;

		for(unsigned int i = 0; i < size; i++)
		{
			ptr[i] = byte_value;
		}

		return ptr;
	}
	```
*/
void* memset(void* ptr, char c, size_t size)
{
	unsigned char* byte_ptr = (unsigned char *)ptr;
	unsigned char byte_value = (unsigned char)c;

	for(unsigned int i = 0; i < size; i++)
	{
		byte_ptr[i] = byte_value;
	}

	return ptr;
}
