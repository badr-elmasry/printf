#include "main.h"

/****************** PRINT MEMORY POINTER ******************/
/**
 * NB_printMemoryPointer - Prints the memory address stored in a pointer variable
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printMemoryPointer(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	char NB_extraChar = 0, NB_paddingChar = ' ';
	int NB_index = NB_BUFF_SIZE - 2, NB_length = 2, NB_paddingStart = 1; /* length=2, for '0x' */
	unsigned long NB_numAddress;
	char NB_mapTo[] = "0123456789abcdef";
	void *NB_address = va_arg(NB_arguments, void *);

	NB_UNUSED(NB_width);
	NB_UNUSED(NB_size);

	if (NB_address == NULL)
		return (write(1, "(nil)", 5));

	NB_outputBuffer[NB_BUFF_SIZE - 1] = '\0';
	NB_UNUSED(NB_precision);

	NB_numAddress = (unsigned long)NB_address;

	while (NB_numAddress > 0)
	{
		NB_outputBuffer[NB_index--] = NB_mapTo[NB_numAddress % 16];
		NB_numAddress /= 16;
		NB_length++;
	}

	if ((NB_flags & NB_F_ZERO) && !(NB_flags & NB_F_MINUS))
		NB_paddingChar = '0';
	if (NB_flags & NB_F_PLUS)
		NB_extraChar = '+', NB_length++;
	else if (NB_flags & NB_F_SPACE)
		NB_extraChar = ' ', NB_length++;

	NB_index++;

	return (NB_writePointer(NB_outputBuffer, NB_index, NB_length,
		NB_width, NB_flags, NB_paddingChar, NB_extraChar, NB_paddingStart));
}

/************************* PRINT NON-PRINTABLE *************************/
/**
 * NB_printNonPrintable - Prints ASCII codes in hexadecimal for non-printable characters
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printNonPrintable(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_i = 0, NB_offset = 0;
	char *NB_str = va_arg(NB_arguments, char *);

	NB_UNUSED(NB_flags);
	NB_UNUSED(NB_width);
	NB_UNUSED(NB_precision);
	NB_UNUSED(NB_size);

	if (NB_str == NULL)
		return (write(1, "(null)", 6));

	while (NB_str[NB_i] != '\0')
	{
		if (NB_isPrintable(NB_str[NB_i]))
			NB_outputBuffer[NB_i + NB_offset] = NB_str[NB_i];
		else
			NB_offset += NB_appendHexCode(NB_str[NB_i], NB_outputBuffer, NB_i + NB_offset);

		NB_i++;
	}

	NB_outputBuffer[NB_i + NB_offset] = '\0';

	return (write(1, NB_outputBuffer, NB_i + NB_offset));
}

/************************* PRINT REVERSE *************************/
/**
 * NB_printReverse - Prints a reversed string.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printReverse(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	char *NB_str;
	int NB_i, NB_count = 0;

	NB_UNUSED(NB_outputBuffer);
	NB_UNUSED(NB_flags);
	NB_UNUSED(NB_width);
	NB_UNUSED(NB_size);

	NB_str = va_arg(NB_arguments, char *);

	if (NB_str == NULL)
	{
		NB_UNUSED(NB_precision);

		NB_str = ")Null(";
	}
	for (NB_i = 0; NB_str[NB_i]; NB_i++)
		;

	for (NB_i = NB_i - 1; NB_i >= 0; NB_i--)
	{
		char NB_char = NB_str[NB_i];

		write(1, &NB_char, 1);
		NB_count++;
	}
	return (NB_count);
}

/************************* PRINT STRING IN ROT13 *************************/
/**
 * NB_printRot13String - Prints a string in ROT13 encoding.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printRot13String(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	char NB_x;
	char *NB_str;
	unsigned int NB_i, NB_j;
	int NB_count = 0;
	char NB_in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char NB_out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	NB_str = va_arg(NB_arguments, char *);

	NB_UNUSED(NB_outputBuffer);
	NB_UNUSED(NB_flags);
	NB_UNUSED(NB_width);
	NB_UNUSED(NB_precision);
	NB_UNUSED(NB_size);

	if (NB_str == NULL)
		NB_str = "(AHYY)";
	for (NB_i = 0; NB_str[NB_i]; NB_i++)
	{
		for (NB_j = 0; NB_in[NB_j]; NB_j++)
		{
			if (NB_in[NB_j] == NB_str[NB_i])
			{
				NB_x = NB_out[NB_j];
				write(1, &NB_x, 1);
				NB_count++;
				break;
			}
		}
		if (!NB_in[NB_j])
		{
			NB_x = NB_str[NB_i];
			write(1, &NB_x, 1);
			NB_count++;
		}
	}
	return (NB_count);
}
