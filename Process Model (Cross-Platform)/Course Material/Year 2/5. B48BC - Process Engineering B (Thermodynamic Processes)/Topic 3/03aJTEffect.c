//
//  03aJTEffect.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 27/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
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
#include "03CubicEOS.h"
#include "B48BC_T3.h"
#include "03aJTEffect.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 8.3145

/// MARK: VARIABLE INPUT
void JTEffectVariable(double *Tc, double *Pc, double *T, double *P, double *v, double *c_p)
{
    printf("Critical properties:\n");
    *Tc = inputDouble(0, 1, "Critical Temperature", "deg C");
    *Tc = (*Tc)+273.15;
    
    *Pc = inputDouble(0, 0, "Critical Pressure", "bar");
    *Pc = (*Pc)*100000;
    
    printf("System properties:\n");
    *T = inputDouble(1, 1, "System Temperature", "deg C");
    *T = (*T)+273.15;
    
    *P = inputDouble(0, 0, "System Pressure", "kPa");
    *P = (*P)*1000;
    
    printf("Fluid specific properties:\n");
    *v = inputDouble(0, 0, "Molar volume", "m3/kmol");
    *v = (*v)*0.001;
    
    *c_p = inputDouble(0, 0, "Heat capacity at constant pressure", "J/mol.K");
}

/// MARK: GENERAL CALCULATIONS
double JTCoefficientCalculation(double v, double c_p, double T, double P, double a, double b)
{
    double term1 = 0.0;
    double term2 = 0.0;
    double term2top = 0.0;
    double term2bot = 0.0;
    double term2sto = 0.0;
    
    double mu_JT = 0.0;
    
    // Calculating the denominator
    term1 = v/c_p;                      // Term 1 calculated.
    
    term2bot = P*v;
    term2sto = a/v;
    term2bot = (term2bot)-term2sto;
    
    term2sto = pow(v, 2);
    term2top = a*b;
    term2top = 2*(term2top);
    
    term2sto = (term2top)/(term2sto);
    term2top = 0.0;
    term2bot = (term2bot) + term2sto;   // Denominator calculated.
    
    term2top = R*T;
    
    term2 = term2top/term2bot;          // Term 2 calculated
    term2 = term2 - 1;                  // Bracketed term calculated.
    
    mu_JT = term1*term2;
    
    return mu_JT;
}

double JTInvTemperatureCalculation(double P, double v, double a, double b)
{
    double top1 = 0.0;
    double top2 = 0.0;
    double top3 = 0.0;
    
    double Tinv = 0.0;
    
    top2 = 2*a;
    top2 = (top2)*b;
    top3 = pow(v, 2);
    top3 = (top2)/(top3);
    top2 = 0.0;
    
    top1 = P*v;
    
    top2 = a/v;
    
    Tinv = top1 - top2;
    Tinv = (Tinv) + top3;
    Tinv = (Tinv)/R;
    
    return Tinv;
}

/// MARK: DISPLAY AND WRITE
void JTEffectDisplay(double Tc, double Pc, double T, double P, double v, double c_p, double a, double b, double mu_JT, double Tinv)
{
    printf("_Joule-Thomson_Effect_\n");
    printf("\tInput parameters\n");
    printf("Critical Temperature:\n");
    printf("Tc =\t%.3f\tdeg C\n", Tc - 273.15);
    printf("Critical Pressure:\n");
    printf("Pc =\t%.3f\tbar\n", Pc/100000);
    printf("System Temperature:\n");
    printf("T =\t%.3f\tdeg C\n", T - 273.15);
    printf("System Pressure:\n");
    printf("P =\t%.3f\tbar\n", P/100000);
    printf("Molar volume:\n");
    printf("v =\t%.3f\tm3/kmol\n", v*1000);
    printf("Heat capacity at constant pressure:\n");
    printf("c_p =\t%.3f\tJ/(mol.K)\n\n", c_p);
    
    printf("\tIntermediate parameters\nVan der Waals EOS constants\n");
    printf("a =\t%.3f\t(J.m3)/(mol2)\n", a);
    printf("b =\t%.3fE-05\tm3/mol\n\n", b*100000);
    
    printf("\tOutput parameters\n");
    printf("Isobaric thermal expansion coefficient:\n");
    printf("alpha =\t%.5f\t(1/K)\n", 1/Tinv);
    printf("Joule-Thomson Coefficient:\n");
    printf("mu_JT =\t%.3f\tK/Pa\n", mu_JT);
    if(mu_JT > 0)
    {
        //  Coefficient is positive
        printf("The VdW gas will cool as it expands\n\n");
    }
    if(mu_JT < 0)
    {
        //  Coefficient is negative
        printf("The VdW gas will heat up as it expands\n\n");
    }
    if(mu_JT == 0)
    {
        //  Coefficient is at the inversion temperature
        printf("The VdW gas is at its inversion temperature\n\n");
    }
    printf("Inversion Temperature:\n");
    printf("T_i =\t%.2f\tK\n", Tinv);
    fflush(stdout);
}

