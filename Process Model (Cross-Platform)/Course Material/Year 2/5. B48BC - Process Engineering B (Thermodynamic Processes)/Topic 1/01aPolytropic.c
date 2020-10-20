//
//  01aPolytropic.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  Custom header files
#include "B48BC_T1.h"
#include "01aPolytropic.h"

#define maxstrlen 128

void PolyVariable(int method, double *P1, double *P2, double *V1, double *T1,double *T2, double *n, double *R, double *alpha)
{
    char input[maxstrlen];
    
    if(method == 2){
        printf("Initial system semperature (deg C) = ");
        *T1 = atof(fgets(input, sizeof(input), stdin));
        *T1 = (*T1) + 273.15;
    }
    if(method == 2){
        printf("Final system temperature (deg C) = ");
        *T2 = atof(fgets(input, sizeof(input), stdin));
        *T2 = (*T2) + 273.15;
    }
    if(method == 2 && fabs(*T2 - *T1) < 0.005){
        printf("You have stated an isothermal process. Changing to the Pressure-Volume equation.\n\n");
        method = 1;
    }
    if(method == 1){
        printf("Initial system pressure (kPa) = ");
        *P1 = atof(fgets(input, sizeof(input), stdin));
        *P1 = (*P1)*1000;
    }
    if(method == 1){
        printf("Final system pressure (kPa) = ");
        *P2 = atof(fgets(input, sizeof(input), stdin));
        *P2 = (*P2)*1000;
    }
    if(method == 1){
        printf("Initial system volume (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 1 || method == 2){
        printf("Moles in system (kmol/s) = ");
        *n = atof(fgets(input, sizeof(input), stdin));
        *n = (*n)*1000;
    }
    if(method == 1 || method == 2){
        printf("Gas constant (R) (kJ/(kmol.K)) = ");
        *R = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 1 || method == 2){
        printf("Polytropic index ([ ]) = ");
        *alpha = atof(fgets(input, sizeof(input), stdin));
    }
    fflush(stdout);
}

double PolyVolume(double P1, double P2, double V1, double alpha)
{
    double power = 0.0;
    double brack = 0.0;
    double fracnum = 0.0;
    double fracden = 0.0;
    double work = 0.0;
    
    power = alpha - 1;
    power = (power)/alpha;
    
    brack = P2/P1;
    brack = pow(brack, power);
    brack = 1 - (brack);
    
    fracnum = P1*V1;
    fracden = alpha - 1;
    
    work = fracnum/fracden;
    work = (work)*brack;
    work = -1*(work);
    
    return work;
}

double PolyTemperature(double n, double R, double T1, double T2, double alpha)
{
    double brack = 0.0;
    double fracnum = 0.0;
    double fracden = 0.0;
    double work = 0.0;
    
    brack = T2/T1;
    brack = (brack) - 1;
    
    fracnum = n*R;
    fracnum = (fracnum)*T1;
    fracden = alpha - 1;
    
    work = fracnum/fracden;
    work = (work)*brack;
    
    return work;
}

double PolyFinalVolume(double P1, double P2, double V1, double alpha)
{
    double logfrac = 0.0;
    double frac = 0.0;
    double V2 = 0.0;
    
    logfrac = pow(V1, alpha);
    logfrac = P1*(logfrac);
    logfrac = (logfrac)/P2;
    logfrac = log(logfrac);
    
    frac = (logfrac)/alpha;
    
    V2 = exp(frac);
    
    return V2;
}

double PolyFinalPressure(double T1, double T2, double P1, double alpha)
{
    double power = 0.0;
    double logfrac = 0.0;
    double frac = 0.0;
    double P2 = 0.0;
    
    power = 1.0 - alpha;
    power = (power)/alpha;
    
    logfrac = pow(P1, power);
    logfrac = T1*(logfrac);
    logfrac = (logfrac)/T2;
    logfrac = log(logfrac);
    
    frac = (logfrac)/(power);
    
    P2 = exp(frac);
    
    return P2;
}

double PolyFinalTemperature(double T1, double P1, double P2, double alpha)
{
    double T2 = 0.0;
    double power = 0.0;
    double frac = 0.0;
    
    power = 1 - alpha;
    power = (power)/alpha;
    
    frac = P1/P2;
    
    T2 = pow(frac, power);
    T2 = T1 * (T2);
    
    return T2;
}

T1ThermoProf PolyProfile(int method, double P1, double P2, double V1, double T1, double T2, double n, double R, double alpha)
{
    double incr = 0.0; // Increment between data points
    int reso = 0; // Resolution of generated plot
    int i = 0; // Row controller
    
    T1ThermoProf profile;
    double total = 0.0;
    
    reso = 249;
        
    if(method == 1){
        incr = P2 - P1;
        incr = (incr)/reso;
    }
    if(method == 2){
        incr = T2 - T1;
        incr = (incr)/reso;
    }
    
    i = 0;
    if(method == 1){
        // Pressure and volume must be stated
        double Tnum = 0.0;
        double Tden = 0.0;
        
        profile.P[i] = P1;
        profile.V[i] = V1;
        
        Tnum = (profile.P[i])*(profile.V[i]);
        Tden = n*R;
        profile.T[i] = Tnum/Tden;
    }
    if(method == 2){
        // Temperature must be known. Not enough information is given to calculate the system pressure or volume
        printf("Assuming Ideal Gas Law applies\n\n");
        profile.P[i] = 0.0;
        profile.V[i] = 0.0;
        profile.T[i] = T1;
    }
    profile.W_V[i] = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            double Tnum = 0.0;
            double Tden = 0.0;
            
            profile.P[i] = profile.P[i-1] + incr;
            profile.V[i] = PolyFinalVolume(profile.P[i-1], profile.P[i], profile.V[i-1], alpha);
            
            Tnum = (profile.P[i])*(profile.V[i]);
            Tden = n*R;
            profile.T[i] = Tnum/Tden;
            
            profile.W_V[i] = PolyVolume(profile.P[i-1], profile.P[i], profile.V[i-1], alpha);
            total = total + profile.W_V[i];
        }
        if(method == 2){
            profile.P[i] = 0.0;
            profile.V[i] = 0.0;
            profile.T[i] = profile.T[i - 1] + incr;
            profile.W_V[i] = PolyTemperature(n, R, profile.T[i - 1], profile.T[i], alpha);
            total = total + profile.W_V[i];
        }
    }
    
    printf("Total Volume work done = %.3f kW\n", total*0.001);
    printf("Profile calculated in %d rows\n\n", i);
    
    fflush(stdout);
    return profile;
}

void Polytropic()
{
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Polytropic Volume Work\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        // Variable declaration
        
        char methodinput[maxstrlen];
        
        double P1 = 0.0;
        double P2 = 0.0;
        double V1 = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        double n = 0.0;
        double R = 0.0;
        double alpha = 0.0;
        
        int method = 0;
        
        int whilmethod = 0;
        int whilcont = 0;
        
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
        if(method == 1||method == 2){
            PolyVariable(method, &P1, &P2, &V1, &T1, &T2, &n, &R, &alpha);
            
            // Data Manipulation
            profile = PolyProfile(method, P1, P2, V1, T1, T2, n, R, alpha);
            
            printf("P (kPa)\tV (m3)\tT(deg C)\tW_V (kW)\tW_V (kW)\n");
            for(int i = 0; i < 250; ++i){
                printf("%f\t", profile.P[i]*0.001);
                printf("%f\t", profile.V[i]);
                printf("%f\t", profile.T[i] - 273.15);
                printf("%f\t", profile.W_V[i]*0.001);
                total += profile.W_V[i]*0.001;
                printf("%f\n", total);
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
