//
//  03bMultistageCompressor.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 28/10/2020.
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
#include "IdealGasLaw.h"
#include "01cIsobaric.h"
#include "01eAdiabatic.h"
#include "02bPolyShaftWork.h"
#include "03bMultistageCompressor.h"

#define maxstrlen 128
#define R 8.3145

void MSCompVariable(double *P1, double *P2, double *Vc, double *T1, double *n, int *N, double *gamma)
{
    *P1 = inputDouble(0, "system pressure before compression", "kPa");
    *P1 = (*P1)*1000;
    
    *P2 = inputDouble(0, "final system pressure", "kPa");
    *P2 = (*P2)*1000;
    
    *Vc = inputDouble(0, "clearance volume", "m3");
    
    *T1 = inputDouble(1, "system temperature before compression", "kPa");
    *T1 = (*T1) + 273.15;
    
    *n = inputDouble(0, "molar flowrate", "kmol/s");
    *n = (*n)*1000;
    
    *gamma = inputDouble(0, "heat capacity ratio", "[ ]");
    
    int control = 0;
    control = 1;
    while(control == 1){
        *N = (int)inputDouble(0, "number of stages", "[ ]");
        if(*N <= 6){
            // struct will divide nicely
            control = 0;
        }else{
            printf("Too many stages have been given, please enter a lower value.\n");
        }
    }
}

double calculatePressureRatio(double P1, double P2)
{
    return P2/P1;
}

int stageIntake(int elements, int stage, int stages)
{
    int hold = 0;
    
    hold = elements/stages;
    hold = stage*(hold);
    
    return hold;
}

int stageProcess(int elements, int stage, int stages)
{
    int hold = 0;
    
    hold = elements/stages;
    hold = stage*(hold);
    
    hold = (hold) + 10;
    
    return hold;
}

int ProcessStages(int elements, int stages)
{
    int points = 0;
    
    points = elements/stages;
    points = (points) - 20;
    
    return points;
}

int stageDischarge(int elements, int stage, int stages)
{
    int hold = 0;
    
    hold = elements/stages;
    hold = (stage + 1)*(hold);
    
    hold = (hold) - 10;
    
    return hold;
}

T3CompProfile MSCompProfile(double P1, double P2, double Vc, double T1, double n, int N, double gamma)
{
    static T3CompProfile profile;
    
    // Initialising values in the struct
    for(int i = 0; i < 1500; ++i){
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = 0.0;
        profile.W_V[i] = 0.0;
        profile.W_S[i] = 0.0;
        // 7500 total double elements = 60 000 bytes = 60 KB required. Struct is fine living on the stack.
    }
    
    // Declaring variables to be used throughout the process;
    double ratio = 0.0;
    double PInt = 0.0;  // Intermediate pressure
    double VInt = 0.0;  // Intermediate volume
    double incr = 0.0;  // Increment between pressure values
    int elem = 0;       // Element counter
    
    // Finding the optimum pressure ratio for each stage.
    double power = 0.0;
    ratio = calculatePressureRatio(P1, P2);
    power = (1.0)/N;
    
    ratio = pow(ratio, power);
    PInt = P1*ratio;
    
    //  Loading initial values
    elem = 0;
    
    
    double Vstart = 0.0;
    
    for(int stage = 0; stage < N; ++stage)
    {
        // Intake (Vc to V1)
        if(stage == 0){
            elem = 0;
            profile.P[elem] = P1;
            profile.V[elem] = Vc;
            profile.T[elem] = IdealTemperature(n, profile.P[elem], profile.V[elem]);
            profile.W_V[elem] = 0.0;
            profile.W_S[elem] = 0.0;
        }else{
            elem = stageIntake(1500, stage, N);
            profile.P[elem] = profile.P[elem-1];
            profile.V[elem] = Vc;
            profile.T[elem] = IdealTemperature(n, profile.P[elem], profile.V[elem]);
            profile.W_V[elem] = 0.0;
            profile.W_S[elem] = 0.0;
        }
            // Finding V1
        Vstart = IdealVolume(n, profile.P[elem], T1);
        
        incr = Vstart - profile.V[elem];
        incr = (incr)/9;
        
            // Running isobaric expansion (Intake stroke).
        for(int i = elem + 1; i < stageProcess(1500, stage, N); ++i)
        {
            profile.P[i] = profile.P[i - 1];
            profile.V[i] = profile.V[i - 1] + incr;
            profile.T[i] = IsobFinalTemperature(profile.V[i - 1], profile.V[i], profile.T[i-1]);
            profile.W_V[i] = IsobVolume(profile.P[i - 1], profile.V[i - 1], profile.V[i]);
            profile.W_S[i] = 0.0;
        }
        
        // Adiabatic Process
            // Finding intermediate pressure and pressure increment.
        if(stage == 0){
            PInt = ratio*(profile.P[0]);
            
            incr = PInt - (profile.P[0]);
            incr = (incr)/(double)ProcessStages(1500, N);
        }else{
            PInt = ratio*(profile.P[stageIntake(1500, stage, N)]);
            
            incr = PInt -(profile.P[stageIntake(1500, stage, N)]);
            incr = (incr)/(double)ProcessStages(1500, N);
        }
        
            // Finding the adiabat
        for(int i = stageProcess(1500, stage, N); i < stageDischarge(1500, stage, N); ++i)
        {
            profile.P[i] = profile.P[i - 1] + incr;
            profile.T[i] = AdiaFinalTemp(profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma);
            profile.V[i] = AdiaFinalVol(profile.V[i-1], profile.P[i-1], profile.P[i], gamma);
            profile.W_V[i] = AdiaTemperature(n, profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma);
            profile.W_S[i] = PolyShaftCalculation(n, R, profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma);
        }
        
        // Process discharge (V to Vc)
        VInt = profile.V[stageDischarge(1500, stage, N) - 1];
        
        incr = Vc - VInt;
        incr = (incr)/10;
        
        for(int i = stageDischarge(1500, stage, N); i < stageIntake(1500, stage +1, N); ++i)
        {
            profile.P[i] = profile.P[i - 1];
            profile.V[i] = profile.V[i-1] + incr;
            profile.T[i] = IsobFinalTemperature(profile.V[i-1], profile.V[i], profile.T[i-1]);
            profile.W_V[i] = IsobVolume(profile.P[i], profile.V[i-1], profile.V[i]);
        }
        printf("Stage successfully calculated\n\n");
    }
    
    return profile;
}

