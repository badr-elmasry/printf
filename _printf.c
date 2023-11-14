#include "main.h"

/**
 * buffer_print - Print the buffer content if it exists
 * @buffer: Array of characters
 * @buff_ind: Index for the next character, representing the length.
 */
void buffer_print(char buffer[], int *buff_ind);

/**
 * custom_printf - Custom printf function
 * @format: Format string.
 * Return: Number of characters printed (excluding null byte).
 */
int custom_printf(const char *format, ...)
{
	int i, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (!format)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				buffer_print(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			buffer_print(buffer, &buff_ind);
			flags = extract_flags(format, &i);
			width = extract_width(format, &i, list);
			precision = extract_precision(format, &i, list);
			size = extract_size(format, &i);
			++i;
			printed_chars += process_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed_chars == -1)
				return (-1);
		}
	}

	buffer_print(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * buffer_print - Print the buffer content if it exists
 * @buffer: Array of characters
 * @buff_ind: Index for the next character, representing the length.
 */
void buffer_print(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

