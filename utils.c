#include "main.h"

/**
 * @brief Checks if a character is printable.
 *
 * @param c The character to evaluate.
 * @return 1 if c is printable, 0 otherwise.
 */
int nb_is_printable(char c)
{
	if (c >= 32 && c < 127)
		return 1;

	return 0;
}

/**
 * @brief Appends ASCII in hexadecimal code to the buffer.
 *
 * @param ascii_code The ASCII code.
 * @param buffer The array of characters.
 * @param i The index at which to start appending.
 * @return Always 3.
 */
int nb_append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return 3;
}

/**
 * @brief Checks if a character is a digit.
 *
 * @param c The character to be evaluated.
 * @return 1 if c is a digit, 0 otherwise.
 */
int nb_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;

	return 0;
}

/**
 * @brief Casts a number to the specified size.
 *
 * @param num The number to be casted.
 * @param size The number indicating the type to be casted.
 * @return The casted value of num.
 */
long int nb_convert_size_number(long int num, int size)
{
	if (size == NB_S_LONG)
		return num;
	else if (size == NB_S_SHORT)
		return (short)num;

	return (int)num;
}

/**
 * @brief Casts a number to the specified size (unsigned).
 *
 * @param num The number to be casted.
 * @param size The number indicating the type to be casted.
 * @return The casted value of num.
 */
long int nb_convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == NB_S_LONG)
		return num;
	else if (size == NB_S_SHORT)
		return (unsigned short)num;

	return (unsigned int)num;
}
