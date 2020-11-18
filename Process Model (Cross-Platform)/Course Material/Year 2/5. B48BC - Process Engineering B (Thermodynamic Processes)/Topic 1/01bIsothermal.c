//
//  01bIsothermal.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
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
#include "01bIsothermal.h"
#include "IdealGasLaw.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void IsotVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T, double *n)
{
    if(method == 1){
        // Volume definition
        *V1 = inputDouble(0, 0, "initial system volume", "m3");
        
        *V2 = inputDouble(0, 0, "final system volume", "m3");
    }
    if(method == 2){
        // Pressure definition
        *P1 = inputDouble(0, 0, "initial system pressure", "kPa");
        *P1 = (*P1)*1000;
        
        *P2 = inputDouble(0, 0, "final system pressure", "kPa");
        *P2 = (*P2)*1000;
    }
    if(method == 1 || method == 2){
        // Common variables
        *T = inputDouble(1, 1, "system temperature", "deg C");
        *T = (*T) + 273.15;
        
        *n = inputDouble(0, 0, "molar flowrate", "kmol/s");
        *n = (*n)*1000;
    }
}

/// MARK: GENERAL CALCULATIONS
double IsotVolume(double n, double T, double V1, double V2)
{
    double frac = 0.0;
    double work = 0.0;
    
    frac = V2/V1;
    frac = log(frac);
    
    work = n*R;
    work = (work)*T;
    work = (work)*(frac);
    work = -1*(work);
    
    return work;
}

double IsotPressure(double n, double T, double P1, double P2)
{
    double frac = 0.0;
    double work = 0.0;
    
    frac = P2/P1;
    frac = log(frac);
    
    work = n*R;
    work = (work)*T;
    work = (work)*(frac);
    
    return work;
}

double IsotFinalPressure(double P1, double V1, double V2)
{
    double P2 = 0.0;
    
    P2 = P1 * V1;
    P2 = (P2)/V2;
    
    return P2;
}

double IsotFinalVolume(double V1, double P1, double P2)
{
    double V2 = 0.0;
    
    V2 = P1*V1;
    V2 = (V2)/P2;
    
    return V2;
}

/// MARK: ARRAY FUNCTION
T1ThermoProf IsotProfile(int method, double n, double T, double P1, double P2, double V1, double V2)
{
    double incr = 0.0;  // Increment between data points
    int reso = 0;       // Resolution of the generated plot
    int i = 0;          // Row control
    
    T1ThermoProf profile = {0.0};
    double total = 0.0;
    
    reso = 249;
    
    //Setting initial system conditions
    i = 0;
    if(method == 1){
        incr = V2 - V1;
        incr = (incr)/reso;
        
        profile.V[i] = V1;
        profile.T[i] = T;
        profile.P[i] = IdealPressure(n, profile.T[i], profile.V[i]);
    }
    if(method == 2){
        incr = P2 - P1;
        incr = (incr)/reso;
        
        profile.P[i] = P1;
        profile.T[i] = T;
        profile.V[i] = IdealVolume(n, profile.P[i], profile.T[i]);
    }
    profile.W_V[i] = 0.0;
    total = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            profile.V[i] = profile.V[i-1] + incr;
            profile.T[i] = T;
            profile.P[i] = IsotFinalPressure(profile.P[i - 1], profile.V[i-1], profile.V[i]);
            profile.W_V[i] = IsotVolume(n, profile.T[i], profile.V[i-1], profile.V[i]);
            total = total + profile.W_V[i];
        }
        if(method == 2){
            profile.P[i] = profile.P[i-1] + incr;
            profile.T[i] = T;
            profile.V[i] = IsotFinalVolume(profile.V[i - 1], profile.P[i-1], profile.P[i]);
            profile.W_V[i] = IsotPressure(n, profile.T[i], profile.P[i-1], profile.P[i]);
            total = total + profile.W_V[i];
        }
    }
    printf("Total Volume work done = %.3f kW\n", total*0.001);
    printf("Profile calculated in %d rows\n\n", i);
    
    return profile;
}

