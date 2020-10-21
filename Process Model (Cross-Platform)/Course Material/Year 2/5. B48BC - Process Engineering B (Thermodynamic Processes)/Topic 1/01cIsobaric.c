//
//  01cIsobaric.c
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
#include <time.h>

//Custom Header Files
#include "01cIsobaric.h"
#include "IdealGasLaw.h"

#define maxstrlen 128
#define R 8.3145

void IsobVariable(int method, double *P, double *V1,double *V2, double *T1, double *T2, double *n)
{
    char input[maxstrlen];
    
    if(method == 1){
        printf("System pressure (kPa) = ");
        *P = atof(fgets(input, sizeof(input), stdin));
        *P = (*P)*1000;
        
        printf("Initial system volume (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
        
        printf("Final system volume (m3) = ");
        *V2 = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 2){
        printf("Initial system temperature (deg C) = ");
        *T1 = atof(fgets(input, sizeof(input), stdin));
        *T1 = (*T1) + 273.15;
        
        printf("Final system temperature (deg C) = ");
        *T2 = atof(fgets(input, sizeof(input), stdin));
        *T2 = (*T2) + 273.15;
    }
    if(method == 1 || method == 2){
        printf("Moles of substance (kmol/s) = ");
        *n = atof(fgets(input, sizeof(input), stdin));
        *n = (*n)*1000;
    }
    fflush(stdout);
}

double IsobVolume(double P, double V1, double V2)
{
    double work = 0.0;
    
    work = V2 - V1;
    work = P*(work);
    work = -1*(work);
    
    return work;
}

double IsobTemperature(double n, double T1, double T2)
{
    double work = 0.0;
    
    work = T2 - T1;
    work = R*(work);
    work = n*(work);
    
    return work;
}

double IsobFinalTemperature(double V1, double V2, double T1)
{
    double T2 = 0.0;
    
    T2 = V2/V1;
    T2 = (T2)*T1;
    
    return T2;
}

T1ThermoProf IsobProfile(int method, double P, double V1, double V2, double T1, double T2, double n)
{
    double incr = 0.0; // Increment between data points
    int reso = 0; // Resolution of generated plot
    int i = 0; // Row controller
    
    T1ThermoProf profile;
    double total = 0.0;
    
    reso = 249;
    
    if(method == 1){
        incr = V2 - V1;
        incr = (incr)/reso;
    }
    if(method == 2){
        incr = T2 - T1;
        incr = (incr)/reso;
    }
    
    // Setting initial system conditions
    i = 0;
    if(method == 1){
        profile.P[i] = P;
        profile.V[i] = V1;
        profile.T[i] = IdealTemperature(n, profile.P[i], profile.V[i]);
    }
    if(method == 2){
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = T1;
    }
    profile.W_V[i] = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            profile.P[i] = P;
            profile.V[i] = profile.V[i - 1] + incr;
            profile.T[i] = IsobFinalTemperature(profile.V[i - 1], profile.V[i], profile.T[i - 1]);
            profile.W_V[i] = IsobVolume(profile.P[i], profile.V[i-1], profile.V[i]);
            total = total + profile.W_V[i];
        }
        if(method == 2){
            profile.P[i] = 0.0;
            profile.V[i] = 0.0;
            profile.T[i] = profile.T[i - 1] + incr;
            profile.W_V[i] = IsobTemperature(n, profile.T[i - 1], profile.T[i]);
            total = total + profile.W_V[i];
        }
    }
    
    if(method == 1 || method == 2){
        printf("Total Volume work done = %.3f kW\n", total*0.001);
        printf("Profile calculated in %d rows\n\n", i);
    }
    fflush(stdout);
    return profile;
}

void IsobProcWrite(double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Isobaric Process Results
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof *filename);
    
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Isobaric Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");
    printf("File path: \"%s\"\n", filepath);
    
    strcat(filepath, filename);
    void free(void *filename); // Removing 'filename' from the heap
    
    printf("File name: \"%s\"\n", filename);
    printf("Full file path: \"%s\"\n\n", filepath);
    
    //Testing if directory is not present
    if(fopen(filepath, "r") == NULL){
        printf("Directory does not exist, writing data to \"Documents\" folder instead.\n");
        strcpy(filepath, "/Users/user/Documents/");
        printf("File is now being outputted to: %s\n", filepath);
    }
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filepath, "w+");
    
    //Write to file
    fprintf(fp, "_Isobaric_Process_Results_\n");
    
    //Write to file
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "System pressure: ");
    fprintf(fp, "P =\t%.3f\tkPa\n\n", P*0.001);
    
    fprintf(fp, "Initial system volume: ");
    fprintf(fp, "V1 =\t%.3f\tm3\n\n", V1);
    fprintf(fp, "Final system volume: ");
    fprintf(fp, "V2 =\t%.3f\tm3\n\n", V2);
    
    fprintf(fp, "Initial system temperature: ");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n\n", T1-273.15);
    fprintf(fp, "Final system volume: ");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    fprintf(fp, "_System-Specific_parameters:_\n");
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n\n", n);
    fprintf(fp, "R =\t%.3f\tJ/(mol. K)\n\n", R);
    
    fprintf(fp, "\tOutput parameters:\n");
    
    double total = 0.0;
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

void IsobProcWriteCheck(double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile)
{
    int SaveC;
    SaveC = 1;
    while(SaveC == 1)
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
                IsobProcWrite(P, V1, V2, T1, T2, n, profile);
                SaveC = 0;
                break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                SaveC = 0;
                break;
            default:
                printf("Input not recognised\n");
                break;
        }
    }
}

void Isobaric()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Isobaric Process\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char methodinput[maxstrlen];
        
        double P = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        double n = 0.0;
        
        int method = 0;
        
        static T1ThermoProf profile;
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
        
        //Data Collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure-Volume\n2. Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(methodinput, sizeof(methodinput), stdin);
            switch(methodinput[0])
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
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1 || method == 2){
            //Data collection
            IsobVariable(method, &P, &V1, &V2, &T1, &T2, &n);
            
            //Data manipulation
            profile = IsobProfile(method, P, V1, V2, T1, T2, n);
            
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
            IsobProcWriteCheck(P, V1, V2, T1, T2, n, profile);
            
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
        fflush(stdout);
    }
}
