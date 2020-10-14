//
//  02hHagPois.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T2.h"
#include "02hHagPois.h"
#include "02g1LamVelPro.h"

#define maxstrlen 128

void HagPoisVar(double *u, double *mu, double *L, double *d)
{
    //Declaring input
    char input[maxstrlen];
    
    printf("Pipe horizontal length (m) = ");
    *L = atof(fgets(input, sizeof(input), stdin));
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    
    *d = (*d)*0.001; //Conversion (mm to m)
    
    printf("Average fluid velocity (m/s) = ");
    *u = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid viscosity (cP) = ");
    *mu = atof(fgets(input, sizeof(input), stdin));
    
    *mu = *mu * 0.001; //Conversion (cP to Pa.s)
    
    fflush(stdout);
}

double HagPoisCalc(double u, double mu, double L, double d)
{
    double top = 0.0;
    double bot = 0.0;
    
    double dP = 0.0;
    
    top = 32*u;
    top = (top)*mu;
    top = (top)*L;
    bot = pow(d, 2);
    
    dP = (top)/(bot);
    printf("Frictional pressure loss = %.3f kPa\n", dP*0.001);
    return dP;
}
/*
void [Data Plot & Write](...)
{
    char filename[maxstrlen];
    char path[maxstrlen];
    char filepath[maxstrlen*2];

    FILE *fp
    
    //Set file name as timestamp + Name of Program
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof(filename));
    
    strftime(filename, 16, "%Y%m%d %H%M%S", info);
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " (Name of Program)");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof(filepath));
    
    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");
    printf("File path: \"%s\"\n", filepath);
    
    strcat(filepath, filename);
    void free(void *filename);
    
    printf("File name: \"%s\"\n", filename);
    printf("Full file path: \"%s\"\n\n", filepath);
    
    //Testing if directory is not present
    
    if(fopen(filepath, "r") == NULL){
        printf("Directory does not exist, writing data to \"Documents\" folder instead.\n");
        strcpy(filepath, "/Users/user/Documents/");
        printf("File is now being outputted to: %s\n", filepath);
    }
    printf("Note that write sequence disabled by zsh\n");
    
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
void HagPois()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Hagen-Poiseuille Equation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char velprof[maxstrlen];
        
        double u = 0.0; //Average fluid velocity
        double mu = 0.0; //Fluid viscosity
        double L = 0.0; //Horizontal pipe length
        double d = 0.0; //Pipe diameter
        
        double dP = 0.0; //Frictional pressure loss
        
        int rows = 0;
        
        LamVelProf profile;
        
        //Data collection
        HagPoisVar(&u, &mu, &L, &d);
        
        //Data manipulation
        dP = HagPoisCalc(u, mu, L, d);
        printf("Assuming fluid flow is isothermal\n");
        int whilprof = 1;
        while(whilprof == 1)
        {
            printf("Do you want to calculate the velocity profile? ");
            fgets(velprof, sizeof(whilprof), stdin);
            switch(velprof[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    printf("Calculating velocity profile from data...\n");
                    profile = LamVelProfCalc(dP, L, d, mu, &rows);
                    //  Displaying generated array
                    printf("r (mm)\tv_x (m/s)\tv/v_max\n");
                    for(int i = 0; i < rows; ++i){
                        printf("%f\t%f\t%f\n", profile.r[i]*1000, profile.v_x[i], profile.ratio[i]);
                    }
                    
                    whilprof = 0;
                break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    whilprof = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        //Ask for file write (Remember while loop)
        //...
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
    }
    fflush(stdout);
}
