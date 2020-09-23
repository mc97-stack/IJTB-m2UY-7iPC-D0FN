//
//  03cHydrDiam.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T3.h"
#include "03cHydrDiam.h"

#define maxstrlen 128

void HydrDiamVar(double *A_F, double *P_W)
{
    //Input variables
    char input[maxstrlen];
    
    double convfactor = 0.0;
    
    printf("Cross-sectional flow area (mm2) = ");
    *A_F = atof(fgets(input, sizeof(input), stdin));
    
    convfactor = pow(1000,2);
    convfactor = 1/(convfactor);
    *A_F = (*A_F)*convfactor;
    
    printf("Wetted perimeter (cm) = ");
    *P_W = atof(fgets(input, sizeof(input), stdin));
    
    *P_W = (*P_W)*0.01;
    
    fflush(stdout);
}

double HydrDiamCalc(double A_F, double P_W)
{
    double d_H = 0.0;
    double top = 0.0;
    double bot = 0.0;
    
    top = 4*A_F;
    bot = P_W;
    d_H = (top)/(bot);
    
    return d_H;
}

void HydrDiam()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Hydraulic diameter calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Declaring variables
        double A_F = 0.0; //Cross-sectional flow area
        double P_W = 0.0; //Wetted perimeter
        
        double d_H = 0.0; //Hydraulic diameter
        
        int whilcont = 0;
        //Data collection
        HydrDiamVar(&A_F, &P_W);
        
        //Data manipulation
        d_H = HydrDiamCalc(A_F, P_W);
        
        printf("d_H = %.3f mm\n\n", d_H*1000);
        
        //Continue function
        whilcont = 0;
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
    }
    fflush(stdout);
}
