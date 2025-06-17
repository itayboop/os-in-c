#include <stdarg.h>

#include "VgaBuffer.hpp"
#include "Utils/Functions/PrintUtils.hpp"

void PrintUtils::printk(const char *formatted_str, ...)
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
