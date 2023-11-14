#include "main.h"

/**
 * get_width - Unveils the magic of calculating the width for printing.
 * @format: The formatted string in which the arguments shall perform.
 * @i: A guiding star leading through the astral plane of the format string.
 * @list: A cosmic list of arguments, ready to transcend to the printed realm.
 *
 * Return: A width so vast, it stretches across the universe of characters.
 */
int get_width(const char *format, int *i, va_list list)
{
    int curr_i;
    int width = 0;

    for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            width *= 10;
            width += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            curr_i++;
            width = va_arg(list, int);
            break;
        }
        else
            break;
    }

    *i = curr_i - 1;

    return (width);
}
