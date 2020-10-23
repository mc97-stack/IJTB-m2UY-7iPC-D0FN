//
//  03d1Fittings.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>

//  Custom header files
#include "B48BB_T3.h"
#include "03dOneK.h"
#include "03dTwoK.h"
#include "03dThreeK.h"
#include "03dEquivLeng.h"

#define maxstrlen 128

void Fittings()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("Pressure Loss through Pipe Fittings\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];
        
        int whilside = 1;
        while(whilside == 1)
        {
            //Data collection
            printf("Which method do you want to use to calculate friction losses:\n");
            printf("1. 1K (Lost velocity heads)(Excess heads method) (Recommended for small pipe sizes)\n");
            printf("2. 2K (Lost velocity heads)\n");
            printf("3. 3K (Lost velocity heads) (Recommended for NPS > NPS 12)\n");
            printf("4. Equivalent length\n");
            printf("Selection: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    OneK();
                    whilside = 0;
                    break;
                case '2':
                    TwoK();
                    whilside = 0;
                    break;
                case '3':
                    ThreeK();
                    whilside = 0;
                    break;
                case '4':
                    EquivLeng();
                    whilside = 0;
                    break;
                default:
                    printf("Input not recognised\n");
                    break;
            }
        }
        
        //Continue function
        int whilcont = 1;
        while(whilcont == 1)
        {
            printf("Do you want to continue? ");
            fgets(ContCond, sizeof(ContCond), stdin);
            switch(ContCond[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    whilcont = 0;
                break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    whilcont = 0;
                    whilmain = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        printf("\n");
    }
    fflush(stdout);
}
