//
//  03cMultistageEstimation.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 28/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

/// MARK: HEADER DECLARATIONS
//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "B48BC_T3.h"
#include "03cMultistageEstimation.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void MSShaftWorkVariable(double *P1, double *P2, double *T1, double *mol, int *N, double *gamma)
{
    *P1 = inputDouble(0, 0, "system pressure before compression", "kPa");
    *P1 = (*P1)*1000;
    
    *P2 = inputDouble(0, 0, "final system pressure", "kPa");
    *P2 = (*P2)*1000;
    
    *T1 = inputDouble(1, 1, "system temperature before compression", "kPa");
    *T1 = (*T1) + 273.15;
    
    *mol = inputDouble(0, 0, "molar flowrate", "kmol/s");
    *mol = (*mol)*1000;
    
    *gamma = inputDouble(0, 0, "heat capacity ratio", "[ ]");
    
    *N = (int)inputDouble(0, 0, "number of stages", "[ ]");
}

/// MARK: GENERAL CALCULATION
double MSShaftWorkEquation(double P1, double P2, double T1, double mol, double gamma, double N)
{
    double brack = 0.0;
    double power = 0.0;
    
    double shaftWork = 0.0;
    
    brack = P2/P1;
    power = N*gamma;
    power = (gamma - 1)/(power);
    brack = pow(brack, power);
    brack = 1 - (brack);
    
    shaftWork = mol*R;
    shaftWork = (shaftWork)*T1;
    shaftWork = (shaftWork)*(brack);
    
    power = (1.0)/(power);
    shaftWork = (shaftWork)*(power);
    shaftWork = (shaftWork)*-1;
    
    return shaftWork;
}

double MSShaftWorkCalculation(double P1, double P2, double T1, double mol, double gamma, double N)
{
    double shaftWork = 0.0;
    
    double incr = 0.0;
    double calc[50];
    
    // Initialising the 1D matrix
    for(int i = 0; i < 50; ++i){calc[i] = 0.0;}
    
    incr = P2 - P1;
    incr = (incr)/50;
    
    calc[0] = P1;
    for(int i = 1; i < 50; ++i)
    {
        calc[i] = calc[i - 1] + incr;
        shaftWork += MSShaftWorkEquation(calc[i - 1], calc[i], T1, mol, gamma, N);
    }
    
    return shaftWork;
}

/// MARK: DISPLAY AND WRITE
void MSShaftWorkDisplay(double P1, double P2, double T1, double mol, double gamma, double N, double shaftwork)
{
    printf("_Multistage_Compressor_Shaft_Work_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure: ");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure: ");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Initial system temperature: ");
    printf("T1 =\t%.3f\tdeg C\n\n", T1-273.15);
    
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", mol*0.001);
    printf("Universal Gas Constant:\n");
    printf("R =\t%.3f\tJ/(mol. K)\n\n", R);
    
    printf("Heat capacity ratio:\n");
    printf("gamma =\t%.3f\t[ ]\n\n", gamma);
    
    printf("\tOutput parameters:\n");
    printf("Total shaft work:\n");
    printf("shaftWork =\t%.3f\tkW\n\n", shaftwork*0.001);
    fflush(stdout);
}

void MSShaftWorkWrite(double P1, double P2, double T1, double mol, double gamma, double N, double shaftwork)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Multistage Shaft Work Estimation
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Multistage Shaft Work Estimation");
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
    fprintf(fp, "_Multistage_Compressor_Shaft_Work_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure: ");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure: ");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "Initial system temperature: ");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n\n", T1-273.15);
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n", mol*0.001);
    fprintf(fp, "Universal Gas Constant:\n");
    fprintf(fp, "R =\t%.3f\tJ/(mol. K)\n\n", R);
    
    fprintf(fp, "Heat capacity ratio:\n");
    fprintf(fp, "gamma =\t%.3f\t[ ]\n\n", gamma);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Total shaft work:\n");
    fprintf(fp, "shaftWork =\t%.3f\tkW\n", shaftwork*0.001);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void MSShaftWorkWriteSwitch(double P1, double P2, double T1, double mol, double gamma, double N, double shaftwork)
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
                MSShaftWorkWrite(P1, P2, T1, mol, gamma, N, shaftwork);
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
void MultistageShaftWork(void)
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Multistage Gas Compression Shaft Work\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double shaftWork = 0.0;     // Estimated shaft work for a N-stage compression.
        
        double P1 = 0.0;            // Initial system pressure before compression.
        double P2 = 0.0;            // Final system pressure after multistage compression.
        double T1 = 0.0;            // Initial system temperature
        double mol = 0.0;           // Moles of component in system.
        int N = 0;                  // Number of stages.
        double gamma = 0.0;         // Heat capacity ratio.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        MSShaftWorkVariable(&P1, &P2, &T1, &mol, &N, &gamma);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        shaftWork = MSShaftWorkCalculation(P1, P2, T1, mol, gamma, N);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        MSShaftWorkDisplay(P1, P2, T1, mol, gamma, N, shaftWork);
        
        //  Writing to File
        MSShaftWorkWriteSwitch(P1, P2, T1, mol, gamma, N, shaftWork);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
