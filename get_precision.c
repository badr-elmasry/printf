#include "main.h"

/**
 * calculate_precision - Calculate precision for printing
 * @format: Formatted string to analyze for precision
 * @index: Pointer to the current index in the format string
 * @list: List of arguments
 *
 * Return: Calculated precision
 */
int calculate_precision(const char *format, int *index, va_list list)
{
	int current_index = *index + 1;
	int precision = -1;

	if (format[current_index] != '.')
		return (precision);

	precision = 0;

	for (current_index += 1; format[current_index] != '\0'; current_index++)
	{
		if (is_digit(format[current_index]))
		{
			precision *= 10;
			precision += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_index++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*index = current_index - 1;

	return (precision);
}
