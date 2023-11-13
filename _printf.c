#include "main.h"

void nb_print_buffer(char nb_buffer[], int *nb_buff_ind);

/**
 * nb_printf - Custom Printf function for NB project
 * @nb_format: Format string.
 * Return: Number of printed characters.
 */
int nb_printf(const char *nb_format, ...)
{
	int i, nb_printed = 0, nb_printed_chars = 0;
	int nb_flags, nb_width, nb_precision, nb_size, nb_buff_ind = 0;
	va_list nb_args;
	char nb_buffer[NB_BUFF_SIZE];

	if (nb_format == NULL)
		return (-1);

	va_start(nb_args, nb_format);

	for (i = 0; nb_format && nb_format[i] != '\0'; i++)
	{
		if (nb_format[i] != '%')
		{
			nb_buffer[nb_buff_ind++] = nb_format[i];
			if (nb_buff_ind == NB_BUFF_SIZE)
				nb_print_buffer(nb_buffer, &nb_buff_ind);
			nb_printed_chars++;
		}
		else
		{
			nb_print_buffer(nb_buffer, &nb_buff_ind);
			nb_flags = nb_get_flags(nb_format, &i);
			nb_width = nb_get_width(nb_format, &i, nb_args);
			nb_precision = nb_get_precision(nb_format, &i, nb_args);
			nb_size = nb_get_size(nb_format, &i);
			++i;
			nb_printed = nb_handle_print(nb_format, &i, nb_args, nb_buffer,
				nb_flags, nb_width, nb_precision, nb_size);
			if (nb_printed == -1)
				return (-1);
			nb_printed_chars += nb_printed;
		}
	}

	nb_print_buffer(nb_buffer, &nb_buff_ind);

	va_end(nb_args);

	return (nb_printed_chars);
}

/**
 * nb_print_buffer - Prints the contents of the buffer if it exists
 * @nb_buffer: Array of characters
 * @nb_buff_ind: Index at which to add the next character, represents the length.
 */
void nb_print_buffer(char nb_buffer[], int *nb_buff_ind)
{
	if (*nb_buff_ind > 0)
		write(1, &nb_buffer[0], *nb_buff_ind);

	*nb_buff_ind = 0;
}

