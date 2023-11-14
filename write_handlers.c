/* Include header file */
#include "main.h"

/*
 * nb_handle_write_char - Write a character
 * @nb_char: Character to write  
 * @nb_buffer: Buffer array
 * @nb_flags: Flags
 * @nb_width: Width 
 * @nb_precision: Precision
 * @nb_size: Size
 *
 * Return: Number of chars written
 */
int nb_handle_write_char(char nb_char, char nb_buffer[],
                         int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  /* Char stored left, padding right */
  int nb_i = 0;
  char nb_pad = ' ';

  UNUSED(nb_precision);
  UNUSED(nb_size);

  if (nb_flags & NB_ZERO) {
    nb_pad = '0';
  }

  nb_buffer[nb_i++] = nb_char;
  nb_buffer[nb_i] = '\0';

  if (nb_width > 1) {
    nb_buffer[NB_BUFF_SIZE - 1] = '\0';
    
    for (nb_i = 0; nb_i < nb_width - 1; nb_i++) {
      nb_buffer[NB_BUFF_SIZE - nb_i - 2] = nb_pad;
    }

    if (nb_flags & NB_MINUS) {
      return (write(1, &nb_buffer[0], 1) + 
              write(1, &nb_buffer[NB_BUFF_SIZE - nb_i - 1], nb_width - 1));
    } else {
      return (write(1, &nb_buffer[NB_BUFF_SIZE - nb_i - 1], nb_width - 1) +
              write(1, &nb_buffer[0], 1));
    }
  }

  return (write(1, &nb_buffer[0], 1));

}

/*  
 * nb_write_number - Write a number 
 * @nb_is_neg: 1 if number is negative, 0 if positive
 * @nb_index: Index of number start in buffer
 * @nb_buffer: Buffer array
 * @nb_flags: Flags  
 * @nb_width: Width
 * @nb_precision: Precision
 * @nb_size: Size
 *
 * Return: Number of chars written
 */
int nb_write_number(int nb_is_neg, int nb_index, char nb_buffer[],
                    int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  int nb_length = NB_BUFF_SIZE - nb_index - 1;
  char nb_pad = ' ', nb_extra = 0;

  UNUSED(nb_size);

  if ((nb_flags & NB_ZERO) && !(nb_flags & NB_MINUS)) {
    nb_pad = '0';
  }

  if (nb_is_neg) {
    nb_extra = '-';
  } else if (nb_flags & NB_PLUS) {
    nb_extra = '+';
  } else if (nb_flags & NB_SPACE) {
    nb_extra = ' ';
  }

  return (nb_write_number(nb_index, nb_buffer, nb_flags, nb_width, nb_precision,
                          nb_length, nb_pad, nb_extra));

}

/*
 * nb_write_unsigned - Write unsigned number
 * @nb_is_neg: 1 if negative, 0 if positive (ignored for unsigned)
 * @nb_index: Index of number start in buffer  
 * @nb_buffer: Buffer array
 * @nb_flags: Flags 
 * @nb_width: Width
 * @nb_precision: Precision
 * @nb_size: Size (ignored)
 *
 * Return: Number of chars written
 */ 
int nb_write_unsigned(int nb_is_neg, int nb_index, 
                      char nb_buffer[], int nb_flags, int nb_width, 
                      int nb_precision, int nb_size)
{
  /* Number stored right, starting at index */
  int nb_length = NB_BUFF_SIZE - nb_index - 1, nb_i = 0;
  char nb_pad = ' ';

  UNUSED(nb_is_neg);
  UNUSED(nb_size);

  if (nb_precision == 0 && nb_index == NB_BUFF_SIZE - 2 && nb_buffer[nb_index] == '0') {
    return 0; 
  }

  if (nb_precision > 0 && nb_precision < nb_length) {
    nb_pad = ' ';
  }

  while (nb_precision > nb_length) {
    nb_buffer[--nb_index] = '0';
    nb_length++;
  }

  if ((nb_flags & NB_ZERO) && !(nb_flags & NB_MINUS)) {
    nb_pad = '0';
  }

  // Handle padding

  return (nb_write(1, &nb_buffer[nb_index], nb_length));

}

/*
 * nb_write_pointer - Write pointer address
 * @nb_buffer: Buffer array
 * @nb_index: Index of address start in buffer
 * @nb_length: Length of address  
 * @nb_width: Width 
 * @nb_flags: Flags
 * @nb_pad: Padding character
 * @nb_extra: Extra char  
 * @nb_pad_start: Start index for padding
 *
 * Return: Number of chars written
 */
int nb_write_pointer(char nb_buffer[], int nb_index, int nb_length,
                     int nb_width, int nb_flags, char nb_pad, char nb_extra, 
                     int nb_pad_start)
{
  int nb_i;

  // Handle padding

  nb_buffer[--nb_index] = 'x';
  nb_buffer[--nb_index] = '0';
  
  if (nb_extra) {
    nb_buffer[--nb_index] = nb_extra;
  }

  return (write(1, &nb_buffer[nb_index], NB_BUFF_SIZE - nb_index - 1));
}
