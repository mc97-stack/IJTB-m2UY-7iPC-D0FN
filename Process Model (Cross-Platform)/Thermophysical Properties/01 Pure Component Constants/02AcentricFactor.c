//
//  02AcentricFactor.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/11/2020.
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
#include "01PureComponent.h"
#include "02AcentricFactor.h"

#define maxstrlen 128

void AcFactorVariable(int mode, double *Pc, double *Tc, double *TBoil, double *ANTA, double *ANTB, double *ANTC)
{
    *Pc = inputDouble(0, "critical pressure", "bar");
    *Tc = inputDouble(0, "critical temperature", "K");
    
    if(mode == 2 || mode == 3 || mode == 4){
        *TBoil = inputDouble(0, "normal boiling point", "deg C");
        *TBoil = (*TBoil) + 273.15;
    }
    
    if(mode == 1 || mode == 4){
        *ANTA = inputDouble(0, "antoine constant (A)", "mmHg");
        *ANTB = inputDouble(0, "antoine constant (B)", "K.mmHg");
        *ANTC = inputDouble(0, "antoine constant (C)", "deg C");
    }
}

double AntoineEquation(double ANTA, double ANTB, double ANTC, double T)
{
    double PHat = 0.0;
    
    PHat = T + ANTC;
    PHat = ANTB/(PHat);
    PHat = ANTA - (PHat);
    
    PHat = pow(10, PHat);
    
    return PHat;
}

double AcFactorPHatCalculation(double ANTA, double ANTB, double ANTC, double Tc, double Pc)
{
    double omega = 0.0;     // Acentric factor
    
    double T = 0.0;         // Temperature at T_r = 0.7
    double PHat = 0.0;      // Vapour pressure
    
    T = Tc*0.7;
    T = (T) - 273.15;
    
    PHat = AntoineEquation(ANTA, ANTB, ANTC, T);
    
    PHat = (PHat)/(750.06156130264);    // Conversion (mmhg -> bar).
    PHat = (PHat)/Pc;                   // Calculating reduced vapour pressure.
    
    omega = log10(PHat);
    omega = -1*(omega);
    omega = (omega) - 1.0;
    
    return omega;
}

double AcFactorCritCalc(double Pc, double Tc, double TBoil)
{
    double omega = 0.0; // Acentric factor.
    
    double theta = 0.0; // TBoil/Tc
    double sto1 = 0.0;
    
    Pc = Pc/(1.01325);  // Conversion (bar -> atm)
    
    theta = TBoil/Tc;
    
    omega = (3.0)/(7.0);
    sto1 = 1 - (theta);
    sto1 = (theta)/(sto1);
    theta = (theta)*(sto1);
    
    sto1 = log10(Pc);
    theta = (theta)*(sto1);
    theta = (theta) - 1;
    
    return omega;
}

double AcFactorLKCalc(double Pc, double Tc, double TBoil)
{
    double omega = 0.0; // Acentric factor.
    
    double theta = 0.0; // TBoil/Tc
    double alpha = 0.0;
    double beta = 0.0;
    double sto1 = 0.0;
    
    Pc = Pc/(1.01325);  // Conversion (bar -> atm)
    
    theta = TBoil/Tc;
    
    alpha = log(Pc);
    alpha = -1*(alpha);
    alpha = (alpha) - 5.92714;
    
    sto1 = 6.09648/(theta);
    alpha = (alpha) + (sto1);
    
    sto1 = log(theta);
    sto1 = 1.28862*(sto1);
    alpha = (alpha) + (sto1);
    
    sto1 = pow(theta, 6);
    sto1 = 0.169347*(sto1);
    alpha = (alpha) - (sto1);
    
    beta = 15.6875/(theta);
    beta = 15.2518 - (beta);
    
    sto1 = log(theta);
    sto1 = 13.4721*(sto1);
    beta = (beta) - (sto1);
    
    sto1 = pow(theta, 6);
    sto1 = 0.43577*(sto1);
    (beta) = (beta) + (sto1);
    
    omega = alpha/beta;
    
    return omega;
}

void AcFactorDisplay(int mode, double Pc, double Tc, double TBoil, double ANTA, double ANTB, double ANTC, double omegaANT, double omegaCRI, double omegaLK)
{
    printf("_Acentric_Factor_Results_\n");
    printf("\tInput parameters:\n");
    if(mode == 1 || mode == 4)
    {
        printf("Antoine Equation Constants:\n");
        printf("ANTA =\t%.5f\tmmHg\n", ANTA);
        printf("ANTB =\t%.2f\tmmHg.K\n", ANTB);
        printf("ANTC =\t%.3f\tK\n\n", ANTC);
    }
    
    printf("Critical pressure:\n");
    printf("Pc =\t%.3f\tbar\n", Pc);
    printf("Critical temperature:\n");
    printf("Tc =\t%.3f\tK\n", Tc);
    if(mode == 2 || mode == 3 || mode == 4)
    {
        printf("Normal boiling point:\n");
        printf("Tboil =\t%.3f\tdeg C\n", TBoil - 273.15);
    }
    
    printf("\tOutput parameters:\n");
    printf("Acentric Factor:\n");
    
    if(mode == 1 || mode == 4){
        printf("omegaANT =\t%.3f\t[ ]\n", omegaANT);
    }
    if(mode == 2 || mode == 4){
        printf("omegaCRI =\t%.3f\t[ ]\n", omegaCRI);
    }
    if(mode == 3 || mode == 4){
        printf("omegaLK =\t%.3f\t[ ]\n", omegaLK);
    }
    fflush(stdout);
}

