#include "main.h"

void print_out_buffer(char char_arr[], int *arr_idx); 

/*
* display_printf - Display function  
* @fmt: format string.
* Return: Number of printed characters.
*/

int display_printf(const char *fmt, ...)

{

  int idx, chars_printed = 0, num_printed = 0;
  int flags, width, precision, size, buf_idx = 0;
  va_list arg_list;
  char buf[BUF_SIZE];

  if (!fmt) 
    return -1;

  va_start(arg_list, fmt);

  for (idx = 0; fmt[idx] != '\0'; idx++) {

    if (fmt[idx] != '%') {

      buf[buf_idx++] = fmt[idx];

      if (buf_idx == BUF_SIZE)
        print_out_buffer(buf, &buf_idx); 

      /* write(1, &fmt[idx], 1); */
      chars_printed++;

    } else {

      print_out_buffer(buf, &buf_idx);

      flags = get_flags(fmt, &idx);
      width = get_width(fmt, &idx, arg_list);
      precision = get_precision(fmt, &idx, arg_list);
      size = get_size(fmt, &idx);

      idx++;

      num_printed = handle_output(fmt, &idx, arg_list, buf,  
                                  flags, width, precision, size);

      if (num_printed == -1)
        return -1;

      chars_printed += num_printed;

    }

  }

  print_out_buffer(buf, &buf_idx);

  va_end(arg_list);

  return chars_printed;

}

/*
* print_out_buffer - Print buffer contents if exists
* @char_arr: Array of characters  
* @arr_idx: Index to add next char, represents length
*/

void print_out_buffer(char char_arr[], int *arr_idx) {

  if (*arr_idx > 0)
    write(1, &char_arr[0], *arr_idx);

  *arr_idx = 0;

}
