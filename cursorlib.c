#include <stdio.h>

typedef enum Direction{
	RIGHT,
	LEFT,
	AT,
	BETWEEN
} Direction;

//Transversing in the memory to right or left from the 
//given starting adress. Cheacks if the given character exists.
//Gives back the adress of that char.
//If char doesn't exist till the given condition then it ouputs NULL.
char *cursor(char *cursor, char condition, char c, Direction DIR){
	switch(DIR){
		case RIGHT:
			cursor++;
			while(*cursor != condition){
				if(*cursor == c){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor++;
			}
			printf("Cursor at: %c\n", *cursor);
			break;

		case LEFT:
			cursor--;
			while(*cursor != condition){
				if(*cursor == c){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor--;
			}
			printf("Cursor at: %c\n", *cursor);
			break;

		case BETWEEN:
			cursor++;
			while(*cursor != ')'){
				if(*cursor >= condition && *cursor <= c && *cursor != 'x'){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor++;
			}
			printf("Cursor at: %c\n", *cursor);
			break;

		case AT:
			cursor++;
			while(*cursor != ')'){
				if(*cursor == condition || *cursor == c){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor++;
			}
			printf("Cursor at: %c\n", *cursor);
			break;
		default:
			printf("Error!\nThere is no such direction!\n");
			break;
	}	
	return cursor;
}