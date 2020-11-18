//
//  02g0VelProfileMenu.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 29/06/2020.
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

//  Standard header files
#include <stdio.h>

//  Custom header files
#include "System.h"
#include "B48BB_T2.h"
#include "02g0VelProfileMenu.h"
#include "02g1LamVelPro.h"
#include "02g2TurVelPro.h"

#define maxstrlen 128

void VelocityProfileMenu()
{
    int whilmain = 0;
    printf("Velocity Profile Selection\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        char CalcCheck[maxstrlen];
        int whilselec = 1;
        while(whilselec == 1){
            printf("Please select which velocity profile you would like to calculate:\n");
            printf("1. Laminar Flow\n");
            printf("2. Turbulent Flow\n\n");
            printf("Selection: ");
            fgets(CalcCheck, sizeof(CalcCheck), stdin);
            switch(CalcCheck[0])
            {
                case '1':
                case 'L':
                case 'l':
                    LaminarVelPro();
                    whilselec = 0;
                    break;
                case '2':
                case 'T':
                case 't':
                    TurbulentVelPro();
                    whilselec = 0;
                    break;
                default:
                    printf("Input not recognised\n");
                    break;
            }
        }
        //Continue function
        whilmain = Continue(whilmain);
    }
    printf("\n");
    fflush(stdout);
}
