//
//  04cCarnotCycle.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 31/10/2020.
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
#include "01bIsothermal.h"
#include "01eAdiabatic.h"
#include "B48BC_T4.h"
#include "04aThermalEfficiency.h"
#include "04cCarnotCycle.h"
#include "04dClausiusInequality.h"

#define maxstrlen 128

void CarnotVariable(double *P1, double *P2, double *P3, double *P4, double *THot, double *TCold, double *n, double *gamma1, double *gamma2)
{
    int control = 0;
    
    *P1 = inputDouble(0, "pressure before entry into pump (P1)", "kPa");
    *P1 = (*P1)*1000;
    
    control = 1;
    while(control == 1){
        *P2 = inputDouble(0, "pressure before entry into boiler (P2)", "kPa");
        *P2 = (*P2)*1000;
        if((*P2) > (*P1))
        {
            // Pressure increasing in the pump
            control = 0;
        }else{
            printf("Please a pressure value that is higher than P1.\n");
        }
    }
    
    control = 1;
    while(control == 1){
        *P3 = inputDouble(0, "pressure before entry into turbine (P3)", "kPa");
        *P3 = (*P3)*1000;
        if((*P3) < (*P2))
        {
            // Pressure increases in the boiler
            control = 0;
        }else{
            printf("Please a pressure value that is lower than P2.\n");
        }
    }
    
    control = 1;
    while(control == 1)
    {
        *P4 = inputDouble(0, "pressure before entry into condenser (P4)", "kPa");
        *P4 = (*P4)*1000;
        if((*P4) < (*P3) && (*P4) < (*P1))
        {
            // Valid pressure prior to entry into condenser
            control = 0;
        }else{
            printf("Please a pressure value that is lower than P3 and lower than P1.\n");
        }
    }
    
    *THot = inputDouble(0, "boiler temperature", "deg C");
    *THot = (*THot) + 273.15;
    
    *TCold = inputDouble(0, "condenser temperature", "deg C");
    *TCold = (*TCold) + 273.15;
    
    *gamma1 = inputDouble(0, "heat capacity ratio in pump", "[ ]");
    *gamma2 = inputDouble(0, "heat capacity ratio in turbine", "[ ]");
    
    *n = inputDouble(0, "molar flowrate", "kmol/s");
    *n = (*n)*1000;
}

