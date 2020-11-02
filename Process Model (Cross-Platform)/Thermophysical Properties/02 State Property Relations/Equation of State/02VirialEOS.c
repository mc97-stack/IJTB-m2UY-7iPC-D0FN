//
//  02VirialEOS.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 01/11/2020.
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
#include "02PVTRelations.h"
#include "EquationofState.h"
#include "02VirialEOS.h"

#define maxstrlen 128
#define R 83.145    // (bar.cm3)/(mol.K)

void VirialEOSVariable(int polar, double *Pc, double *Tc, double *Vc, double *accFactor, double *a, double *b)
{
    *Pc = inputDouble(0, "critical pressure", "bar");
    
    *Tc = inputDouble(0, "critical temperature", "K");
    
    *Vc = inputDouble(0, "critical molar volume", "cm3/mol");
    
    *accFactor = inputDouble(0, "accentric factor", "[ ]");
    
    if(polar == 1)
    {
        // User has told the computer that the molecule is polar
        *a = inputDouble(0, "a", "[ ]");
        *b = inputDouble(0, "b", "[ ]");
    }
}

double reducedProperty(double critical, double process)
{
    return process/critical;
}
/*  This commented out code is for when you would like to calculate a and b from the dimensionless dipole moment. Remember to change the inputted parameters and subroutine to calculate B^(2) when called.
double reducedDipoleMoment(double mu, double Pc, double Tc)
{
    double top = 0.0;
    double bot = 0.0;
    
    top = pow(mu, 2);
    top = (top)*Pc;
    top = (top)*pow(10,5);
    
    bot = pow(Tc, 2);
    
    return top/bot;
}

void group1(double mu_r, double *a, double *b)
{
    double num1 = 0.0;
    double num2 = 0.0;
    
    num1 = pow(10, -4);
    num1 = -2.112*(num1);
    
    num2 = pow(10, -21);
    num2 = 3.877*(num2);
    
    *a = num1*mu_r;
    *a = (*a) - num2;
    
    *b = 0.0;
}

void group2(double mu_r, double *a, double *b)
{
    *a = pow(mu_r, 8);
    *b = 0.0;
}

void group3(double mu_r, double *a, double *b)
{
    *a = 0.0;
    *b = 0.0;
}

void group4(double mu_r, double *a, double *b)
{
    double num1 = 0.0;
    double num2 = 0.0;
    
    num1 = pow(10, -11);
    num1 = 2.076*(num1);
    
    num2 = pow(10, -21);
    num2 = 7.048*(num2);
    num2 = (num2)*pow(mu_r, 8);
    
    *a = pow(mu_r,4);
    *a = num1*(*a);
    *a = (*a) - num2;
    
    *b = 0.0;
}

void group5(double mu_r, double *a, double *b)
{
    *a = 0.0878;
    *b = 0.04;  // Can be between 0.04 and 0.06
}

void group6(double mu_r, double *a, double *b)
{
    *a = -0.0136;
    *b = 0.0;
}
*/
double VirialEOSB0Calc(double Tr)
{
    double B0 = 0.0;
    
    B0 = pow(Tr, 1.6);
    B0 = 0.422/(B0);
    B0 = 0.083 - (B0);
    
    return B0;
}

double VirialEOSB1Calc(double Tr)
{
    double B1 = 0.0;
    
    B1 = pow(Tr, 4.2);
    B1 = 0.172/(B1);
    B1 = 0.139 - (B1);
    
    return B1;
}

double VirialEOSB2Calc(double a, double b, double Tr)
{
    double B2 = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    
    frac1 = pow(Tr, 6);
    frac1 = a/(frac1);
    
    frac2 = pow(Tr, 8);
    frac2 = b/(frac2);
    
    B2 = frac1 - frac2;
    
    return B2;
}

double VirialEOSBHat(double B0, double B1, double B2,  double accFactor)
{
    double BHat = 0.0;
    
    BHat = accFactor*B1;
    BHat = B0 + (BHat);
    BHat = (BHat) + B2;
    
    return BHat;
}

double VirialEOSBCalc(double BHat, double Pc, double Tc)
{
    double B = 0.0;
    double LHS = 0.0;
    
    LHS = R*Tc;
    LHS = (LHS)/Pc;
    
    B = BHat*LHS;
    
    return B;
}

double VirialEOSC0Calc(double Tr)
{
    double C0 = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    
    frac1 = 0.02432/Tr;
    
    frac2 = pow(Tr, 10.5);
    frac2 = 0.00313/(frac2);
    
    C0 = 0.01407 + frac1;
    C0 = (C0) - frac2;
    
    return C0;
}

double VirialEOSC1Calc(double Tr)
{
    double C1 = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    
    frac1 = pow(Tr, 2.7);
    frac1 = 0.05539/(frac1);
    
    frac2 = pow(Tr, 10.5);
    frac2 = 0.00242/(frac2);
    
    C1 = 0.01407 + frac1;
    C1 = (C1) - frac2;
    
    return C1;
}

