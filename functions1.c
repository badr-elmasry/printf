/* Include header file */
#include "main.h"

/*
 * nb_print_unsigned - Prints an unsigned number
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width 
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_unsigned(va_list nb_args, char nb_buffer[],
                      int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  int nb_index = NB_BUFF_SIZE - 2;
  unsigned long int nb_num = va_arg(nb_args, unsigned long int);

  nb_num = nb_convert_size_unsigned(nb_num, nb_size);

  if (nb_num == 0) {
    nb_buffer[nb_index--] = '0';
  }

  nb_buffer[NB_BUFF_SIZE - 1] = '\0';

  while (nb_num > 0) {
    nb_buffer[nb_index--] = (nb_num % 10) + '0';
    nb_num /= 10;
  }

  nb_index++;

  return (nb_write_unsigned(0, nb_index, nb_buffer, nb_flags, 
                            nb_width, nb_precision, nb_size));

}

/*
 * nb_print_octal - Prints an unsigned number in octal format  
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_octal(va_list nb_args, char nb_buffer[],
                   int nb_flags, int nb_width, int nb_precision, int nb_size)
{

  int nb_index = NB_BUFF_SIZE - 2;
  unsigned long int nb_num = va_arg(nb_args, unsigned long int);
  unsigned long int nb_initial = nb_num;

  UNUSED(nb_width);

  nb_num = nb_convert_size_unsigned(nb_num, nb_size);

  if (nb_num == 0) {
    nb_buffer[nb_index--] = '0';
  }

  nb_buffer[NB_BUFF_SIZE - 1] = '\0';

  while (nb_num > 0) {
    nb_buffer[nb_index--] = (nb_num % 8) + '0';
    nb_num /= 8;
  }

  if (nb_flags & NB_HASH && nb_initial != 0) {
    nb_buffer[nb_index--] = '0';
  }

  nb_index++;

  return (nb_write_unsigned(0, nb_index, nb_buffer, nb_flags,
                            nb_width, nb_precision, nb_size));

}

/*
 * nb_print_hex - Prints an unsigned number in hexadecimal format
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing  
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */ 
int nb_print_hex(va_list nb_args, char nb_buffer[],
                 int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  return (nb_print_hexa(nb_args, "0123456789abcdef", nb_buffer, nb_flags,
                        'x', nb_width, nb_precision, nb_size));
}

/*
 * nb_print_hex_upper - Prints an unsigned number in upper hexadecimal format
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width 
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_hex_upper(va_list nb_args, char nb_buffer[],
                       int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  return (nb_print_hexa(nb_args, "0123456789ABCDEF", nb_buffer, nb_flags,
                        'X', nb_width, nb_precision, nb_size));
}

/*
 * nb_print_hexa - Prints a number in hexadecimal format (lower/upper)  
 * @nb_args: List of arguments
 * @nb_map: Map of values to represent hex digits
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_flag_ch: Flag character (x or X) 
 * @nb_width: Width
 * @nb_precision: Precision specification 
 * @nb_size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_print_hexa(va_list nb_args, char nb_map[], char nb_buffer[],
                  int nb_flags, char nb_flag_ch, int nb_width, 
                  int nb_precision, int nb_size)
{
  int nb_index = NB_BUFF_SIZE - 2;
  unsigned long int nb_num = va_arg(nb_args, unsigned long int);
  unsigned long int nb_initial = nb_num;

  UNUSED(nb_width);

  nb_num = nb_convert_size_unsigned(nb_num, nb_size);

  if (nb_num == 0) {
    nb_buffer[nb_index--] = '0'; 
  }

  nb_buffer[NB_BUFF_SIZE - 1] = '\0';

  while (nb_num > 0) {
    nb_buffer[nb_index--] = nb_map[nb_num % 16]; 
    nb_num /= 16;
  }

  if (nb_flags & NB_HASH && nb_initial != 0) {
    nb_buffer[nb_index--] = nb_flag_ch;
    nb_buffer[nb_index--] = '0';
  }

  nb_index++;

  return (nb_write_unsigned(0, nb_index, nb_buffer, nb_flags, 
                            nb_width, nb_precision, nb_size));
}
