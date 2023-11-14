#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curi;
	int width = 0;

	for (curi = *i + 1; format[curi] != '\0'; curi++)
	{
		if (is_digit(format[curi]))
		{
			width *= 10;
			width += format[curi] - '0';
		}
		else if (format[curi] == '*')
		{
			curi++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curi - 1;

	return (width);
}
