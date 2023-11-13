#include "main.h"

/*
 * nb_sizeEvaluator - Determines the size for typecasting the argument
 * @formatString: String with the argument specifier
 * @index: Index of the argument specifier in the format string
 *
 * Return: The size specifier.
 */
int nb_sizeEvaluator(const char *formatString, int *index) {
    int currentIndex = *index + 1;
    int dataSize = 0;

    // Check for 'l' or 'h' size specifiers
    if (formatString[currentIndex] == 'l')
        dataSize = NB_SIZE_LONG;
    else if (formatString[currentIndex] == 'h')
        dataSize = NB_SIZE_SHORT;

    // Update the index based on the evaluated size
    if (dataSize == 0)
        *index = currentIndex - 1;
    else
        *index = currentIndex;

    return dataSize;
}
