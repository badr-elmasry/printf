#include "main.h"

/************************* CHAR PRINTING FUNCTION *************************/

/**
 * print_char - Delicately manages the printing of a single character.
 * @types: Assorted arguments list.
 * @buffer: Skillfully crafted array for print management.
 * @flags: Ingeniously calculates and applies active flags.
 * @width: Width specification, tailored for perfection.
 * @precision: Precision directive, fine-tuned to exquisite detail.
 * @size: A size specifier, carefully chosen for optimal performance.
 * Return: An artful count of characters printed.
 */
int print_char(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char c = va_arg(types, int);

    return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* STRING PRINTING FUNCTION *************************/
/**
 * print_string - Orchestrates the eloquent printing of a string.
 * @types: A curated list of arguments.
 * @buffer: An intricately designed array for print orchestration.
 * @flags: Crafts and applies calculated active flags with finesse.
 * @width: Width specification, tailored for visual perfection.
 * @precision: Precision directive, finely tuned for visual harmony.
 * @size: A carefully selected size specifier for optimal presentation.
 * Return: A symphony of characters artfully printed.
 */
int print_string(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int length = 0, i;
    char *str = va_arg(types, char *);

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    /* Maestro, please direct the performance! */
    if (str == NULL)
    {
        str = "(null)";
        if (precision >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (precision >= 0 && precision < length)
        length = precision;

    if (width > length)
    {
        if (flags & F_MINUS)
        {
            write(1, &str[0], length);
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            return (width);
        }
        else
        {
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (width);
        }
    }

    return (write(1, str, length));
}

/************************* PERCENT SIGN PRINTING FUNCTION *************************/
/**
 * print_percent - Renders the perfect printing of a percent sign.
 * @types: A list of arguments awaiting the spotlight.
 * @buffer: A canvas carefully prepared for print mastery.
 * @flags: A choreography of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, meticulously chosen.
 * @size: A size specifier, tailored for visual impact.
 * Return: The applause-worthy count of characters printed.
 */
int print_percent(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    UNUSED(types);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    return (write(1, "%%", 1));
}

/************************* INTEGER PRINTING FUNCTION *************************/
/**
 * print_int - Showcases the mastery of printing an integer.
 * @types: A lineup of arguments awaiting their grand entrance.
 * @buffer: A canvas where print artistry unfolds.
 * @flags: A symphony of calculated active flags.
 * @width: A width specification, finely tuned.
 * @precision: A precision directive, crafted with precision.
 * @size: A size specifier, chosen for optimum impact.
 * Return: An impressive count of characters expertly printed.
 */
int print_int(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    int i = BUFF_SIZE - 2;
    int is_negative = 0;
    long int n = va_arg(types, long int);
    unsigned long int num;

    n = convert_size_number(n, size);

    if (n == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0)
    {
        num = (unsigned long int)((-1) * n);
        is_negative = 1;
    }

    while (num > 0)
    {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* BINARY PRINTING FUNCTION *************************/
/**
 * print_binary - Conducts a majestic performance of printing an unsigned binary number.
 * @types: A distinguished list of arguments awaiting their grand performance.
 * @buffer: A canvas meticulously prepared for print orchestration.
 * @flags: A symphony of calculated active flags.
 * @width: A visual width, set with precision.
 * @precision: A precision directive, crafted with precision.
 * @size: A size specifier, chosen for optimum impact.
 * Return: A resounding applause for the number of characters printed.
 */
int print_binary(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    unsigned int n, m, i, sum;
    unsigned int a[32];
    int count;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    n = va_arg(types, unsigned int);
    m = 2147483648; /* (2 ^ 31) */
    a[0] = n / m;

    for (i = 1; i < 32; i++)
    {
        m /= 2;
        a[i] = (n / m) % 2;
    }

    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += a[i];
        if (sum || i == 31)
        {
            char z = '0' + a[i];
            write(1, &z, 1);
            count++;
        }
    }

    return (count);
}
