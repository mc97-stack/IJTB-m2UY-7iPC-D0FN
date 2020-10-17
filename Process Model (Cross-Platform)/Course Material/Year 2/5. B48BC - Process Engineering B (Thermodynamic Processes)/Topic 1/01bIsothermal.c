//
//  01bIsothermal.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Custom Header Files
#include "B48BC_T1.h"
#include "01bIsothermal.h"
#include "IdealGasLaw.h"

#define maxstrlen 128
#define R 8.3145

void IsotVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T, double *n)
{
    char input[maxstrlen];
    
    if(method == 1){
        // Volume definition
        printf("Initial system volume (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
        
        printf("Final system volume (m3) = ");
        *V2 = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 2){
        // Pressure definition
        printf("Initial system pressure (kPa) = ");
        *P1 = atof(fgets(input, sizeof(input), stdin));
        *P1 = (*P1)*1000;
        
        printf("Final system pressure (kPa) = ");
        *P2 = atof(fgets(input, sizeof(input), stdin));
        *P2 = (*P2)*1000;
    }
    if(method == 1 || method == 2){
        // Common variables
        printf("System Temperature (deg C) = ");
        *T = atof(fgets(input, sizeof(input), stdin));
        *T = (*T) + 273.15;
        
        printf("Moles of substance (kmol/s) = ");
        *n = atof(fgets(input, sizeof(input), stdin));
        *n = (*n)*1000;
    }
    fflush(stdout);
}

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

T1ThermoProf IsotProfile(int method, double n, double T, double P1, double P2, double V1, double V2)
{
    double incr = 0.0; // Increment between data points
    int reso = 0; // Resolution of the generated plot
    int i = 0; // Row control
    
    T1ThermoProf profile;
    double total = 0.0;
    
    reso = 249;
    
    if(method == 1){
        incr = V2 - V1;
        incr = (incr)/reso;
    }
    if(method == 2){
        incr = P2 - P1;
        incr = (incr)/reso;
    }
    
    //Setting initial system conditions
    i = 0;
    if(method == 1){
        profile.V[i] = V1;
        profile.T[i] = T;
        profile.P[i] = IdealPressure(n, profile.T[i], profile.V[i]);
    }
    if(method == 2){
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
            profile.P[i] = IdealPressure(n, profile.T[i], profile.V[i]);
            profile.W_V[i] = IsotVolume(n, profile.T[i], profile.V[i-1], profile.V[i]);
            total = total + profile.W_V[i];
        }
        if(method == 2){
            profile.P[i] = profile.P[i-1] + incr;
            profile.T[i] = T;
            profile.V[i] = IdealVolume(n, profile.P[i], profile.T[i]);
            profile.W_V[i] = IsotPressure(n, profile.T[i], profile.P[i-1], profile.P[i]);
            total = total + profile.W_V[i];
        }
    }
    printf("Total Volume work done = %.3f kW\n", total*0.001);
    printf("Profile calculated in %d rows\n\n", i);
    
    return profile;
}

/*
void [Data Plot & Write](...)
{
    char filename[maxstrlen];
    char path[maxstrlen];
    char filepath[maxstrlen*2];

    FILE *fp
    
    //Set file name as timestamp + Name of Program
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof(filename));
    
    strftime(filename, 16, "%Y%m%d %H%M%S", info);
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " (Name of Program)");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof(filepath));
    
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
    printf("Note that write sequence disabled by zsh\n");
    
    //Get file path - This step is optional
    *path = (char)malloc(sizeof(path));
    ...
    
    //Creating the full path and name through concatenation
    *filepath = (char)malloc(sizeof(filepath));
    strcpy(filepath, filepath);
    strcat(filepath, filename);
    strcat(filepath, ".txt");
    
    //Testing if directory exists
    if(fopen(filepath, "r") == NULL)
    {
            printf("Directory does not exist, writing data to \"Documents\" folder\n");
            strcpy(filepath, "/Users/user/Documents/");
            printf("Filepath: %s\n", filepath);
    }
    
    printf("Beginning file write\n");
    //File open
    fp = fopen(filepath, "w+");
    
    //Writing to file
    fprintf(fp, "...", ...);
    ...
    
    //File close
    fclose(fp);
    
    printf("Write successful\n");
    fflush(stdout);
}
*/
void Isothermal()
{
    //Main Function
    char ContCond[maxstrlen];
    char methodinput[maxstrlen];
    
    int whilmain = 0;
    printf("Isothermal Process\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        double n = 0.0;
        double T = 0.0;
        double P1 = 0.0;
        double P2 = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        
        int method = 0;
        
        T1ThermoProf profile;
        double total = 0.0;
        
        // Initialising profile to arrays on zeros
        for(int j = 0; j < 250; ++j){
            profile.P[j] = 0.0;
            profile.V[j] = 0.0;
            profile.T[j] = 0.0;
            profile.W_V[j] = 0.0;
            profile.Q[j] = 0.0;
        }
        
        int whilmethod = 0;
        int whilcont = 0;
        
        //Data collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure\n2. Volume\n");
            printf("Selection [1 - 2]: ");
            fgets(methodinput, sizeof(methodinput), stdin);
            switch(methodinput[0])
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
                    whilmethod = 0;
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1||method == 2){
            IsotVariable(method, &P1, &P2, &V1, &V2, &T, &n);
            
            //Data manipulation
            profile = IsotProfile(method, n, T, P1, P2, V1, V2);
            
            printf("P (kPa)\tV (m3)\tT(deg C)\tW_V (kW)\tW_V (kW)\n");
            for(int i = 0; i < 250; ++i){
                printf("%f\t", profile.P[i]*0.001);
                printf("%f\t", profile.V[i]);
                printf("%f\t", profile.T[i] - 273.15);
                printf("%f\t", profile.W_V[i]*0.001);
                total += profile.W_V[i]*0.001;
                printf("%f\n", total);
            }
            
            //Ask for file write (Remember while loop)
            
            //Continue function
            whilcont = 1;
            while(whilcont == 1)
            {
                printf("Do you want to continue? ");
                fgets(ContCond, sizeof(ContCond), stdin);
                switch(ContCond[0])
                {
                    case '1':
                    case 'T':
                    case 'Y':
                    case 't':
                    case 'y':
                        whilcont = 0;
                    break;
                    case '0':
                    case 'F':
                    case 'N':
                    case 'f':
                    case 'n':
                        whilcont = 0;
                        whilmain = 0;
                    break;
                    default:
                        printf("Input not recognised\n");
                    break;
                }
            }
        }else{
            whilmain = 0;
        }
        
    }
    fflush(stdout);
}
