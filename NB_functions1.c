#include "main.h"

/************************* PRINT UNSIGNED INTEGER *************************/
/**
 * NB_printUnsigned - Handles printing an unsigned integer.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printUnsigned(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_i = NB_BUFF_SIZE - 2;
	unsigned long int NB_num = va_arg(NB_arguments, unsigned long int);

	NB_num = NB_convertSizeUnsgnd(NB_num, NB_size);

	if (NB_num == 0)
		NB_outputBuffer[NB_i--] = '0';

	NB_outputBuffer[NB_BUFF_SIZE - 1] = '\0';

	while (NB_num > 0)
	{
		NB_outputBuffer[NB_i--] = (NB_num % 10) + '0';
		NB_num /= 10;
	}

	NB_i++;

	return (NB_writeUnsgnd(0, NB_i, NB_outputBuffer, NB_flags, NB_width, NB_precision, NB_size));
}

/************* PRINT UNSIGNED INTEGER IN OCTAL  ****************/
/**
 * NB_printOctal - Handles printing an unsigned integer in octal notation.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printOctal(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_i = NB_BUFF_SIZE - 2;
	unsigned long int NB_num = va_arg(NB_arguments, unsigned long int);
	unsigned long int NB_initNum = NB_num;

	NB_UNUSED(NB_width);

	NB_num = NB_convertSizeUnsgnd(NB_num, NB_size);

	if (NB_num == 0)
		NB_outputBuffer[NB_i--] = '0';

	NB_outputBuffer[NB_BUFF_SIZE - 1] = '\0';

	while (NB_num > 0)
	{
		NB_outputBuffer[NB_i--] = (NB_num % 8) + '0';
		NB_num /= 8;
	}

	if (NB_flags & NB_F_HASH && NB_initNum != 0)
		NB_outputBuffer[NB_i--] = '0';

	NB_i++;

	return (NB_writeUnsgnd(0, NB_i, NB_outputBuffer, NB_flags, NB_width, NB_precision, NB_size));
}

/************** PRINT UNSIGNED INTEGER IN HEXADECIMAL **************/
/**
 * NB_printHexadecimal - Handles printing an unsigned integer in hexadecimal notation.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printHexadecimal(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	return (NB_printHexa(NB_arguments, "0123456789abcdef", NB_outputBuffer,
		NB_flags, 'x', NB_width, NB_precision, NB_size));
}

/************* PRINT UNSIGNED INTEGER IN UPPER HEXADECIMAL **************/
/**
 * NB_printHexaUpper - Handles printing an unsigned integer in upper hexadecimal notation.
 * @NB_arguments: Variable argument list.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printHexaUpper(va_list NB_arguments, char NB_outputBuffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	return (NB_printHexa(NB_arguments, "0123456789ABCDEF", NB_outputBuffer,
		NB_flags, 'X', NB_width, NB_precision, NB_size));
}

/************** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER **************/
/**
 * NB_printHexa - Handles printing a hexadecimal number in lower or upper case.
 * @NB_arguments: Variable argument list.
 * @NB_mapTo: Array of values to map the number to.
 * @NB_outputBuffer: Buffer for storing characters.
 * @NB_flags: Flags indicating formatting options.
 * @NB_flagCh: Flag indicating whether to use lower or upper case.
 * @NB_width: Width specifier.
 * @NB_precision: Precision specifier.
 * @NB_size: Size specifier.
 * Return: Number of characters printed.
 */
int NB_printHexa(va_list NB_arguments, char NB_mapTo[], char NB_outputBuffer[],
	int NB_flags, char NB_flagCh, int NB_width, int NB_precision, int NB_size)
{
	int NB_i = NB_BUFF_SIZE - 2;
	unsigned long int NB_num = va_arg(NB_arguments, unsigned long int);
	unsigned long int NB_initNum = NB_num;

	NB_UNUSED(NB_width);

	NB_num = NB_convertSizeUnsgnd(NB_num, NB_size);

	if (NB_num == 0)
		NB_outputBuffer[NB_i--] = '0';

	NB_outputBuffer[NB_BUFF_SIZE - 1] = '\0';

	while (NB_num > 0)
	{
		NB_outputBuffer[NB_i--] = NB_mapTo[NB_num % 16];
		NB_num /= 16;
	}

	if (NB_flags & NB_F_HASH && NB_initNum != 0)
	{
		NB_outputBuffer[NB_i--] = NB_flagCh;
		NB_outputBuffer[NB_i--] = '0';
	}

	NB_i++;

	return (NB_writeUnsgnd(0, NB_i, NB_outputBuffer, NB_flags, NB_width, NB_precision, NB_size));
}