/// MARK: DISPLAY AND WRITE
void IsotProcDisplay(double P1, double P2, double V1, double V2, double T, double n, T1ThermoProf profile)
{
    double total = 0.0;
    
    printf("_Isothermal_Process_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure: ");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure: ");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Initial system volume: ");
    printf("V1 =\t%.3f\tm3\n", V1);
    printf("Final system volume: ");
    printf("V2 =\t%.3f\tm3\n\n", V2);
    
    printf("System temperature: ");
    printf("T =\t%.3f\tdeg C\n\n", T - 273.15);
    
    printf("_System-Specific_parameters:_\n");
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    printf("R =\t8.3145\tJ/(mol. K)\n\n");
    
    printf("\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\n");
    for(int i = 0; i < 250; ++i)
    {
        printf("%f\t", profile.P[i]*0.001);
        printf("%f\t", profile.V[i]);
        printf("%f\t", profile.T[i]);
        printf("%f\t\t", profile.T[i] - 273.15);
        printf("%f\t", profile.W_V[i]*0.001);
        total += profile.W_V[i]*0.001;
        printf("%f\n", total);
    }
    fflush(stdout);
}

void IsotProcWrite(double P1, double P2, double V1, double V2, double T, double n, T1ThermoProf profile)
{
    //  Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //  Set file name as timestamp + Isothermal Process Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Isothermal Results");
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
    double total = 0.0;
    
    fprintf(fp, "_Isothermal_Process_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure: ");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure: ");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "Initial system volume: ");
    fprintf(fp, "V1 =\t%.3f\tm3\n", V1);
    fprintf(fp, "Final system volume: ");
    fprintf(fp, "V2 =\t%.3f\tm3\n\n", V2);
    
    fprintf(fp, "System temperature: ");
    fprintf(fp, "T =\t%.3f\tdeg C\n\n", T - 273.15);
    
    fprintf(fp, "_System-Specific_parameters:_\n");
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n", n*0.001);
    fprintf(fp, "R =\t8.3145\tJ/(mol. K)\n\n");
    
    fprintf(fp, "\tOutput parameters:\n");
    
    //  Profile (Two Temperature columns (K and deg C))
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\n");
    for(int i = 0; i < 250; ++i)
    {
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "%f\t\t", profile.T[i] - 273.15);
        fprintf(fp, "%f\t", profile.W_V[i]*0.001);
        total += profile.W_V[i]*0.001;
        fprintf(fp, "%f\n", total);
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void IsotProcWriteSwitch(double P1, double P2, double V1, double V2, double T, double n, T1ThermoProf profile)
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
                IsotProcWrite(P1, P2, V1, V2, T, n, profile);
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
void Isothermal()
{
    //Main Function
    int whilmain = 0;
    printf("Isothermal Process\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];          // Varaible used to store character input.
        int method = 0;                 // Variable used to control system behaviour.
        int whilmethod = 0;             // Variable used to control user input.
        int elems = 0;                  // Variable used to store the total number of elements used in the profile struct.
        
        elems = 5*250;
        
        T1ThermoProf *profile = calloc(elems, sizeof(double));   // Struct used to store the generated isothermal process profile.
        
        double P1 = 0.0;                // Initial system pressure.
        double P2 = 0.0;                // Final system pressure.
        double V1 = 0.0;                // Initial system volume.
        double V2 = 0.0;                // Final system volume.
        double T = 0.0;                 // System temperature.
        double n = 0.0;                 // Moles of component in system
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //Data collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure\n2. Volume\n");
            printf("Selection [1 - 2]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'P':
                case 'p':
                    //code
                    method  = 2;
                    whilmethod = 0;
                    break;
                case '2':
                case 'V':
                case 'v':
                    //code
                    method = 1;
                    whilmethod = 0;
                    break;
                case 'Q':
                case 'q':
                case '0':
                    whilmethod = 0;
                    whilmain = 0;
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1||method == 2){
            IsotVariable(method, &P1, &P2, &V1, &V2, &T, &n);
            
            //  Running calculations
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            *profile = IsotProfile(method, n, T, P1, P2, V1, V2);
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying results
            IsotProcDisplay(P1, P2, V1, V2, T, n, *profile);
            
            //  Writing to File
            IsotProcWriteSwitch(P1, P2, V1, V2, T, n, *profile);
            free(profile);
        }
        //Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
