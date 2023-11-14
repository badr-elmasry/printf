#include "main.h"

/**
 * NB_handleWriteChar - Prints a character
 * @NB_c: Character to be printed.
 * @NB_buffer: Buffer array to handle print.
 * @NB_flags: Active flags.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int NB_handleWriteChar(char NB_c, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{ /* char is stored at left and padding at buffer's right */
	int NB_i = 0;
	char NB_padd = ' ';

	UNUSED(NB_precision);
	UNUSED(NB_size);

	if (NB_flags & NB_F_ZERO)
		NB_padd = '0';

	NB_buffer[NB_i++] = NB_c;
	NB_buffer[NB_i] = '\0';

	if (NB_width > 1)
	{
		NB_buffer[NB_BUFF_SIZE - 1] = '\0';
		for (NB_i = 0; NB_i < NB_width - 1; NB_i++)
			NB_buffer[NB_BUFF_SIZE - NB_i - 2] = NB_padd;

		if (NB_flags & NB_F_MINUS)
			return (write(1, &NB_buffer[0], 1) +
					write(1, &NB_buffer[NB_BUFF_SIZE - NB_i - 1], NB_width - 1));
		else
			return (write(1, &NB_buffer[NB_BUFF_SIZE - NB_i - 1], NB_width - 1) +
					write(1, &NB_buffer[0], 1));
	}

	return (write(1, &NB_buffer[0], 1));
}

/**
 * NB_writeNumber - Prints a number
 * @NB_isNegative: Indicates if the number is negative.
 * @NB_ind: Index.
 * @NB_buffer: Buffer array to handle print.
 * @NB_flags: Active flags.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int NB_writeNumber(int NB_isNegative, int NB_ind, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_length = NB_BUFF_SIZE - NB_ind - 1;
	char NB_padd = ' ', NB_extraCh = 0;

	UNUSED(NB_size);

	if ((NB_flags & NB_F_ZERO) && !(NB_flags & NB_F_MINUS))
		NB_padd = '0';
	if (NB_isNegative)
		NB_extraCh = '-';
	else if (NB_flags & NB_F_PLUS)
		NB_extraCh = '+';
	else if (NB_flags & NB_F_SPACE)
		NB_extraCh = ' ';

	return (NB_writeNum(NB_ind, NB_buffer, NB_flags, NB_width, NB_precision,
		NB_length, NB_padd, NB_extraCh));
}

/**
 * NB_writeNum - Writes a number using a buffer
 * @NB_ind: Index.
 * @NB_buffer: Buffer array to handle print.
 * @NB_flags: Active flags.
 * @NB_width: Width specifier.
 * @NB_prec: Precision specifier.
 * @NB_length: Length of the number.
 * @NB_padd: Padding character.
 * @NB_extraC: Extra character.
 *
 * Return: Number of characters printed.
 */
