#include "main.h"

/**
 * determine_size - Determine the size for casting the argument
 * @format: Formatted string for analyzing argument size
 * @index: Pointer to the current index in the format string
 *
 * Return: Size for argument casting
 */
int determine_size(const char *format, int *index)
{
	int current_index = *index + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = S_LONG;
	else if (format[current_index] == 'h')
		size = S_SHORT;

	if (size == 0)
		*index = current_index - 1;
	else
		*index = current_index;

	return (size);
}
