//
//  Year2.c
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <stdio.h>
#include <stdlib.h>

//Custom Header Files
#include "main.h"
#include "Courses.h"

#define maxstrlen 128

void Year2()
{
    char selec[maxstrlen];
    
    int whilc = 0;
    
    whilc = 1;
    while(whilc == 1){
        printf("Year 2 Courses\n");
        printf("1. B18AP - Chemical Thermodynamics and Introductory Chemical Kinetics for Chemical Engineers\n");
        printf("2. B48BA - Process Industries C\n");
        printf("3. B48BB - Process Engineering A (Fluid Statics and Dynamics)\n");
        printf("4. F18XC - Mathematics for Engineers and Scientists 3\n");
        printf("5. B48BC - Process Engineering B (Thermodynamic Processes)\n");
        printf("6. B48BD - Process Engineering C (Heat Transfer)\n");
        printf("7. F18XD - Mathematics for Engineers and Scientists 4\n");
        printf("q. Exit menu\n");
        printf("\nSelection: ");
        fgets(selec,sizeof(selec),stdin);
        switch(selec[0]){
            case '1':
                //B18AP();
                printf("Bear with me, this is still being written...\n");
                break;
            case '2':
                //B48BA();
                printf("Bear with me, this is still being written...\n");
                break;
            case '3':
                B48BB();
                //printf("Bear with me, this is still being written...\n");
                break;
            case '4':
                //F18XC();
                printf("Bear with me, this is still being written...\n");
                break;
            case '5':
                B48BC();
                //printf("Bear with me, this is still being written...\n");
                break;
            case '6':
                //B48BD();
                printf("Bear with me, this is still being written...\n");
                break;
            case '7':
                //F18XD();
                printf("Bear with me, this is still being written...\n");
                break;
            case '0':
            case 'Q':
            case 'q':
                whilc = 0;
                break;
            default:
                printf("Input not recognised\n");
                break;
        }
        fflush(stdout);
    }
}
