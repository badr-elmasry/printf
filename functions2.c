/* Include header file */
#include "main.h"

/*
 * nb_print_pointer - Prints a pointer 
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array for printing
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of chars printed
 */
int nb_print_pointer(va_list nb_args, char nb_buffer[],
                     int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  char nb_extra = 0, nb_pad = ' ';
  int nb_index = NB_BUFF_SIZE - 2;
  int nb_length = 2; /* For '0x' */
  int nb_pad_start = 1;  
  unsigned long nb_num;
  char nb_map[] = "0123456789abcdef";
  void *nb_ptr = va_arg(nb_args, void*);

  UNUSED(nb_width);
  UNUSED(nb_size);

  if (!nb_ptr) {
    return (write(1, "(nil)", 5));
  }

  nb_buffer[NB_BUFF_SIZE - 1] = '\0';

  UNUSED(nb_precision);

  nb_num = (unsigned long)nb_ptr;

  while (nb_num > 0) {
    nb_buffer[nb_index--] = nb_map[nb_num % 16];
    nb_num /= 16;
    nb_length++;
  }

  if ((nb_flags & NB_ZERO) && !(nb_flags & NB_MINUS)) {
    nb_pad = '0';
  }

  if (nb_flags & NB_PLUS) {
    nb_extra = '+';
    nb_length++;
  } else if (nb_flags & NB_SPACE) {
    nb_extra = ' ';
    nb_length++;
  }

  nb_index++;
  
  return (nb_write_pointer(nb_buffer, nb_index, nb_length, nb_width,
                           nb_flags, nb_pad, nb_extra, nb_pad_start));

}

/*
 * nb_print_non_printable - Print non-printable characters
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array for printing  
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of chars printed
 */
int nb_print_non_printable(va_list nb_args, char nb_buffer[],
                           int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  int nb_index = 0, nb_offset = 0;
  char *nb_str = va_arg(nb_args, char*);

  UNUSED(nb_flags);
  UNUSED(nb_width);
  UNUSED(nb_precision);
  UNUSED(nb_size);

  if (!nb_str) {
    return (write(1, "(null)", 6));
  }

  while (nb_str[nb_index]) {
    if (nb_is_printable(nb_str[nb_index])) {
      nb_buffer[nb_index + nb_offset] = nb_str[nb_index];
    } else {
      nb_offset += nb_append_hexa_code(nb_str[nb_index], nb_buffer, 
                                       nb_index + nb_offset);
    }

    nb_index++;
  }

  nb_buffer[nb_index + nb_offset] = '\0';

  return (write(1, nb_buffer, nb_index + nb_offset));

}

/*
 * nb_print_reverse - Prints a string in reverse
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array for printing
 * @nb_flags: Active flags  
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of chars printed
 */
int nb_print_reverse(va_list nb_args, char nb_buffer[],
                     int nb_flags, int nb_width, int nb_precision, int nb_size) 
{
  char *nb_str;
  int nb_index, nb_count = 0;

  UNUSED(nb_buffer);
  UNUSED(nb_flags);
  UNUSED(nb_width);
  UNUSED(nb_size);

  nb_str = va_arg(nb_args, char*);

  if (!nb_str) {
    UNUSED(nb_precision);
    nb_str = ")Null("; 
  }

  for (nb_index = 0; nb_str[nb_index]; nb_index++);

  for (nb_index--; nb_index >= 0; nb_index--) {
    char nb_char = nb_str[nb_index];
    write(1, &nb_char, 1);
    nb_count++;
  }

  return nb_count;

}

/*
 * nb_print_rot13 - Prints a string in rot13 format
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array for printing
 * @nb_flags: Active flags
 * @nb_width: Width 
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of chars printed
 */
int nb_print_rot13(va_list nb_args, char nb_buffer[],
                   int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  char nb_char;
  char *nb_str;
  unsigned int nb_i, nb_j;
  int nb_count = 0;
  char nb_in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklm";
  char nb_out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

  nb_str = va_arg(nb_args, char*);

  UNUSED(nb_buffer);
  UNUSED(nb_flags);
  UNUSED(nb_width);
  UNUSED(nb_precision);
  UNUSED(nb_size);

  if (!nb_str) {
    nb_str = "(AHYY)";
  }

  for (nb_i = 0; nb_str[nb_i]; nb_i++) {
    for (nb_j = 0; nb_in[nb_j]; nb_j++) {
      if (nb_in[nb_j] == nb_str[nb_i]) {
        nb_char = nb_out[nb_j];
        write(1, &nb_char, 1);
        nb_count++;
        break;
      }
    }
    if (!nb_in[nb_j]) {
      nb_char = nb_str[nb_i];
      write(1, &nb_char, 1);
      nb_count++;
    }
  }

  return nb_count;
}
