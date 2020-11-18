//
//  03fOrifice.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
#include "03fOrifice.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define g 9.80665
#define PI 3.14159265

/// MARK: VARIABLE INPUT
void OrificeVariable(double *C_d, double *d1, double *d2, double *rho, double *P1, double *P2, double *h_f)
{
    *C_d = inputDouble(0, 0, "discharge coefficient", "[ ]");
    
    *d1 = inputDouble(0, 0, "pipe diameter", "mm");
    *d1 = (*d1)*0.001; //Conversion (mm to m)
    
    *d2 = inputDouble(0, 0, "Vena Contracta diameter", "mm");
    *d2 = (*d2)*0.001; //Conversion (mm to m)
    
    *rho = inputDouble(0, 0, "process fluid density", "kg/m3");
    
    *P1 = inputDouble(0, 0, "initial system pressure", "kPa");
    *P1 = (*P1)*1000;
    
    *P2 = inputDouble(0, 0, "final system pressure", "kPa");
    *P2 = (*P2)*1000;
    
    *h_f = inputDouble(0, 0, "frictional head loss", "m");
}

/// MARK: GENERAL CALCULATION
void OrificeCalculation(double C_d, double d1, double d2, double rho, double P1, double P2, double h_f, double *u, double *Q, double *m)
{
    //Preparing variables for calculation
    double are1 = 0.0;
    double are2 = 0.0;
    
    are1 = d1/2;
    are1 = pow(are1, 2);
    are1 = PI*(are1);
    
    are2 = d2/2;
    are2 = pow(are2, 2);
    are2 = PI*(are2);
    
    double top = 0.0;
    double bot = 0.0;
    double frac = 0.0;
    
    top = P1 - P2;
    top = 2 * (top);
    top = top - g*h_f;
    
    bot = pow(are1, 2);
    bot = (bot)/(pow(are2, 2));
    bot = (bot) - 1;
    bot = rho * (bot);
    
    frac = (top)/(bot);
    
    *u = pow(frac, 0.5);
    *u = C_d * (*u); //Average fluid velocity solved
    
    *Q = (*u) * are1;
    
    *m = rho * (*Q);
}

/// MARK: DISPLAY AND WRITE
void OrificeDisplay(double P1, double P2, double rho, double d1, double d2, double C_d, double h_f, double u, double Q, double m)
{
    printf("_Orifice_Plate_Flow_Measurement_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial fluid pressure:\n");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure:\n");
    printf("P2 =\t%.3f\tkPa\n", P2*0.001);
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    
    printf("Pipe diameter:\n");
    printf("d1 =\t%.3f\tmm\n", d1*1000);
    printf("Vena Contracta Diameter:\n");
    printf("d2 =\t%.3f\tmm\n", d2*1000);
    printf("Discharge coefficient:\n");
    printf("C_d =\t%.3f\t[ ]\n", C_d);
    printf("Frictional head loss:\n");
    printf("h_f =\t%.3f\tm\n\n", h_f);
    
    printf("\tOutput parameters:\n");
    printf("Process fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Process fluid volumetric flowrate:\n");
    printf("Q =\t%.3f\tm3/s\n", Q);
    printf("Process fluid mass flowrate:\n");
    printf("m =\t%.3f\tkg/s\n", m);
    fflush(stdout);
}

void OrificeWrite(double P1, double P2, double rho, double d1, double d2, double C_d, double h_f, double u, double Q, double m)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Orifice Plate Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Orifice Plate Results");
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
    fprintf(fp, "_Orifice_Plate_Flow_Measurement_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial fluid pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n", P2*0.001);
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d1 =\t%.3f\tmm\n", d1*1000);
    fprintf(fp, "Vena Contracta Diameter:\n");
    fprintf(fp, "d2 =\t%.3f\tmm\n", d2*1000);
    fprintf(fp, "Discharge coefficient:\n");
    fprintf(fp, "C_d =\t%.3f\t[ ]\n", C_d);
    fprintf(fp, "Frictional head loss:\n");
    fprintf(fp, "h_f =\t%.3f\tm\n\n", h_f);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Process fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Process fluid volumetric flowrate:\n");
    fprintf(fp, "Q =\t%.3f\tm3/s\n", Q);
    fprintf(fp, "Process fluid mass flowrate:\n");
    fprintf(fp, "m =\t%.3f\tkg/s\n", m);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void OrificeWriteSwitch(double P1, double P2, double rho, double d1, double d2, double C_d, double h_f, double u, double Q, double m)
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
                OrificeWrite(P1, P2, rho, d1, d2, C_d, h_f, u, Q, m);
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
void OrificePlateMeter()
{
    //Main Function
    int whilmain = 0;
    printf("Orifice Plate Meter Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double u = 0.0;     // Fluid velocity.
        double Q = 0.0;     // Fluid volumetric flowrate.
        double m = 0.0;     // Mass flowrate.
        
        double C_d = 0.0;   // Discharge coefficient.
        double d1 = 0.0;    // Internal pipe diameter.
        double d2 = 0.0;    // Diameter of vena contracta.
        double rho = 0.0;   // Fluid density.
        double P1 = 0.0;    // Initial fluid pressure.
        double P2 = 0.0;    // Fluid pressure at vena contracta.
        double h_f = 0.0;   // Frictional head loss.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        OrificeVariable(&C_d, &d1, &d2, &rho, &P1, &P2, &h_f);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        OrificeCalculation(C_d, d1, d2, rho, P1, P2, h_f, &u, &Q, &m);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        OrificeDisplay(P1, P2, rho, d1, d2, C_d, h_f, u, Q, m);
        
        //  Writing to File
        OrificeWriteSwitch(P1, P2, rho, d1, d2, C_d, h_f, u, Q, m);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
