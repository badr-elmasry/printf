#include "main.h"

/**
 * nb_print_unsigned - Prints an unsigned number
 * @nb_types: List a of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed.
 */
int nb_print_unsigned(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	int nb_i = NB_BUFF_SIZE - 2;
	unsigned long int nb_num = va_arg(nb_types, unsigned long int);

	nb_num = nb_convert_size_unsgnd(nb_num, nb_size);

	if (nb_num == 0)
		nb_output[nb_i--] = '0';

	nb_output[NB_BUFF_SIZE - 1] = '\0';

	while (nb_num > 0)
	{
		nb_output[nb_i--] = (nb_num % 10) + '0';
		nb_num /= 10;
	}

	nb_i++;

	return (nb_write_unsgnd(0, nb_i, nb_output, nb_flags, nb_width, nb_precision, nb_size));
}

/**
 * nb_print_octal - Prints an unsigned number in octal notation
 * @nb_types: Lista of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_octal(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	int nb_i = NB_BUFF_SIZE - 2;
	unsigned long int nb_num = va_arg(nb_types, unsigned long int);
	unsigned long int nb_init_num = nb_num;

	UNUSED(nb_width);

	nb_num = nb_convert_size_unsgnd(nb_num, nb_size);

	if (nb_num == 0)
		nb_output[nb_i--] = '0';

	nb_output[NB_BUFF_SIZE - 1] = '\0';

	while (nb_num > 0)
	{
		nb_output[nb_i--] = (nb_num % 8) + '0';
		nb_num /= 8;
	}

	if (nb_flags & NB_F_HASH && nb_init_num != 0)
		nb_output[nb_i--] = '0';

	nb_i++;

	return (nb_write_unsgnd(0, nb_i, nb_output, nb_flags, nb_width, nb_precision, nb_size));
}

/**
 * nb_print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @nb_types: Lista of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_hexadecimal(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	return (nb_print_hexa(nb_types, "0123456789abcdef", nb_output,
		nb_flags, 'x', nb_width, nb_precision, nb_size));
}

/**
 * nb_print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @nb_types: Lista of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_hexa_upper(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	return (nb_print_hexa(nb_types, "0123456789ABCDEF", nb_output,
		nb_flags, 'X', nb_width, nb_precision, nb_size));
}

/**
 * nb_print_hexa - Prints a hexadecimal number in lower or upper
 * @nb_types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_flag_ch: Calculates active flags
 * @nb_width: get width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * @nb_size: Size specification
 * Return: Number of chars printed
 */
int nb_print_hexa(va_list nb_types, char map_to[], char nb_output[],
	int nb_flags, char nb_flag_ch, int nb_width, int nb_precision, int nb_size)
{
	int nb_i = NB_BUFF_SIZE - 2;
	unsigned long int nb_num = va_arg(nb_types, unsigned long int);
	unsigned long int nb_init_num = nb_num;

	UNUSED(nb_width);

	nb_num = nb_convert_size_unsgnd(nb_num, nb_size);

	if (nb_num == 0)
		nb_output[nb_i--] = '0';

	nb_output[NB_BUFF_SIZE - 1] = '\0';

	while (nb_num > 0)
	{
		nb_output[nb_i--] = map_to[nb_num % 16];
		nb_num /= 16;
	}

	if (nb_flags & NB_F_HASH && nb_init_num != 0)
	{
		nb_output[nb_i--] = nb_flag_ch;
		nb_output[nb_i--] = '0';
	}

	nb_i++;

	return (nb_write_unsgnd(0, nb_i, nb_output, nb_flags, nb_width, nb_precision, nb_size));
}

