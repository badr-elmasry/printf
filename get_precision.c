#include "main.h"

/*
 * nb_calculate_precision - Determines the precision for printing
 * @nb_format: Formatted string for printing arguments
 * @nb_index: Index of the current character in the format string
 * @nb_args: List of arguments
 *
 * Returns: Calculated precision.
 */
int nb_calculate_precision(const char *nb_format, int *nb_index, va_list nb_args)
{
	int nb_current_index = *nb_index + 1;
	int nb_precision = -1;

	if (nb_format[nb_current_index] != '.')
		return (nb_precision);

	nb_precision = 0;

	for (nb_current_index += 1; nb_format[nb_current_index] != '\0'; nb_current_index++)
	{
		if (nb_is_digit(nb_format[nb_current_index]))
		{
			nb_precision *= 10;
			nb_precision += nb_format[nb_current_index] - '0';
		}
		else if (nb_format[nb_current_index] == '*')
		{
			nb_current_index++;
			nb_precision = va_arg(nb_args, int);
			break;
		}
		else
			break;
	}

	*nb_index = nb_current_index - 1;

	return nb_precision;
}
