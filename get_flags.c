/* Include header file */
#include "main.h"

/*
 * nb_get_flags - Get active flags from format string
 * @nb_format: Formatted string to print arguments
 * @nb_i: Pointer to index in format string
 *
 * Return: Active flags
 */ 
int nb_get_flags(const char *nb_format, int *nb_i)
{
  /* - + 0 # ' ' */
  /* 1 2 4 8 16 */
  int nb_j, nb_curr;  
  int nb_flags = 0;

  char NB_FLAGS[] = {'-', '+', '0', '#', ' ', '\0'};

  int NB_FLAG_VALS[] = {NB_MINUS, NB_PLUS, NB_ZERO, NB_HASH, NB_SPACE, 0};

  for (nb_curr = *nb_i + 1; nb_format[nb_curr]; nb_curr++) {

    for (nb_j = 0; NB_FLAGS[nb_j]; nb_j++) {
      if (nb_format[nb_curr] == NB_FLAGS[nb_j]) {
        nb_flags |= NB_FLAG_VALS[nb_j];
        break;
      }
    }

    if (!NB_FLAGS[nb_j]) {
      break;
    }

  }

  *nb_i = nb_curr - 1;

  return nb_flags;

}
