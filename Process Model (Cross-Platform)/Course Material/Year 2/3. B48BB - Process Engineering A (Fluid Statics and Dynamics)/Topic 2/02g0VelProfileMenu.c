//
//  02g0VelProfileMenu.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 21/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//



//  Created by Matthew Cheung on 29/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T2.h"
#include "02g0VelProfileMenu.h"
#include "02g1LamVelPro.h"
#include "02g2TurVelPro.h"

#define maxstrlen 128

void VelProfile()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain;
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
                    LamVelPro();
                    whilselec = 0;
                break;
                case '2':
                case 'T':
                case 't':
                    TurVelPro();
                    whilselec = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        //Continue function
        int whilcont;
        whilcont = 1;
        while(whilcont == 1)
        {
            printf("Do you want to exit the velocity profile program? ");
            fgets(ContCond, sizeof(ContCond), stdin);
            switch(ContCond[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    whilcont = 0;
                    whilmain = 0;
                break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    whilcont = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
    }
    printf("\n");
    fflush(stdout);
}
