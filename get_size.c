#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int curi = *i + 1;
	int size = 0;

	if (format[curi] == 'l')
		size = S_LONG;
	else if (format[curi] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curi - 1;
	else
		*i = curi;

	return (size);
}
