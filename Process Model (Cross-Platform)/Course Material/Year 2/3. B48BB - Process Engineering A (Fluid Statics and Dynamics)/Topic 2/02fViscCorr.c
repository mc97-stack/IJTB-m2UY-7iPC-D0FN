//
//  02fViscCorr.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 29/06/2020.
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
#include "B48BB_T2.h"
#include "02fViscCorr.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define exp 2.718281828459045

/// MARK: VARIABLE INPUT
void ViscCorrVariable(double *a, double *b, double *T, double *rho)
{
    char input[maxstrlen];
    int control = 0;
    
    *a = inputDouble(0, "a", "");
    
    *b = inputDouble(0, "b", "");
    
    *T = inputDouble(0, "system temperature", "deg C");
    
    control = 1;
    while(control == 1)
    {
        printf("Does temperature need converting to K? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *T = (*T) + 273.15;
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
        fflush(stdout);
    }
    
    printf("Fluid density (kg/m3) = ");
    *rho = inputDouble(0, "fluid density", "kg/m3");
}

/// MARK: GENERAL CALCULATIONS
double LiquidViscCalculation(double a, double b, double T)
{
    double frac = 0.0;
    double mu = 0.0;
    
    frac = b/T;
    mu = pow(exp, (frac));
    
    mu = a*(mu);
    
    printf("Liquid viscosity = %.3f [Units]\n", mu);
    return mu;
}

double VapourViscCalculation(double a, double b, double T)
{
    double top = 0.0;
    double bot = 0.0;
    
    double mu = 0.0;
    
    top = pow(T, (1.5));
    top = a * (top);
    
    bot = b + T;
    
    mu = (top)/(bot);
    
    printf("Vapour viscosity = %.3f [Units]\n", mu);
    return mu;
}

double KineticVisc(double mu, double rho)
{
    double upsi = 0.0;
    
    upsi = (mu)/(rho);
    printf("Kinematic viscosity = %.3f [Units]\n", upsi);
    return upsi;
}

/// MARK: DISPLAY AND WRITE
void ViscDisplay(int method, double a, double b, double T, double rho, double mu, double upsi)
{
    if(method == 1){
        printf("_Liquid_Viscosity_Correlation_\n");
    }
    if(method == 2){
        printf("_Vapour_Viscosity_Correlation_\n");
    }
    printf("\tInput parameters:\n");
    printf("a =\t%.3f\n", a);
    printf("b =\t%.3f\n", b);
    printf("Temperature:\n");
    printf("T =\t%.3f\t\n", T);
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n\n", rho);
    
    printf("\tOutput parameters:\n");
    if(method == 1){
        printf("mu =\t%.3f\t...\t=ae^{\\frac{b}{T}}\n", mu);
    }
    if(method == 2){
        printf("mu =\t%.3f\t...\t=\\frac{aT^{1.5}}{(b + T)\n", mu);
    }
    printf("upsilon =\t%.3f\t...\t=\\frac{\\mu}{\\rho}\n", upsi);
    fflush(stdout);
}

void ViscWrite(int method, double a, double b, double T, double rho, double mu, double upsi)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + ... Viscosity Correlation Results
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
    
    if(method == 1){
        strcat(filename, " Liquid Viscosity Correlation Results");
        //printf("File name: \"%s\"\n", filename);
    }
    if(method == 2){
        strcat(filename, " Vapour Viscosity Correlation Results");
        //printf("File name: \"%s\"\n", filename);
    }
    
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
    if(method == 1){
        fprintf(fp, "_Liquid_Viscosity_Correlation_\n");
    }
    if(method == 2){
        fprintf(fp, "_Vapour_Viscosity_Correlation_\n");
    }
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "a =\t%.3f\n", a);
    fprintf(fp, "b =\t%.3f\n", b);
    fprintf(fp, "Temperature:\n");
    fprintf(fp, "T =\t%.3f\t\n", T);
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n\n", rho);
    
    fprintf(fp, "\tOutput parameters:\n");
    if(method == 1){
        fprintf(fp, "mu =\t%.3f\t...\t=ae^{\\frac{b}{T}}\n", mu);
    }
    if(method == 2){
        fprintf(fp, "mu =\t%.3f\t...\t=\\frac{aT^{1.5}}{(b + T)\n", mu);
    }
    fprintf(fp, "upsilon =\t%.3f\t...\t=\\frac{\\mu}{\\rho}\n", upsi);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ViscWriteSwitch(int method, double a, double b, double T, double rho, double mu, double upsi)
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
                ViscWrite(method, a, b, T, rho, mu, upsi);
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
void ViscosityCorrelation()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Viscosity Correlation Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];  // Character input variable.
        
        double mu = 0.0;        // Fluid viscosity.
        double upsi = 0.0;      // Fluid kinematic viscosity.
        
        double a = 0.0;         // First constant required for standard viscosity correlations.
        double b = 0.0;         // Second constant required for standard viscosity correlatons.
        double T = 0.0;         // System temperature.
        double rho = 0.0;       // Fluid density.
        
        int method = 0;         // Variable used to control subroutine behaviour in terms of what state of matter viscosity is being calculated for.
        int whilmethod = 0;     // Variable used to control user input when collected which method to use.
        whilmethod = 1;
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        while(whilmethod == 1)
        {
            printf("Please select from the following types of calculation:\n");
            printf("1. Liquid Viscosity\n2. Vapour Viscosity\n");
            printf("Selection ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'L':
                case 'l':
                    printf("Liquid viscosity correlation selected.\n");
                    method = 1;
                    whilmethod = 0;
                break;
                case '2':
                case 'V':
                case 'v':
                    printf("Vapour viscosity correlation selected\n");
                    method = 2;
                    whilmethod = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        printf("\n");
        
        ViscCorrVariable(&a, &b, &T, &rho);
        printf("\n");
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        mu = 0; //Initialising viscosity variable
        switch(method)
        {
            case '1':
                mu = LiquidViscCalculation(a, b, T);
                break;
            case '2':
                mu = VapourViscCalculation(a, b, T);
                break;
            //Default case is not needed as input is checked earlier in function
        }
        printf("\n");
        upsi = KineticVisc(mu, rho);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        ViscDisplay(method, a, b, T, rho, mu, upsi);
        
        //  Writing to File
        ViscWriteSwitch(method, a, b, T, rho, mu, upsi);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    printf("\n");
    fflush(stdout);
}
