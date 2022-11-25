#include <stdio.h>
#include "charlib.h"

/* is is in he header file because of redecleration*/
// typedef enum Direction{
// 	RIGHT,
// 	LEFT,
//     FUNCTION
// } Direction;

/*
	Parameters:
	-cursor (from where you want to start)
	-char1 (fist character)
	-char2 (second character)
	-mode (the mode of cursor)
	Output:
	-pointer in the char array to the found char
	Traversing in the char array given the starting address.
	Checks if the given character exists according to mode.
	Gives back the address of that char. If the char doesn’t exits
	it returns the ‘)’ address.
*/
char *cursor(char *cursor, char c1, char c2, char c3, Direction mode){
	switch(mode){
		case RIGHT:
			/*it start searching from the right of where it is
				...+...
					↑→
			*/
			for(cursor++; *cursor != c1 && *cursor != c2 && *cursor != c3 && *cursor != ')'; cursor++);
			//printf("RIGHT: %c\n", cursor[0]);
			return cursor;
			break;
		case LEFT:
			/*it start searching from the right of where it is
				...+...
				 ←↑
			*/
			for(cursor--; *cursor != c1 && *cursor != c2 && *cursor != c3 && *cursor != ')'; cursor--);
			//printf("LEFT: %c\n", *cursor);
			return cursor;
			break;
		case FUNCTION:
			/*
				Until the next ')' checks if the value at 
				curser is between the char values.
			*/
			for(cursor++; *cursor != ')' && !is_small_letter(*cursor, 'x'); cursor++);
			//printf("FUCNTION: %c\n", *cursor);
			return cursor;
			break;
		default:
			printf("Error!\nThere is no such direction!\n");
			break;
	}	
	return cursor;
}