double VirialEOSCHat(double C0, double C1, double accFactor)
{
    double CHat = 0.0;
    
    CHat = accFactor*C1;
    CHat = C0 + (CHat);
    
    return CHat;
}

double VirialEOSCCalc(double CHat, double Pc, double Tc)
{
    double C = 0.0;
    double LHS = 0.0;
    double sto = 0.0;
    
    sto = pow(R, 2);
    LHS = pow(Tc, 2);
    LHS = (sto)*(LHS);
    
    sto = pow(Pc, 2);
    LHS = (LHS)/(sto);
    
    C = CHat*LHS;
    
    return C;
}

double VirialEOSCalc(double T, double V, double B, double C)
{
    double P = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    double frac3 = 0.0;
    double denom = 0.0;
    
    frac1 = R*T;
    frac1 = (frac1)/V;
    
    frac2 = R*T;
    frac2 = (frac2)*B;
    denom = pow(V, 2);
    frac2 = (frac2)/(denom);
    
    frac3 = R*T;
    frac3 = (frac2)*C;
    denom = pow(V, 3);
    frac3 = (frac2)/(denom);
    
    P = frac1 + frac2;
    P = (P) + frac3;
    
    return P;
}

EOSIsotherm VirialEOSIsotherm(double Pc, double Tc, double Vc, double T, double omega, double *B, double *C)
{
    EOSIsotherm Isotherm = {0.0};
    
    double Tr = 0.0;
    double Vr = 0.0;
    
    double BHat = 0.0;
    
    double CHat = 0.0;
    
    Tr = reducedProperty(Tc, T);
    
    //  Calculating coefficients
    BHat = VirialEOSBHat(VirialEOSB0Calc(Tr), VirialEOSB1Calc(Tr), 0, omega);
    *B = VirialEOSBCalc(BHat, Pc, Tc);
    
    CHat = VirialEOSCHat(VirialEOSC0Calc(Tr), VirialEOSC1Calc(Tr), omega);
    *C = VirialEOSCCalc(CHat, Pc, Tc);
    
    Vr = 0.001;
    for(int i = 0; i < 1000; ++i)
    {
        Isotherm.V[i] = Vr*Vc;
        Isotherm.T[i] = T;
        Isotherm.P[i] = VirialEOSCalc(Isotherm.T[i], Isotherm.V[i], *B, *C);
        
        Vr += 0.001;
    }
    
    return Isotherm;
}

EOSIsotherm VirialEOSIsothermPolar(double Pc, double Tc, double Vc, double T, double omega, double a, double b, double *B, double *C)
{
    EOSIsotherm Isotherm = {0.0};
    
    double Tr = 0.0;
    double Vr = 0.0;
    
    double BHat = 0.0;
    
    double CHat = 0.0;
    
    Tr = reducedProperty(Tc, T);
    
    //  Calculating coefficients
    BHat = VirialEOSBHat(VirialEOSB0Calc(Tr), VirialEOSB1Calc(Tr), VirialEOSB2Calc(a, b, Tr), omega);
    *B = VirialEOSBCalc(BHat, Pc, Tc);
    
    CHat = VirialEOSCHat(VirialEOSC0Calc(Tr), VirialEOSC1Calc(Tr), omega);
    *C = VirialEOSCCalc(CHat, Pc, Tc);
    
    Vr = 0.001;
    for(int i = 0; i < 1000; ++i)
    {
        Isotherm.V[i] = Vr*Vc;
        Isotherm.T[i] = T;
        Isotherm.P[i] = VirialEOSCalc(Isotherm.T[i], Isotherm.V[i], *B, *C);
        
        Vr += 0.001;
    }
    
    return Isotherm;
}

void VirialEOSDisplay(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, EOSIsotherm data, double B, double C)
{
    printf("_Virial_Equation_of_State_Results_\n");
    printf("\tInput parameters:\n");
    printf("Critical pressure:\n");
    printf("Pc =\t%.3f\tbar\n", Pc);
    printf("Critical temperature:\n");
    printf("Tc =\t%.3f\tK\n", Tc);
    printf("Critical molar volume:\n");
    printf("Vc =\t%.3f\tcm3/mol\n", Vc);
    printf("Acentric factor:\n");
    printf("omega =\t%.3f\t[ ]\n\n", omega);
    
    if(polar == 1)
    {
        printf("a =\t%.3f\t[ ]\n", a);
        printf("b =\t%.3f\t[ ]\n\n", b);
    }
    
    printf("\tIntermediate parameters:\n");
    printf("Second virial coefficient:\n");
    printf("B =\t%.3f\tcm3/mol\n", B);
    printf("Third virial coefficient:\n");
    printf("C =\t%.3f\tcm6/mol2\n\n", C);
    
    printf("\tOutput parameters:\n");
    printf("Isotherm produced at:");
    printf("T =\t%.3f\tK\n\n", T);
    
    printf("P (bar)\tV_m (cm3/mol)\tT (K)\tZ ([ ])\n");
    for(int i = 0; i < 1000; ++i)
    {
        printf("%f\t", (data.P[i]));
        printf("%f\t", (data.V[i]));
        printf("%f\t", data.T[i]);
        printf("%f\n", ( (data.P[i])*(data.V[i]) )/( R*(data.T[i]) ));
    }
}

