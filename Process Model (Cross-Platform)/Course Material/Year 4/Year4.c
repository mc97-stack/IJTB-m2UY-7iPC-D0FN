//
//  Year4.c
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