void AcFactorWrite(int mode, double Pc, double Tc, double TBoil, double ANTA, double ANTB, double ANTC, double omegaANT, double omegaCRI, double omegaLK)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Acentric Factor Results
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
    
    strcat(filename, " Acentric Factor Results");
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
    free(filename);
    
    //Write to file
    fprintf(fp, "_Acentric_Factor_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    if(mode == 1 || mode == 4)
    {
        fprintf(fp, "Antoine Equation Constants:\n");
        fprintf(fp, "ANTA =\t%.5f\tmmHg\n", ANTA);
        fprintf(fp, "ANTB =\t%.2f\tmmHg.K\n", ANTB);
        fprintf(fp, "ANTC =\t%.3f\tK\n\n", ANTC);
    }
    
    fprintf(fp, "Critical pressure:\n");
    fprintf(fp, "Pc =\t%.3f\tbar\n", Pc);
    fprintf(fp, "Critical temperature:\n");
    fprintf(fp, "Tc =\t%.3f\tK\n", Tc);
    if(mode == 2 || mode == 3 || mode == 4)
    {
        fprintf(fp, "Normal boiling point:\n");
        fprintf(fp, "Tboil =\t%.3f\tdeg C\n", TBoil - 273.15);
    }
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Acentric Factor:\n");
    
    if(mode == 1 || mode == 4){
        fprintf(fp, "omegaANT =\t%.4f\t[ ]\n", omegaANT);
    }
    if(mode == 2 || mode == 4){
        fprintf(fp, "omegaCRI =\t%.4f\t[ ]\n", omegaCRI);
    }
    if(mode == 3 || mode == 4){
        fprintf(fp, "omegaLK =\t%.4f\t[ ]\n", omegaLK);
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void AcFactorSwitch(int mode1, int mode2, double Pc, double Tc, double TBoil, double ANTA, double ANTB, double ANTC, double omegaANT, double omegaCRI, double omegaLK)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        if(mode1 == 1){
            printf("Do you want to display the results? ");
        }
        if(mode1 == 2){
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
                if(mode1 == 1){
                    AcFactorDisplay(mode2, Pc, Tc, TBoil, ANTA, ANTB, ANTC, omegaANT, omegaCRI, omegaLK);
                }
                if(mode1 == 2){
                    AcFactorWrite(mode2, Pc, Tc, TBoil, ANTA, ANTB, ANTC, omegaANT, omegaCRI, omegaLK);
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

void AcentricFactor(void)
{
    int whilmain = 0;
    printf("Acentric Factor Calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        int mode = 0;
        int control = 0;
        
        double omegaANT = 0.0;     // Acentric Factor (Antoine Equation).
        double omegaCRI = 0.0;     // Acentric Factor (Critical properties and Normal boiling point).
        double omegaLK = 0.0;      // Acentric Factor (Lee-Kesler vapour pressure relations).
        
        double ANTA = 0.0;      // Constant A for Antoine equation.
        double ANTB = 0.0;      // Constant B for Antoine equation.
        double ANTC = 0.0;      // Constant C for Antoine equation.
        double Pc = 0.0;        // Critical pressure.
        double Tc = 0.0;        // Critical temperature.
        double TBoil = 0.0;     // Normal boiling temperature.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("Please choose from the following calculation methods:\n");
            printf("1. Antoine equation.\n");
            printf("2. Critical parameters and normal boiling point.\n");
            printf("3. Lee-Kesler vapour pressure relations.\n");
            printf("4. All.\n");
            printf("Selection [1 - 4]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    mode = 1;
                    control = 0;
                    break;
                case '2':
                    mode = 2;
                    control = 0;
                    break;
                case '3':
                    mode = 3;
                    control = 0;
                    break;
                case '4':
                    mode = 4;
                    control = 0;
                    break;
                case '0':
                case 'Q':
                case 'q':
                    goto end;
                    break;
                default:
                    printf("Input not recognised. Please enter an integer between 1 and 4.\n");
                    break;
            }
            fflush(stdout);
        }
        AcFactorVariable(mode, &Pc, &Tc, &TBoil, &ANTA, &ANTB, &ANTC);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        if(mode == 1 || mode == 4){
            omegaANT = AcFactorPHatCalculation(ANTA, ANTB, ANTC, Tc, Pc);
        }
        if(mode == 2 || mode == 4){
            omegaCRI = AcFactorCritCalc(Pc, Tc, TBoil);
        }
        if(mode == 3 || mode == 4){
            omegaLK = AcFactorLKCalc(Pc, Tc, TBoil);
        }
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);
        
        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        AcFactorSwitch(1, mode, Pc, Tc, TBoil, ANTA, ANTB, ANTC, omegaANT, omegaCRI, omegaLK);
        
        //  Writing to File
        AcFactorSwitch(2, mode, Pc, Tc, TBoil, ANTA, ANTB, ANTC, omegaANT, omegaCRI, omegaLK);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
end:
    fflush(stdout);
}
