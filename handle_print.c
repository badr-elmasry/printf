/* Include header file */
#include "main.h"

/* 
 * nb_handle_print - Handle printing argument based on type
 * @nb_fmt: Formatted string to print arguments
 * @nb_index: Pointer to index in format string
 * @nb_args: List of arguments
 * @nb_buffer: Buffer array to handle printing
 * @nb_flags: Active flags
 * @nb_width: Width
 * @nb_precision: Precision specification 
 * @nb_size: Size modifier
 *
 * Return: Number of chars printed or -1 on failure
 */
int nb_handle_print(const char *nb_fmt, int *nb_index, va_list nb_args, char nb_buffer[],
                    int nb_flags, int nb_width, int nb_precision, int nb_size)
{
  int nb_i, nb_unknown_len = 0, nb_printed = -1;

  fmt_t nb_fmts[] = {
    {'c', nb_print_char}, 
    {'s', nb_print_string},
    {'%', nb_print_percent},
    {'i', nb_print_int},
    {'d', nb_print_int},
    {'b', nb_print_binary},
    {'u', nb_print_unsigned},
    {'o', nb_print_octal},
    {'x', nb_print_hex},
    {'X', nb_print_hex_upper},
    {'p', nb_print_pointer},
    {'S', nb_print_non_printable}, 
    {'r', nb_print_reverse},
    {'R', nb_print_rot13},
    {'\0', NULL}
  };

  for (nb_i = 0; nb_fmts[nb_i].fmt; nb_i++) {
    if (nb_fmt[*nb_index] == nb_fmts[nb_i].fmt) {
      return nb_fmts[nb_i].fn(nb_args, nb_buffer, nb_flags, nb_width, 
                              nb_precision, nb_size);
    }
  }

  if (!nb_fmts[nb_i].fmt) {

    if (!nb_fmt[*nb_index]) {
      return -1;
    }

    nb_unknown_len += write(1, "%%", 1);

    if (nb_fmt[*nb_index - 1] == ' ') {
      nb_unknown_len += write(1, " ", 1);  
    } else if (nb_width) {
      --*nb_index;
      while (nb_fmt[*nb_index] != ' ' && nb_fmt[*nb_index] != '%') {
        --*nb_index; 
      }
      if (nb_fmt[*nb_index] == ' ') {
        --*nb_index;
      }
      return 1;
    }

    nb_unknown_len += write(1, &nb_fmt[*nb_index], 1);

    return nb_unknown_len;
  }

  return nb_printed;
}
