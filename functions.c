/* Include header file */
#include "main.h"

/*
 * nb_print_char - Prints a character 
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_char(va_list nb_args, char nb_buffer[], 
                  int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  char nb_char = va_arg(nb_args, int);

  return (nb_handle_write_char(nb_char, nb_buffer, nb_flags, nb_width,
                               nb_precision, nb_size));
}

/* 
 * nb_print_string - Prints a string
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_string(va_list nb_args, char nb_buffer[],
                    int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  int nb_length = 0, i;
  char *nb_str = va_arg(nb_args, char*);

  UNUSED(nb_buffer);
  UNUSED(nb_flags);
  UNUSED(nb_width);
  UNUSED(nb_precision);
  UNUSED(nb_size);

  if (!nb_str) {
    nb_str = "(null)";
    if (nb_precision >= 6) {
      nb_str = "      ";
    }
  }

  while (nb_str[nb_length]) {
    nb_length++;
  }

  if (nb_precision >= 0 && nb_precision < nb_length) {
    nb_length = nb_precision;
  }

  if (nb_width > nb_length) {
    if (nb_flags & NB_MINUS) {
      write(1, &nb_str[0], nb_length);
      for (i = nb_width - nb_length; i > 0; i--) {
        write(1, " ", 1);
      }
      return (nb_width);
    } else {
      for (i = nb_width - nb_length; i > 0; i--) {
        write(1, " ", 1);
      }
      write(1, &nb_str[0], nb_length);
      return (nb_width);
    }
  }

  return (write(1, nb_str, nb_length));
}

/*
 * nb_print_percent - Prints a percent sign
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing 
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_percent(va_list nb_args, char nb_buffer[],
                     int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  UNUSED(nb_args);
  UNUSED(nb_buffer);
  UNUSED(nb_flags);
  UNUSED(nb_width);
  UNUSED(nb_precision);
  UNUSED(nb_size);

  return (write(1, "%%", 1));
}

/*
 * nb_print_int - Prints an integer
 * @nb_args: List of arguments  
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification 
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_int(va_list nb_args, char nb_buffer[],
                 int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  int nb_index = NB_BUFF_SIZE - 2;
  int nb_is_negative = 0;
  long int nb_num = va_arg(nb_args, long int);
  unsigned long int nb_abs_num;

  nb_num = nb_convert_size(nb_num, nb_size);

  if (nb_num == 0) {
    nb_buffer[nb_index--] = '0';
  }

  nb_buffer[NB_BUFF_SIZE - 1] = '\0';

  if (nb_num < 0) {
    nb_abs_num = -nb_num;
    nb_is_negative = 1;
  } else {
    nb_abs_num = nb_num;
  }

  while (nb_abs_num > 0) {
    nb_buffer[nb_index--] = (nb_abs_num % 10) + '0';
    nb_abs_num /= 10;
  }

  nb_index++;

  return (nb_write_number(nb_is_negative, nb_index, nb_buffer,
                          nb_flags, nb_width, nb_precision, nb_size));
}

/*
 * nb_print_binary - Prints a number in binary 
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags  
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_binary(va_list nb_args, char nb_buffer[],
                    int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  unsigned int nb_num, nb_m, i, nb_sum;
  unsigned int nb_bits[32];
  int nb_count;

  UNUSED(nb_buffer);
  UNUSED(nb_flags);
  UNUSED(nb_width);
  UNUSED(nb_precision);
  UNUSED(nb_size);

  nb_num = va_arg(nb_args, unsigned int);
  nb_m = 2147483648; /* (2 ^ 31) */

  nb_bits[0] = nb_num / nb_m;

  for(i = 1; i < 32; i++) {
    nb_m /= 2;
    nb_bits[i] = (nb_num / nb_m) % 2; 
  }

  for(i = 0, nb_sum = 0, nb_count = 0; i < 32; i++) {
    nb_sum += nb_bits[i];
    if (nb_sum || i == 31) {
      char nb_char = '0' + nb_bits[i];
      write(1, &nb_char, 1);
      nb_count++;
    }
  }

  return (nb_count);
}

