//
//  01eAdiabatic.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 07/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "01eAdiabatic.h"
#include "IdealGasLaw.h"

#define maxstrlen 128
#define R 8.3145 // J/mol.K

void AdiaVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T1, double *n, double *gamma)
{
    char input[maxstrlen];
    
    if(method == 1||method == 2){
        *P1 = inputDouble(0, "initial system pressure", "kPa");
        *P1 = (*P1)*1000;
    }
    if(method == 2){
        *P2 = inputDouble(0, "final system pressure", "kPa");
        *P2 = (*P2)*1000;
    }
    if(method == 1){
        *V1 = inputDouble(0, "initial system volume", "m3");
        *V2 = inputDouble(0, "final system volume", "m3");
    }
    if(method == 2){
        *T1 = inputDouble(1, "initial system temperature", "deg C");
        *T1 = (*T1)+273.15;
    }
    if(method == 1 || method == 2){
        *n = inputDouble(0, "molar flowrate", "kmol/s");
        *n = (*n)*1000;
    }
    if(method == 1 || method == 2)
    {
        printf("Heat capacity ratio ([]): ");
        *gamma = atof(fgets(input, sizeof(input), stdin));
    }
    
    fflush(stdout);
}

double AdiaVolume(double P1, double V1, double V2, double gamma)
{
    double frac1num = 0.0;
    double frac1den = 0.0;
    double frac2 = 0.0;
    double power = 0.0;
    double brack = 0.0;
    double work = 0.0;
    
    frac2 = V1/V2;
    power = gamma - 1;
    brack = pow(frac2, power);
    brack = 1 - brack; // Bracket term calculated
    
    frac1num = P1*V1;
    frac1den = 1 - gamma; 
    
    work = frac1num/frac1den; // Starting fraction calculated
    work = work*brack;
    
    return work;
}

double AdiaTemperature(double n, double T1, double P1, double P2, double gamma)
{
    double frac1num = 0.0;
    double frac1den = 0.0;
    double frac2 = 0.0;
    double power = 0.0;
    double brack = 0.0;
    double work = 0.0;
    
    frac2 = P2/P1;
    power = gamma - 1;
    power = (power)/gamma;
    
    brack = pow(frac2, power);
    brack = 1 - brack; // Bracket term calculated
    
    frac1num = n*R;
    frac1num = frac1num*T1;
    frac1den = gamma - 1; 
    
    work = frac1num/frac1den; // Starting fraction calculated
    work = work*brack; // Volume work calculated
    work = work*(-1);
    
    return work;
}

double AdiaFinalPress(double P1, double V1, double V2, double gamma)
{
    double V1f = 0.0;
    double V2f = 0.0;
    double P = 0.0;
    
    // Used for the Pressure-Volume relation
    V1f = pow(V1, gamma);
    V2f = pow(V2, gamma);
    
    P = P1*V1f;
    P = (P)/V2f;
    
    return P;
}

double AdiaFinalTemp(double T1, double P1, double P2, double gamma)
{
    double power = 0.0;
    double PRatio = 0.0;
    double T = 0.0;
    // Calculated from Pressure-Temperature relation
    power = gamma - 1;
    power = (power)/gamma;
    
    PRatio = P2/P1;
    
    T = pow(PRatio, power);
    T = T1*(T);
    
    return T;
}

double AdiaFinalVol(double V1, double P1, double P2, double gamma)
{
    // Can also calculate using temperature but using pressure is less computationally expensive.
    double V2 = 0.0;
    double power = 0.0;
    double frac = 0.0;
    
    frac = P1/P2;
    power = (1.0)/(gamma);
    frac = pow(frac, power);
    
    V2 = frac*V1;
    
    return V2;
}

T1ThermoProf AdiaProfile(int method, double P1, double P2, double V1, double V2, double T1, double n, double gamma)
{
    double incr = 0.0;  // Difference between datapoints.
    int reso = 249;     // Resolution of dataset.
    int i = 0;          // Row controller.
    
    T1ThermoProf profile = {0.0};
    // Initialising profile to arrays on zeros
    for(int j = 0; j < 250; ++j){
        profile.P[j] = 0.0;
        profile.V[j] = 0.0;
        profile.T[j] = 0.0;
        profile.W_V[j] = 0.0;
        profile.Q[j] = 0.0;
    }
    
    double total = 0.0;
    
    if(method == 1){
        // Volume work calculated from volume ratio
        incr = V2 - V1;
        incr = (incr)/reso;
    }
    if(method == 2){
        // Volume work calculated from pressure ratio
        incr = P2 - P1;
        incr = (incr)/reso;
    }
    
    i = 0;
    if(method == 1)
    {
        profile.P[i] = P1;
        profile.V[i] = V1;
        profile.T[i] = IdealTemperature(n, profile.P[i], profile.V[i]);
        
        profile.W_V[i] = 0.0;
        total = 0.0;
    }
    if(method == 2)
    {
        profile.P[i] = P1;
        profile.T[i] = T1;
        profile.V[i] = IdealVolume(n, profile.P[i], profile.T[i]);
        
        profile.W_V[i] = 0.0;
        total = 0.0;
    }
    for(i = 1; i< (reso+1) ; ++i)
    {
        if(method == 1)
        {
            profile.V[i] = profile.V[i - 1] + incr;
            profile.P[i] = AdiaFinalPress(profile.P[i - 1], profile.V[i - 1], profile.V[i], gamma);
            profile.T[i] = AdiaFinalTemp(profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma);
            profile.W_V[i] = AdiaVolume(profile.P[i - 1], profile.V[i - 1], profile.V[i], gamma);
            total += profile.W_V[i];
        }
        if(method == 2)
        {
            profile.P[i] = profile.P[i - 1]+incr;
            profile.T[i] = AdiaFinalTemp(profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma);
            profile.V[i] = AdiaFinalVol(profile.V[i - 1], profile.P[i - 1], profile.P[i], gamma);
            profile.W_V[i] = AdiaTemperature(n, profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma);
            total += profile.W_V[i];
        }
    }
    printf("Total Volume work done = %.3f kW\n", total*0.001);
    printf("Profile calculated in %d rows\n\n", i);
    
    return profile;
}

