#include "main.h"

/*
 * nb_get_flags - Determine active flags
 * @nb_format: Formatted string for printing arguments
 * @nb_i: Index parameter
 * Return: Active flags
 */
int nb_get_flags(const char *nb_format, int *nb_i)
{
	// Flag characters: - + 0 # ' '
	// Flag values:     1  2  4  8  16
	int nb_j, nb_curr_i;
	int nb_flags = 0;
	const char NB_FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int NB_FLAGS_ARR[] = {NB_F_MINUS, NB_F_PLUS, NB_F_ZERO, NB_F_HASH, NB_F_SPACE, 0};

	for (nb_curr_i = *nb_i + 1; nb_format[nb_curr_i] != '\0'; nb_curr_i++)
	{
		for (nb_j = 0; NB_FLAGS_CH[nb_j] != '\0'; nb_j++)
			if (nb_format[nb_curr_i] == NB_FLAGS_CH[nb_j])
			{
				nb_flags |= NB_FLAGS_ARR[nb_j];
				break;
			}

		if (NB_FLAGS_CH[nb_j] == 0)
			break;
	}

	*nb_i = nb_curr_i - 1;

	return (nb_flags);
}