T4CarnotProfile CarnotProfileCalc(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, double *worknet, double *qhot, double *qcold)
{
    static T4CarnotProfile profile;
    
    double incr = 0.0;  // Variable used to hold the increment between data points
    double AvgTemp = 0.0;
    
    //  Setting initial values
    profile.P[0] = P1;
    profile.T[0] = TCold;
    profile.V[0] = IdealVolume(n, profile.P[0], profile.T[0]);
    profile.work[0] = 0.0;
    profile.heat[0] = 0.0;
    *worknet = 0.0;
    *qhot = 0.0;
    *qcold = 0.0;
    
    //  Adiabatic compression (Pump) (P1 -> P2)
    incr = P2 - P1;
    incr = (incr)/374;
    
    for(int i = 1; i < 375; ++i)
    {
        profile.P[i] = profile.P[i - 1] + incr;
        profile.V[i] = AdiaFinalVol(profile.V[i - 1], profile.P[i - 1], profile.P[i], gamma1);
        profile.T[i] = AdiaFinalTemp(profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma1);
        profile.work[i] = AdiaTemperature(n, profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma1);
        profile.heat[i] = 0.0;  // By definition.
        
        *worknet += profile.work[i];
        
        AvgTemp = profile.T[i] + profile.T[i - 1];
        AvgTemp = (AvgTemp)/2;
        
        profile.entropy[i] = EntropyCalc(profile.heat[i], AvgTemp);
    }
    
    //  Isothermal expansion (Boiling) (P2 -> P3)
    incr = P3 - P2;
    incr = (incr)/375;
    
    for(int i = 375; i < 750; ++i)
    {
        profile.T[i] = THot;
        profile.P[i] = profile.P[i - 1] + incr;
        profile.V[i] = IsotFinalVolume(profile.V[i - 1], profile.P[i - 1], profile.P[i]);
        profile.work[i] = IsotPressure(n, profile.T[i], profile.P[i - 1], profile.P[i]);
        profile.heat[i] = (-1) * (profile.work[i]); // From first law.
        
        *worknet += profile.work[i];
        *qhot += profile.heat[i];
        
        AvgTemp = profile.T[i] + profile.T[i - 1];
        AvgTemp = (AvgTemp)/2;
        
        profile.entropy[i] = EntropyCalc(profile.heat[i], AvgTemp);
    }
    
    //  Adiabatic expansion (Turbine) (P3 -> P4)
    incr = P4 - P3;
    incr = (incr)/375;
    
    for(int i = 750; i < 1125; ++i)
    {
        profile.P[i] = profile.P[i - 1] + incr;
        profile.V[i] = AdiaFinalVol(profile.V[i - 1], profile.P[i - 1], profile.P[i], gamma1);
        profile.T[i] = AdiaFinalTemp(profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma1);
        profile.work[i] = AdiaTemperature(n, profile.T[i - 1], profile.P[i - 1], profile.P[i], gamma1);
        profile.heat[i] = 0.0;  // By definition.
        
        *worknet += profile.work[i];
        
        AvgTemp = profile.T[i] + profile.T[i - 1];
        AvgTemp = (AvgTemp)/2;
        
        profile.entropy[i] = EntropyCalc(profile.heat[i], AvgTemp);
    }
    
    //  Isothermal Compression (Condensation) (P4 -> P1)
    incr = P1 - P4;
    incr = (incr)/375;
    
    for(int i = 1125; i < 1500; ++i)
    {
        profile.T[i] = TCold;
        profile.P[i] = profile.P[i - 1] + incr;
        profile.V[i] = IsotFinalVolume(profile.V[i - 1], profile.P[i - 1], profile.P[i]);
        profile.work[i] = IsotPressure(n, profile.T[i], profile.P[i - 1], profile.P[i]);
        profile.heat[i] = (-1) * (profile.work[i]); // From first law.
        
        *worknet += profile.work[i];
        *qcold += profile.heat[i];
        
        AvgTemp = profile.T[i] + profile.T[i - 1];
        AvgTemp = (AvgTemp)/2;
        
        profile.entropy[i] = EntropyCalc(profile.heat[i], AvgTemp);
    }
    return profile;
}

