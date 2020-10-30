//
//  01aFluComp .c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/06/2020.
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
#include "01aFluComp.h"

#define maxstrlen 128
#define R 8.31455
#define BST (+1)

void FluCompVariable(double *P, double *V, double *n, double *T)
{
    //Pressure
    *P = inputDouble(0, "absolute system pressure", "kPa_abs");
    *P = *P * 1000.0;
    
    //Temperature
    *T = inputDouble(1, "system temperature", "deg C");
    *T = *T + 273.15; //Conversion to K
    
    //Volume
    *V = inputDouble(0, "system volume", "m3");
    
    //moles
    *n = inputDouble(0, "moles of substance", "kmol");
    *n = *n * 1000.0; //Conversion to mol
    
    //printf("You have entered:\n%f Pa\n%f m3\n%f mol\n%f K\n\n", *P, *V, *n, *T); // This line is commented out unless checking the variable allocations in this subroutine.
    fflush(stdout);
}

double FluCompCalculation(double P, double V, double n, double T)
{
    double top = 0.0;   // Numerator of the bracketed term.
    double bot = 0.0;   // Denominator of the bracketed term.
    double frac = 0.0;  // Initial fraction of start of formula.
    
    double c = 0.0;     //  Fluid compressibility factor
    
    frac = (1.0)/V;
    frac = (-1.0)*(frac);
    
    top = (-1.0)*n;
    top = (top)*R;
    top = (top)*T;
    
    bot = pow(P, 2);
    
    c = (top)/(bot);
    
    c = (frac)*(c);
    
    //printf("c = %f m3/ Pa \n", c);
    return c;
}

void FluCompDisplay(double P, double V, double n, double T, double c)
{
    printf("_Fluid_Coefficient_of_Compressibility_Results_\n");
    printf("P = %.3f kPa\n", P*0.001);
    printf("V = %.3f m3\n", V);
    printf("n = %.3f mol\n", n);
    printf("T = %.3f deg C\n\n", (T - 273.15));
    printf("c = $$-\\frac{1}{V}\\left(\\frac{\\delta{V}}{\\delta{P}}\\right))_T$$ = %.6f m3/Pa\n", c);
}

void FluCompWrite(double P, double V, double n, double T, double c)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;   // Pointer to the file location.
    //Set file name as timestamp + Fluid Coefficient of Compressibility
    
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
    
    strcat(filename, " Fluid Coefficient of Compressibility Results");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /* //  This code does not work
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "~/Documents/ModelFiles/");
    printf("File path: \"%s\"\n", filepath);
    
    strcat(filepath, filename);
    void free(void *filename);
    
    printf("File name: \"%s\"\n", filename);
    printf("Full file path: \"%s\"\n\n", filepath);
    
    //Testing if directory is not present
    
    if(fopen(filepath, "r") == NULL){
        printf("Directory does not exist, writing data to \"Documents\" folder instead.\n");
        strcpy(filepath, "~/Documents/");
        printf("File is now being outputted to: %s\n", filepath);
    }
    */
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filename, "w+");
    
    //Write to file
    fprintf(fp, "_Fluid_Coefficient_of_Compressibility_Results_\n");
    fprintf(fp, "P = %.3f kPa\n", P*0.001);
    fprintf(fp, "V = %.3f m3\n", V);
    fprintf(fp, "n = %.3f mol\n", n);
    fprintf(fp, "T = %.3f deg C\n\n", (T - 273.15));
    fprintf(fp, "c = $$-\\frac{1}{V}\\left(\\frac{\\delta{V}}{\\delta{P}}\\right))_T$$ = %.6f m3/Pa\n", c);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void FluCompWriteSwitch(double P, double V, double n, double T, double c)
{
    int control = 0;  // Variable used to control the following while loop.
    
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
                FluCompWrite(P, V, n, T, c);
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

void CoefficientofCompressibility()
{
    //  "CoefficientofCompressibility" has been abbreviated to "FluComp" followed by the function intention.
    int whilmain = 0;
    
    printf("Fluid Coefficient of Compressibility\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Declaring variables
        double c = 0.0;
        double P = 0.0;
        double V = 0.0;
        double n = 0.0;
        double T = 0.0;
        
        //  Collecting data
        FluCompVariable(&P, &V, &n, &T);
        //printf("Function has outputted:\n%f Pa\n%f m3\n%f mol\n%f K\n\n", P, V, n, T);
        
        //  Running calculation
        clock_t timer = clock();
        c = FluCompCalculation(P, V, n, T);
        //printf("Function has outputted = %f m3/ Pa\n\n", c);
        timer = clock() - timer;
        
        int calctime = 0;
        calctime = ((int)timer*1000)/CLOCKS_PER_SEC;
        printf("Calculation completed in %d seconds and %d milliseconds.\n\n", calctime/1000, calctime%1000);
        
        //  Displaying data
        FluCompDisplay(P, V, n, T, c);
        
        //  Writing to file
        FluCompWriteSwitch(P, V, n, T, c);
        
        //  Continue function
        whilmain = Continue(whilmain);
        
        fflush(stdout);
    }
    //fflush(stdout);
}
