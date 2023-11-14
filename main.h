#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handlePrint(const char *fmt, int *i,
                va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Functions to print chars and strings */
int printChar(va_list types, char buffer[],
              int flags, int width, int precision, int size);
int printString(va_list types, char buffer[],
                int flags, int width, int precision, int size);
int printPercent(va_list types, char buffer[],
                 int flags, int width, int precision, int size);

/* Functions to print numbers */
int printInt(va_list types, char buffer[],
             int flags, int width, int precision, int size);
int printBinary(va_list types, char buffer[],
                int flags, int width, int precision, int size);
int printUnsigned(va_list types, char buffer[],
                  int flags, int width, int precision, int size);
int printOctal(va_list types, char buffer[],
               int flags, int width, int precision, int size);
int printHexadecimal(va_list types, char buffer[],
                     int flags, int width, int precision, int size);
int printHexaUpper(va_list types, char buffer[],
                   int flags, int width, int precision, int size);

int printHexa(va_list types, char map_to[],
              char buffer[], int flags, char flagCh, int width, int precision, int size);

/* Function to print non-printable characters */
int printNonPrintable(va_list types, char buffer[],
                      int flags, int width, int precision, int size);

/* Function to print memory address */
int printPointer(va_list types, char buffer[],
                 int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int getFlags(const char *format, int *i);
int getWidth(const char *format, int *i, va_list list);
int getPrecision(const char *format, int *i, va_list list);
int getSize(const char *format, int *i);

/* Function to print string in reverse */
int printReverse(va_list types, char buffer[],
                 int flags, int width, int precision, int size);

/* Function to print a string in rot13 */
int printRot13String(va_list types, char buffer[],
                     int flags, int width, int precision, int size);

/* Width handler */
int handleWriteChar(char c, char buffer[],
                    int flags, int width, int precision, int size);
int writeNumber(int isPositive, int ind, char buffer[],
                int flags, int width, int precision, int size);
int writeNum(int ind, char bff[], int flags, int width, int precision,
             int length, char padd, char extraC);
int writePointer(char buffer[], int ind, int length,
                 int width, int flags, char padd, char extraC, int paddStart);

int writeUnsigned(int isNegative, int ind,
                  char buffer[],
                  int flags, int width, int precision, int size);

/****************** UTILS ******************/
int isPrintable(char);
int appendHexaCode(char, char[], int);
int isDigit(char);

long int convertSizeNumber(long int num, int size);
long int convertSizeUnsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