void CarnotDisplay(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, T4CarnotProfile profile, double worknet, double qhot, double qcold)
{
    printf("_Carnot_Cycle_Results_\n");
    printf("\tInput parameters:\n");
    printf("Pressure before entry into pump:\n");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Pressure before entry into boiler:\n");
    printf("P2 =\t%.3f\tkPa\n", P2*0.001);
    printf("Pressure before entry into turbine:\n");
    printf("P3 =\t%.3f\tkPa\n", P3*0.001);
    printf("Pressure before entry into condenser:\n");
    printf("P4 =\t%.3f\tkPa\n\n", P4*0.001);
    
    printf("Hot reservoir temperature:\n");
    printf("T_Hot =\t%.2f\tdeg C\n", THot - 273.15);
    printf("Cold reservoir temperature:\n");
    printf("T_Cold =\t%.2f\tdeg C\n\n", TCold - 273.15);
    
    printf("Heat capacity ratio in pump:\n");
    printf("gamma1 =\t%.3f\t[ ]\n", gamma1);
    printf("Heat capacity ratio in turbine:\n");
    printf("gamma2 =\t%.3f\t[ ]\n\n", gamma2);
    
    printf("Molar flowrate in system:\n");
    printf("n =\t%.3f\tkmol/s\n\n", n*0.001);
    
    printf("\tCalculated process parameters:\n");
    printf("Net work:\n");
    printf("w_net =\t%.3f\tkW\n", worknet*0.001);
    printf("Heat supplied to cycle from hot reservoir:\n");
    printf("q_Hot =\t%.3f\tkW\n", qhot*0.001);
    printf("Heat sent from cycle from cold reservoir:\n");
    printf("q_Cold =\t%.3f\tkW\n", qcold*0.001);
    
    double etaproc = 0.0;
    double etarev = 0.0;
    
    etaproc = ThermEffCalc2(qhot, qcold);
    etarev = ThermEffCarnotCalculation(THot, TCold);
    
    printf("Thermal efficiency of cycle:\n");
    printf("eta =\t%.3f\t%%\n", etaproc*100);
    printf("Thermal efficiency from reservoir temperatures:\n");
    printf("eta =\t%.3f\t%%\n", etarev*100);
    
    if(etaproc == etarev)
    {
        printf("Your process is reversible\n\n");
    }else{
        if(etaproc < etarev)
        {
            printf("Your process is irreversible\n\n");
        }else{
            printf("Your process violates the second law.\n\n");
        }
    }
    
    printf("\tOutput parameters:\n");
    double totalwork = 0.0;
    double totalheat = 0.0;
    double totalchaos = 0.0;
    
    printf("P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\t\tQ (kW)\tQ (kW)\t\tS (kJ/K(.s))\tS (kJ/K(.s))\n");
    for(int i = 0; i < 1500; ++i)
    {
        printf("%f\t", profile.P[i]*0.001);
        printf("%f\t", profile.V[i]);
        printf("%f\t", profile.T[i]);
        printf("%f\t\t", profile.T[i] - 273.15);
        
        printf("%f\t", profile.work[i]*0.001);
        totalwork += profile.work[i];
        printf("%f\t\t", totalwork);
        
        printf("%f\t", profile.heat[i]*0.001);
        totalheat += profile.heat[i];
        printf("%f\t\t", totalheat);
        
        printf("%f\t", profile.entropy[i]*0.001);
        totalchaos += profile.entropy[i];
        printf("%f\n", totalchaos);
    }
}

