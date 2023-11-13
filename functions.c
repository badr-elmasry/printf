#include "main.h"

/************************* OUTPUT CHARACTER *************************/

/**
 * NB_printChar - Handles the printing of a single character.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printChar(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	char c = va_arg(NB_arguments, int);

	return (NB_handleWriteChar(c, NB_outputBuffer, NB_flags, NB_width, NB_precision, NB_size));
}

/************************* OUTPUT STRING *************************/

/**
 * NB_printString - Handles the printing of a string.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printString(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_length = 0, NB_i;
	char *NB_str = va_arg(NB_arguments, char *);

	NB_UNUSED(NB_outputBuffer);
	NB_UNUSED(NB_flags);
	NB_UNUSED(NB_width);
	NB_UNUSED(NB_precision);
	NB_UNUSED(NB_size);

	if (NB_str == NULL)
	{
		NB_str = "(null)";
		if (NB_precision >= 6)
			NB_str = "      ";
	}

	while (NB_str[NB_length] != '\0')
		NB_length++;

	if (NB_precision >= 0 && NB_precision < NB_length)
		NB_length = NB_precision;

	if (NB_width > NB_length)
	{
		if (NB_flags & NB_F_MINUS)
		{
			write(1, &NB_str[0], NB_length);
			for (NB_i = NB_width - NB_length; NB_i > 0; NB_i--)
				write(1, " ", 1);
			return (NB_width);
		}
		else
		{
			for (NB_i = NB_width - NB_length; NB_i > 0; NB_i--)
				write(1, " ", 1);
			write(1, &NB_str[0], NB_length);
			return (NB_width);
		}
	}

	return (write(1, NB_str, NB_length));
}

/************************* OUTPUT PERCENT SIGN *************************/

/**
 * NB_printPercent - Handles the printing of a percent sign.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printPercent(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	NB_UNUSED(NB_arguments);
	NB_UNUSED(NB_outputBuffer);
	NB_UNUSED(NB_flags);
	NB_UNUSED(NB_width);
	NB_UNUSED(NB_precision);
	NB_UNUSED(NB_size);
	return (write(1, "%%", 1));
}

/************************* OUTPUT INTEGER *************************/

/**
 * NB_printInteger - Handles the printing of an integer.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printInteger(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_i = NB_BUFF_SIZE - 2;
	int NB_isNegative = 0;
	long int NB_n = va_arg(NB_arguments, long int);
	unsigned long int NB_num;

	NB_n = NB_convertSizeNumber(NB_n, NB_size);

	if (NB_n == 0)
		NB_outputBuffer[NB_i--] = '0';

	NB_outputBuffer[NB_BUFF_SIZE - 1] = '\0';
	NB_num = (unsigned long int)NB_n;

	if (NB_n < 0)
	{
		NB_num = (unsigned long int)((-1) * NB_n);
		NB_isNegative = 1;
	}

	while (NB_num > 0)
	{
		NB_outputBuffer[NB_i--] = (NB_num % 10) + '0';
		NB_num /= 10;
	}

	NB_i++;

	return (NB_writeNumber(NB_isNegative, NB_i, NB_outputBuffer, NB_flags, NB_width, NB_precision, NB_size));
}

/************************* OUTPUT BINARY *************************/

/**
 * NB_printBinary - Handles the printing of a binary number.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printBinary(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	unsigned int NB_n, NB_m, NB_i, NB_sum;
	unsigned int NB_a[32];
	int NB_count;

	NB_UNUSED(NB_outputBuffer);
	NB_UNUSED(NB_flags);
	NB_UNUSED(NB_width);
	NB_UNUSED(NB_precision);
	NB_UNUSED(NB_size);

	NB_n = va_arg(NB_arguments, unsigned int);
	NB_m = 2147483648; /* (2 ^ 31) */
	NB_a[0] = NB_n / NB_m;

	for (NB_i = 1; NB_i < 32; NB_i++)
	{
		NB_m /= 2;
		NB_a[NB_i] = (NB_n / NB_m) % 2;
	}

	for (NB_i = 0, NB_sum = 0, NB_count = 0; NB_i < 32; NB_i++)
	{
		NB_sum += NB_a[NB_i];
		if (NB_sum || NB_i == 31)
		{
			char NB_z = '0' + NB_a[NB_i];
			write(1, &NB_z, 1);
			NB_count++;
		}
	}

	return (NB_count);
}
