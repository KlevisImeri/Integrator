#ifndef cursorlib
#define cursorlib

#include <stdio.h>

typedef enum Direction{
	RIGHT,
	LEFT,
    FUNCTION
} Direction;
char *cursor(char *cursor, char c1, char c2, char c3, Direction mode);

#endif