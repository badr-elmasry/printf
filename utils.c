#include "main.h"

/**
 * isPrintable - Evaluates if a char is printable
 * @character: Char to be evaluated.
 *
 * Return: 1 if character is printable, 0 otherwise
 */
int isPrintable(char character)
{
	if (character >= 32 && character < 127)
		return 1;

	return 0;
}

/**
 * appendHexaCode - Append ASCII in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @index: Index at which to start appending.
 * @asciiCode: ASCII CODE.
 * Return: Always 3
 */
int appendHexaCode(char asciiCode, char buffer[], int index)
{
	char mapTo[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */
	if (asciiCode < 0)
		asciiCode *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = mapTo[asciiCode / 16];
	buffer[index] = mapTo[asciiCode % 16];

	return 3;
}

/**
 * isDigit - Verifies if a char is a digit
 * @character: Char to be evaluated
 *
 * Return: 1 if character is a digit, 0 otherwise
 */
int isDigit(char character)
{
	if (character >= '0' && character <= '9')
		return 1;

	return 0;
}

/**
 * convertSizeNumber - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number
 */
long int convertSizeNumber(long int number, int size)
{
	if (size == S_LONG)
		return number;
	else if (size == S_SHORT)
		return (short)number;

	return (int)number;
}

/**
 * convertSizeUnsigned - Casts a number to the specified size
 * @number: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convertSizeUnsigned(unsigned long int number, int size)
{
	if (size == S_LONG)
		return number;
	else if (size == S_SHORT)
		return (unsigned short)number;

	return (unsigned int)number;
}
