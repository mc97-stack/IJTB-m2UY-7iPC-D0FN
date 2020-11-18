//
//  Year1.c
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
void Year1()
{
    char selec[maxstrlen];
    //Memory Allocation
    int whilc = 0; //Initialising variable whilc
    
    whilc = 1;
    while(whilc == 1){
        printf("Year 1 Courses\n");
        printf("1. B17CA - Principles of Chemistry\n");
        printf("2. B47AA - Process Industries A\n");
        printf("3. B47AC - Foundation Engineering A (Physics)\n");
        printf("4. F17XA - Mathematics for Engineers and Scientists 1\n");
        printf("5. B17BC - Chemical Reactivity\n");
        printf("6. B47AB - Process Industries B\n");
        printf("7. B47AD - Foundation Engineering B (Biology)\n");
        printf("8. F17XB - Mathematics for Engineers and Scientists 2\n");
        printf("q. Exit menu\n");
        printf("\nSelection: ");
        fgets(selec,sizeof(selec),stdin);
        switch(selec[0])
        {
            case '1':
                //B17CA();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '2':
                //B47AA();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '3':
                //B47AC();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '4':
                //F17XA();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '5':
                //B17BC();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '6':
                //B47AB();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '7':
                //B47AD();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
                break;
            case '8':
                //F17XB();
                printf("Bear with me, this is still being written...\n");
                //whilc = 0;
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
