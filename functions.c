#include "main.h"

/**
 * nb_print_char - Prints a char
 * @nb_types: List a of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: Width
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_char(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	char nb_char = va_arg(nb_types, int);

	return (nb_handle_write_char(nb_char, nb_output, nb_flags, nb_width, nb_precision, nb_size));
}

/**
 * nb_print_string - Prints a string
 * @nb_types: List a of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width.
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_string(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	int nb_length = 0, nb_i;
	char *nb_str = va_arg(nb_types, char *);

	UNUSED(nb_output);
	UNUSED(nb_flags);
	UNUSED(nb_width);
	UNUSED(nb_precision);
	UNUSED(nb_size);
	if (nb_str == NULL)
	{
		nb_str = "(null)";
		if (nb_precision >= 6)
			nb_str = "      ";
	}

	while (nb_str[nb_length] != '\0')
		nb_length++;

	if (nb_precision >= 0 && nb_precision < nb_length)
		nb_length = nb_precision;

	if (nb_width > nb_length)
	{
		if (nb_flags & NB_F_MINUS)
		{
			write(1, &nb_str[0], nb_length);
			for (nb_i = nb_width - nb_length; nb_i > 0; nb_i--)
				write(1, " ", 1);
			return (nb_width);
		}
		else
		{
			for (nb_i = nb_width - nb_length; nb_i > 0; nb_i--)
				write(1, " ", 1);
			write(1, &nb_str[0], nb_length);
			return (nb_width);
		}
	}

	return (write(1, nb_str, nb_length));
}

/**
 * nb_print_percent - Prints a percent sign
 * @nb_types: List a of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width.
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_percent(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	UNUSED(nb_types);
	UNUSED(nb_output);
	UNUSED(nb_flags);
	UNUSED(nb_width);
	UNUSED(nb_precision);
	UNUSED(nb_size);
	return (write(1, "%%", 1));
}

/**
 * nb_print_int - Print int
 * @nb_types: List a of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width.
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Number of chars printed
 */
int nb_print_int(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	int nb_i = NB_BUFF_SIZE - 2;
	int nb_is_negative = 0;
	long int nb_n = va_arg(nb_types, long int);
	unsigned long int nb_num;

	nb_n = nb_convert_size_number(nb_n, nb_size);

	if (nb_n == 0)
		nb_output[nb_i--] = '0';

	nb_output[NB_BUFF_SIZE - 1] = '\0';
	nb_num = (unsigned long int)nb_n;

	if (nb_n < 0)
	{
		nb_num = (unsigned long int)((-1) * nb_n);
		nb_is_negative = 1;
	}

	while (nb_num > 0)
	{
		nb_output[nb_i--] = (nb_num % 10) + '0';
		nb_num /= 10;
	}

	nb_i++;

	return (nb_write_number(nb_is_negative, nb_i, nb_output, nb_flags, nb_width, nb_precision, nb_size));
}

/**
 * nb_print_binary - Prints an unsigned number
 * @nb_types: List a of arguments
 * @nb_output: Output buffer array to handle print
 * @nb_flags:  Calculates active flags
 * @nb_width: get width.
 * @nb_precision: Precision specification
 * @nb_size: Size specifier
 * Return: Numbers of char printed.
 */
int nb_print_binary(va_list nb_types, char nb_output[],
	int nb_flags, int nb_width, int nb_precision, int nb_size)
{
	unsigned int nb_n, nb_m, nb_i, nb_sum;
	unsigned int nb_a[32];
	int nb_count;

	UNUSED(nb_output);
	UNUSED(nb_flags);
	UNUSED(nb_width);
	UNUSED(nb_precision);
	UNUSED(nb_size);

	nb_n = va_arg(nb_types, unsigned int);
	nb_m = 2147483648; /* (2 ^ 31) */
	nb_a[0] = nb_n / nb_m;
	for (nb_i = 1; nb_i < 32; nb_i++)
	{
		nb_m /= 2;
		nb_a[nb_i] = (nb_n / nb_m) % 2;
	}
	for (nb_i = 0, nb_sum = 0, nb_count = 0; nb_i < 32; nb_i++)
	{
		nb_sum += nb_a[nb_i];
		if (nb_sum || nb_i == 31)
		{
			char nb_z = '0' + nb_a[nb_i];

			write(1, &nb_z, 1);
			nb_count++;
		}
	}
	return (nb_count);
}

