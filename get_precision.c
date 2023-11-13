#include "main.h"

/**
 * NB_getPrecision - Determines the precision for printing
 * @NB_format: Formatted string containing the arguments
 * @NB_i: Index of the current character in the format string
 * @NB_list: List of arguments to be printed
 *
 * Return: Precision for printing.
 */
int NB_getPrecision(const char *NB_format, int *NB_i, va_list NB_list)
{
	int NB_currIndex = *NB_i + 1;
	int NB_precision = -1;

	if (NB_format[NB_currIndex] != '.')
		return (NB_precision);

	NB_precision = 0;

	for (NB_currIndex += 1; NB_format[NB_currIndex] != '\0'; NB_currIndex++)
	{
		if (NB_isDigit(NB_format[NB_currIndex]))
		{
			NB_precision *= 10;
			NB_precision += NB_format[NB_currIndex] - '0';
		}
		else if (NB_format[NB_currIndex] == '*')
		{
			NB_currIndex++;
			NB_precision = va_arg(NB_list, int);
			break;
		}
		else
			break;
	}

	*NB_i = NB_currIndex - 1;

	return (NB_precision);
}
