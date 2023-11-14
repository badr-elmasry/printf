#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_c - Prints a string
 * @c: char types.
 * @buf: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_c(char c, char buf[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char pa = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pa = '0';

	buf[i++] = c;
	buf[i] = '\0';

	if (width > 1)
	{
		buf[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buf[BUFF_SIZE - i - 2] = pa;

		if (flags & F_MINUS)
			return (write(1, &buf[0], 1) +
					write(1, &buf[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buf[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buf[0], 1));
	}

	return (write(1, &buf[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buf: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pa = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buf, flags, width, precision,
		length, pa, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buf: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buf[],
	int flags, int width, int prec,
	int length, char pa, char extra_c)
{
	int i, pa_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buf[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buf[ind] == '0')
		buf[ind] = pa = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		pa = ' ';
	while (prec > length)
		buf[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buf[i] = pa;
		buf[i] = '\0';
		if (flags & F_MINUS && pa == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[ind], length) + write(1, &buf[1], i - 1));
		}
		else if (!(flags & F_MINUS) && pa == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[1], i - 1) + write(1, &buf[ind], length));
		}
		else if (!(flags & F_MINUS) && pa == '0')
		{
			if (extra_c)
				buf[--pa_start] = extra_c;
			return (write(1, &buffer[pa_start], i - pa_start) +
				write(1, &buf[ind], length - (1 - pa_start)));
		}
	}
	if (extra_c)
		buf[--ind] = extra_c;
	return (write(1, &buf[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buf: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buf[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char pa = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buf[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		pa = ' ';

	while (precision > length)
	{
		buf[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pa = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buf[i] = pa;

		buf[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buf[ind], length) + write(1, &buf[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buf[0], i) + write(1, &buf[ind], length));
		}
	}

	return (write(1, &buf[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buf: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buf[], int ind, int length,
	int width, int flags, char pa, char extra_c, int pa_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buf[i] = pa;
		buf[i] = '\0';
		if (flags & F_MINUS && pa == ' ')/* Asign extra char to left of buffer */
		{
			buf[--ind] = 'x';
			buf[--ind] = '0';
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[ind], length) + write(1, &buf[3], i - 3));
		}
		else if (!(flags & F_MINUS) && pa == ' ')/* extra char to left of buffer */
		{
			buf[--ind] = 'x';
			buf[--ind] = '0';
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[3], i - 3) + write(1, &buf[ind], length));
		}
		else if (!(flags & F_MINUS) && pa == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buf[--pa_start] = extra_c;
			buf[1] = '0';
			buf[2] = 'x';
			return (write(1, &buf[pa_start], i - pa_start) +
				write(1, &buf[ind], length - (1 - pa_start) - 2));
		}
	}
	buf[--ind] = 'x';
	buf[--ind] = '0';
	if (extra_c)
		buf[--ind] = extra_c;
	return (write(1, &buf[ind], BUFF_SIZE - ind - 1));
}
