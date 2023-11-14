#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS  (1 << 0)
#define F_PLUS   (1 << 1)
#define F_ZERO   (1 << 2)
#define F_HASH   (1 << 3)
#define F_SPACE  (1 << 4)

/* SIZES */
#define S_LONG   (1 << 0)
#define S_SHORT  (1 << 1)

/**
 * struct fmt - Struct to represent a format specifier and its associated function.
 * @fmt: The format specifier character.
 * @fn: The function associated with the format specifier.
 */
struct fmt
{
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef fmt_t - Typedef for struct fmt.
 * @fmt: The format specifier character.
 * @fn: The function associated with the format specifier.
 */
typedef struct fmt fmt_t;

/**
 * _printf - Custom printf function that supports various format specifiers.
 * @format: The formatted string containing format specifiers.
 * @...: Variable number of arguments corresponding to the format specifiers.
 *
 * Return: The number of characters printed (excluding null byte).
 */
int _printf(const char *format, ...);

/**
 * handle_print - Handles the printing of arguments based on their format specifier.
 * @fmt: The formatted string guiding the printing.
 * @ind: The index of the current character in the format string.
 * @list: The list of arguments.
 * @buffer: The buffer array to handle print.
 * @flags: Active flags influencing the printing.
 * @width: The width specifier for formatting.
 * @precision: The precision specifier for formatting.
 * @size: The size specifier for casting.
 *
 * Return: The number of characters printed.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
                  int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Functions to print chars and strings */
int print_char(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_to[], char buffer[],
               int flags, char flag_ch, int width, int precision, int size);

/* Function to print non-printable characters */
int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function to print memory address */
int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/* Function to print string in reverse */
int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function to print a string in ROT13 */
int print_rot13string(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Width handler */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision, int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