void CarnotWrite(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, T4CarnotProfile profile, double worknet, double qhot, double qcold)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Carnot Cycle Results
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
    
    strcat(filename, " Carnot Cycle Results");
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
    fprintf(fp, "_Carnot_Cycle_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Pressure before entry into pump:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Pressure before entry into boiler:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n", P2*0.001);
    fprintf(fp, "Pressure before entry into turbine:\n");
    fprintf(fp, "P3 =\t%.3f\tkPa\n", P3*0.001);
    fprintf(fp, "Pressure before entry into condenser:\n");
    fprintf(fp, "P4 =\t%.3f\tkPa\n\n", P4*0.001);
    
    fprintf(fp, "Hot reservoir temperature:\n");
    fprintf(fp, "T_Hot =\t%.2f\tdeg C\n", THot - 273.15);
    fprintf(fp, "Cold reservoir temperature:\n");
    fprintf(fp, "T_Cold =\t%.2f\tdeg C\n\n", TCold - 273.15);
    
    fprintf(fp, "Heat capacity ratio in pump:\n");
    fprintf(fp, "gamma1 =\t%.3f\t[ ]\n", gamma1);
    fprintf(fp, "Heat capacity ratio in turbine:\n");
    fprintf(fp, "gamma2 =\t%.3f\t[ ]\n\n", gamma2);
    
    fprintf(fp, "Molar flowrate in system:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n\n", n*0.001);
    
    fprintf(fp, "\tCalculated process parameters:\n");
    fprintf(fp, "Net work:\n");
    fprintf(fp, "w_net =\t%.3f\tkW\n", worknet*0.001);
    fprintf(fp, "Heat supplied to cycle from hot reservoir:\n");
    fprintf(fp, "q_Hot =\t%.3f\tkW\n", qhot*0.001);
    fprintf(fp, "Heat sent from cycle from cold reservoir:\n");
    fprintf(fp, "q_Cold =\t%.3f\tkW\n", qcold*0.001);
    
    double etaproc = 0.0;
    double etarev = 0.0;
    
    etaproc = ThermEffCalc2(qhot, qcold);
    etarev = ThermEffCarnotCalculation(THot, TCold);
    
    fprintf(fp, "Thermal efficiency of cycle:\n");
    fprintf(fp, "eta =\t%.3f\t%%\n", etaproc*100);
    fprintf(fp, "Thermal efficiency from reservoir temperatures:\n");
    fprintf(fp, "eta =\t%.3f\t%%\n", etarev*100);
    
    if(etaproc == etarev)
    {
        fprintf(fp, "Your process is reversible\n\n");
    }else{
        if(etaproc < etarev)
        {
            fprintf(fp, "Your process is irreversible\n\n");
        }else{
            fprintf(fp, "Your process violates the second law.\n\n");
        }
    }
    
    fprintf(fp, "\tOutput parameters:\n");
    double totalwork = 0.0;
    double totalheat = 0.0;
    double totalchaos = 0.0;
    
    fprintf(fp, "P (kPa)\tV (m3)\tT (K)\tT(deg C)\t\tW_V (kW)\tW_V (kW)\t\tQ (kW)\tQ (kW)\t\tS (kJ/K(.s))\tS (kJ/K(.s))\n");
    for(int i = 0; i < 1500; ++i){
        fprintf(fp, "%f\t", profile.P[i]*0.001);
        fprintf(fp, "%f\t", profile.V[i]);
        fprintf(fp, "%f\t", profile.T[i]);
        fprintf(fp, "%f\t\t", profile.T[i] - 273.15);
        
        fprintf(fp, "%f\t", profile.work[i]*0.001);
        totalwork += profile.work[i];
        fprintf(fp, "%f\t\t", totalwork*0.001);
        
        fprintf(fp, "%f\t", profile.heat[i]*0.001);
        totalheat += profile.heat[i];
        fprintf(fp, "%f\t\t", totalheat*0.001);
        
        fprintf(fp, "%f\t", profile.entropy[i]*0.001);
        totalchaos += profile.entropy[i];
        fprintf(fp, "%f\n", totalchaos*0.001);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CarnotWriteSwitch(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, T4CarnotProfile profile, double worknet, double qhot, double qcold)
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
                CarnotWrite(P1, P2, P3, P4, THot, TCold, n, gamma1, gamma2, profile, worknet, qhot, qcold);
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

void CarnotCycle(void)
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Carnot Cycle\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double worknet = 0.0;   // Net work on/by system.
        double qhot = 0.0;      // Total heat received to system from hot reservoir.
        double qcold = 0.0;     // Total heat sent from system to cold reservoir.
        
        double P1 = 0.0;        // System pressure before adiabatic compression (Pump).
        double P2 = 0.0;        // System pressure before isothermal expansion (Boiler).
        double P3 = 0.0;        // System pressure before adiabatic expansion (Turbine).
        double P4 = 0.0;        // System pressure before isothermal compression (Condenser).
        double THot = 0.0;      // Hot reservoir temperature (Boiler temperature).
        double TCold = 0.0;     // Cold reservoir temperature (Condenser temperature)
        double n = 0.0;         // Moles present in system.
        double gamma1 = 0.0;    // Heat capacity ratio for the pump.
        double gamma2 = 0.0;    // Heat capacity ratio for the turbine.
        
        T4CarnotProfile profile = {0.0};
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        CarnotVariable(&P1, &P2, &P3, &P4, &THot, &TCold, &n, &gamma1, &gamma2);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        profile = CarnotProfileCalc(P1, P2, P3, P4, THot, TCold, n, gamma1, gamma2, &worknet, &qhot, &qcold);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        CarnotDisplay(P1, P2, P3, P4, THot, TCold, n, gamma1, gamma2, profile, worknet, qhot, qcold);
        
        //  Writing to File
        CarnotWriteSwitch(P1, P2, P3, P4, THot, TCold, n, gamma1, gamma2, profile, worknet, qhot, qcold);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
