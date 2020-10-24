//
//  System.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 24/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <stdio.h>

#include "System.h"

#define maxstrlen 128

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