void AdiaProcDisplay(double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma, T1ThermoProf profile)
{
    double total = 0.0;
    
    printf("_Adiabatic_Process_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure: ");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure: ");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Initial system volume: ");
    printf("V1 =\t%.3f\tm3\n", V1);
    printf("Final system volume: ");
    printf("V2 =\t%.3f\tm3\n\n", V2);
    
    printf("Initial system temperature: ");
    printf("T1 =\t%.3f\tdeg C\n", T1-273.15);
    printf("Final system volume: ");
    printf("T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    printf("_System-Specific_parameters:_\n");
    
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    printf("R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    printf("Adiabatic Index:\n");
    printf("gamma =\t%.3f\t[ ]\n\n", gamma);
    
    printf("\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\n");
    for(int i = 0; i < 250; ++i){
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

void AdiaProcWrite(double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma, T1ThermoProf profile)
{
    //Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Adiabatic Process Results
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
    
    strcat(filename, " Adiabatic Results");
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
    double total = 0.0;
    
    fprintf(fp, "_Adiabatic_Process_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure: ");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure: ");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "Initial system volume: ");
    fprintf(fp, "V1 =\t%.3f\tm3\n", V1);
    fprintf(fp, "Final system volume: ");
    fprintf(fp, "V2 =\t%.3f\tm3\n\n", V2);
    
    fprintf(fp, "Initial system temperature: ");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1-273.15);
    fprintf(fp, "Final system volume: ");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    fprintf(fp, "_System-Specific_parameters:_\n");
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n", n*0.001);
    fprintf(fp, "R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    fprintf(fp, "Adiabatic Index:\n");
    fprintf(fp, "gamma =\t%.3f\t[ ]\n\n", gamma);
    
    fprintf(fp, "\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\n");
    for(int i = 0; i < 250; ++i){
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "%f\t\t", profile.T[i] - 273.15);
        fprintf(fp, "%f\t", profile.W_V[i]*0.001);
        total += profile.W_V[i]*0.001;
        fprintf(fp, "%f\n", total);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void AdiaProcWriteSwitch(double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma, T1ThermoProf profile)
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
                AdiaProcWrite(P1, P2, V1, V2, T1, T2, n, gamma, profile);
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

void Adiabatic()
{
    //Main Function
    int whilmain = 0;
    
    printf("Adiabatic Volume Work\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];          // Variable used to store character input.
        int method = 0;                 // Variable used to control subroutine behaviour.
        int whilmethod = 0;             // Variable used to control user input.
        
        T1ThermoProf profile = {0.0};   // Struct used to store the generated adiabatic process profile.
        double T2 = 0.0;                // Final system temperature.
        
        double P1 = 0.0;                // Initial system pressure.
        double P2 = 0.0;                // Final system pressure.
        double V1 = 0.0;                // Initial system volume.
        double V2 = 0.0;                // Final system volume.
        double T1 = 0.0;                // Initial system temperature.
        double n = 0.0;                 // Moles of component in system.
        double gamma = 0.0;             // Heat capacity ratio.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //Data collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure-Volume\n2. Pressure-Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'V':
                case 'v':
                    //code
                    method  = 1;
                    whilmethod = 0;
                    break;
                case '2':
                case 'T':
                case 't':
                    //code
                    method = 2;
                    whilmethod = 0;
                    break;
                case 'Q':
                case 'q':
                    whilmethod = 0;
                    whilmain = 0;
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1||method == 2){
            //  Collecting data
            AdiaVariable(method, &P1, &P2, &V1, &V2, &T1, &n, &gamma);
            
            //  Running calculations
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            profile = AdiaProfile(method, P1, P2, V1, V2, T1, n, gamma);
            
            T2 = profile.T[249];
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying results
            AdiaProcDisplay(P1, P2, V1, V2, T1, T2, n, gamma, profile);
            
            //  Writing to File
            AdiaProcWriteSwitch(P1, P2, V1, V2, T1, T2, n, gamma, profile);
        }
        //Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
