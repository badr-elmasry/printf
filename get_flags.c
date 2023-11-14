#include "main.h"

/**
 * identify_flags - Identify and calculate active flags
 * @format: Formatted string to analyze for flags
 * @index: Pointer to the current index in the format string
 *
 * Return: Calculated flags
 */
int identify_flags(const char *format, int *index)
{
	int i, current_index;
	int flags = 0;
	const char FLAG_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAG_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_index = *index + 1; format[current_index] != '\0'; current_index++)
	{
		for (i = 0; FLAG_CHARACTERS[i] != '\0'; i++)
		{
			if (format[current_index] == FLAG_CHARACTERS[i])
			{
				flags |= FLAG_VALUES[i];
				break;
			}
		}

		if (FLAG_CHARACTERS[i] == 0)
			break;
	}

	*index = current_index - 1;

	return (flags);
}
