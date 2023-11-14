#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)

#define NB_BUFF_SIZE 1024 

/* FLAGS */
#define NB_MINUS 1
#define NB_PLUS 2
#define NB_ZERO 4
#define NB_HASH 8
#define NB_SPACE 16

/* SIZES */
#define NB_LONG 2
#define NB_SHORT 1

/*  
 * struct fmt - Format specifier struct
 * @fmt: The format char
 * @fn: Associated function
*/
struct fmt {
  char fmt;
  int (*fn)(va_list, char[], int, int, int, int);
};

/*
 * typedef struct fmt fmt_t - Format specifier type
 * @fmt: The format char
 * @fm_t: Associated function
*/
typedef struct fmt fmt_t;

/* Main print function */
int nb_print_formatted(const char *format, ...);

/* Handle printing based on specifier */
int nb_handle_print(const char *fmt, int *index, va_list args, 
                    char buffer[], int flags, int width, int precision, int size);

/*** PRINT FUNCTIONS ***/

/* Print characters and strings */
int nb_print_char(va_list args, char buffer[], 
                  int flags, int width, int precision, int size);

int nb_print_string(va_list args, char buffer[],
                    int flags, int width, int precision, int size);

int nb_print_percent(va_list args, char buffer[],
                     int flags, int width, int precision, int size);

/* Print numbers */                   
int nb_print_int(va_list args, char buffer[],
                 int flags, int width, int precision, int size);

int nb_print_binary(va_list args, char buffer[],
                    int flags, int width, int precision, int size);

int nb_print_unsigned(va_list args, char buffer[],
                      int flags, int width, int precision, int size);

int nb_print_octal(va_list args, char buffer[],
                   int flags, int width, int precision, int size);
                   
int nb_print_hex(va_list args, char buffer[],
                 int flags, int width, int precision, int size);

int nb_print_hex_upper(va_list args, char buffer[],
                       int flags, int width, int precision, int size);                      

int nb_print_hexa(va_list args, char map[], char buffer[],
                  int flags, char flag, int width, int precision, int size);
                  
/* Print non-printables */                  
int nb_print_non_printable(va_list args, char buffer[],
                           int flags, int width, int precision, int size);
                           
/* Print pointer */
int nb_print_pointer(va_list args, char buffer[],
                     int flags, int width, int precision, int size);
                     
/*** HANDLE SPECIFIERS ***/

/* Get flags */                    
int nb_get_flags(const char *format, int *index);

/* Get width */
int nb_get_width(const char *format, int *index, va_list args);

/* Get precision */
int nb_get_precision(const char *format, int *index, va_list args);

/* Get size */
int nb_get_size(const char *format, int *index);  

/* Print reverse string */
int nb_print_reverse(va_list args, char buffer[],
                     int flags, int width, int precision, int size);
                     
/* Print rot13 string */                      
int nb_print_rot13(va_list args, char buffer[],
                   int flags, int width, int precision, int size);
                   
/*** WRITE HANDLERS ***/                   

/* Handle write char */
int nb_handle_write_char(char c, char buffer[],
                         int flags, int width, int precision, int size);
                         
/* Handle write number */  
int nb_write_number(int is_positive, int index, char buffer[],
                    int flags, int width, int precision, int size);
                    
/* Handle write unsigned number */
int nb_write_unsigned(int is_negative, int index, 
                      char buffer[], int flags, int width, 
                      int precision, int size);
                      
/* Handle write pointer */                      
int nb_write_pointer(char buffer[], int index, int length,
                     int width, int flags, char padding, char extra, 
                     int padding_start);
                     
/*** UTILS ***/

/* Check if char is printable */
int nb_is_printable(char c);

/* Append hex code to buffer */
int nb_append_hexa_code(char c, char buffer[], int index);

/* Check if char is digit */
int nb_is_digit(char c);

/* Convert number to specified size */
long int nb_convert_size(long int num, int size); 

/* Convert unsigned number to size */
unsigned long int nb_convert_size_unsigned(unsigned long int num, int size);

#endif /* MAIN_H */
