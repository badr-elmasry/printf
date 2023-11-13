#include "main.h"

/*
 * nb_handle_print - Processes and prints arguments based on their types
 * @nb_fmt: Formatted string to print arguments.
 * @nb_list: List of arguments to be printed.
 * @nb_ind: Index.
 * @nb_buffer: Output buffer array for print handling.
 * @nb_flags: Calculates active flags.
 * @nb_width: Width.
 * @nb_precision: Precision specification.
 * @nb_size: Size specifier.
 * Return: Number of characters printed or -1 for errors.
 */
int nb_handle_print(const char *nb_fmt, int *nb_ind, va_list nb_list, char nb_buffer[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	int nb_i, nb_unknown_len = 0, nb_printed_chars = -1;
	nb_fmt_t nb_fmt_types[] = {
		{'c', nb_print_char}, {'s', nb_print_string}, {'%', nb_print_percent},
		{'i', nb_print_int}, {'d', nb_print_int}, {'b', nb_print_binary},
		{'u', nb_print_unsigned}, {'o', nb_print_octal}, {'x', nb_print_hexadecimal},
		{'X', nb_print_hexa_upper}, {'p', nb_print_pointer}, {'S', nb_print_non_printable},
		{'r', nb_print_reverse}, {'R', nb_print_rot13string}, {'\0', NULL}
	};

	for (nb_i = 0; nb_fmt_types[nb_i].nb_fmt != '\0'; nb_i++)
		if (nb_fmt[*nb_ind] == nb_fmt_types[nb_i].nb_fmt)
			return (nb_fmt_types[nb_i].nb_fn(nb_list, nb_buffer, nb_flags, nb_width, nb_precision, nb_size));

	if (nb_fmt_types[nb_i].nb_fmt == '\0')
	{
		if (nb_fmt[*nb_ind] == '\0')
			return (-1);
		nb_unknown_len += write(1, "%%", 1);
		if (nb_fmt[*nb_ind - 1] == ' ')
			nb_unknown_len += write(1, " ", 1);
		else if (nb_width)
		{
			--(*nb_ind);
			while (nb_fmt[*nb_ind] != ' ' && nb_fmt[*nb_ind] != '%')
				--(*nb_ind);
			if (nb_fmt[*nb_ind] == ' ')
				--(*nb_ind);
			return (1);
		}
		nb_unknown_len += write(1, &nb_fmt[*nb_ind], 1);
		return (nb_unknown_len);
	}
	return (nb_printed_chars);
}
