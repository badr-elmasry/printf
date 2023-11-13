#include "main.h"

/**
 * NB_getFlags - Determines active formatting flags
 * @NB_format: Formatted string containing the arguments
 * @NB_i: Index of the current character in the format string
 * Return: Active flags based on the format string
 */
int NB_getFlags(const char *NB_format, int *NB_i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int NB_j, NB_currIndex;
	int NB_flags = 0;
	const char NB_FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int NB_FLAGS_ARRAY[] = {NB_F_MINUS, NB_F_PLUS, NB_F_ZERO, NB_F_HASH, NB_F_SPACE, 0};

	for (NB_currIndex = *NB_i + 1; NB_format[NB_currIndex] != '\0'; NB_currIndex++)
	{
		for (NB_j = 0; NB_FLAGS_CHAR[NB_j] != '\0'; NB_j++)
		{
			if (NB_format[NB_currIndex] == NB_FLAGS_CHAR[NB_j])
			{
				NB_flags |= NB_FLAGS_ARRAY[NB_j];
				break;
			}
		}

		if (NB_FLAGS_CHAR[NB_j] == 0)
			break;
	}

	*NB_i = NB_currIndex - 1;

	return (NB_flags);
}
