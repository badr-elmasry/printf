#include "main.h"

/**
 * NB_getWidth - Determines the width for printing
 * @NB_format: Formatted string containing the arguments
 * @NB_i: Index of the current character in the format string
 * @NB_list: List of arguments to be printed
 *
 * Return: Width for printing.
 */
int NB_getWidth(const char *NB_format, int *NB_i, va_list NB_list)
{
	int NB_currIndex;
	int NB_width = 0;

	for (NB_currIndex = *NB_i + 1; NB_format[NB_currIndex] != '\0'; NB_currIndex++)
	{
		if (NB_isDigit(NB_format[NB_currIndex]))
		{
			NB_width *= 10;
			NB_width += NB_format[NB_currIndex] - '0';
		}
		else if (NB_format[NB_currIndex] == '*')
		{
			NB_currIndex++;
			NB_width = va_arg(NB_list, int);
			break;
		}
		else
			break;
	}

	*NB_i = NB_currIndex - 1;

	return (NB_width);
}