void JTEffectWrite(double Tc, double Pc, double T, double P, double v, double c_p, double a, double b, double mu_JT, double Tinv)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + Joule-Thomson Effect
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, "  Joule-Thomson Effect");
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
    fprintf(fp, "_Joule-Thomson_Effect_\n");
    fprintf(fp, "\tInput parameters\n");
    fprintf(fp, "Critical Temperature:\n");
    fprintf(fp, "Tc =\t%.3f\tdeg C\n", Tc - 273.15);
    fprintf(fp, "Critical Pressure:\n");
    fprintf(fp, "Pc =\t%.3f\tbar\n", Pc/100000);
    fprintf(fp, "System Temperature:\n");
    fprintf(fp, "T =\t%.3f\tdeg C\n", T - 273.15);
    fprintf(fp, "System Pressure:\n");
    fprintf(fp, "P =\t%.3f\tbar\n", P/100000);
    fprintf(fp, "Molar volume:\n");
    fprintf(fp, "v =\t%.3f\tm3/kmol\n", v*1000);
    fprintf(fp, "Heat capacity at constant pressure:\n");
    fprintf(fp, "c_p =\t%.3f\tJ/(mol.K)\n\n", c_p);
    
    fprintf(fp, "\tIntermediate parameters\nVan der Waals EOS constants\n");
    fprintf(fp, "a =\t%.3f\t(J.m3)/(mol2)\n", a);
    fprintf(fp, "b =\t%.3fE-05\tm3/mol\n\n", b*100000);
    
    fprintf(fp, "\tOutput parameters\n");
    fprintf(fp, "Isobaric thermal expansion coefficient:\n");
    fprintf(fp, "alpha =\t%.5f\t1/K\n", 1/Tinv);
    fprintf(fp, "Joule-Thomson Coefficient:\n");
    fprintf(fp, "mu_JT =\t%.3f\tK/Pa\n", mu_JT);
    if(mu_JT > 0)
    {
        //  Coefficient is positive
        fprintf(fp, "The VdW gas will cool as it expands\n\n");
    }
    if(mu_JT < 0)
    {
        //  Coefficient is negative
        fprintf(fp, "The VdW gas will heat up as it expands\n\n");
    }
    if(mu_JT == 0)
    {
        //  Coefficient is at the inversion temperature
        fprintf(fp, "The VdW gas is at its inversion temperature\n\n");
    }
    fprintf(fp, "Inversion Temperature:\n");
    fprintf(fp, "T_i =\t%.2f\tK\n", Tinv);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void JTEffectWriteSwitch(double Tc, double Pc, double T, double P, double v, double c_p, double a, double b, double mu_JT, double Tinv)
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
                JTEffectWrite(Tc, Pc, T, P, v, c_p, a, b, mu_JT, Tinv);
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
void JouleThomsonEffect(void)
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Joule-Thomson Effect\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double a = 0.0;     // First van der Waals equation constant.
        double b = 0.0;     // Second van der Waals equation constant.
        double mu_JT = 0.0; // Joule-Thomson Coefficient.
        double Tinv = 0.0;  // Inversion temperature.
        
        double Tc = 0.0;    // Critical temperature.
        double Pc = 0.0;    // Critical pressure.
        double T = 0.0;     // System temperature.
        double P = 0.0;     // System pressure.
        double v = 0.0;     // System molar volume.
        double c_p = 0.0;   // Heat capacity at constant pressure.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        JTEffectVariable(&Tc, &Pc, &T, &P, &v, &c_p);
        
        //  Data Manipulation
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        a = VdWcalculateA(Tc, Pc);
        b = VdWcalculateB(Tc, Pc);
        
        mu_JT = JTCoefficientCalculation(v, c_p, T, P, a, b);
        Tinv = JTInvTemperatureCalculation(P, v, a, b);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        JTEffectDisplay(Tc, Pc, T, P, v, c_p, a, b, mu_JT, Tinv);
        
        //  Writing to File
        JTEffectWriteSwitch(Tc, Pc, T, P, v, c_p, a, b, mu_JT, Tinv);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
