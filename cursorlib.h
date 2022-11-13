#ifndef cursorlib
#define cursorlib

#include <stdio.h>

typedef enum Direction{
	RIGHT,
	LEFT,
	AT,
	ATX,
	BETWEEN
} Direction;
char *cursor(char *cursor, char char1, char char2, Direction mode);

#endif