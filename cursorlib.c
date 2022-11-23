#include <stdio.h>

typedef enum Direction{
	RIGHT,
	LEFT,
	AT,
	ATX,
	BETWEEN
} Direction;

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
char *cursor(char *cursor, char char1, char char2, Direction mode){
	char char3 = 'x';
	switch(mode){
		case RIGHT:
			/*it start searching from the right of where it is
				...+...
					↑→
			*/
			for(cursor++; *cursor != char2; cursor++){
				if(*cursor == char1){
					// printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
			}
			// printf("Cursor didn't found %c\n", char1);
			// printf("Cursot at: %c\n", *cursor);
			return cursor;
			break;

		case LEFT:
			/*it start searching from the right of where it is
				...+...
				 ←↑
			*/
			for(cursor--; *cursor != char2; cursor--){
				if(*cursor == char1){
					// printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
			}
			// printf("Cursor didn't found %c\n", char1);
			// printf("Cursot at: %c\n", *cursor);
			return cursor;
			break;

		case BETWEEN:
			/*
				Until the next ')' checks if the value at 
				curser is between the char values.
			*/
			for(cursor++; *cursor != ')'; cursor++){
				if(*cursor >= char1 && *cursor <= char2 && *cursor != 'x'){
					// printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
			}
			// printf("No char such that %c=<c<=%c\n", char1, char2);
			// printf("Cursot at: %c\n", *cursor);
			return cursor;
			break;

		case AT:
			/*
				Until the next ')' checks if the value at 
				courser is one of the char values.
			*/
			for(cursor++; *cursor != ')'; cursor++){
				if(*cursor == char1 || *cursor == char2){
					// printf("Cursor at: %c\n", *cursor);
					return cursor;
				} 
			}
			// printf("No char such that c=%c or c=%c\n", char1, char2);
			// printf("Cursor at: %c\n", *cursor);
			return cursor;
			break;
		case ATX:
			
			for(cursor++; *cursor != ')'; cursor++){
				if(*cursor == char1 ||*cursor == char2 || *cursor == char3){
					// printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
			}
			return cursor;
			break;
		default:
			printf("Error!\nThere is no such direction!\n");
			break;
	}	
	return cursor;
}