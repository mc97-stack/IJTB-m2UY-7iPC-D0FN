//
//  System.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 24/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "System.h"

#define maxstrlen 128

double inputDouble(char VariableName[], char Units[])
{
    char value[maxstrlen];  // Variable used to hold keyboard input.
    double input = 0.0;     // Variable used to store the double value before being returned to the calling function.
    
    int control = 0;        // Integer value used to force a non-zero value to be inputted.
    
    control = 1;
    while(control == 1)
    {
        printf("Please enter a value for %s (%s): ", VariableName, Units);
        input = atof(fgets(value, sizeof(value), stdin));
        if(input == 0.0)
        {
            printf("This variable must have a non-zero value. Please enter a different value.\n");
        }else{
            control = 0;    // Break the while loop.
        }
    }
    fflush(stdout);
    return input;
}

int Continue(int ControlVariable)
{
    char input[maxstrlen];
    int ContCond;
    
    ContCond = 1;
    while(ContCond == 1)
    {
        printf("Do you want to continue? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                ContCond = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                ContCond = 0;
                ControlVariable = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    
    return ControlVariable;
}
