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
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T2.h"
#include "02hHagPois.h"

#define maxstrlen 128

void HagPoisVariable(double *u, double *mu, double *L, double *d)
{
    *L = inputDouble(0, "pipe horizontal length", "m");
    
    *d = inputDouble(0, "pipe diameter", "mm");
    *d = (*d)*0.001; //Conversion (mm to m)
    
    *u = inputDouble(0, "average fluid velocity", "m/s");
    
    *mu = inputDouble(0, "fluid viscosity", "cP");
    *mu = *mu * 0.001; //Conversion (cP to Pa.s)
    
    fflush(stdout);
}

double HagPoisCalculation(double u, double mu, double L, double d)
{
    double top = 0.0;
    double bot = 0.0;
    
    double dP = 0.0;
    
    top = 32*u;
    top = (top)*mu;
    top = (top)*L;
    bot = pow(d, 2);
    
    dP = (top)/(bot);
    
    return dP;
}

void HagPoisDisplay(double u, double mu, double L, double d, double dP)
{
    printf("_Hagen-Pouseuille_Equation_Results_\n");
    printf("\tInput parameters:\n");
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n", mu*1000);
    printf("Pipe length:\n");
    printf("L =\t%.3f\tm\n", L);
    printf("Pipe diameter:\n");
    printf("d =\t%.3f\tmm\n\n", d*1000);
    
    printf("\tOutput parameters:\n");
    printf("Assuming fluid flow is isothermal\n");
    printf("Fluid pressure loss:\n");
    printf("dP =\t%.3f\tPa\t= \\frac{32u\\mu L}{d^2}", dP);
    fflush(stdout);
}

void HagPoisWrite(double u, double mu, double L, double d, double dP)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Hagen-Poiseuille Equation Results
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
    
    strcat(filename, " Hagen-Poiseuille Equation Results");
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
    
    //Write to file
    fprintf(fp, "_Hagen-Pouseuille_Equation_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tcP\n", mu*1000);
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "L =\t%.3f\tm\n", L);
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n\n", d*1000);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Assuming fluid flow is isothermal\n");
    fprintf(fp, "Fluid pressure loss:\n");
    fprintf(fp, "dP =\t%.3f\tPa\t= \\frac{32u\\mu L}{d^2}", dP);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void HagPoisWriteSwitch(double u, double mu, double L, double d, double dP)
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
                HagPoisWrite(u, mu, L, d, dP);
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

void HagenPoiseuille()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Hagen-Poiseuille Equation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double dP = 0.0; //Frictional pressure loss.
        
        double u = 0.0; //Average fluid velocity.
        double mu = 0.0; //Fluid viscosity.
        double L = 0.0; //Horizontal pipe length.
        double d = 0.0; //Pipe diameter.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        HagPoisVariable(&u, &mu, &L, &d);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        dP = HagPoisCalculation(u, mu, L, d);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        HagPoisDisplay(u, mu, L, d, dP);
        
        //  Writing to File
        HagPoisWriteSwitch(u, mu, L, d, dP);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
