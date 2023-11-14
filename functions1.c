#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Embarks on the adventure of printing an unsigned number.
 * @types: A list of arguments awaiting their moment in the spotlight.
 * @buffer: An artfully crafted array for handling the print.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width to enhance the presentation.
 * @precision: A precision directive, carefully chosen.
 * @size: A size specifier, tailor-made for the occasion.
 * Return: A standing ovation for the number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int i = BUFF_SIZE - 2;
    unsigned long int num = va_arg(types, unsigned long int);

    num = convert_size_unsgnd(num, size);

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Unveils the artistry of printing an unsigned octal number.
 * @types: A curated list of arguments.
 * @buffer: An elegant array designed for print orchestration.
 * @flags: A choreography of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with finesse.
 * @size: A size specifier, chosen for optimum impact.
 * Return: A round of applause for the characters gracefully printed.
 */
int print_octal(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{

    int i = BUFF_SIZE - 2;
    unsigned long int num = va_arg(types, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(width);

    num = convert_size_unsgnd(num, size);

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[i--] = (num % 8) + '0';
        num /= 8;
    }

    if (flags & F_HASH && init_num != 0)
        buffer[i--] = '0';

    i++;

    return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Captures the essence of printing an unsigned hexadecimal number.
 * @types: A carefully selected list of arguments.
 * @buffer: A canvas meticulously prepared for print orchestration.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with precision.
 * @size: A size specifier, chosen for optimal impact.
 * Return: A resounding applause for the characters skillfully printed.
 */
int print_hexadecimal(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    return (print_hexa(types, "0123456789abcdef", buffer,
        flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Embodies the elegance of printing an unsigned uppercase hexadecimal number.
 * @types: A carefully selected list of arguments.
 * @buffer: A canvas meticulously prepared for print orchestration.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with precision.
 * @size: A size specifier, chosen for optimal impact.
 * Return: A standing ovation for the characters gracefully printed.
 */
int print_hexa_upper(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    return (print_hexa(types, "0123456789ABCDEF", buffer,
        flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Embarks on a journey to print a hexadecimal number, either in lower or upper case.
 * @types: A curated list of arguments.
 * @map_to: An array of values to map the number to.
 * @buffer: An elegantly crafted array for print orchestration.
 * @flags: A choreography of calculated active flags.
 * @flag_ch: A flag character indicating the chosen case (lower or upper).
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with precision.
 * @size: A size specifier, chosen for optimal impact.
 * Return: A standing ovation for the characters gracefully printed.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
    int flags, char flag_ch, int width, int precision, int size)
{
    int i = BUFF_SIZE - 2;
    unsigned long int num = va_arg(types, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(width);

    num = convert_size_unsgnd(num, size);

    if (num == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[i--] = map_to[num % 16];
        num /= 16;
    }

    if (flags & F_HASH && init_num != 0)
    {
        buffer[i--] = flag_ch;
        buffer[i--] = '0';
    }

    i++;

    return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
