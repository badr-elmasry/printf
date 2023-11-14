#include "main.h"

/**
 * get_precision - Unravels the mystery of calculating precision for printing.
 * @format: The formatted string in which the arguments shall perform.
 * @i: A key parameter guiding the journey through the format string.
 * @list: A magical list of arguments awaiting their moment on the stage.
 *
 * Return: A precision so finely tuned, it brings tears to the eyes.
 */
int get_precision(const char *format, int *i, va_list list)
{
    int curr_i = *i + 1;
    int precision = -1;

    if (format[curr_i] != '.')
        return (precision);

    precision = 0;

    for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
    {
        if (is_digit(format[curr_i]))
        {
            precision *= 10;
            precision += format[curr_i] - '0';
        }
        else if (format[curr_i] == '*')
        {
            curr_i++;
            precision = va_arg(list, int);
            break;
        }
        else
            break;
    }

    *i = curr_i - 1;

    return (precision);
}