void MSCompDisplay(double P1, double P2, double Vc, double T1, double n, double N, double gamma, T3CompProfile profile)
{
    printf("_Multistage_Compressor_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure: ");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure: ");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Clearance volume:\n");
    printf("Vc =\t%.3f\tm3\n\n", Vc);
    
    printf("Initial system temperature: ");
    printf("T1 =\t%.3f\tdeg C\n\n", T1-273.15);
    
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    printf("Universal Gas Constant:\n");
    printf("R =\t%.4f\tJ/(mol. K)\n\n", R);
    
    printf("Heat capacity ratio:\n");
    printf("gamma =\t%.3f\t[ ]\n\n", gamma);
    
    printf("\tOutput parameters:\n");
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_S (kW)\n");
    for(int i = 0; i < 1500; ++i){
        printf("%f\t", profile.P[i]*0.001);
        printf("%f\t", profile.V[i]);
        printf("%f\t", profile.T[i]);
        printf("%f\t\t", profile.T[i] - 273.15);
        printf("%f\t", profile.W_V[i]*0.001);
        printf("%f\n", profile.W_S[i]*0.001);
    }
}

void MSCompWrite(double P1, double P2, double Vc, double T1, double n, double N, double gamma, T3CompProfile profile)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Multistage Compressor Results
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
    
    strcat(filename, " Multistage Results");
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
    void free(void *filename); // Removing 'filename' from the heap
    
    printf("File name: \"%s\"\n", filename);
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
    fprintf(fp, "_Multistage_Compressor_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure: ");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure: ");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "Clearance volume:\n");
    fprintf(fp, "Vc =\t%.3f\tm3\n\n", Vc);
    
    fprintf(fp, "Initial system temperature: ");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n\n", T1-273.15);
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n", n*0.001);
    fprintf(fp, "Universal Gas Constant:\n");
    fprintf(fp, "R =\t%.3f\tJ/(mol. K)\n\n", R);
    
    fprintf(fp, "Heat capacity ratio:\n");
    fprintf(fp, "gamma =\t%.3f\t[ ]\n\n", gamma);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_S (kW)\n");
    for(int i = 0; i < 1500; ++i){
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "%f\t\t", profile.T[i] - 273.15);
        fprintf(fp, "%f\t", profile.W_V[i]*0.001);
        fprintf(fp, "%f\n", profile.W_S[i]*0.001);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void MSCompWriteSwitch(double P1, double P2, double Vc, double T1, double n, double N, double gamma, T3CompProfile profile)
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
                MSCompWrite(P1, P2, Vc, T1, n, N, gamma, profile);
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

void MultistageCompressor(void)
{
    int whilmain = 0;
    printf("Multistage Gas Compression (Adiabatic)\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double P1 = 0.0;
        double P2 = 0.0;
        double Vc = 0.0;
        double T1 = 0.0;
        double n = 0.0;
        int N = 0.0;
        double gamma = 0.0;
        
        T3CompProfile profile = {0.0};
        
        //  Data Collection
        MSCompVariable(&P1, &P2, &Vc, &T1, &n, &N, &gamma);
        
        //  Data Manipulation
        clock_t start, end;
        double timeTaken = 0.0;
        
        start = clock();
        
        profile = MSCompProfile(P1, P2, Vc, T1, n, N, gamma);
        
        end = clock();
        
        timeTaken = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Process completed in %.3f seconds.\n\n", timeTaken);
        
        //  Displaying results
        MSCompDisplay(P1, P2, Vc, T1, n, N, gamma, profile);
        
        //  Writing to File
        MSCompWriteSwitch(P1, P2, Vc, T1, n, N, gamma, profile);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
