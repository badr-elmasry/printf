/* Include header file */
#include "main.h"

/*
 * nb_get_precision - Get precision for printing 
 * @nb_format: Formatted string to print arguments
 * @nb_i: Pointer to index in format string
 * @nb_args: List of arguments 
 *
 * Return: Precision value
 */
int nb_get_precision(const char *nb_format, int *nb_i, va_list nb_args)
{
  int nb_curr = *nb_i + 1;
  int nb_precision = -1;

  if (nb_format[nb_curr] != '.') {
    return nb_precision; 
  }

  nb_precision = 0;

  for (nb_curr++; nb_format[nb_curr]; nb_curr++) {
    
    if (nb_is_digit(nb_format[nb_curr])) {
      nb_precision *= 10;
      nb_precision += nb_format[nb_curr] - '0';

    } else if (nb_format[nb_curr] == '*') {
      nb_curr++;
      nb_precision = va_arg(nb_args, int);
      break;

    } else {
      break;
    }

  }

  *nb_i = nb_curr - 1;

  return nb_precision;

}
