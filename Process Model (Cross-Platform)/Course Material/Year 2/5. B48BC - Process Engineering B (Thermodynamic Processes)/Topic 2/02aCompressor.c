//
//  02aCompressor.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

// Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Custom header files
#include "System.h"
#include "B48BC_T2.h"
#include "02aCompressor.h"
#include "02bPolyShaftWork.h"

#include "01aPolytropic.h"
#include "01bIsothermal.h"
#include "01cIsobaric.h"

#define maxstrlen 128

void CompressorVar(int method, double *P1, double *P2, double *Vc, double *V1, double *T1, double *T2, double *n, double *R, double *alpha)
{
    char input[maxstrlen];
    
    int compcheck = 0;
    
    if(method == 1 || method == 2){
        printf("Initial system pressure (kPa) = ");
        *P1 = atof(fgets(input, sizeof(input), stdin));
        *P1 = (*P1)*1000;
    }
    if(method == 1 || method == 2){
        compcheck = 1;
        while(compcheck == 1)
        {
            printf("Final system pressure (kPa) = ");
            *P2 = atof(fgets(input, sizeof(input), stdin));
            *P2 = (*P2)*1000;
            if((*P1) > (*P2))
            {
                printf("System pressure at start of compression = %.3f kPa\n", (*P1)*0.001);
                printf("Expansion process has been stated, please re-enter value for P2.\n");
            }else{
                // P2 > P1 indicated a compression is indeed happening
                compcheck = 0;
            }
        }
    }
    
    if(method == 1 || method == 2){
        printf("Initial system temperature (deg C) = ");
        *T1 = atof(fgets(input, sizeof(input), stdin));
        *T1 = (*T1) + 273.15;
    }
    
    if(method == 1 || method == 2){
        printf("Moles present in system (kmol/ s) = ");
        *n = atof(fgets(input, sizeof(input), stdin));
        *n = (*n) * 1000;
    }
    
    if(method == 1 || method == 2){
        printf("Clearance volume (m3) = ");
        *Vc = atof(fgets(input, sizeof(input), stdin));
        
        printf("Maximum system volume before compression (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
    }
    
    
    if(method == 1){
        *R = 8.3145;
    }
    if(method == 2){
        printf("Specific gas constant (J/ mol. K) = ");
        *R = atof(fgets(input, sizeof(input), stdin));
    }
    
    if(method == 1){
        *alpha = 1;
    }
    if(method == 2){
        printf("Polytropic index ([ ]) = ");
        *alpha = atof(fgets(input, sizeof(input), stdin));
    }
    fflush(stdout);
}

T2CompProfile CompressorProfile(int method, double P1, double P2, double Vc, double V1, double T1, double T2, double n, double R, double alpha, double *V2)
{
    T2CompProfile profile;
    
    // Initialising all values in the struct
    for(int i = 0; i < 512; ++i){
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = 0.0;
        profile.W_V[i] = 0.0;
        profile.W_S[i] = 0.0;
        //  2560 total double elements -> 2560 * 8 bytes = 20 480 bytes = 20.480 KB required.
        //  Automatic memory allocation should be able to handle this struct. Assuming typical cache size for a modern computer is about 32 KB. Some computers with a core CPU cache less than 17 KB may struggle with this program. Intel Core i3 - 6100E has a cache size of 3MB so this program should run fine on intel machines.
    }
    double incr = 0.0; // Increment between datapoints
    int elem = 0; // Element counter
    // Stage 1: Isobaric Expansion (Volume increases)
        // This process must occur between elements 0 to 5
    // Expansion from Vc to V1 (Only variable that is changing in this process)
    incr = V1 - Vc;
    incr = (incr)/5; // Vc will go into element 0 process into 1 to 5
    
    // Loading initial values
    elem = 0;
    profile.P[elem] = P1;
    profile.V[elem] = Vc;
    profile.T[elem] = T1;
    profile.W_V[elem] = 0.0;
    profile.W_S[elem] = 0.0;
    
    for(elem = 1; elem < 6; ++ elem){
        profile.P[elem] = P1; // Isobaric process, pressure will stay constant
        profile.V[elem] = profile.V[elem - 1] + incr;
        profile.T[elem] = IsobFinalTemperature(profile.V[elem - 1], profile.V[elem], profile.T[elem - 1]);
        profile.W_V[elem] = IsobVolume(profile.P[elem], profile.V[elem - 1], profile.V[elem]);
        profile.W_S[elem] = profile.V[elem]*(profile.P[elem] - profile.P[elem - 1]); // Pressure is not changing so no shaft work is being done. Calculation is being performed just in case.
    }
    // Stage 2: Isothermal/ Polytropic Compression
        // This process must occur between elements 6 to 505
    if(method == 1 || method == 2){
        // Pressure is used to set the data point on the profile
        incr = P2 - P1;
        incr = (incr)/500;
    }
    
    for(elem = 6; elem < 506; ++elem){
        if(method == 1){
            profile.P[elem] = profile.P[elem - 1] + incr;
            profile.T[elem] = profile.T[5];
            profile.V[elem] = IsotFinalVolume(profile.V[elem - 1], profile.P[elem - 1], profile.P[elem]);
            profile.W_V[elem] = IsotPressure(n, profile.T[elem], profile.P[elem - 1], profile.P[elem]);
            profile.W_S[elem] = IdealShaftCalc(n, R, profile.T[elem - 1], profile.P[elem - 1], profile.P[elem]);
        }
        if(method == 2){
            profile.P[elem] = profile.P[elem - 1] + incr;
            profile.V[elem] = PolyFinalVolume(profile.P[elem - 1], profile.P[elem], profile.V[elem - 1], alpha);
            profile.T[elem] = PolyFinalTemperature(profile.T[elem - 1], profile.P[elem - 1], profile.P[elem], alpha);
            profile.W_V[elem] = PolyVolume(profile.P[elem - 1], profile.P[elem], profile.V[elem - 1], alpha);
            profile.W_S[elem] = PolyShaftCalc(n, R, profile.T[elem - 1], profile.P[elem - 1], profile.P[elem], alpha);
        }
    }
    *V2 = profile.V[505];
    
    // Stage 3: Isobaric Compression (Volume decreases
        // This process must occur between elements 506 to 511
    // System volume is used to set the data points on the profile
    incr = Vc - profile.V[505];
    incr = (incr)/6;
    
    for(elem = 506; elem < 512; ++elem){
        profile.P[elem] = profile.P[505]; // Isobaric process, pressure will stay constant
        profile.V[elem] = profile.V[elem - 1] + incr;
        profile.T[elem] = IsobFinalTemperature(profile.V[elem - 1], profile.V[elem], profile.T[elem - 1]);
        profile.W_V[elem] = IsobVolume(profile.P[elem], profile.V[elem - 1], profile.V[elem]);
        profile.W_S[elem] = profile.V[elem]*(profile.P[elem] - profile.P[elem - 1]); // Pressure is not changing so no shaft work is being done. Calculation is being performed just in case.
    }
    
    return profile;
}

void CompresDisp(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double R, double alpha, T2CompProfile profile)
{
    printf("_Reciprocating_Compressor_Results_\n");
    printf("\tInput parameters:\n");
    printf("Initial system pressure: ");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Final system pressure: ");
    printf("P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    printf("Clearance volume:\n");
    printf("Vc =\t%.3f\tm3\n", Vc);
    printf("System volume before compression: ");
    printf("V1 =\t%.3f\tm3\n", V1);
    printf("System volume after compression: ");
    printf("V2 =\t%.3f\tm3\n\n", V2);
    
    printf("Initial system temperature: ");
    printf("T1 =\t%.3f\tdeg C\n", T1-273.15);
    printf("Final system volume: ");
    printf("T2 =\t%.3f\tdeg C\n\n", T2-273.15);
    
    printf("_System-Specific_parameters:_\n");
    printf("Molar flowrate of component i:\n");
    printf("n =\t%.3f\tkmol/s\n", n*0.001);
    if( (fabs( R - (8.3145) ) < 0.001 && ((R >= 8.3140) || (R < 8.31449 && R < 8.31451))) ){
        printf("Universal Gas Constant:\n");
        printf("R =\t%.3f\tJ/(mol. K)\n\n", R);
    }else{
        printf("Specific Gas Constant:\n");
        printf("R =\t%.3f\tJ/(mol. K)\n\n", R);
    }
    
    printf("Polytropic Index:\n");
    printf("alpha =\t%.3f\t[ ]\n\n", alpha);
    
    printf("\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_S (kW)\n");
    for(int i = 0; i < 512; ++i){
        printf("%f\t", profile.P[i]*0.001);
        printf("%f\t", profile.V[i]);
        printf("%f\t", profile.T[i]);
        printf("0%f\t\t", profile.T[i] - 273.15);
        printf("%f\t", profile.W_V[i]*0.001);
        printf("%f\n", profile.W_S[i]*0.001);
    }
}

void CompresWrite(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double R, double alpha, T2CompProfile profile)
{
    //Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Polytropic Process Results
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
    
    strcat(filename, " Polytropic Results");
    printf("File name: \"%s\"\n", filename);
    
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
    fprintf(fp, "_Reciprocating_Compressor_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial system pressure: ");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final system pressure: ");
    fprintf(fp, "P2 =\t%.3f\tkPa\n\n", P2*0.001);
    
    fprintf(fp, "Clearance volume:\n");
    fprintf(fp, "Vc =\t%.3f\tm3\n", Vc);
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
    if( (fabs( R - (8.3145) ) < 0.001 && ((R >= 8.3140) || (R < 8.31449 && R < 8.31451))) ){
        fprintf(fp, "Universal Gas Constant:\n");
        fprintf(fp, "R =\t%.3f\tJ/(mol. K)\n\n", R);
    }else{
        fprintf(fp, "Specific Gas Constant:\n");
        fprintf(fp, "R =\t%.3f\tJ/(mol. K)\n\n", R);
    }
    
    fprintf(fp, "Polytropic Index:\n");
    fprintf(fp, "alpha =\t%.3f\t[ ]\n\n", alpha);
    
    fprintf(fp, "\tOutput parameters:\n");
    
    // Profile (Two Temperature columns (K and deg C))
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_S (kW)\n");
    for(int i = 0; i < 512; ++i){
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "0%f\t\t", profile.T[i] - 273.15);
        fprintf(fp, "%f\t", profile.W_V[i]*0.001);
        fprintf(fp, "%f\n", profile.W_S[i]*0.001);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CompresWriteCheck(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double R, double alpha, T2CompProfile profile)
{
    int SaveC = 0;
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
                CompresWrite(P1, P2, Vc, V1, V2, T1, T2, n, R, alpha, profile);
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

void Compressor(void)
{
    int whilmain = 0;
    printf("Reciprocating Compressor\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        // Variable declaration
        char methodinput[maxstrlen];
        
        double P1 = 0.0;
        double P2 = 0.0;
        double Vc = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        double n = 0.0;
        double R = 0.0;
        double alpha = 0.0;
        
        int method = 0;
        
        int whilmethod = 0;
        T2CompProfile profile;
        
        // Initialising profile to arrays on zeros
        for(int j = 0; j < 250; ++j){
            profile.P[j] = 0.0;
            profile.V[j] = 0.0;
            profile.T[j] = 0.0;
            profile.W_V[j] = 0.0;
            profile.W_S[j] = 0.0;
        }
        
        //Data Collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Isothermal Compression\n2. Polytropic Compression\n");
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
                    whilmain = 0;
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1||method == 2){
            //  Collecting data
            CompressorVar(method, &P1, &P2, &Vc, &V1, &T1, &T2, &n, &R, &alpha);
            if(alpha == 1.0){
                method = 1;
            }
            
            //  Data Manipulation
            profile = CompressorProfile(method, P1, P2, Vc, V1, T1, T2, n, R, alpha, &V2);
            
            //  Displaying results
            CompresDisp(P1, P2, Vc, V1, V2, T1, T2, n, R, alpha, profile);
            
            //  Writing to File
            CompresWriteCheck(P1, P2, Vc, V1, V2, T1, T2, n, R, alpha, profile);
        }
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
