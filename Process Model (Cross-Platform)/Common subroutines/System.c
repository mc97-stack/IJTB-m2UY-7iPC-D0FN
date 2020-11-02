//
//  System.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 24/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  Custom header files.
#include "System.h"

#define maxstrlen 128

double inputDouble(int allowZero, char VariableName[], char Units[])
{
    char value[maxstrlen];  // Variable used to hold keyboard input.
    double input = 0.0;     // Variable used to store the double value before being returned to the calling function.
    
    int control = 0;        // Integer value used to force a non-zero value to be inputted.
    
    control = 1;
    while(control == 1)
    {
        printf("Please enter a value for %s (%s): ", VariableName, Units);
        input = atof(fgets(value, sizeof(value), stdin));
        if(allowZero == 0 && input == 0.0){
            printf("This variable must have a non-zero value. Please enter a different value.\n");
        }else{
            control = 0;    // Break the while loop.
        }
    }
    fflush(stdout);
    return input;
}

double timer(struct timespec start, struct timespec end)
{
    double seconds = 0.0;
    double nanos = 0.0;
    double elapsed = 0.0;
    
    seconds = end.tv_sec - start.tv_sec;
    seconds = (seconds)*pow(10, 9);
    
    nanos = end.tv_nsec - start.tv_nsec;
    
    elapsed = seconds + nanos;
    elapsed = (elapsed)*pow(10, -9);
    
    return elapsed;
}

int Continue(int ControlVariable)
{
    char input[maxstrlen];
    int ContCond = 0;
    
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
                ControlVariable = 0;
                ContCond = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    fflush(stdout);
    return ControlVariable;
}
