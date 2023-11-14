#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>  
#include <unistd.h>

#define IGNORE(x) (void)(x)

#define BUFFER_SIZE 1024

/* FLAGS */  
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* SIZES */
#define SIZE_LONG 2
#define SIZE_SHORT 1

/*  
* Struct fmt_s - Format struct
*
* @fmt_char: The format character. 
* @fmt_fn: The associated print function.
*/

struct fmt_s {
  char fmt_char;
  int (*fmt_fn)(va_list, char[], int, int, int, int);
};

/*
* Typedef struct fmt_s - Format struct typedef 
*
* @fmt_s: The format struct type.
*/

typedef struct fmt_s fmt_t;

int _printf(const char *format, ...);

int handle_print(const char *format, int i, va_list arg_list,
                 char buffer[], int flags, int width,  
                 int precision, int size);

/* Functions to print chars and strings */

int print_char(va_list arg_list, char buffer[],
               int flags, int width, int precision, int size);
               
int print_string(va_list arg_list, char buffer[],  
                 int flags, int width, int precision, int size);
                 
int print_percent(va_list arg_list, char buffer[],
                  int flags, int width, int precision, int size);
                  
/* Functions to print numbers */                   

int print_int(va_list arg_list, char buffer[],
              int flags, int width, int precision, int size);
              
int print_binary(va_list arg_list, char buffer[],
                 int flags, int width, int precision, int size);
                 
int print_unsigned(va_list arg_list, char buffer[],
                   int flags, int width, int precision, int size);
                   
int print_octal(va_list arg_list, char buffer[],
                int flags, int width, int precision, int size);
                
int print_hex(va_list arg_list, char buffer[],  
              int flags, int width, int precision, int size);
              
int print_hex_upper(va_list arg_list, char buffer[],
                    int flags, int width, int precision, int size);
                    
int print_hex(va_list arg_list, char map_to[], char buffer[],
              int flags, char flag_char, int width, 
              int precision, int size);

/* Function to print non-printable characters */ 

int print_non_printable(va_list arg_list, char buffer[],
                        int flags, int width, int precision, int size);
                        
/* Function to print memory address */                         
                        
int print_pointer(va_list arg_list, char buffer[],
                  int flags, int width, int precision, int size);
                  
/* Functions to handle other specifiers */
                   
int get_flags(const char *format, int i);

int get_width(const char *format, int i, va_list arg_list);

int get_precision(const char *format, int i, va_list arg_list);

int get_size(const char *format, int i);

/* Function to print string in reverse */  

int print_reverse(va_list arg_list, char buffer[],
                  int flags, int width, int precision, int size);
                  
/* Function to print a string in rot13 */                   

int print_rot13(va_list arg_list, char buffer[],
                int flags, int width, int precision, int size);
                
/* Width handler */                
                
int handle_write_char(char c, char buffer[],  
                      int flags, int width, int precision, int size);
                      
int write_number(int is_positive, int idx, char buffer[],
                 int flags, int width, int precision, int size);
                 
int write_num(int idx, char buffer[], int flags, int width,
              int precision, int length, char padding, char extra);
              
int write_pointer(char buffer[], int idx, int length,
                  int width, int flags, char padding, 
                  char extra, int pad_start);
                  
int write_unsigned(int is_negative, int idx, char buffer[],
                   int flags, int width, int precision, int size);
                   
/* Utilities */                    

int is_printable(char c);  

int append_hex(char n, char buffer[], int idx);

int is_digit(char c);

long int convert_size_number(long int num, int size);  

unsigned long int convert_size_unsigned(unsigned long int num, int size);

#endif /* MAIN_H */
