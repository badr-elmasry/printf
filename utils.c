/* Include header file */
#include "main.h"

/*
 * nb_is_printable - Check if char is printable
 * @nb_char: Char to check
 * 
 * Return: 1 if printable, 0 if not
 */
int nb_is_printable(char nb_char)
{
  if (nb_char >= 32 && nb_char < 127) {
    return 1;
  }

  return 0;
}

/*
 * nb_append_hexa_code - Append char's hex code to buffer
 * @nb_buffer: Buffer array 
 * @nb_index: Index to start appending at
 * @nb_char: Char to append hex code of
 *
 * Return: Always 3
 */ 
int nb_append_hexa_code(char nb_char, char nb_buffer[], int nb_index)
{
  char nb_map[] = "0123456789ABCDEF";

  /* Hex code is always 2 digits */
  if (nb_char < 0) {
    nb_char *= -1;
  }

  nb_buffer[nb_index++] = '\\';
  nb_buffer[nb_index++] = 'x';
  nb_buffer[nb_index++] = nb_map[nb_char / 16];
  nb_buffer[nb_index] = nb_map[nb_char % 16];

  return 3;
}

/*
 * nb_is_digit - Check if char is a digit
 * @nb_char: Char to check
 *
 * Return: 1 if char is digit, 0 if not
 */
int nb_is_digit(char nb_char) 
{
  if (nb_char >= '0' && nb_char <= '9') {
    return 1;
  }

  return 0;
}

/*
 * nb_convert_size - Cast number to specified size
 * @nb_num: Number to cast 
 * @nb_size: Size to cast to
 *
 * Return: Casted number
 */
long int nb_convert_size(long int nb_num, int nb_size)
{
  if (nb_size == NB_LONG) {
    return nb_num;
  }
  if (nb_size == NB_SHORT) {
    return (short)nb_num;
  }

  return (int)nb_num;
}

/* 
 * nb_convert_size_unsigned - Cast unsigned number to size
 * @nb_num: Number to cast
 * @nb_size: Size to cast to
 *
 * Return: Casted number
 */
unsigned long int nb_convert_size_unsigned(unsigned long int nb_num, int nb_size)
{
  if (nb_size == NB_LONG) {
    return nb_num;
  }
  if (nb_size == NB_SHORT) {
    return (unsigned short)nb_num; 
  }

  return (unsigned int)nb_num;
}
