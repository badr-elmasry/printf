#include "main.h"

/**
 * handlePrint - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @index: Index.
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed.
 */
int handlePrint(const char *format, int *index, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknownLen = 0, printedChars = -1;
	FormatType formatTypes[] = {
		{'c', printChar}, {'s', printString}, {'%', printPercent},
		{'i', printInt}, {'d', printInt}, {'b', printBinary},
		{'u', printUnsigned}, {'o', printOctal}, {'x', printHexadecimal},
		{'X', printHexaUpper}, {'p', printPointer}, {'S', printNonPrintable},
		{'r', printReverse}, {'R', printRot13String}, {'\0', NULL}
	};

	for (i = 0; formatTypes[i].format != '\0'; i++)
		if (format[*index] == formatTypes[i].format)
			return (formatTypes[i].function(list, buffer, flags, width, precision, size));

	if (formatTypes[i].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknownLen += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			unknownLen += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		unknownLen += write(1, &format[*index], 1);
		return (unknownLen);
	}
	return (printedChars);
}
