#include <stdio.h>
// int size_of_array = 6;
// char char_input = '';
// int real_index = 0;

//defining the type of tokens we can have
typedef enum Token_type{
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,
    NEGATE,
    ID,
    INTEGER
} Token_type;

//creating a structure of a token
typedef struct Token{
    Token_type type;
    int value;
} Token;

//cheach if the char is valid Number input
int isNumber(char c){
    //!we need to check if this works
    return  c>47 && c<58;
}
//print array;
void print_array(char* c, int size){
    for(int i=0; i<size; i++){
        printf("[%d]{%d}  ", i, c[i]);
    }
    printf("\n");
}

//makes string to int
//!use a pointer!
//break tealls you the lenght of the nubmer
int string_to_int(char* c, int size, int length){
    // print_array(c, 10);
    int number = 0;
    // printf("length: %d\n", length);
    for(int i=0; i<length; i++){
        number += (c[i]-'0')*((length-1)*10);
        // printf("number: %d\n", number);
        length--;
    }
    number += (c[length]-'0');
    return number;
}

//prits the TOKENS beautifully;
void printf_Tokens(Token tokens[]){
    for(int i=0; i<10; i++){
        printf("[%d]{%d,%d}\n", i, tokens[i].type, tokens[i].value);
    }
}

//array to save the tokens !for the moment we put a big number and inicate 0!
 //we need to chech if it inicialzing all to 0;

//turns the string of expression to tokens
void make_token(char* input_str, int size_of_array, Token* output_tokens){p

    int index = 0;
    int tokens_index =0;
    while(index <  size_of_array){
        Token token ={0};
        switch(input_str[index]){
            case ' ':
                printf("I am a space at %d\n", index);
                index++;
                break;
            case '+':
                token.type = ADD;
                token.value = '+';
                //!this should not be at that index! we ned it at the read_index 
                //in c arrays are not dynamic you cannot use push().
                output_tokens[tokens_index]= token;
                index++;
                tokens_index++;
                break;
            case '-':
                token.type = SUBSTRACT;
                token.value = '-';
                output_tokens[tokens_index]= token;
                index++;
                tokens_index++;
                break;
            case '*':
                token.type = MULTIPLY;
                token.value = '*';
                output_tokens[tokens_index]= token;
                index++;
                tokens_index++;
                break;
            case '/':
                token.type = DIVIDE;
                token.value = '/';
                output_tokens[tokens_index]= token;
                index++;
                tokens_index++;
                break;
            default:
                if(isNumber(input_str[index])){
                    // printf("I am in if %d\n", index);
                    //do not input numbers bigger than 10 digits
                    char number_str[10] = {0};
                    //_______________________________________________________________
                    //Make it a function
                    int i = 0;
                    do{
                        if(i>10){
                            printf("You have entered a very big nuber at index %d", index);
                        }
                        number_str[i]  = input_str[index];
                        i++;
                        index++;
                        // printf("index:%d i:%d\n", index, i);
                    }while(isNumber(input_str[index]) && (index <  size_of_array));

                    number_str[i] = '|';//for asthetic printf 
                    //_______________________________________________________________
                    int number = string_to_int(number_str, 10, i);
                    printf("number: %d\n", number);
                    token.type = INTEGER;
                    token.value = number;
                    output_tokens[tokens_index] = token;
                    tokens_index++;
                    break;
                    
                }else{
                    printf("The input at index %d is not a valid input!\n", index);
                    index++;
                    break;
                }
                break;

        }
    }
}



int main(){
    char expression[10] = {'1', '0' ,' ', '+',' ', '2', '+', ' ', '6', ' '};
    Token tokens[10] = {0};
    make_token(expression, 10, tokens); //input should be 10 nubbers in array
    printf_Tokens(tokens);

    return 0;
}