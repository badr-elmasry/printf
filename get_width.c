#include "nb_main.h"

/*
 * nb_calculate_output_width - Determines the width for printing
 * @nb_format: Formatted string for printing arguments.
 * @nb_index: Index of the current character in the format string.
 * @nb_args: List of arguments.
 *
 * Returns: Calculated width.
 */
int nb_calculate_output_width(const char *nb_format, int *nb_index, va_list nb_args)
{
    int nb_curr_index;
    int nb_width = 0;

    for (nb_curr_index = *nb_index + 1; nb_format[nb_curr_index] != '\0'; nb_curr_index++)
    {
        if (nb_is_digit(nb_format[nb_curr_index]))
        {
            nb_width *= 10;
            nb_width += nb_format[nb_curr_index] - '0';
        }
        else if (nb_format[nb_curr_index] == '*')
        {
            nb_curr_index++;
            nb_width = va_arg(nb_args, int);
            break;
        }
        else
            break;
    }

    *nb_index = nb_curr_index - 1;

    return nb_width;
}
