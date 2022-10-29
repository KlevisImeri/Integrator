#ifndef cursorlib
#define cursorlib

#include <stdio.h>

typedef enum Direction{
	RIGHT,
	LEFT,
	AT,
	BETWEEN
} Direction;
char *cursor(char *cursor, char condition, char c, Direction DIR);

#endif