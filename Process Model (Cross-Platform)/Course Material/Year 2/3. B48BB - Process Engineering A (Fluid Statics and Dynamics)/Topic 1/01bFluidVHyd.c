//
//  01bFluidVHyd.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T1.h"
#include "01bFluidVHyd.h"

//  Fixed variable definitions
#define maxstrlen 128 //Max string length
#define g 9.80665 // Acceleration due to gravity

void FluidVHydVar(double *rho, double *h)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Fluid Density (kg/m3) = ");
    
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid height (m) = ");
    
    *h = atof(fgets(input, sizeof(input), stdin));
    
    //Displaying function results
    printf("rho = %f kg/m3\n", *rho);
    printf("h = %f m\n", *h);
    fflush(stdout);
}

double FluidVHydCalc(double rho, double h, double *P) 
{
    *P = rho * g;
    *P = *P * h;
    printf("P|_{h = %.1f m} = %.3f kPa\n", h, *P * 0.001);
    return *P;
}

/*
void FluidVHydWrite(...)
{
    char filename[maxstrlen];
    char path[maxstrlen];
    char filepath[maxstrlen*2];

    FILE *fp
    
    //Get file name
    *filename = (char)malloc(sizeof(filename);
    ...
    
    //Get file path - This step is optional
    *path = (char)malloc(sizeof(path));
    ...
    
    //Creating the full path and name through concatenation
    *filepath = (char)malloc(sizeof(filepath));
    strcpy(filepath, filepath);
    strcat(filepath, filename);
    strcat(filepath, ".txt");
    
    //Testing if directory exists
    if(fopen(filepath, "r") == NULL)
    {
            printf("Directory does not exist, writing data to \"Documents\" folder\n");
            strcpy(filepath, "/Users/user/Documents/");
            printf("Filepath: %s\n", filepath);
    }
    
    printf("Beginning file write\n");
    //File open
    fp = fopen(filepath, "w+");
    
    //Writing to file
    fprintf(fp, "...", ...);
    ...
    
    //File close
    fclose(fp);
    
    printf("Write successful\n");
    fflush(stdout);
}
*/
void FluidVHyd()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    printf("Vertical Hydrostatic Pressure Gradient\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        double rho = 0.0;
        double h = 0.0;
        double P = 0.0;
        
        int whilcont = 0;
        
        FluidVHydVar(&rho, &h);
        printf("rho = %f kg/m3\n", rho);
        printf("h = %f m\n", h);
        
        FluidVHydCalc(rho, h, &P);
        printf("Function returns %f\n", P);
        
        //Ask for file write (Remember while loop)
        //printf("Do you want to plot the pressure variations up to this height? ");
        //FluidVHydProfile(*rho, *h);
        //printf("Profile is linear...");
        //Continue function
        whilcont = 1;
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
