//
//  02aCompressor.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Custom header files
#include "B48BC_T2.h"
#include "02aCompressor.h"
#include "02bPolyShaftWork.h"

// Loading the thermodynamic processes required for this subroutine
#include "01cIsobaric.h"
#include "01bIsothermal.h"
#include "01aPolytropic.h"

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

T2CompProfile CompressorProfile(int method, double P1, double P2, double Vc, double V1, double T1, double T2, double n, double R, double alpha)
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

void Compressor(void)
{
    char ContCond[maxstrlen];
    
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
        double T1 = 0.0;
        double T2 = 0.0;
        double n = 0.0;
        double R = 0.0;
        double alpha = 0.0;
        
        int method = 0;
        
        int whilmethod = 0;
        int whilcont = 0;
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
            CompressorVar(method, &P1, &P2, &Vc, &V1, &T1, &T2, &n, &R, &alpha);
            
            // Data Manipulation
            profile = CompressorProfile(method, P1, P2, Vc, V1, T1, T2, n, R, alpha);
            
            // Viewing the generated profile
            printf("P (kPa)\tV (m3)\tT (deg C)\tW_V (kW)\tW_S (kW)\n");
            for(int i = 0; i < 512; ++i){
                printf("%.3f\t", 0.001 * profile.P[i]);
                printf("%.3f\t", profile.V[i]);
                printf("%.2f\t", (profile.T[i]) - 273.15);
                printf("%.3f\t", 0.001 * profile.W_V[i]);
                printf("%.3f\n", 0.001 * profile.W_S[i]);
            }
            
            // File write
            
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
