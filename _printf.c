#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * @brief Prints formatted data to stdout.
 *
 * This function implements a simplified version of printf to handle
 * a subset of format specifiers. It takes a format string and a variable
 * number of arguments and prints the formatted output to the standard output.
 *
 * @param format A pointer to the format string.
 * @return The number of characters printed (excluding the null byte),
 *         or -1 if an error occurred.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * @brief Prints the contents of the buffer to stdout.
 *
 * This function is responsible for printing the buffered content to
 * the standard output. It is used to ensure efficient writing of characters
 * in chunks rather than one at a time.
 *
 * @param buffer Array of characters containing the buffered data.
 * @param buff_ind Index at which to add the next character, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
