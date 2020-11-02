//
//  02PVTRelations.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 01/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>

//  Custom header files
#include "02PVTRelations.h"

#define maxstrlen 128

void statePropertyRelations()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Subroutines available:\n");
        printf("1. Ideal gas law.\n");
        printf("2. Virial equation of state.\n");
        printf("3. Cubic equations of state.\n");
        printf("4. General Benedict-Webb-Rubin equation of state.\n");
        printf("5. Estimation of normal saturated liquid volume.\n");
        printf("Q. Exit menu.\n\n");
        
        printf("Selection [1 - 2]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                IdealEOS();
                break;
            case '2':
                VirialEOS();
                break;
            case '3':
                //CubicEOS();
                printf("Bear with me, this is still being written...\n");
                break;
            case '4':
                //GenBWREOS();
                printf("Bear with me, this is still being written...\n");
                break;
            case '5':
                //saturatedMolarVolume();
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
