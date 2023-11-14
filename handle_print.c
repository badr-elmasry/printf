#include "main.h"

/**
 * handle_print - Unleashes the printing magic for various argument types.
 * @fmt: The formatted string guiding the mystical printing journey.
 * @ind: The mysterious index, a key to the uncharted territory of the format string.
 * @list: The list of magical arguments awaiting their moment on the printed stage.
 * @buffer: The enchanted buffer array, where the print shall manifest.
 * @flags: A constellation of active flags guiding the printing ritual.
 * @width: The ethereal width, shaping the dimensions of the printed universe.
 * @precision: A precision so finely tuned, it brings clarity to the printed realm.
 * @size: The cosmic size specifier, influencing the casting of the printed arguments.
 *
 * Return: The magical number 1 or 2, a sign of successful printing invocation.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
