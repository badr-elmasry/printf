#include "main.h"

/**
 * NB_handlePrint - Prints an argument based on its type
 * @NB_fmt: Formatted string in which to print the arguments
 * @NB_ind: Index of the current character in the format string
 * @NB_list: List of arguments to be printed
 * @NB_buffer: Buffer array to handle print
 * @NB_flags: Active flags for formatting
 * @NB_width: Width specification
 * @NB_precision: Precision specification
 * @NB_size: Size specifier
 * Return: Number of characters printed or -1 for unknown format
 */
int NB_handlePrint(const char *NB_fmt, int *NB_ind, va_list NB_list, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size)
{
	int NB_i, NB_unknownLen = 0, NB_printedChars = -1;

	/* List of format types and their corresponding functions */
	NB_fmt_t NB_fmtTypes[] = {
		{'c', NB_printChar}, {'s', NB_printString}, {'%', NB_printPercent},
		{'i', NB_printInt}, {'d', NB_printInt}, {'b', NB_printBinary},
		{'u', NB_printUnsigned}, {'o', NB_printOctal}, {'x', NB_printHexadecimal},
		{'X', NB_printHexaUpper}, {'p', NB_printPointer}, {'S', NB_printNonPrintable},
		{'r', NB_printReverse}, {'R', NB_printRot13String}, {'\0', NULL}
	};

	/* Loop through the format types and call the corresponding function */
	for (NB_i = 0; NB_fmtTypes[NB_i].NB_fmt != '\0'; NB_i++)
	{
		if (NB_fmt[*NB_ind] == NB_fmtTypes[NB_i].NB_fmt)
			return (NB_fmtTypes[NB_i].NB_fn(NB_list, NB_buffer, NB_flags, NB_width, NB_precision, NB_size));
	}

	/* Check for unknown format */
	if (NB_fmtTypes[NB_i].NB_fmt == '\0')
	{
		if (NB_fmt[*NB_ind] == '\0')
			return (-1);

		/* Print '%' character */
		NB_unknownLen += write(1, "%%", 1);

		/* Handle space character or width */
		if (NB_fmt[*NB_ind - 1] == ' ')
			NB_unknownLen += write(1, " ", 1);
		else if (NB_width)
		{
			--(*NB_ind);
			while (NB_fmt[*NB_ind] != ' ' && NB_fmt[*NB_ind] != '%')
				--(*NB_ind);
			if (NB_fmt[*NB_ind] == ' ')
				--(*NB_ind);
			return (1);
		}

		/* Print the unknown character */
		NB_unknownLen += write(1, &NB_fmt[*NB_ind], 1);

		return (NB_unknownLen);
	}

	return (NB_printedChars);
}
