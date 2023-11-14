#include "main.h"

/**
 * NB_getSize - Determines the size to cast the argument
 * @NB_format: Formatted string containing the arguments
 * @NB_i: Index of the current character in the format string
 *
 * Return: Size to cast the argument.
 */
int NB_getSize(const char *NB_format, int *NB_i)
{
	int NB_currIndex = *NB_i + 1;
	int NB_size = 0;

	if (NB_format[NB_currIndex] == 'l')
		NB_size = NB_S_LONG;
	else if (NB_format[NB_currIndex] == 'h')
		NB_size = NB_S_SHORT;

	if (NB_size == 0)
		*NB_i = NB_currIndex - 1;
	else
		*NB_i = NB_currIndex;

	return (NB_size);
}
