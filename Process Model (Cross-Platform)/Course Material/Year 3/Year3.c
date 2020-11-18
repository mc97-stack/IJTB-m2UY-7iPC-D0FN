//
//  Year3.c
//  Process Model (MacOS Version)
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

//Standard Header Files
#include <stdio.h>
#include <stdlib.h>

//Custom Header Files
#include "main.h"
#include "Courses.h"

#define maxstrlen 128

void Year3()
{
    char selec[maxstrlen];
    //Memory Allocation
    int whilc = 0;
    
    whilc = 1;
    while(whilc == 1){
        printf("Year 3 Courses\n");
        printf("1. B18OA - Organic Structural Identification, Stereochemistry and Reaction Mechanisms\n");
        printf("2. B48CA - Separation Processes A\n");
        printf("3. B49CB - Business Awareness, Safety and Sustainability\n");
        printf("4. F49CC - Chemical Reaction Engineering A\n");
        printf("5. B18OB - Synthesis in Organic Chemistry\n");
        printf("6. B48CB - Separation Processes B\n");
        printf("7. B49CE - Multiphase Thermodynamics\n");
        printf("8. B49CF - Process Modelling and Control\n");
        printf("q. Exit menu\n");
        printf("\nSelection: ");
        fgets(selec,sizeof(selec),stdin);
        switch(selec[0]){
            case '1':
                //B18OA();
                printf("Bear with me, this is still being written...\n");
                break;
            case '2':
                //B48CA();
                printf("Bear with me, this is still being written...\n");
                break;
            case '3':
                //B49CB();
                printf("Bear with me, this is still being written...\n");
                break;
            case '4':
                //B18OB();
                printf("Bear with me, this is still being written...\n");
                break;
            case '5':
                //B18OB();
                printf("Bear with me, this is still being written...\n");
                break;
            case '6':
                //B48CB();
                printf("Bear with me, this is still being written...\n");
                break;
            case '7':
                //B49CD();
                printf("Bear with me, this is still being written...\n");
                break;
            case '8':
                //B49CF();
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
    }
}
