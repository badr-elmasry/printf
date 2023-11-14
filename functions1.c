#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/

/**
 * printUnsigned - Prints an unsigned number
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int printUnsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = convertSizeUnsigned(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (writeUnsigned(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/

/**
 * printOctal - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int printOctal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int initNum = num;

	UNUSED(width);

	num = convertSizeUnsigned(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && initNum != 0)
		buffer[i--] = '0';

	i++;

	return (writeUnsigned(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/

/**
 * printHexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int printHexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHex(args, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/

/**
 * printHexadecimalUpper - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int printHexadecimalUpper(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHex(args, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEX NUM IN LOWER OR UPPER **************/

/**
 * printHex - Prints a hexadecimal number in lower or upper
 * @args: List of arguments
 * @mapTo: Array of values to map the number to
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @flagCh: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int printHex(va_list args, char mapTo[], char buffer[],
	int flags, char flagCh, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int initNum = num;

	UNUSED(width);

	num = convertSizeUnsigned(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = mapTo[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && initNum != 0)
	{
		buffer[i--] = flagCh;
		buffer[i--] = '0';
	}

	i++;

	return (writeUnsigned(0, i, buffer, flags, width, precision, size));
}
