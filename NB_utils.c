#include "main.h"

/**
 * NB_isPrintable - Checks if a character is printable
 * @NB_c: Character to be evaluated.
 *
 * Return: 1 if NB_c is printable, 0 otherwise
 */
int NB_isPrintable(char NB_c)
{
	if (NB_c >= 32 && NB_c < 127)
		return (1);

	return (0);
}

/**
 * NB_appendHexaCode - Appends ASCII in hexadecimal code to buffer
 * @NB_buffer: Array of characters.
 * @NB_i: Index at which to start appending.
 * @NB_asciiCode: ASCII code.
 * Return: Always 3
 */
int NB_appendHexaCode(char NB_asciiCode, char NB_buffer[], int NB_i)
{
	char NB_mapTo[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */
	if (NB_asciiCode < 0)
		NB_asciiCode *= -1;

	NB_buffer[NB_i++] = '\\';
	NB_buffer[NB_i++] = 'x';

	NB_buffer[NB_i++] = NB_mapTo[NB_asciiCode / 16];
	NB_buffer[NB_i] = NB_mapTo[NB_asciiCode % 16];

	return (3);
}

/**
 * NB_isDigit - Checks if a character is a digit
 * @NB_c: Character to be evaluated
 *
 * Return: 1 if NB_c is a digit, 0 otherwise
 */
int NB_isDigit(char NB_c)
{
	if (NB_c >= '0' && NB_c <= '9')
		return (1);

	return (0);
}

/**
 * NB_convertSizeNumber - Casts a number to the specified size
 * @NB_num: Number to be casted.
 * @NB_size: Number indicating the type to be casted.
 *
 * Return: Casted value of NB_num
 */
long int NB_convertSizeNumber(long int NB_num, int NB_size)
{
	if (NB_size == NB_S_LONG)
		return (NB_num);
	else if (NB_size == NB_S_SHORT)
		return ((short)NB_num);

	return ((int)NB_num);
}

/**
 * NB_convertSizeUnsigned - Casts an unsigned number to the specified size
 * @NB_num: Number to be casted.
 * @NB_size: Number indicating the type to be casted.
 *
 * Return: Casted value of NB_num
 */
unsigned long int NB_convertSizeUnsigned(unsigned long int NB_num, int NB_size)
{
	if (NB_size == NB_S_LONG)
		return (NB_num);
	else if (NB_size == NB_S_SHORT)
		return ((unsigned short)NB_num);

	return ((unsigned int)NB_num);
}
