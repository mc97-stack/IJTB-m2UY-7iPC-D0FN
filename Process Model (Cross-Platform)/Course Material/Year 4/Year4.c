//
//  Year4.c
//  Process Model (MacOS Version)
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <stdio.h>
#include <stdlib.h>

//Custom Header Files
#include "main.h"
#include "Courses.h"

#define maxstrlen 128

void Year4()
{
    char selec[maxstrlen];
    
    //Memory Allocation
    int whilc = 0;
    
    whilc = 1;
    while(whilc == 1){
        printf("Year 4 Courses\n");
        printf("1. B40DB - Sustainability, Health and Safety\n");
        printf("2. B40EA - Unit Operations A\n");
        printf("3. B40DC - Energy Generation and Utilisation\n");
        printf("4. B41OA - Oil and Gas Processing\n");
        printf("5. B40DD - Reaction Engineering B\n");
        printf("q. Exit menu\n");
        printf("\nSelection: ");
        fgets(selec,sizeof(selec),stdin);
        switch(selec[0]){
            case '1':
                //B40DB();
                printf("Bear with me, this is still being written...\n");
            break;
            case '2':
                //B40EA();
                printf("Bear with me, this is still being written...\n");
            break;
            case '3':
                //B40DC();
                printf("Bear with me, this is still being written...\n");
            break;
            case '4':
                //B41OA();
                printf("Bear with me, this is still being written...\n");
            break;
            case '5':
                //B40DD();
                printf("Bear with me, this is still being written...\n");
            break;
            case 'q':
                whilc = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
}
