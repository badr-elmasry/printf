#include "main.h"

/****************** PRINT POINTER ******************/

/**
 * printPointer - Prints the value of a pointer variable
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int printPointer(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char extraChar = 0, paddingChar = ' ';
	int index = BUFF_SIZE - 2, length = 2, paddingStart = 1; /* length=2, for '0x' */
	unsigned long numAddresses;
	char mapTo[] = "0123456789abcdef";
	void *addresses = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (addresses == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	numAddresses = (unsigned long)addresses;

	while (numAddresses > 0)
	{
		buffer[index--] = mapTo[numAddresses % 16];
		numAddresses /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddingChar = '0';
	if (flags & F_PLUS)
		extraChar = '+', length++;
	else if (flags & F_SPACE)
		extraChar = ' ', length++;

	index++;

	return (writePointer(buffer, index, length,
		width, flags, paddingChar, extraChar, paddingStart));
}

/************************* PRINT NON-PRINTABLE *************************/

/**
 * printNonPrintable - Prints ASCII codes in hexadecimal of non-printable chars
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int printNonPrintable(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (isPrintable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += appendHexaCode(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/************************* PRINT REVERSE *************************/

/**
 * printReverse - Prints a reverse string.
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Numbers of chars printed
 */
int printReverse(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(args, char *);

	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char character = str[i];
		write(1, &character, 1);
		count++;
	}

	return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/

/**
 * printRot13String - Print a string in ROT13.
 * @args: List of arguments
 * @buffer: Buffer array for handling print
 * @flags: Calculate active flags
 * @width: Get width
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Numbers of chars printed
 */
int printRot13String(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";

	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}

		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}

	return (count);
}
