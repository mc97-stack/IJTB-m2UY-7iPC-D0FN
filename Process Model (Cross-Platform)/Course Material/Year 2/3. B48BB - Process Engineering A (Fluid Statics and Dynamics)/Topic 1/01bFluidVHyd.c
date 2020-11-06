//
//  01bFluidVHyd.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

/// MARK: HEADER DECLARATIONS
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

/// MARK: SUBROUTINE DEFINITIONS
//  Fixed variable definitions
#define maxstrlen 128   // Max string length
#define g 9.80665       // Acceleration due to gravity

/// MARK: VARIABLE INPUT
void FluidVHydVariable(double *rho, double *h)
{
    *rho = inputDouble(0, "fluid density", "kg/m3");
    
    *h = inputDouble(1, "fluid height", "m");
}

/// MARK: GENERAL CALCULATION
double FluidVHydCalculation(double rho, double h) 
{
    double P = 0.0; // Fluid hydrostatic pressure.
    
    P = rho * g;
    P = (P) * h;
    
    return P;
}

/// MARK: DISPLAY AND WRITE
void FluidVHydDisplay(double rho, double h, double P)
{
    printf("_Fluid_Vertical_Hydrostatic_Pressure_Results_\n");
    printf("g =\t%.5f\tm/s2\n\n", g);
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("h =\t%.3f\tm\n", h);
    printf("P =\t%.3f\tPa\n", P);
    fflush(stdout);
}

void FluidVHydWrite(double rho, double h, double P)
{
    //Function variables
    char filename[maxstrlen];   // Character array used to store file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
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
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Vertical Hydrostatic Pressure Theorem Results");
    //printf("File name: \"%s\"\n", filename);
    
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
    free(filename);
    
    //Write to file
    fprintf(fp, "_Fluid_Vertical_Hydrostatic_Pressure_Results_\n");
    fprintf(fp, "g =\t%.5f\tm/s2\n\n", g);
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "h =\t%.3f\t m\n", h);
    fprintf(fp, "P =\t%.3f\tPa\n", P);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void FluidVHydWriteSwitch(double rho, double h, double P)
{
    int control = 0;    // Variable used to control user input.
    
    control = 1;
    while(control == 1)
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
                control = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                control = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
}

/// MARK: PSEUDO-MAIN FUNCTION
void FluidVerticalHydrostaticPressure()
{
    //  Pseudo-main function.
    int whilmain = 0;
    
    printf("Vertical Hydrostatic Pressure Gradient\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //  Declaring variables
        double P = 0.0;     // Hydrostatic pressure.
        
        double rho = 0.0;   // Fluid density.
        double h = 0.0;     // Vertical height of fluid.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Collecting data
        FluidVHydVariable(&rho, &h);
        
        //  Running calculation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        P = FluidVHydCalculation(rho, h);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);
        
        printf("Calculations completed in %.6f seconds.\n\n", elapsed);
        
        //  Displaying results
        FluidVHydDisplay(rho, h, P);
        
        //  Writing to file
        FluidVHydWriteSwitch(rho, h, P);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
