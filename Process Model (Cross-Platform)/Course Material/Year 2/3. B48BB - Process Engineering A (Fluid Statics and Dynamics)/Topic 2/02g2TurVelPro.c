//
//  02g2TurVelPro.c
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
#include "02g2TurVelPro.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128

/// MARK: VARIABLE INPUT
void TurVelProVariable(double *umax, double *d)
{
    double u = 0.0;
    u = inputDouble(0, 0, "average fluid velocity", "m/s");
    
    *umax = (49.0)/(60.0);
    *umax = (*umax) * u;
    
    *d = inputDouble(0, 0, "pipe diameter", "mm");
    *d = (*d) * 0.001;
}

/// MARK: GENERAL CALCULATION
double TurVelCalculation(double vmax, double r, double d, double *gen) 
{
    //Calculated using Prandtl's one-seventh law
    double bot = 0.0;
    double y = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    double v_x = 0.0;
    
    bot = d/2;
    frac2 = (1.0)/(7.0);
    
    y = bot - r;
    frac1 = y/(bot);
    v_x = pow(frac1, frac2);
    *gen = v_x;
    
    v_x = vmax*(v_x);
    
    return v_x;
}

/// MARK: ARRAY FUNCTION
TurVelProf TurVelProCalculation(double vmax, double d, int *rows) 
{
    double interval = 0.0;
    double prad = 0.0;
    
    TurVelProf profile = {0.0};
    
    interval = 0.001;
    prad = d/2;
    
    *rows = ((prad)/ (interval)) + 1;
    
    printf("%i rows required\n", *rows);
    
    int i = 0;
    for(double r = 0.0; r < (prad + (interval/2)); r += interval)
    {
        profile.r[i] = r; //Displaying point radius
        profile.v_x[i] = TurVelCalculation(vmax, r, d, &profile.ratio[i]);
        ++i;
    }
    printf("%i rows successfully generated\n\n", i);
    *rows = i;
    return profile;
}

/// MARK: DISPLAY AND WRITE
void TurVelProDisplay(double umax, double d, int rows, TurVelProf profile)
{
    printf("_Turbulent_Velocity_Profile_(Prandtl's_One-Seventh_Law)_Results_\n");
    
    //Write to file
    printf("\tInput parameters:\n");
    printf("Maximum fluid velocity:");
    printf("u_{max.} =\t%.3f\tm/s\n", umax);
    printf("Pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    
    printf("\tOutput parameters:\n");
    printf("r (mm)\tv_x (m/s)\tv_x/v_{max}\n");
    for(int i = 0; i < ++rows; ++i)
    {
        printf("%.3f\t", 1000*profile.r[i]);
        printf("%.3f\t", profile.v_x[i]);
        printf("%.3f\n", profile.ratio[i]);
    }
}

void TurVelProWrite(double umax, double d, int rows, TurVelProf profile)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Turbulent Velocity Profile Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Turbulent Velocity Profile Results");
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
    fprintf(fp, "_Turbulent_Velocity_Profile_(Prandtl's_One-Seventh_Law)_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Maximum fluid velocity:");
    fprintf(fp, "u_{max.} =\t%.3f\tm/s\n", umax);
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    
    fprintf(fp, "\tOutput parameters:\n");
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

void TurVelProWriteSwitch(double umax, double d, int rows, TurVelProf profile)
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
                TurVelProWrite(umax, d, rows, profile);
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
void TurbulentVelPro()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Prandtl's One-Seventh Law Velocity Profile\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        int elems = 0;                  // Variable used to store the total number of elements used in the data struct.
        
        elems = 3*5000;
        
        TurVelProf *profile = calloc(elems, sizeof(double)); // Struct used to store the velocity profile.
        
        double vmax = 0;            // Maximum fluid velocity.
        double d = 0;               // Internal pipe diameter.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        int rows = 0;
        
        //  Data collection
        TurVelProVariable(&vmax, &d);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        *profile = TurVelProCalculation(vmax, d, &rows);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        TurVelProDisplay(vmax, d, rows, *profile);
        
        //  Writing to File
        TurVelProWriteSwitch(vmax, d, rows, *profile);
        free(profile);
    }
    fflush(stdout);
}
