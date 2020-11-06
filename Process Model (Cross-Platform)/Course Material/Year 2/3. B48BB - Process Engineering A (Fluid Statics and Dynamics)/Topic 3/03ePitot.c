//
//  03ePitot.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/07/2020.
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
#include "B48BB_T3.h"
#include "03ePitot.h"
#include "01cMano.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define PI 3.14159265

/// MARK: VARIABLE INPUT
void PitotVariable(double *P2, double *rho1, double *rho2, double *h1, double *h2, double *d)
{
    *P2 = inputDouble(0, "static pressure on connection", "kPa");
    *P2 = (*P2)*1000; //Conversion (kPa to Pa)
    
    *rho1 = inputDouble(0, "process fluid density", "kg/m3");
    
    *rho2 = inputDouble(0, "manometer fluid density", "kg/m3");
    
    *h1 = inputDouble(0, "process fluid height in manometer", "cm");
    *h1 = (*h1)*0.01; //Conversion (cm to m)
    
    *h2 = inputDouble(0, "manometer fluid height in manometer", "cm");
    *h2 = (*h2)*0.01; //Conversion (cm to m)
    
    *d = inputDouble(0, "internal pipe diameter", "mm");
    *d = (*d)*0.001; //Conversion (mm to m)
}

/// MARK: GENERAL CALCULATION
void PitotCalculation(double P2, double rho1, double rho2, double h1, double h2, double d, double *P1, double *v, double *Q)
{
    //P1 = Process fluid pressure
    double dP = 0.0;
    double frac = 0.0;
    double pare = 0.0;
    
    //Manometer calculations - Get dP
    *P1 = ManoMeasCalculation(P2, rho1, h1, rho2, h2);
    dP = P2 - (*P1);
    
    //Velocity calculation
    frac = 2*dP;
    frac = (frac)/(rho1);
    printf("frac = %f\n", frac);
    *v = pow((frac), 0.5);
    
    //Volumetric flowrate calculation
        //Calculating pipe area
    pare = d/(2.0); //Getting pipe radius
    pare = pow(pare, 2);
    pare = PI*(pare);
    
    *Q = (*v) * (pare);
}

/// MARK: DISPLAY AND WRITE
void PitotDisplay(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q)
{
    printf("_Pitot_Static_Tube_Results_\n");
    printf("\tInput parameters:\n");
    printf("Static pressure on connection:\n");
    printf("P2 =\t%.3f\tkPa\n", P2*0.001);
    printf("Process fluid density:\n");
    printf("rho1 =\t%.3f\tkg/m3\n", rho1);
    printf("Process fluid height in manometer element:\n");
    printf("h1 =\t%.3f\tcm\n", h1*100);
    printf("Manometer fluid density:\n");
    printf("rho2 =\t%.3f\tkg/m3\n", rho2);
    printf("Manometer fluid height:\n");
    printf("h2 =\t%.3f\tcm\n\n", h2*100);
    
    printf("\tOutput parameters:\n");
    printf("Assuming skin friction losses can be ignored.\n");
    printf("Therefore, assuming that the impact connection is located on the pipe centreline\n\n");
    
    printf("Process fluid pressure:\n");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Process fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", v);
    printf("Process fluid volumetric flowrate:\n");
    printf("Q =\t%.3f\tm3/s\n", Q);
    fflush(stdout);
}

void PitotWrite(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Pitot Static Tube Results
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof *filename);
    
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Pitot Static Tube Results");
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
    
    //Open file
    fp = fopen(filename, "w+");
    free(filename);
    
    //Write to file
    fprintf(fp, "_Pitot_Static_Tube_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Static pressure on connection:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n", P2*0.001);
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Process fluid height in manometer element:\n");
    fprintf(fp, "h1 =\t%.3f\tcm\n", h1*100);
    fprintf(fp, "Manometer fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n", rho2);
    fprintf(fp, "Manometer fluid height:\n");
    fprintf(fp, "h2 =\t%.3f\tcm\n", h2*100);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Assuming skin friction losses can be ignored.\n");
    fprintf(fp, "Therefore, assuming that the impact connection is located on the pipe centreline\n\n");
    
    fprintf(fp, "Process fluid pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Process fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", v);
    fprintf(fp, "Process fluid volumetric flowrate:\n");
    fprintf(fp, "Q =\t%.3f\tm3/s\n", Q);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PitotWriteSwitch(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q)
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
                PitotWrite(P1, P2, rho1, rho2, h1, h2, d, v, Q);
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
void PitotStaticTube()
{
    //Main Function
    int whilmain = 0;
    printf("Pitot static tube calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double P1 = 0.0;    // Pressure of process fluid at measurement point.
        double v = 0.0;     // Fluid velocity at measurement point.
        double Q = 0.0;     // Volumetric flowrate at measurement point.
        
        double P2 = 0.0;    // Static pressure on connection.
        double rho1 = 0.0;  // Process fluid density.
        double rho2 = 0.0;  // Manometer fluid density.
        double h1 = 0.0;    // Height of process fluid in manometer.
        double h2 = 0.0;    // Height of manometer fluid in manometer.
        double d = 0.0;     // Internal pipe diameter.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        PitotVariable(&P2, &rho1, &rho2, &h1, &h2, &d);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        PitotCalculation(P2, rho1, rho2, h1, h2, d, &P1, &v, &Q);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        PitotDisplay(P1, P2, rho1, rho2, h1, h2, d, v, Q);
        
        //  Writing to File
        PitotWriteSwitch(P1, P2, rho1, rho2, h1, h2, d, v, Q);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