void VirialEOSWrite(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, EOSIsotherm data, double B, double C)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    char filetemp[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Virial EOS T ... K Results
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
    
    strcat(filename, " Virial EOS");
    //printf("File name: \"%s\"\n", filename);
    
    sprintf(filetemp, " T %.0f K", T);
    strcat(filename, filetemp);
    
    strcat(filename," Results.txt");
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
    fprintf(fp, "_Virial_Equation_of_State_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Critical pressure:\n");
    fprintf(fp, "Pc =\t%.3f\tbar\n", Pc);
    fprintf(fp, "Critical temperature:\n");
    fprintf(fp, "Tc =\t%.3f\tK\n", Tc);
    fprintf(fp, "Critical molar volume:\n");
    fprintf(fp, "Vc =\t%.3f\tcm3/mol\n", Vc);
    fprintf(fp, "Acentric factor:\n");
    fprintf(fp, "omega =\t%.3f\t[ ]\n\n", omega);
    
    if(polar == 1)
    {
        fprintf(fp, "a =\t%.3f\t[ ]\n", a);
        fprintf(fp, "b =\t%.3f\t[ ]\n\n", b);
    }
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Second virial coefficient:\n");
    fprintf(fp, "B =\t%.3f\tcm3/mol\n", B);
    fprintf(fp, "Third virial coefficient:\n");
    fprintf(fp, "C =\t%.3f\tcm6/mol2\n\n", C);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Isotherm produced at:");
    fprintf(fp, "T =\t%.3f\tK\n\n", T);
    
    fprintf(fp, "P (bar)\tV_m (cm3/mol)\tT (K)\tZ ([ ])\n");
    for(int i = 0; i < 1000; ++i)
    {
        fprintf(fp, "%.3f\t", data.P[i]);
        fprintf(fp, "%.3f\t", data.V[i]);
        fprintf(fp, "%.3f\t", data.T[i]);
        fprintf(fp, "%.3f\n", ( (data.P[i])*(data.V[i]) )/( R*(data.T[i]) ));
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void VirialEOSWriteSwitch(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, EOSIsotherm data, double B, double C)
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
                VirialEOSWrite(polar, Pc, Tc, Vc, T, omega, a, b, data, B, C);
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

void VirialEOS(void)
{
    int whilmain = 0;
    printf("Virial Equation of State\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char input[maxstrlen];
        
        double Pc = 0.0;
        double Tc = 0.0;
        double Vc = 0.0;
        double T = 0.0;
        double omega = 0.0; // Accentric factor
        double a = 0.0;
        double b = 0.0;
        
        double B = 0.0;
        double C = 0.0;
        
        int control = 0;
        
        EOSIsotherm data = {0.0};
        
        int polar = 0;
        //  Data Collection
        control = 1;
        while(control == 1)
        {
            printf("Is the molecule polar? ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    polar = 1;
                    control = 0;
                    break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    polar = 0;
                    control = 0;
                    break;
                default:
                    printf("Input not recognised. Please try again.\n");
                    break;
            }
        }
        
        VirialEOSVariable(polar, &Pc, &Tc, &Vc, &omega, &a, &b);
        
        control = 1;
        while(control == 1)
        {
            T = inputDouble(0, "temperature of produced isotherm", "deg C");
            T = (T) + 273.15;
            
            //  Data Manipulation
            clock_t start, end;
            double timeTaken = 0.0;
            
            start = clock();
            
            // Calculation function(s)
            if(polar == 0)
            {
                data = VirialEOSIsotherm(Pc, Tc, Vc, T, omega, &B, &C);
            }
            if(polar == 1)
            {
                data = VirialEOSIsothermPolar(Pc, Tc, Vc, T, omega, a, b, &B, &C);
            }
            
            end = clock();
            
            timeTaken = ((double)(end - start))/CLOCKS_PER_SEC;
            printf("Process completed in %.3f seconds.\n\n", timeTaken);
            
            //  Displaying results
            VirialEOSDisplay(polar, Pc, Tc, Vc, T, omega, a, b, data, B, C);
            
            //  Writing to File
            VirialEOSWriteSwitch(polar, Pc, Tc, Vc, T, omega, a, b, data, B, C);
            
            char input[maxstrlen];
            int ContCond;
            
            ContCond = 1;
            while(ContCond == 1)
            {
                printf("Do you want to create another isotherm? ");
                fgets(input, sizeof(input), stdin);
                switch(input[0])
                {
                    case '1':
                    case 'T':
                    case 'Y':
                    case 't':
                    case 'y':
                        ContCond = 0;
                    break;
                    case '0':
                    case 'F':
                    case 'N':
                    case 'f':
                    case 'n':
                        control = 0;
                        ContCond = 0;
                    break;
                    default:
                        printf("Input not recognised\n");
                    break;
                }
            }
        }
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
