//
//  02aMassCon.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 26/06/2020.
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
#include "02aMassCon.h"

#define maxstrlen 128
#define PI 3.141592653

void MassConVariable(double *rho1, double *rho2, double *d1, double *d2, double *u1)
{
    *rho1 = inputDouble(0, "initial fluid density", "kg/m3");
    
    *rho2 = inputDouble(0, "final fluid density", "kg/m3");
    
    *d1 = inputDouble(0, "initial internal pipe diameter", "mm");
    *d1 = (*d1)*0.001; //Conversion (mm to m)
    
    *d2 = inputDouble(0, "final internal pipe diameter", "mm");
    *d2 = (*d2)*0.001; //Conversion (mm to m)
    
    *u1 = inputDouble(0, "initial fluid velocity", "m/s");
}

double FinalVelocityCalculation(double u1, double d1, double d2)
{
    double frac = 0.0;
    double u2 = 0.0;
    
    frac = d1/d2;
    frac = pow((frac), 2);
    
    u2 = u1*(frac);
    
    return u2;
}

double VolumetricFlowCalculation(double u, double d)
{
    double A = 0.0; //Area of cross-section
    double q = 0.0; //Volumetric flow rate
    
    A = d/2;
    A = pow((A), 2);
    A = PI*(A);
    
    q = u*(A);
    
    return q;
}

double MassFlowCalculation(double rho, double d, double u)
{
    double A = 0.0; //Area of cross-section
    double m = 0.0; //Mass flowrate
    
    A = d/2;
    A = pow((A), 2);
    A = PI * (A);
    
    m = rho * (A);
    m = (m) * u;
    
    return m;
}

void MassConDisplay(double rho1, double rho2, double d1, double d2, double u1, double u2, double q1, double q2, double m1, double m2, double error)
{
    printf("_Mass_Conservation_Principle_\n");
    printf("Assuming the fluid is incompressible. \n");
    printf("\tInput parameters:\n");
    printf("Initial fluid density:\n");
    printf("rho1 =\t%.3f\tkg/m3\n", rho1);
    printf("Final fluid density:\n");
    printf("rho2 =\t%.3f\tkg/m3\n", rho2);
    printf("Initial pipe diameter:\n");
    printf("d1 =\t%.3f\tmm\n", d1*1000);
    printf("Final pipe diameter:\n");
    printf("d2 =\t%.3f\tmm\n", d2*1000);
    printf("Initial fluid velocity:\n");
    printf("u1 =\t%.3f\tm/s\n\n", u1);
    
    printf("\tOutput parameters:\n");
    printf("Final fluid velocity:\n");
    printf("u2 =\t%.3f\tm/s\n", u2);
    printf("Initial volumetric flowrate:\n");
    printf("q1 =\t%.3f\tm3/s\n", q1);
    printf("Final volumetric flowrate:\n");
    printf("q2 =\t%.3f\tm3/s\n", q2);
    printf("Initial mass flowrate:\n");
    printf("m1 =\t%.3f\tkg/s\n", m1);
    printf("Final pipe diameter:\n");
    printf("m2 =\t%.3f\tkg/s\n\n", m2);
    
    printf("Mass difference:\n");
    printf("error =\t%.3f\tkg/s\n\n", error);
    
    if(error < 0.001)
    {
        printf("Mass balances.\n\n");
    }else{
        printf("Mass does not balance.\n\n");
        if(rho1 != rho2)
        {
            printf("This program is under the assumption that the fluid is incompressible so density cannot fluctuate\n");
        }
    }
    fflush(stdout);
}

