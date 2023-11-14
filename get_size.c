#include "main.h"

/**
 * get_size - Unlocks the secret to calculating the size for argument casting.
 * @format: The formatted string in which the arguments shall manifest.
 * @i: A key parameter guiding the expedition through the format string.
 *
 * Return: The chosen size, a mystical essence for perfect casting.
 */
int get_size(const char *format, int *i)
{
    int curr_i = *i + 1;
    int size = 0;

    if (format[curr_i] == 'l')
        size = S_LONG;
    else if (format[curr_i] == 'h')
        size = S_SHORT;

    if (size == 0)
        *i = curr_i - 1;
    else
        *i = curr_i;

    return (size);
}
