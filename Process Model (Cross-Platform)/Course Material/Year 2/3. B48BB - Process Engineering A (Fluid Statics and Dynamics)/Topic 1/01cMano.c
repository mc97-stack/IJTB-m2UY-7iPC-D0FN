//
//  01cMano.c
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
#include "01cMano.h"

/// MARK: SUBROUTINE DEFINITIONS
//  Fixed variable definitions
#define maxstrlen 128
#define g 9.80665
#define PI 3.14159265

/// MARK: VARIABLE INPUT
void ManoMeasVariable(double *P2, double *rho1, double *h1, double *rho2, double *h2)
{
    char input[maxstrlen];   // Variable used to store character input into a menu.
    int control = 0;        // Variable used to control user input.
    
    double L = 0.0;         // Length of manometer arm.
    double incl = 0.0;      // Inclination angle.
    
    control = 1;
    while(control == 1)
    {
        printf("Take reference pressure as absolute atmospheric pressure? ");
        
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *P2 = 101.325;
                control = 0;
                break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                *P2 = inputDouble(0, "P_2", "kPa_{abs}");
            
                if(*P2 == 0) // Double checking in case a gauge pressure is inputted
                {
                    *P2 = *P2 + 101.325;
                }
                control = 0;
                break;
            default:
                printf("Input not recognised\n");
                break;
        }
    }
    
    *P2 = *P2 * 1000; //Conversion (kPa to Pa)
    
    *rho1 = inputDouble(0, "density of process fluid", "kg/m3");
    
    *h1 = inputDouble(0, "Height of process fluid in manometer", "cm");
    *h1 = *h1 * 0.01; //Conversion (cm to m)
    
    *rho2 = inputDouble(0, "manometer fluid density", "kg/m3");
    
    //Check for an inclined manometer
    control = 1;
    while(control == 1)
    {
        printf("Is the manometer inclined? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                //Length along arm
                L = inputDouble(0, "length of manometer fluid in inclined arm", "cm");
                
                //Degree of inclination
                incl = inputDouble(0, "Degree of inclination", "deg");
                
                incl = (incl)*(PI/180); //Conversion to radians
                *h2 = (L)*sin( (incl) );
                
                control = 0;
                break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                printf("Height of manometer fluid (cm) = ");
                *h2 = inputDouble(0, "height of manometer fluid", "cm");
                
                control = 0;
                break;
            default:
                printf("Input not recognised\n");
                break;
        }
    }
    
    *h2 = *h2 * 0.01; //Conversion (cm to m)
    printf("\n");
}

void ManoEstiVariable(double *P1, double *P2, double *rho1, double *rho2, double *h1)
{
    //Misc function variables
    char input[maxstrlen];  // Variable used to store character input.
    int PresCheck = 0;
    
    *P1 = inputDouble(0, "P_1", "kPa_{abs}");
    *P1 = (*P1)*1000; //Conversion (kPa to Pa)
    
    PresCheck = 1;
    
    //P2 variable collection
    while(PresCheck == 1)
    {
        printf("Take reference pressure as 101.325 kPa? ");
        fgets(input, sizeof(input), stdin);
        
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *P2 = 101.325;
                PresCheck = 0;
                break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                *P2 = inputDouble(0, "P_2", "kPa_{abs}");
                
                if(*P2 == 0)
                {
                    *P2 = *P2 + 101.325;
                }
                PresCheck = 0;
                break;
            default:
                printf("Input not recognised\n");
                break;
        }
    }
    *P2 = (*P2) *1000; //Conversion (kPa to Pa)
    
    *rho1 = inputDouble(0, "process fluid density", "kg/m3");
    
    *h1 = inputDouble(0, "height of process fluid in manometer", "cm");
    *h1 = (*h1)*0.01; //Conversion (cm to m)
    
    *rho2 = inputDouble(0, "manometer fluid density", "kg/m3");
    
    fflush(stdout);
}

/// MARK: GENERAL CALCULATIONS
double ManoMeasCalculation(double P2, double rho1, double h1, double rho2, double h2)
{
    double brack = 0.0;
    double P1 = 0.0;
    
    brack = rho2 * h2;
    brack = brack - rho1 * h1;
    
    P1 = g*(brack);
    
    P1 = P2 + (P1);
    
    return P1;
}

