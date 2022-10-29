#include <stdio.h>
#include <math.h>
#include "cursorlib.h"

//chechking if a character is a number
int is_num(char adress){
	if(adress >= '0' && adress <= '9'){
		return 1;
	}
	return 0;
}

//Convert char to 1digit int;
int char_to_int(char c){
	return c-'0';
}

//Creates an integer written as an array of char. 
//It evaluates from right ot left form the given starting point or '.' for decimal
int string_to_int(char *start){
	//to start form a number not th inputed char
	start--;

	//preperation
	int num = 0;
	for(int i=0; is_num(*start); i++, start--){
		num += char_to_int(*start) * pow(10, i);
		*start = 0;
	}

	return num;
}

//Evaualtes the decimal point numbers form '.' to the right.
//Number is given as an array of char.
double string_to_decimal(char *start){
	//put strat to the start of the decimal
	start++;

	//preperation
	double num = 0.0;
	for(int i=1; is_num(*start); i++, start++){
		num += char_to_int(*start) * pow(10, -i);
		*start = 0;
	}

	return num;
}

//converting a char to double
//Takes in the adress of the first or last dig depending on direction
double convert_to_num(char *adress, Direction DIR){
	printf("%c---\n", *adress);
	char *cursor = adress;
	int num = 0;
	double decimal = 0;

	switch(DIR){
		case RIGHT:
			//while finds the '.' int the number
			while(is_num(*cursor)){
				cursor++;
			}
			//find the integer and decimal part of a number from '.'
			if(*cursor =='.'){
				//making the '.' an '\0'
				*cursor = 0;
				num = string_to_int(cursor);
				decimal = string_to_decimal(cursor);
			}else{
				//if there is no '.' it means there is only an integer
				//you start from the end where the courso is right now
				num = string_to_int(cursor);
			}
			
			break;
		case LEFT:
			//while finds the '.' int the number
			while(is_num(*cursor)){
				cursor--;
			}
			//find the integer and decimal part of a number from '.'
			if(*cursor =='.'){
				*cursor = 0;
				num = string_to_int(cursor);
				decimal = string_to_decimal(cursor);
			}else{
				//if there is no '.' it means there is only an integer
				//you strat from the binary operation
				num = string_to_int(adress+1);
				//there is adress+1 because the adress is at the number 
				//and not at the operator
			}
			break;
		default:
			printf("Error!\nThere is no such direction!\n");	
	}

	//add the int and dec parts
	return num+decimal;
}
