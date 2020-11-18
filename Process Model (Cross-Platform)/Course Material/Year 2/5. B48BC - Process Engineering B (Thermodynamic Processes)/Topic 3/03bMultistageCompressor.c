//
//  03bMultistageCompressor.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 28/10/2020.
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

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void MSCompVariable(double *P1, double *P2, double *Vc, double *T1, double *n, int *N, double *gamma)
{
    *P1 = inputDouble(0, 0, "system pressure before compression", "kPa");
    *P1 = (*P1)*1000;
    
    *P2 = inputDouble(0, 0, "final system pressure", "kPa");
    *P2 = (*P2)*1000;
    
    *Vc = inputDouble(0, 0, "clearance volume", "m3");
    
    *T1 = inputDouble(1, 1, "system temperature before compression", "deg C");
    *T1 = (*T1) + 273.15;
    
    *n = inputDouble(0, 0, "molar flowrate", "kmol/s");
    *n = (*n)*1000;
    
    *gamma = inputDouble(0, 0, "heat capacity ratio", "[ ]");
    
    int control = 0;
    control = 1;
    while(control == 1){
        *N = (int)inputDouble(0, 0, "number of stages", "[ ]");
        if(*N <= 6){
            // struct will divide nicely
            control = 0;
        }else{
            printf("Too many stages have been given, please enter an integer between 1 and 6.\n");
        }
    }
}

/// MARK: GENERAL CALCULATIONS
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

/// MARK: ARRAY FUNCTION
T3CompProfile MSCompProfile(double P1, double P2, double Vc, double T1, double n, int N, double gamma)
{
    T3CompProfile profile = {0.0};
    
    double ratio = 0.0; // Optimum pressure ratio.
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
    double Vstart = 0.0;
    
    for(int stage = 0; stage < N; ++stage)
    {
        // Intake (Vc to V1)
        if(stage == 0){
            elem = 0;
            profile.P[elem] = P1;
            profile.V[elem] = Vc;
            profile.T[elem] = T1;
            profile.W_V[elem] = 0.0;
            profile.W_S[elem] = 0.0;
        }else{
            elem = stageIntake(1500, stage, N);
            profile.P[elem] = profile.P[elem-1];
            profile.V[elem] = Vc;
            profile.T[elem] = profile.T[elem - 1];
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
            profile.T[i] = profile.T[i - 1];
            profile.W_V[i] = IsobVolume(profile.P[i - 1], profile.V[i - 1], profile.V[i]);
            profile.W_S[i] = 0.0;
        }
        
        // Adiabatic Process
            // Finding intermediate pressure and calculating consequent pressure increment.
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
            profile.V[i] = profile.V[i - 1] + incr;
            profile.T[i] = profile.T[i - 1];
            profile.W_V[i] = IsobVolume(profile.P[i], profile.V[i-1], profile.V[i]);
            elem = i;
        }
        printf("Stage successfully calculated\n\n");
    }
    
    return profile;
}

/// MARK: DISPLAY AND WRITE
void MSCompDisplay(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double N, double gamma, T3CompProfile profile)
{
    printf("_Multistage_Compressor_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure: ");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure: ");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Clearance volume:\n");
    printf("Vc =\t%.3f\tm3\n", Vc);
    printf("Initial system volume before compression: ");
    printf("V1 =\t%.3f\tm3\n", V1);
    printf("Final system volume after compression: ");
    printf("V2 =\t%.3f\tm3\n\n", V2);
    
    printf("Initial system temperature: ");
    printf("T1 =\t%.3f\tdeg C\n", T1-273.15);
    printf("Final system temperature: ");
    printf("T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
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
    fflush(stdout);
}

void MSCompWrite(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double N, double gamma, T3CompProfile profile)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Multistage Compressor Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Multistage Results");
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
    fprintf(fp, "_Multistage_Compressor_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure: ");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure: ");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "Clearance volume:\n");
    fprintf(fp, "Vc =\t%.3f\tm3\n", Vc);
    fprintf(fp, "Initial system volume before compression: ");
    fprintf(fp, "V1 =\t%.3f\tm3\n", V1);
    fprintf(fp, "Final system volume after compression: ");
    fprintf(fp, "V2 =\t%.3f\tm3\n\n", V2);
    
    fprintf(fp, "Initial system temperature: ");
    fprintf(fp, "T1 =\t%.3f\tdeg C\n", T1-273.15);
    fprintf(fp, "Final system temperature: ");
    fprintf(fp, "T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
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
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void MSCompSwitch(int mode, double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double N, double gamma, T3CompProfile profile)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        if(mode == 1){
            printf("Do you want to display the results? ");
        }
        if(mode == 2){
            printf("Do you want to save results to file? ");
        }
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                if(mode == 1){
                    MSCompDisplay(P1, P2, Vc, V1, V2, T1, T2, n, N, gamma, profile);
                }
                if(mode == 2){
                    MSCompWrite(P1, P2, Vc, V1, V2, T1, T2, n, N, gamma, profile);
                }
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
void MultistageCompressor(void)
{
    int whilmain = 0;
    printf("Multistage Gas Compression (Adiabatic)\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        int elems = 0;                  // Variable used to store the total number of elements used in the data struct.
        
        elems = 5*1500;
        
        T3CompProfile *profile = calloc(elems, sizeof(double));  // Struct where the generated multistage adiabat is stored.
        double V1 = 0.0;                // Initial system volume before compression.
        double V2 = 0.0;                // Final system volume after multistage compression.
        double T2 = 0.0;                // Final system temperature after multistage compression.
        
        double P1 = 0.0;                // Initial system pressure.
        double P2 = 0.0;                // Final system temperature.
        double Vc = 0.0;                // Clearance volume.
        double T1 = 0.0;                // Initial system temperature of each stage before compression.
        double n = 0.0;                 // Moles of component in system.
        int N = 0.0;                    // Number of compression stages (Max. 6)
        double gamma = 0.0;             // Heat capacity ratio.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        MSCompVariable(&P1, &P2, &Vc, &T1, &n, &N, &gamma);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        *profile = MSCompProfile(P1, P2, Vc, T1, n, N, gamma);
        
        V1 = profile->V[9];
        V2 = profile->V[1489];
        T2 = profile->T[1499];
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        MSCompSwitch(1, P1, P2, Vc, V1, V2, T1, T2, n, N, gamma, *profile);
        
        //  Writing to File
        MSCompSwitch(2, P1, P2, Vc, V1, V2, T1, T2, n, N, gamma, *profile);
        free(profile);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
