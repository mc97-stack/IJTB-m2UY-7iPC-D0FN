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
#include <time.h>

//  Custom header files
#include "System.h"
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

double FluidVHydCalc(double rho, double h) 
{
    double P = 0.0;
    
    P = rho * g;
    P = P * h;
    
    return P;
}

void FluidVHydDisp(double rho, double h, double P)
{
    printf("_Fluid_Vertical_Hydrostatic_Pressure_Results_\n");
    printf("g = %.5f\tm/s2\n\n", g);
    printf("rho = %.3f\tkg/m3\n", rho);
    printf("h = %.3f\t m\n", h);
    printf("P\t%.3f\tPa\t= \\rho * g * h =\n", P);
}

void FluidVHydWrite(double rho, double h, double P)
{
    //Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Vertical Hydrostatic Pressure Theorem Results
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS"
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof *filename);
    
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Vertical Hydrostatic Pressure Theorem Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /*
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc((128*2)*sizeof(char));
    
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
    */
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filename, "w+");
    
    //Write to file
    fprintf(fp, "_Fluid_Vertical_Hydrostatic_Pressure_Results_\n");
    fprintf(fp, "g = %.5f\tm/s2\n\n", g);
    fprintf(fp, "rho = %.3f\tkg/m3\n", rho);
    fprintf(fp, "h = %.3f\t m\n", h);
    fprintf(fp, "P\t%.3f\tPa\t= \\rho * g * h =\n", P);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void FluidVHydWriteCheck(double rho, double h, double P)
{
    int SaveC = 0;
    SaveC = 1;
    while(SaveC == 1)
    {
        char input[maxstrlen];
        
        printf("Do you want to save results to file? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                FluidVHydWrite(rho, h, P);
                SaveC = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                SaveC = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
}

void FluidVHyd()
{
    //Main Function
    int whilmain = 0;
    
    printf("Vertical Hydrostatic Pressure Gradient\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //  Declaring variables
        double rho = 0.0;
        double h = 0.0;
        double P = 0.0;
        
        //  Collecting data
        FluidVHydVar(&rho, &h);
        //printf("rho = %f kg/m3\n", rho);
        //printf("h = %f m\n", h);
        
        //  Running calculation
        P = FluidVHydCalc(rho, h);
        //printf("P|_{h = %.1f m} = %.3f kPa\n", h, P * 0.001);
        
        //  Displaying results
        FluidVHydDisp(rho, h, P);
        
        //  Writing to file
        FluidVHydWriteCheck(rho, h, P);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
