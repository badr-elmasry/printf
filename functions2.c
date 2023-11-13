#include "main.h"

/**
 * nb_print_pointer - Outputs the hexadecimal value of a pointer variable.
 * @nb_args: Variable arguments list.
 * @nb_out_buff: Buffer for output.
 * @nb_format_flags: Active formatting flags.
 * @nb_width: Width specification.
 * @nb_precision: Precision specification.
 * @nb_size: Size specifier.
 * Return: Number of characters printed.
 */
int nb_print_pointer(va_list nb_args, char nb_out_buff[],
	int nb_format_flags, int nb_width, int nb_precision, int nb_size)
{
	char nb_extra_char = 0, nb_padding_char = ' ';
	int nb_index = NB_BUFF_SIZE - 2, nb_length = 2, nb_padding_start = 1;
	unsigned long nb_address;
	char nb_hex_map[] = "0123456789abcdef";
	void *nb_pointer = va_arg(nb_args, void *);

	if (nb_pointer == NULL)
		return (write(1, "(nil)", 5));

	nb_out_buff[NB_BUFF_SIZE - 1] = '\0';
	UNUSED(nb_precision);

	nb_address = (unsigned long)nb_pointer;

	while (nb_address > 0)
	{
		nb_out_buff[nb_index--] = nb_hex_map[nb_address % 16];
		nb_address /= 16;
		nb_length++;
	}

	if ((nb_format_flags & NB_F_ZERO) && !(nb_format_flags & NB_F_MINUS))
		nb_padding_char = '0';

	if (nb_format_flags & NB_F_PLUS)
		nb_extra_char = '+', nb_length++;
	else if (nb_format_flags & NB_F_SPACE)
		nb_extra_char = ' ', nb_length++;

	nb_index++;

	return (write_pointer(nb_out_buff, nb_index, nb_length,
		nb_width, nb_format_flags, nb_padding_char, nb_extra_char, nb_padding_start));
}

/**
 * nb_print_non_printable - Outputs ASCII codes in hex of non-printable characters.
 * @nb_args: Variable arguments list.
 * @nb_out_buff: Buffer for output.
 * @nb_format_flags: Active formatting flags.
 * @nb_width: Width specification.
 * @nb_precision: Precision specification.
 * @nb_size: Size specifier.
 * Return: Number of characters printed.
 */
int nb_print_non_printable(va_list nb_args, char nb_out_buff[],
	int nb_format_flags, int nb_width, int nb_precision, int nb_size)
{
	int nb_i = 0, nb_offset = 0;
	char *nb_str = va_arg(nb_args, char *);

	if (nb_str == NULL)
		return (write(1, "(null)", 6));

	while (nb_str[nb_i] != '\0')
	{
		if (nb_is_printable(nb_str[nb_i]))
			nb_out_buff[nb_i + nb_offset] = nb_str[nb_i];
		else
			nb_offset += nb_append_hexa_code(nb_str[nb_i], nb_out_buff, nb_i + nb_offset);

		nb_i++;
	}

	nb_out_buff[nb_i + nb_offset] = '\0';

	return (write(1, nb_out_buff, nb_i + nb_offset));
}

/**
 * nb_print_reverse - Outputs a reversed string.
 * @nb_args: Variable arguments list.
 * @nb_out_buff: Buffer for output.
 * @nb_format_flags: Active formatting flags.
 * @nb_width: Width specification.
 * @nb_precision: Precision specification.
 * @nb_size: Size specifier.
 * Return: Number of characters printed.
 */
int nb_print_reverse(va_list nb_args, char nb_out_buff[],
	int nb_format_flags, int nb_width, int nb_precision, int nb_size)
{
	char *nb_str;
	int nb_i, nb_count = 0;

	nb_str = va_arg(nb_args, char *);

	if (nb_str == NULL)
	{
		UNUSED(nb_precision);
		nb_str = ")Null(";
	}

	for (nb_i = 0; nb_str[nb_i]; nb_i++)
		;

	for (nb_i = nb_i - 1; nb_i >= 0; nb_i--)
	{
		char nb_character = nb_str[nb_i];
		write(1, &nb_character, 1);
		nb_count++;
	}

	return (nb_count);
}

/**
 * nb_print_rot13string - Outputs a string in ROT13.
 * @nb_args: Variable arguments list.
 * @nb_out_buff: Buffer for output.
 * @nb_format_flags: Active formatting flags.
 * @nb_width: Width specification.
 * @nb_precision: Precision specification.
 * @nb_size: Size specifier.
 * Return: Number of characters printed.
 */
int nb_print_rot13string(va_list nb_args, char nb_out_buff[],
	int nb_format_flags, int nb_width, int nb_precision, int nb_size)
{
	char nb_temp_char;
	char *nb_str;
	unsigned int nb_i, nb_j;
	int nb_count = 0;
	char nb_in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char nb_out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	nb_str = va_arg(nb_args, char *);

	if (nb_str == NULL)
		nb_str = "(AHYY)";

	for (nb_i = 0; nb_str[nb_i]; nb_i++)
	{
		for (nb_j = 0; nb_in[nb_j]; nb_j++)
		{
			if (nb_in[nb_j] == nb_str[nb_i])
			{
				nb_temp_char = nb_out[nb_j];
				write(1, &nb_temp_char, 1);
				nb_count++;
				break;
			}
		}

		if (!nb_in[nb_j])
		{
			nb_temp_char = nb_str[nb_i];
			write(1, &nb_temp_char, 1);
			nb_count++;
		}
	}

	return (nb_count);
}

