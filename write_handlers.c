#include "main.h"

/************************* OUTPUT HANDLING *************************/
/**
 * nb_handle_char_output - Handles character output
 * @c: Character to be handled
 * @output: Output buffer array
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_handle_char_output(char c, char output[],
	int flags, int width, int precision, int size)
{
	int index = 0;
	char padding_char = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & NB_F_ZERO)
		padding_char = '0';

	output[index++] = c;
	output[index] = '\0';

	if (width > 1)
	{
		output[NB_BUFF_SIZE - 1] = '\0';
		for (index = 0; index < width - 1; index++)
			output[NB_BUFF_SIZE - index - 2] = padding_char;

		if (flags & NB_F_MINUS)
			return (write(1, &output[0], 1) +
					write(1, &output[NB_BUFF_SIZE - index - 1], width - 1));
		else
			return (write(1, &output[NB_BUFF_SIZE - index - 1], width - 1) +
					write(1, &output[0], 1));
	}

	return (write(1, &output[0], 1));
}

/************************* NUMBER OUTPUT *************************/
/**
 * nb_write_number_output - Handles number output
 * @is_negative: Flag indicating if the number is negative
 * @index: Index at which the number starts in the buffer
 * @output: Output buffer array
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_write_number_output(int is_negative, int index, char output[],
	int flags, int width, int precision, int size)
{
	int length = NB_BUFF_SIZE - index - 1;
	char padding_char = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & NB_F_ZERO) && !(flags & NB_F_MINUS))
		padding_char = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & NB_F_PLUS)
		extra_char = '+';
	else if (flags & NB_F_SPACE)
		extra_char = ' ';

	return (nb_write_number(index, output, flags, width, precision,
		length, padding_char, extra_char));
}

/**
 * nb_write_number - Writes a number using a buffer
 * @index: Index at which the number starts in the buffer
 * @output: Output buffer array
 * @flags: Flags specifier
 * @width: Width specifier
 * @precision: Precision specifier
 * @length: Number length
 * @padding_char: Padding character
 * @extra_char: Extra character
 *
 * Return: Number of characters printed
 */
int nb_write_number(int index, char output[],
	int flags, int width, int precision,
	int length, char padding_char, char extra_char)
{
	int i, padding_start = 1;

	if (precision == 0 && index == NB_BUFF_SIZE - 2 && output[index] == '0' && width == 0)
		return (0);

	if (precision == 0 && index == NB_BUFF_SIZE - 2 && output[index] == '0')
		output[index] = padding_char = ' ';

	if (precision > 0 && precision < length)
		padding_char = ' ';

	while (precision > length)
		output[--index] = '0', length++;

	if (extra_char != 0)
		length++;

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			output[i] = padding_char;

		output[i] = '\0';

		if (flags & NB_F_MINUS && padding_char == ' ')
		{
			if (extra_char)
				output[--index] = extra_char;
			return (write(1, &output[index], length) + write(1, &output[1], i - 1));
		}
		else if (!(flags & NB_F_MINUS) && padding_char == ' ')
		{
			if (extra_char)
				output[--index] = extra_char;
			return (write(1, &output[1], i - 1) + write(1, &output[index], length));
		}
		else if (!(flags & NB_F_MINUS) && padding_char == '0')
		{
			if (extra_char)
				output[--padding_start] = extra_char;
			return (write(1, &output[padding_start], i - padding_start) +
				write(1, &output[index], length - (1 - padding_start)));
		}
	}

	if (extra_char)
		output[--index] = extra_char;

	return (write(1, &output[index], length));
}

/**
 * nb_write_unsigned - Writes an unsigned number
 * @is_negative: Flag indicating if the number is negative
 * @index: Index at which the number starts in the buffer
 * @output: Output buffer array
 * @flags: Flags specifier
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int nb_write_unsigned(int is_negative, int index,
	char output[], int flags, int width, int precision, int size)
{
	int length = NB_BUFF_SIZE - index - 1, i = 0;
	char padding_char = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == NB_BUFF_SIZE - 2 && output[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padding_char = ' ';

	while (precision > length)
	{
		output[--index] = '0';
		length++;
	}

	if ((flags & NB_F_ZERO) && !(flags & NB_F_MINUS))
		padding_char = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			output[i] = padding_char;

		output[i] = '\0';

		if (flags & NB_F_MINUS)
			return (write(1, &output[index], length) + write(1, &output[0], i));
		else
			return (write(1, &output[0], i) + write(1, &output[index], length));
	}

	return (write(1, &output[index], length));
}

/**
 * nb_write_pointer - Writes a memory address
 * @output: Output buffer array
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padding_char: Padding character
 * @extra_char: Extra character
 * @padding_start: Index at which padding should start
 *
 * Return: Number of characters printed
 */
int nb_write_pointer(char output[], int index, int length,
	int width, int flags, char padding_char, char extra_char, int padding_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			output[i] = padding_char;

		output[i] = '\0';

		if (flags & NB_F_MINUS)
		{
			output[--index] = 'x';
			output[--index] = '0';

			if (extra_char)
				output[--index] = extra_char;

			return (write(1, &output[index], length) + write(1, &output[3], i - 3));
		}
		else
		{
			output[--index] = 'x';
			output[--index] = '0';

			if (extra_char)
				output[--index] = extra_char;

			return (write(1, &output[3], i - 3) + write(1, &output[index], length));
		}
	}

	output[--index] = 'x';
	output[--index] = '0';

	if (extra_char)
		output[--index] = extra_char;

	return (write(1, &output[index], NB_BUFF_SIZE - index - 1));
}
