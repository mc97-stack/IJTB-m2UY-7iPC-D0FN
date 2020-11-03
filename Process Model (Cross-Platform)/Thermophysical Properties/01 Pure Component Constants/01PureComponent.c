//
//  01PureComponent.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>

//  Custom header files
#include "01PureComponent.h"

#define maxstrlen 128

void pureComponentConstants()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Subroutines available:\n");
        printf("1. Critical property estimation.\n");
        printf("2. Acentric factor calculation.\n");
        printf("3. Boiling and freezing point estimation.\n");
        printf("Q. Exit menu.\n\n");
        
        printf("Selection [2]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                //CriticalProperty();
                printf("Bear with me, this is still being written...\n");
                break;
            case '2':
                AcentricFactor();
                break;
            case '3':
                //BoilingFreezingPoint();
                printf("Bear with me, this is still being written...\n");
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 2");
                break;
        }
    }
}