void MassConWrite(double rho1, double rho2, double d1, double d2, double u1, double u2, double q1, double q2, double m1, double m2, double error)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Mass Conservation Results
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
    
    strcat(filename, " Mass Conservation Results");
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
    fprintf(fp, "_Mass_Conservation_Principle_\n");
    fprintf(fp, "Assuming the fluid is incompressible. \n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Final fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n", rho2);
    fprintf(fp, "Initial pipe diameter:\n");
    fprintf(fp, "d1 =\t%.3f\tmm\n", d1*1000);
    fprintf(fp, "Final pipe diameter:\n");
    fprintf(fp, "d2 =\t%.3f\tmm\n", d2*1000);
    fprintf(fp, "Initial fluid velocity:\n");
    fprintf(fp, "u1 =\t%.3f\tm/s\n\n", u1);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Final fluid velocity:\n");
    fprintf(fp, "u2 =\t%.3f\tm/s\n", u2);
    fprintf(fp, "Initial volumetric flowrate:\n");
    fprintf(fp, "q1 =\t%.3f\tm3/s\n", q1);
    fprintf(fp, "Final volumetric flowrate:\n");
    fprintf(fp, "q2 =\t%.3f\tm3/s\n", q2);
    fprintf(fp, "Initial mass flowrate:\n");
    fprintf(fp, "m1 =\t%.3f\tkg/s\n", m1);
    fprintf(fp, "Final mass flowrate:\n");
    fprintf(fp, "m2 =\t%.3f\tkg/s\n\n", m2);
    
    fprintf(fp, "Mass difference:\n");
    fprintf(fp, "error =\t%.3f\tkg/s\n\n", error);
    
    if(error < 0.001)
    {
        fprintf(fp, "Mass balances.\n\n");
    }else{
        fprintf(fp, "Mass does not balance.\n\n");
        if(rho1 != rho2)
        {
            fprintf(fp, "This program is under the assumption that the fluid is incompressible so density cannot fluctuate\n");
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}
void MassConWriteSwitch(double rho1, double rho2, double d1, double d2, double u1, double u2, double q1, double q2, double m1, double m2, double error)
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
                MassConWrite(rho1, rho2, d1, d2, u1, u2, q1, q2, m1, m2, error);
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

void MassConservation()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Mass Conservation Principle\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //  Variable declaration
        double u2 = 0.0;    // Final fluid velocity.
        double m1 = 0.0;    // Initial mass flowrate.
        double m2 = 0.0;    // Final mass flowrate.
        double q1 = 0.0;    // Initial volumetric flowrate.
        double q2 = 0.0;    // Final volumetric flowrate.
        
        double rho1 = 0.0;  // Initial fluid density.
        double rho2 = 0.0;  // Final fluid density.
        double d1 = 0.0;    // Initial internal pipe diameter.
        double d2 = 0.0;    // Final internal pipe diameter.
        double u1 = 0.0;    // Initial fluid velocity.
        
        double error = 0.0;
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        MassConVariable(&rho1, &rho2, &d1, &d2, &u1);
        printf("Function returns:\nrho1 = %f\nrho2 = %f\nd1 = %f\nd2 = %f\nu1 = %f\n\n", rho1, rho2, d1, d2, u1);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        u2 = FinalVelocityCalculation(u1, d1, d2);
        //printf("Function returns: u2 = %f\n\n", u2);
        
        q1 = VolumetricFlowCalculation(u1, d1);
        //printf("Volumetric flow rate = %.3f m3/s\n", q1);
        q2 = VolumetricFlowCalculation(u2, d2);
        //printf("Volumetric flow rate = %.3f m3/s\n", q2);
        
        m1 = MassFlowCalculation(rho1, d1, u1);
        //printf("Mass flow rate = %.3f kg/s\n", m1);
        m2 = MassFlowCalculation(rho2, d2, u2);
        //printf("Mass flow rate = %.3f kg/s\n", m2);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying data
        MassConDisplay(rho1, rho2, d1, d2, u1, u2, q1, q2, m1, m2, error);
        
        //  Writing to file
        MassConWriteSwitch(rho1, rho2, d1, d2, u1, u2, q1, q2, m1, m2, error);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
