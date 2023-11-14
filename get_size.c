/* Include header file */
#include "main.h"

/*
 * nb_get_size - Get size modifier for argument 
 * @nb_format: Formatted string to print arguments
 * @nb_i: Pointer to index in format string
 *
 * Return: Size modifier
 */
int nb_get_size(const char *nb_format, int *nb_i) 
{
  int nb_curr = *nb_i + 1;
  int nb_size = 0;

  if (nb_format[nb_curr] == 'l') {
    nb_size = NB_LONG;

  } else if (nb_format[nb_curr] == 'h') {
    nb_size = NB_SHORT;
  }

  if (!nb_size) {
    *nb_i = nb_curr - 1;

  } else {
    *nb_i = nb_curr;
  }

  return nb_size;
}
