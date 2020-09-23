//
//  01eBubPres.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T1.h"
#include "01eBubPres.h"

#define maxstrlen 128

void BubPresVar(double *sigma, double *r)
{
    //Declaring input variable
    char input[maxstrlen];
    
    printf("Surface tension (N/m) = ");
    *sigma = atof(fgets(input, sizeof(input), stdin));
    
    printf("Radius of fluid droplet (mm) = ");
    *r = atof(fgets(input, sizeof(input), stdin));
    
    *r = (*r)*0.001; //Conversion (mm to m)
    printf("Function assignments:\nsigma = %f N/m\nr = %f m\n", *sigma, *r);
    fflush(stdout);
}

double BubPresCalc(double sigma, double r) 
{
    double top = 0.0;
    double P = 0.0;
    
    top = 0.0; //Initialising variable
    
    top = 2*sigma;
    P = (top)/r;
    printf("Bubble pressure = %.3f Pa\n", P);
    return P;
}
/*
void [Data Plot & Write](...)
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
void BubPres()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain;
    
    printf("Bubble Pressure Calculator\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //Declaring & Allocating main variables
        double sigma = 0.0;
        double r = 0.0;
        double P = 0.0;
        
        BubPresVar(&sigma, &r);
        printf("Function returns:\nsigma = %f\nr = %f\n", sigma, r);
        P = BubPresCalc(sigma, r);
        printf("Function returns: P = %f\n", P);
        //Ask for file write (Remember while loop)
        //...
        //Continue function
        int whilcont;
        
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
