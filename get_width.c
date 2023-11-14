/* Include header file */
#include "main.h"

/*
 * nb_get_width - Get width for printing 
 * @nb_format: Formatted string to print arguments
 * @nb_i: Pointer to index in format string
 * @nb_args: List of arguments
 *
 * Return: Width value
 */
int nb_get_width(const char *nb_format, int *nb_i, va_list nb_args)
{
  int nb_curr;
  int nb_width = 0;

  for (nb_curr = *nb_i + 1; nb_format[nb_curr]; nb_curr++) {

    if (nb_is_digit(nb_format[nb_curr])) {
      nb_width *= 10;
      nb_width += nb_format[nb_curr] - '0';

    } else if (nb_format[nb_curr] == '*') {
      nb_curr++;
      nb_width = va_arg(nb_args, int);
      break;

    } else {
      break;
    }

  }
  
  *nb_i = nb_curr - 1;

  return nb_width;
}
