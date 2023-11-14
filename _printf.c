/* Include header file */
#include "main.h" 

/*
 * nb_print_buffer - Prints nb_buffer if contents exist
 * @nb_buffer: Character array 
 * @nb_buff_index: Index to add next char, represents length
 */
void nb_print_buffer(char nb_buffer[], int *nb_buff_index);

/*
 * nb_print_formatted - Printf function
 * @nb_format: Format string
 *
 * Return: Number of characters printed
 */
int nb_print_formatted(const char *nb_format, ...)
{
  /* Declare variables */
  int i;
  int nb_printed = 0;
  int nb_total = 0;

  int nb_flags;
  int nb_width;
  int nb_precision;
  int nb_size;

  int nb_buff_index = 0; 
  va_list nb_args;
  char nb_buffer[NB_BUFF_SIZE];

  /* Handle null format */
  if (!nb_format) {
    return -1;
  }

  /* Initialize va_list */
  va_start(nb_args, nb_format);

  /* Loop through format string */
  for(i = 0; nb_format[i]; i++) {
    
    /* Normal character */
    if (nb_format[i] != '%') {

      /* Add to buffer */
      nb_buffer[nb_buff_index++] = nb_format[i];

      /* Flush full buffer */
      if (nb_buff_index == NB_BUFF_SIZE) {
        nb_print_buffer(nb_buffer, &nb_buff_index);
      }

      /* Increment total chars */
      nb_total++;

    /* Format specifier */
    } else {

      /* Flush buffer */
      nb_print_buffer(nb_buffer, &nb_buff_index);

      /* Get flags */
      nb_flags = nb_get_flags(nb_format, &i);

      /* Get width */ 
      nb_width = nb_get_width(nb_format, &i, nb_args);

      /* Get precision */
      nb_precision = nb_get_precision(nb_format, &i, nb_args);

      /* Get size */
      nb_size = nb_get_size(nb_format, &i);

      /* Increment for specifier */
      i++;

      /* Print formatted */
      nb_printed = nb_print_formatted(nb_format, &i, nb_args, nb_buffer,
                                      nb_flags, nb_width, nb_precision, nb_size); 

      /* Check for error */
      if (nb_printed == -1) {
        return -1;
      }

      /* Update total */
      nb_total += nb_printed;

    }
  }

  /* Flush remaining buffer */
  nb_print_buffer(nb_buffer, &nb_buff_index);

  /* Cleanup */
  va_end(nb_args);

  return nb_total; 
}

/* 
 * nb_print_buffer - Prints nb_buffer if contents exist
 * @nb_buffer: Character array
 * @nb_buff_index: Index to add next char, represents length
 */
void nb_print_buffer(char nb_buffer[], int *nb_buff_index)
{
  if (*nb_buff_index > 0) {
    write(1, &nb_buffer[0], *nb_buff_index);
  }

  *nb_buff_index = 0;
}
