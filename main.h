#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define NB_BUFF_SIZE 1024

/* FLAGS */
#define NB_F_MINUS 1
#define NB_F_PLUS 2
#define NB_F_ZERO 4
#define NB_F_HASH 8
#define NB_F_SPACE 16

/* SIZES */
#define NB_S_LONG 2
#define NB_S_SHORT 1

/**
 * struct NB_fmt - Struct op
 *
 * @NB_fmt: The format.
 * @NB_fn: The function associated.
 */
struct NB_fmt
{
	char NB_fmt;
	int (*NB_fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct NB_fmt NB_fmt_t - Struct op
 *
 * @NB_fmt: The format.
 * @NB_fm_t: The function associated.
 */
typedef struct NB_fmt NB_fmt_t;

int NB_printf(const char *format, ...);
int NB_handlePrint(const char *NB_fmt, int *NB_i,
va_list NB_list, char NB_buffer[], int NB_flags, int NB_width, int NB_precision, int NB_size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int NB_printChar(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printString(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printPercent(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

/* Functions to print numbers */
int NB_printInt(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printBinary(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printUnsigned(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printOctal(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printHexadecimal(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_printHexaUpper(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

int NB_printHexa(va_list types, char map_to[],
char NB_buffer[], int NB_flags, char NB_flagCh, int NB_width, int NB_precision, int NB_size);

/* Function to print non-printable characters */
int NB_printNonPrintable(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

/* Function to print memory address */
int NB_printPointer(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

/* Functions to handle other specifiers */
int NB_getFlags(const char *NB_format, int *NB_i);
int NB_getWidth(const char *NB_format, int *NB_i, va_list NB_list);
int NB_getPrecision(const char *NB_format, int *NB_i, va_list NB_list);
int NB_getSize(const char *NB_format, int *NB_i);

/* Function to print string in reverse */
int NB_printReverse(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

/* Function to print a string in rot 13 */
int NB_printRot13String(va_list types, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

/* Width handler */
int NB_handleWriteChar(char NB_c, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_writeNumber(int NB_isPositive, int NB_ind, char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);
int NB_writeNum(int NB_ind, char NB_bff[], int NB_flags, int NB_width, int NB_precision,
	int NB_length, char NB_padd, char NB_extraC);
int NB_writePointer(char NB_buffer[], int NB_ind, int NB_length,
	int NB_width, int NB_flags, char NB_padd, char NB_extraC, int NB_paddStart);
int NB_writeUnsgnd(int NB_isNegative, int NB_ind,
char NB_buffer[],
	int NB_flags, int NB_width, int NB_precision, int NB_size);

/****************** UTILS ******************/
int NB_isPrintable(char);
int NB_appendHexaCode(char, char[], int);
int NB_isDigit(char);

long int NB_convertSizeNumber(long int num, int NB_size);
long int NB_convertSizeUnsgnd(unsigned long int num, int NB_size);

#endif /* MAIN_H */
