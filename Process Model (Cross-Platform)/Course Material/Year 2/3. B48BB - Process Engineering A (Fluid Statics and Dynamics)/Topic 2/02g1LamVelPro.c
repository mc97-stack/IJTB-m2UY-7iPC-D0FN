//
//  02g1LamVelPro.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/06/2020.
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
#include "02g1LamVelPro.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void LamVelProVariable(double *dP, double *L, double *d, double *mu)
{
    *d = inputDouble(0, 0, "internal pipe diameter", "mm");
    *d = (*d)*0.001;
    
    *L = inputDouble(0, 0, "pipe length", "m");
    
    *dP = inputDouble(0, 0, "fluid pressure loss", "Pa");
    
    *mu = inputDouble(0, 0, "fluid viscosity", "cP");
    *mu = (*mu)*0.001;
}

/// MARK: GENERAL CALCULATION
double LamVelCalculation(double dP, double L, double d, double mu, double r) 
{
    double frac1 = 0.0;
    double frac2 = 0.0;
    double frac3 = 0.0;
    
    double v_x = 0.0;
    
    frac1 = (dP/L);
    
    frac2 = pow(d,2);
    frac2 = (frac2)/(16*mu);
    
    frac3 = 2*r;
    frac3 = (frac3)/d;
    frac3 = pow(frac3, 2);
    frac3 = 1 - (frac3);
    
    v_x = frac1 * frac2;
    v_x = (v_x) * frac3;
    
    return v_x;
}

double LamVelGeneralCalculation(double r, double d)
{
    double func = 0.0;
    
    func = 2*r;
    func = (func)/d;
    func = pow(func, 2);
    func = 1 - (func);
    return func; //Returns v/v_max
}

/// MARK: ARRAY FUNCTION
LamVelProf LamVelProfCalculation(double dP, double L, double d, double mu, int *rows) 
{
    double interval = 0.0; // Interval between radius data entries used to calculate the point velocities.
    double frad = 0.0; // Absolute pipe radius. (N.B. This is different to the variable 'r'.)
    double r = 0.0; // Point radius.
    
    int i = 0;
    
    LamVelProf profile = {0.0};
    
    interval = 0.0001; // m
    
    frad = d/2;
    *rows = ((frad)/ (interval)) + 1; //Calculating number of rows for the profile results matrix
    
    printf("%i rows required\n", *rows);
    
    for(r = 0.0; r < (frad + (interval/2)); r += interval)
    {
        profile.r[i] = r; //Displaying point radius
        profile.v_x[i] = LamVelCalculation(dP, L, d, mu, r); //Calculating point velocity
        profile.ratio[i] = LamVelGeneralCalculation(r, d);
        ++i;
    }
    printf("%i rows successfully generated\n\n", i);
    *rows = i;
    
    return profile;
}

/// MARK: DISPLAY AND WRITE
void LamVelProDisplay(double dP, double L, double d, double mu, int rows, LamVelProf profile)
{
    printf("_Laminar_Velocity_Profile_Calculation_\n");
    printf("\tInput parameters:\n");
    printf("Fluid pressure loss:\n");
    printf("dP =\t%.3f\tPa\n", dP);
    printf("Pipe length:\n");
    printf("L =\t%.3f\tm\n", L);
    printf("Pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    printf("Fluid dynamic viscosity:\n");
    printf("mu =\t%.3f\tcP\n\n", mu*1000);
    
    printf("\tOutput Parameters:\n");
    printf("r (mm)\tv_x (m/s)\tv_x/v_{max}\n");
    for(int i = 0; i < rows; ++i)
    {
        printf("%.3f\t", 1000*profile.r[i]);
        printf("%.3f\t", profile.v_x[i]);
        printf("%.3f\n", profile.ratio[i]);
    }
    fflush(stdout);
}

void LamVelProWrite(double dP, double L, double d, double mu, int rows, LamVelProf profile)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Laminar Velocity Profile Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Laminar Velocity Profile Results");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /*
    //driveloc is not suitable when determining the file path for mac

    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");

    strcat(filepath, filename);

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
    
    //  Open file
    fp = fopen(filename, "w+");
    
    //  Write to file
    fprintf(fp, "_Laminar_Velocity_Profile_Calculation_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid pressure loss:\n");
    fprintf(fp, "dP =\t%.3f\tPa\n", dP);
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "L =\t%.3f\tm\n", L);
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    fprintf(fp, "Fluid dynamic viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tcP\n\n", mu*1000);
    
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "r (mm)\tv_x (m/s)\tv_x/v_{max}\n");
    for(int i = 0; i < ++rows; ++i)
    {
        fprintf(fp, "%.3f\t", 1000*profile.r[i]);
        fprintf(fp, "%.3f\t", profile.v_x[i]);
        fprintf(fp, "%.3f\n", profile.ratio[i]);
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void LamVelProWriteSwitch(double dP, double L, double d, double mu, int rows, LamVelProf profile)
{
    int control = 0;
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
                LamVelProWrite(dP, L, d, mu, rows, profile);
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
void LaminarVelPro()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Laminar flow velocity profile\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        int elems = 0;                  // Variable used to store the total number of elements used in the data struct.
        
        elems = 3*5000;
        
        LamVelProf *profile = calloc(elems, sizeof(double)); // Struct used to store the generated velocity profile.
        
        double dP = 0.0;    // Fluid pressure loss.
        double L = 0.0;     // Pipe length.
        double d = 0.0;     // Internal pipe diameter.
        double mu = 0.0;    // Fluid viscosity.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        int rows = 0;
        
        //  Data collection
        LamVelProVariable(&dP, &L, &d, &mu);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        *profile = LamVelProfCalculation(dP, L, d, mu, &rows);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        LamVelProDisplay(dP, L, d, mu, rows, *profile);
        
        //  Writing to File
        LamVelProWriteSwitch(dP, L, d, mu, rows, *profile);
        free(profile);
    }
    fflush(stdout);
}
