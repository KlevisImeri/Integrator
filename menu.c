#include <stdio.h>
#include <stdlib.h>
#include "CnvCharNum.h"
/*
    Parameters: options to the menu as pointers
    (partion, lowerb bound, upper bound)
    Return: void
    It runs the menu of the programm.
*/
void start_menu(double *partition, double *lower_bound, double *upper_bound){  
    //The selector fot the options int the menu
    char selector;

    //Looping the menu until the user preses exit (3)
    do{
        //Clearing the console 
        system("clear");
        
        //Printing the menu
        printf( "Partition = %g     Lower bound = %g    Upper bound = %g\n", *partition, *lower_bound, *upper_bound);
        printf( "   0.Change the partition.\n"
                "   1.Change Lower bound.\n"
                "   2.Change Upper bound.\n"
                "   3.Continue.\n");
        printf("Choose option: ");  

        //Getting the selector
        scanf("%c", &selector);
        
        //Doing the options of the menus.
        //Converting selector to int
        switch(char_to_int(selector)){
            case 0: 
                printf("Enter partition: ");
                scanf("%lf", partition);
                break;
            case 1: 
                printf("Enter Lower bound: ");
                scanf("%lf", lower_bound);
                break;
            case 2: 
                printf("Enter Upper bound: ");
                scanf("%lf", upper_bound); 
                break;
            default: break;
        }
        //For the system clear to work
        printf("\n");
    }while(char_to_int(selector) != 3);
}