double ManoEstiCalculation(double P1, double P2, double rho1, double h1, double rho2)
{
    char input[maxstrlen];  // Variable used to store user input.
    int control = 0;        // Variable used to control user input.
    
    double h2 = 0.0;        // Estimated height of manometer fluid.
    
    double dP = 0.0;        // Pressure difference.
    double top = 0.0;
    double bot = 0.0;
    double incl = 0.0;      // Inclination angle in degrees.
    double rad = 0.0;       // Inclination angle in radians.
    
    
    dP = P1 - P2;
    top = rho1*g;
    top = (top) * h1;
    top = (top) + dP;
    
    bot = rho2*g;
    
    h2 = (top)/(bot);
    
    control = 1;
    while(control == 1)
    {
        printf("Is the manometer inclined? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                //Degree of inclination
                incl = inputDouble(0, "degree of inclination", "deg");
                
                incl = (incl)*(PI/180.0); //Conversion to radians
                rad = sin(incl);
                
                h2 = (h2)/(rad);
                
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
    return h2;
}

/// MARK: DISPLAY AND WRITE
void ManoMeasDisplay(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    printf("_Manometer_Estimation_Calculations_\n\n");
    printf("_Input_Parameters:_\n");
    printf("\tProcess Fluid:\n");
    printf("P1 =\t%.3f\tkPa_abs\n", P1*0.001);
    printf("Process fluid density:\n");
    printf("rho1 =\t%.3f\tkg/m3\n", rho1);
    printf("Process fluid height:\n");
    printf("h1 =\t%.3f\tm\n", h1);
    printf("\tManometer Fluid:\n");
    printf("P2 =\t%.3f\tkPa_abs\n", P2*0.001);
    printf("Manometer fluid density:\n");
    printf("rho2 =\t%.3f\tkg/m3\n\n", rho2);
    
    printf("_Output_Values:_\n");
    printf("Manometer fluid height:\n");
    printf("h2 =\t%.3f\tm\t= \\frac{\\rho_1gh_1 - \\Delta{P}}{\\rho_2g}\n", h2);
    fflush(stdout);
}

void ManoMeasWrite(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    //  Function variables
    char filename[maxstrlen];   // Character array used to store file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;   // Pointer to the file location.
    
    //  Set file name as timestamp + Manometer Measurement Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Manometer Measurement Results");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    /*//driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
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
    }*/
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //  Open file
    fp = fopen(filename, "w+");
    
    //  Write to file
    fprintf(fp, "_Manometer_Measurement_Calculations_\n\n");
    fprintf(fp, "_Input_Parameters:_\n");
    fprintf(fp, "\tProcess Fluid:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa_abs\n", P1*0.001);
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Process fluid height:\n");
    fprintf(fp, "h1 =\t%.3f\tm\n", h1);
    fprintf(fp, "\tManometer Fluid:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa_abs\n", P2*0.001);
    fprintf(fp, "Manometer fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n\n", rho2);
    
    fprintf(fp, "_Output_Values:_\n");
    fprintf(fp, "Manometer fluid height:\n");
    fprintf(fp, "h2 =\t%.3f\tm\t= \\frac{\\rho_1gh_1 - \\Delta{P}}{\\rho_2g}\n", h2);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ManoMeasWriteSwitch(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        //*SaveQ = (char)malloc(sizeof(SaveQ));
        printf("Do you want to save results to file? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                ManoMeasWrite(P1, P2, rho1, h1, rho2, h2);
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

void ManoEstiDisplay(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    printf("_Manometer_Pressure_Estimation_Calculations_\n\n");
    printf("_Input_Parameters:_\n");
    printf("\tProcess Fluid:\n");
    printf("Process fluid density:\n");
    printf("rho1 =\t%.3f\tkg/m3\n", rho1);
    printf("Process fluid height:\n");
    printf("h1 =\t%.3f\tm\n", h1);
    printf("\tManometer Fluid:\n");
    printf("P2 =\t%.3f\tkPa_abs\n", P2*0.001);
    printf("Process fluid density:\n");
    printf("rho2 =\t%.3f\tkg/m3\n", rho2);
    printf("Process fluid height:\n");
    printf("h2 =\t%.3f\tm\n\n", h2);
    
    printf("_Output_Values:_\n");
    printf("P1 =\t%.3f\tkPa_abs\t= P2 + g(\\rho_2h_2 - \\rho_1h_1)\n", P1*0.001);
    fflush(stdout);
}

void ManoEstiWrite(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    //  Function variables
    char filename[maxstrlen];   // Character array used to store file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;   // Pointer to the file location.
    //  Set file name as timestamp + Manometer Height Estimation Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Manometer Height Estimation Results");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /*
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
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
    printf("Note that write sequence disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //  Open file
    fp = fopen(filename, "w+");
    
    //  Write to file
    fprintf(fp, "_Manometer_Measurement_Calculations_\n\n");
    fprintf(fp, "_Input_Parameters:_\n");
    fprintf(fp, "\tProcess Fluid:\n");
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Process fluid height:\n");
    fprintf(fp, "h1 =\t%.3f\tm\n", h1);
    fprintf(fp, "\tManometer Fluid:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa_abs\n", P2*0.001);
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n", rho2);
    fprintf(fp, "Process fluid height:\n");
    fprintf(fp, "h2 =\t%.3f\tm\n\n", h2);
    
    fprintf(fp, "_Output_Values:_\n");
    fprintf(fp, "P1 =\t%.3f\tkPa_abs\t= P2 + g(\\rho_2h_2 - \\rho_1h_1)\n", P1*0.001);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ManoEstiWriteSwitch(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    int control = 0; // Variable used to control the following while loop.
    
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
                ManoEstiWrite(P1, P2, rho1, h1, rho2, h2);
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
void Manometer()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Manometer calculations\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Declaring variables
        char input[maxstrlen];  // Variable used to store character input.
        int control = 0;   // Integer variable used to control subroutine inputs and behaviour.
        
        double P1 = 0.0;    // Pressure of travelling process fluid.
        double P2 = 0.0;    // Pressure of surroundings on manometer fluid.
        double rho1 = 0.0;  // Density of process fluid.
        double rho2 = 0.0;  // Density of manometer fluid.
        double h1 = 0.0;    // Height of process fluid in manometer.
        double h2 = 0.0;    // Height of manometer fluid in manometer.
        
            // Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        control = 1;
        while(control == 1)
        {
            printf("Please make a selection: \n");
            printf("1. Pressure Measurement\n");
            printf("2. Manometer fluid height estimation\n");
            printf("Selection [1 - 2]: ");
            
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'M':
                case 'm':
                    printf("\n");
                    ManoMeasVariable(&P2, &rho1, &h1, &rho2, &h2);
                    
                    clock_getres(CLOCK_MONOTONIC, &start);
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    
                    P1 = ManoMeasCalculation(P2, rho1, h1, rho2, h2);
                    
                    clock_getres(CLOCK_MONOTONIC, &end);
                    clock_gettime(CLOCK_MONOTONIC, &end);

                    elapsed = timer(start, end);

                    printf("Calculations completed in %.6f seconds.\n", elapsed);
                    
                    ManoMeasDisplay(P1, P2, rho1, h1, rho2, h2);
                    
                    ManoMeasWriteSwitch(P1, P2, rho1, h1, rho2, h2);
                    control = 0;
                break;
                case '2':
                case 'E':
                case 'e':
                    printf("\n");
                    ManoEstiVariable(&P1, &P2, &rho1, &rho2, &h1);
                    
                    clock_getres(CLOCK_MONOTONIC, &start);
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    
                    h2 = ManoEstiCalculation(P1, P2, rho1, h1, rho2);
                    
                    clock_getres(CLOCK_MONOTONIC, &end);
                    clock_gettime(CLOCK_MONOTONIC, &end);

                    elapsed = timer(start, end);

                    printf("Calculations completed in %.6f seconds.\n", elapsed);
                    
                    ManoEstiDisplay(P1, P2, rho1, h1, rho2, h2);
                    
                    ManoEstiWriteSwitch(P1, P2, rho1, h1, rho2, h2);
                    
                    control = 0;
                break;
                default:
                    printf("Input not recognised. \n");
                break;
            }
        }
        //  Continue function
        whilmain = Continue(whilmain);
        printf("\n");
    }
    fflush(stdout);
}
