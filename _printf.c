#include "main.h"

void NB_print_buffer(char NB_output_buffer[], int *NB_buffer_index);

/**
 * NB_printf - Customized Printf function with special handling.
 * @NB_format: Input format string.
 * Return: Number of characters printed.
 */
int NB_printf(const char *NB_format, ...)
{
    int NB_index, NB_printed_count = 0, NB_total_printed = 0;
    int NB_flags, NB_width, NB_precision, NB_size, NB_buffer_index = 0;
    va_list NB_arguments;
    char NB_output_buffer[NB_BUFF_SIZE];

    if (NB_format == NULL)
        return (-1);

    va_start(NB_arguments, NB_format);

    for (NB_index = 0; NB_format && NB_format[NB_index] != '\0'; NB_index++)
    {
        if (NB_format[NB_index] != '%')
        {
            NB_output_buffer[NB_buffer_index++] = NB_format[NB_index];
            if (NB_buffer_index == NB_BUFF_SIZE)
                NB_print_buffer(NB_output_buffer, &NB_buffer_index);
            NB_total_printed++;
        }
        else
        {
            NB_print_buffer(NB_output_buffer, &NB_buffer_index);
            NB_flags = NB_get_flags(NB_format, &NB_index);
            NB_width = NB_get_width(NB_format, &NB_index, NB_arguments);
            NB_precision = NB_get_precision(NB_format, &NB_index, NB_arguments);
            NB_size = NB_get_size(NB_format, &NB_index);
            ++NB_index;
            NB_printed_count = NB_handle_print(NB_format, &NB_index, NB_arguments, NB_output_buffer,
                                               NB_flags, NB_width, NB_precision, NB_size);
            if (NB_printed_count == -1)
                return (-1);
            NB_total_printed += NB_printed_count;
        }
    }

    NB_print_buffer(NB_output_buffer, &NB_buffer_index);

    va_end(NB_arguments);

    return (NB_total_printed);
}

/**
 * NB_print_buffer - Prints the accumulated content of the output buffer.
 * @NB_output_buffer: Array storing characters to be printed.
 * @NB_buffer_index: Index representing the current length of the buffer.
 */
void NB_print_buffer(char NB_output_buffer[], int *NB_buffer_index)
{
    if (*NB_buffer_index > 0)
        write(1, &NB_output_buffer[0], *NB_buffer_index);

    *NB_buffer_index = 0;
}
