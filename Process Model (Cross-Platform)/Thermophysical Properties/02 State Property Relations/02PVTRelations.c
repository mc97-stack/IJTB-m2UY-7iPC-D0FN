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
    
    printf("Subroutines available:\n");
    printf("1. Ideal gas law.\n");
    printf("2. Virial equation of state.\n");
    printf("3. van der Waals equation of state.\n");
    printf("4. Redlich-Kwong equation of state.\n");
    printf("5. Soave-Redlich-Kwong equation of state.\n");
    printf("6. Peng-Robinson equation of state.\n");
    printf("7. General Benedict-Webb-Rubin equation of state.\n");
    printf("8. Estimation of normal saturated liquid volume.\n\n");
    printf("Selection [2]: ");
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
            //vanderWaalsEOS();
            printf("Bear with me, this is still being written...\n");
            break;
        case '4':
            //redlichKwongEOS();
            printf("Bear with me, this is still being written...\n");
            break;
        case '5':
            //soaveRedlichKwongEOS();
            printf("Bear with me, this is still being written...\n");
            break;
        case '6':
            //pengRobinsonEOS();
            printf("Bear with me, this is still being written...\n");
            break;
        case '7':
            //GenBWREOS();
            printf("Bear with me, this is still being written...\n");
            break;
        case '8':
            //saturatedMolarVolume();
            printf("Bear with me, this is still being written...\n");
            break;
        default:
            printf("Input not recognised. Please enter an integer value between 1 and 8");
            break;
    }
}
