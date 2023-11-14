#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Unleashes the power of printing a pointer variable.
 * @types: A list of arguments eagerly awaiting their turn in the spotlight.
 * @buffer: An artistically crafted array for print handling.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width, carefully chosen for an optimal display.
 * @precision: A precision directive, finely tuned for perfection.
 * @size: A size specifier, tailored to enhance the presentation.
 * Return: A round of applause for the characters gracefully printed.
 */
int print_pointer(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
    unsigned long num_addrs;
    char map_to[] = "0123456789abcdef";
    void *addrs = va_arg(types, void *);

    UNUSED(width);
    UNUSED(size);

    if (addrs == NULL)
        return (write(1, "(nil)", 5));

    buffer[BUFF_SIZE - 1] = '\0';
    UNUSED(precision);

    num_addrs = (unsigned long)addrs;

    while (num_addrs > 0)
    {
        buffer[ind--] = map_to[num_addrs % 16];
        num_addrs /= 16;
        length++;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';
    if (flags & F_PLUS)
        extra_c = '+', length++;
    else if (flags & F_SPACE)
        extra_c = ' ', length++;

    ind++;

    return (write_pointer(buffer, ind, length,
        width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON-PRINTABLE *************************/
/**
 * print_non_printable - Dazzles the audience with the hex codes of non-printable characters.
 * @types: A curated list of arguments.
 * @buffer: An elegantly crafted array for print orchestration.
 * @flags: A choreography of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with finesse.
 * @size: A size specifier, chosen for an optimal display.
 * Return: A standing ovation for the characters gracefully printed.
 */
int print_non_printable(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int i = 0, offset = 0;
    char *str = va_arg(types, char *);

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        return (write(1, "(null)", 6));

    while (str[i] != '\0')
    {
        if (is_printable(str[i]))
            buffer[i + offset] = str[i];
        else
            offset += append_hexa_code(str[i], buffer, i + offset);

        i++;
    }

    buffer[i + offset] = '\0';

    return (write(1, buffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Unleashes the magic of printing a reversed string.
 * @types: A curated list of arguments.
 * @buffer: A canvas meticulously prepared for print orchestration.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with finesse.
 * @size: A size specifier, chosen for an optimal display.
 * Return: A standing ovation for the characters gracefully printed.
 */
int print_reverse(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char *str;
    int i, count = 0;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(size);

    str = va_arg(types, char *);

    if (str == NULL)
    {
        UNUSED(precision);

        str = ")Null(";
    }
    for (i = 0; str[i]; i++)
        ;

    for (i = i - 1; i >= 0; i--)
    {
        char z = str[i];

        write(1, &z, 1);
        count++;
    }
    return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Takes the stage to print a string in ROT13.
 * @types: A curated list of arguments.
 * @buffer: A canvas meticulously prepared for print orchestration.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with finesse.
 * @size: A size specifier, chosen for an optimal display.
 * Return: A standing ovation for the characters gracefully printed.
 */
int print_rot13string(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(types, char *);
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