int NB_writeNum(int NB_ind, char NB_buffer[], int NB_flags, int NB_width,
	int NB_prec, int NB_length, char NB_padd, char NB_extraC)
{
	int NB_i, NB_paddStart = 1;

	if (NB_prec == 0 && NB_ind == NB_BUFF_SIZE - 2 && NB_buffer[NB_ind] == '0' && NB_width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (NB_prec == 0 && NB_ind == NB_BUFF_SIZE - 2 && NB_buffer[NB_ind] == '0')
		NB_buffer[NB_ind] = NB_padd = ' '; /* width is displayed with padding ' ' */
	if (NB_prec > 0 && NB_prec < NB_length)
		NB_padd = ' ';
	while (NB_prec > NB_length)
		NB_buffer[--NB_ind] = '0', NB_length++;
	if (NB_extraC != 0)
		NB_length++;
	if (NB_width > NB_length)
	{
		for (NB_i = 1; NB_i < NB_width - NB_length + 1; NB_i++)
			NB_buffer[NB_i] = NB_padd;

		NB_buffer[NB_i] = '\0';

		if (NB_flags & NB_F_MINUS && NB_padd == ' ')/* Asign extra char to left of buffer */
		{
			if (NB_extraC)
				NB_buffer[--NB_ind] = NB_extraC;
			return (write(1, &NB_buffer[NB_ind], NB_length) + write(1, &NB_buffer[1], NB_i - 1));
		}
		else if (!(NB_flags & NB_F_MINUS) && NB_padd == ' ')/* extra char to left of buffer */
		{
			if (NB_extraC)
				NB_buffer[--NB_ind] = NB_extraC;
			return (write(1, &NB_buffer[1], NB_i - 1) + write(1, &NB_buffer[NB_ind], NB_length));
		}
		else if (!(NB_flags & NB_F_MINUS) && NB_padd == '0')/* extra char to left of padd */
		{
			if (NB_extraC)
				NB_buffer[--NB_paddStart] = NB_extraC;
			return (write(1, &NB_buffer[NB_paddStart], NB_i - NB_paddStart) +
				write(1, &NB_buffer[NB_ind], NB_length - (1 - NB_paddStart)));
		}
	}
	if (NB_extraC)
		NB_buffer[--NB_ind] = NB_extraC;
	return (write(1, &NB_buffer[NB_ind], NB_length));
}

/**
 * NB_writeUnsgnd - Writes an unsigned number
 * @NB_isNegative: Indicates if the number is negative.
 * @NB_ind: Index.
 * @NB_buffer: Buffer array to handle print.
 * @NB_flags: Active flags.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 *
 * Return: Number of characters written.
 */
int NB_writeUnsgnd(int NB_isNegative, int NB_ind,
	char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	/* The number is stored at the buffer's right and starts at position i */
	int NB_length = NB_BUFF_SIZE - NB_ind - 1, NB_i = 0;
	char NB_padd = ' ';

	UNUSED(NB_isNegative);
	UNUSED(NB_size);

	if (NB_precision == 0 && NB_ind == NB_BUFF_SIZE - 2 && NB_buffer[NB_ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (NB_precision > 0 && NB_precision < NB_length)
		NB_padd = ' ';

	while (NB_precision > NB_length)
	{
		NB_buffer[--NB_ind] = '0';
		NB_length++;
	}

	if ((NB_flags & NB_F_ZERO) && !(NB_flags & NB_F_MINUS))
		NB_padd = '0';

	if (NB_width > NB_length)
	{
		for (NB_i = 0; NB_i < NB_width - NB_length; NB_i++)
			NB_buffer[NB_i] = NB_padd;

		NB_buffer[NB_i] = '\0';

		if (NB_flags & NB_F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &NB_buffer[NB_ind], NB_length) + write(1, &NB_buffer[0], NB_i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &NB_buffer[0], NB_i) + write(1, &NB_buffer[NB_ind], NB_length));
		}
	}

	return (write(1, &NB_buffer[NB_ind], NB_length));
}

/**
 * NB_writePointer - Writes a memory address
 * @NB_buffer: Buffer array to handle print.
 * @NB_ind: Index.
 * @NB_length: Length of the number.
 * @NB_width: Width specifier.
 * @NB_flags: Active flags.
 * @NB_padd: Padding character.
 * @NB_extraC: Extra character.
 * @NB_paddStart: Index at which padding should start.
 *
 * Return: Number of characters written.
 */
int NB_writePointer(char NB_buffer[], int NB_ind, int NB_length,
	int NB_width, int NB_flags, char NB_padd, char NB_extraC, int NB_paddStart)
{
	int NB_i;

	if (NB_width > NB_length)
	{
		for (NB_i = 3; NB_i < NB_width - NB_length + 3; NB_i++)
			NB_buffer[NB_i] = NB_padd;

		NB_buffer[NB_i] = '\0';

		if (NB_flags & NB_F_MINUS && NB_padd == ' ')/* Asign extra char to left of buffer */
		{
			NB_buffer[--NB_ind] = 'x';
			NB_buffer[--NB_ind] = '0';
			if (NB_extraC)
				NB_buffer[--NB_ind] = NB_extraC;
			return (write(1, &NB_buffer[NB_ind], NB_length) + write(1, &NB_buffer[3], NB_i - 3));
		}
		else if (!(NB_flags & NB_F_MINUS) && NB_padd == ' ')/* extra char to left of buffer */
		{
			NB_buffer[--NB_ind] = 'x';
			NB_buffer[--NB_ind] = '0';
			if (NB_extraC)
				NB_buffer[--NB_ind] = NB_extraC;
			return (write(1, &NB_buffer[3], NB_i - 3) + write(1, &NB_buffer[NB_ind], NB_length));
		}
		else if (!(NB_flags & NB_F_MINUS) && NB_padd == '0')/* extra char to left of padd */
		{
			if (NB_extraC)
				NB_buffer[--NB_paddStart] = NB_extraC;
			NB_buffer[1] = '0';
			NB_buffer[2] = 'x';
			return (write(1, &NB_buffer[NB_paddStart], NB_i - NB_paddStart) +
				write(1, &NB_buffer[NB_ind], NB_length - (1 - NB_paddStart) - 2));
		}
	}

	NB_buffer[--NB_ind] = 'x';
	NB_buffer[--NB_ind] = '0';

	if (NB_extraC)
		NB_buffer[--NB_ind] = NB_extraC;

	return (write(1, &NB_buffer[NB_ind], NB_BUFF_SIZE - NB_ind - 1));
}
