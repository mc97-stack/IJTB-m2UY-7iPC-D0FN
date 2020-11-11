//
//  03CubicEOS.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

/// MARK: HEADER DECLARATIONS
//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom Header Files
#include "System.h"
//#include "EquationofState.h"  // This header is included in "03CubicEOS.h"
#include "02PVTRelations.h"
#include "03CubicEOS.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define R 83.145        // (bar.cm3)/(mol.K)

/// MARK: VARIABLE INPUT
void CubicEOSVariable(double *Pc, double *Tc, double *omega)
{
    *Pc = inputDouble(0, "critical pressure", "bar");
    *Tc = inputDouble(0, "critical temperature", "K");
    *omega = inputDouble(0, "Acentric factor", "[ ]");
}

/// MARK: GENERAL CALCULATIONS
double CubicEOSCalculation(double T, double V, double a, double b, double u, double w)
{
    double P = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    double sto = 0.0;
    
    frac1 = R*T;
    sto = V - b;
    frac1 = (frac1)/(sto);
    
    frac2 = pow(V, 2);
    
    sto = u*b;
    sto = (sto)*V;
    frac2 = (frac2)+(sto);
    
    sto = pow(b, 2);
    sto = (sto)*w;
    frac2 = (frac2) + (sto);
    
    frac2 = a/(frac2);
    
    P = frac1 - frac2;
    
    return P;
}

double CubicEOSCompCalculation(double P, double V, double a, double b, double u, double w)
{
    double Z = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    double store = 0.0;
    
    frac1 = V - b;
    frac1 = V/(frac1);
    
    frac2 = pow(V, 2);
    store = w*b;
    store = (store)*V;
    frac2 = (frac2) + (store);
    store = pow(b, 2);
    store = w*(store);
    frac2 = (frac2) + (store);
    frac2 = P*(frac2);
    
    frac2 = a/(frac2);
    
    Z = (frac1) - (frac2);
    
    return Z;
}

/// MARK: ARRAY FUNCTION
EOSIsotherm CubicEOSIsotherm(double T, double a, double b, double u, double w)
{
    EOSIsotherm Isotherm = {0.0};
    
    double V = 0.0;
    
    V = 0.0;
    
    for(int i = 0; i < 1000; ++i)
    {
        Isotherm.V[i] = V;
        Isotherm.T[i] = T;
        Isotherm.P[i] = CubicEOSCalculation(Isotherm.T[i], Isotherm.V[i], a, b, u, w);
        Isotherm.Z[i] = ((Isotherm.P[i])*(Isotherm.V[i]))/(R*(Isotherm.T[i]));
        V += 0.5;
    }
    
    return Isotherm;
}

/// MARK: DISPLAY AND WRITE
void CubicEOSDisplay(int eqn, double Pc, double Tc, double omega, double T, double a, double b, EOSIsotherm Isotherm)
{
    if(eqn == 1){
        printf("_van_der_Waals_EOS_Results_\n");
    }
    if(eqn == 2){
        printf("_Redlich-Kwong_EOS_Results_\n");
    }
    if(eqn == 3){
        printf("_Soave-Redlich-Kwong_EOS_Results_\n");
    }
    if(eqn == 4){
        printf("_Peng-Robinson_EOS_Results_\n");
    }
    printf("\tInput parameters:\n");
    printf("Critical pressure:\n");
    printf("Pc =\t%.3f\tbar\n", Pc);
    printf("Critical temperature:\n");
    printf("Tc =\t%.3f\tK\n", Tc);
    printf("Acentric factor:\n");
    printf("omega =\t%.3f\t[ ]\n\n", omega);
    
    printf("Isotherm temperature:\n");
    printf("T =\t%.3f\tK\n\n", T);
    
    printf("\tIntermediate parameters:\n");
    printf("Volume repulsivity:\n");
    printf("a =\t%.3f\tbar.cm6/mol2\n", a);
    printf("Real molecular volume:\n");
    printf("b =\t%.3f\tcm3/mol\n\n", b);
    
    printf("\tOutput parameters:\n");
    printf("P (bar)\tv (cm3/mol)\tT (K)\tT (deg C)\t\tZ([ ])\n");
    for(int i = 0; i < 1000; ++i)
    {
        printf("%f\t", Isotherm.P[i]);
        printf("%f\t", Isotherm.V[i]);
        printf("%f\t", Isotherm.T[i]);
        printf("%f\t\t", Isotherm.T[i] - 273.15);
        printf("%f\n", Isotherm.Z[i]);
    }
}

void CubicEOSWrite(int eqn, double Pc, double Tc, double omega, double T, double a, double b, EOSIsotherm Isotherm)
{
    //  Function variables
    char filename[maxstrlen] = {""};   // Variable used to store the file name as it is built.
    char filetemp[maxstrlen] = {""};
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //  Set file name as timestamp + "..." EOS (Z) T ... K Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    if(eqn == 1){
        strcat(filename, " van der Waals EOS");
    }
    if(eqn == 2){
        strcat(filename, " Redlich Kwong EOS");
    }
    if(eqn == 3){
        strcat(filename, " Soave Redlich Kwong EOS");
    }
    if(eqn == 4){
        strcat(filename, " Peng Robinson EOS");
    }
    //printf("File name: \"%s\"\n", filename);
    
    sprintf(filetemp, " T %.0f K", T);
    strcat(filename, filetemp);
    
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
    
    //  Open file
    fp = fopen(filename, "w+");
    free(filename);
    
    //  Write to file
    if(eqn == 1){
        fprintf(fp, "_van_der_Waals_EOS_Results_\n");
    }
    if(eqn == 2){
        fprintf(fp, "_Redlich-Kwong_EOS_Results_\n");
    }
    if(eqn == 3){
        fprintf(fp, "_Soave-Redlich-Kwong_EOS_Results_\n");
    }
    if(eqn == 4){
        fprintf(fp, "_Peng-Robinson_EOS_Results_\n");
    }
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Critical pressure:\n");
    fprintf(fp, "Pc =\t%.3f\tbar\n", Pc);
    fprintf(fp, "Critical temperature:\n");
    fprintf(fp, "Tc =\t%.3f\tK\n", Tc);
    fprintf(fp, "Acentric factor:\n");
    fprintf(fp, "omega =\t%.3f\t[ ]\n\n", omega);
    
    fprintf(fp, "Isotherm temperature:\n");
    fprintf(fp, "T =\t%.3f\tK\n\n", T);
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Volume repulsivity:\n");
    fprintf(fp, "a =\t%.3f\tbar.cm6/mol2\n", a);
    fprintf(fp, "Real molecular volume:\n");
    fprintf(fp, "b =\t%.3f\tcm3/mol\n\n", b);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "P (bar)\tv (cm3/mol)\tT (K)\tT (deg C)\t\tZ([ ])\n");
    for(int i = 0; i < 1000; ++i)
    {
        fprintf(fp, "%f\t", Isotherm.P[i]);
        fprintf(fp, "%f\t", Isotherm.V[i]);
        fprintf(fp, "%f\t", Isotherm.T[i]);
        fprintf(fp, "%f\t\t", Isotherm.T[i] - 273.15);
        fprintf(fp, "%f\n", Isotherm.Z[i]);
    }
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CubicEOSSwitch(int mode, int eqn, double Pc, double Tc, double omega, double T, double VdWa, double VdWb, double RKa, double RKb, double SRKa, double SRKb, double PRa, double PRb, EOSIsotherm VdWIsotherm, EOSIsotherm RKIsotherm, EOSIsotherm SRKIsotherm, EOSIsotherm PRIsotherm)
{
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        char input[maxstrlen];
        
        if(mode == 1)
        {
            printf("Do you want to display the results? ");
        }
        if(mode == 2)
        {
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
                    if(eqn == 1 || eqn == 5){
                        CubicEOSDisplay(1, Pc, Tc, omega, T, VdWa, VdWb, VdWIsotherm);
                    }
                    if(eqn == 2 || eqn == 5){
                        CubicEOSDisplay(2, Pc, Tc, omega, T, RKa, RKb, RKIsotherm);
                    }
                    if(eqn == 3 || eqn == 5){
                        CubicEOSDisplay(3, Pc, Tc, omega, T, SRKa, SRKb, SRKIsotherm);
                    }
                    if(eqn == 4 || eqn == 5){
                        CubicEOSDisplay(4, Pc, Tc, omega, T, PRa, PRb, PRIsotherm);
                    }
                    fflush(stdout);
                }
                if(mode == 2){
                    if(eqn == 1 || eqn == 5){
                        CubicEOSWrite(1, Pc, Tc, omega, T, VdWa, VdWb, VdWIsotherm);
                    }
                    if(eqn == 2 || eqn == 5){
                        CubicEOSWrite(2, Pc, Tc, omega, T, RKa, RKb, RKIsotherm);
                    }
                    if(eqn == 3 || eqn == 5){
                        CubicEOSWrite(3, Pc, Tc, omega, T, SRKa, SRKb, SRKIsotherm);
                    }
                    if(eqn == 4 || eqn == 5){
                        CubicEOSWrite(4, Pc, Tc, omega, T, PRa, PRb, PRIsotherm);
                    }
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
void CubicEOS(void)
{
    int whilmain = 0;
    printf("Cubic Equations of State\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
            //  Subroutine behaviour (Delete me when done)
        char input[maxstrlen];      // Variable used to store character input.
        int control = 0;            // Variable used to control the number of individual isotherms generated.
        int eqn = 0;                // Variable used to control which equation of state is calculated. All equations is also an option.
        int ContCond = 0;           // Variable used to control whether the while loop generating the isotherm should be broken or not.
        int VdWElems = 0;           // Variable used to store the total number of elements used to store the calculated data from the van der Waals equation of state.
        int RKElems = 0;            // Variable used to store the total number of elements used to store the calculated data from the Redlich-Kwong equation of state.
        int SRKElems = 0;           // Variable used to store the total number of elements used to store the calculated data from the Soave-Redlich-Kwong equation of state.
        int PRElems = 0;            // Variable used to store the total number of elements used to store the calculated data from the Peng-Robinson equation of state.
        
        VdWElems = 4*1000;
        RKElems = 4*1000;
        SRKElems = 4*1000;
        PRElems = 4*1000;
        
        double VdWa = 0.0;             // Repulsive term in the van der Waals equation of state.
        double VdWb = 0.0;             // Actual molecular volume term in the van der Waals equation of state.
        double RKa = 0.0;              // Repulsive term in the van der Waals equation of state.
        double RKb = 0.0;              // Actual molecular volume term in the van der Waals equation of state.
        double SRKa = 0.0;             // Repulsive term in the van der Waals equation of state.
        double SRKb = 0.0;             // Actual molecular volume term in the van der Waals equation of state.
        double PRa = 0.0;              // Repulsive term in the van der Waals equation of state.
        double PRb = 0.0;              // Actual molecular volume term in the van der Waals equation of state.
        EOSIsotherm *VdWEOSIsotherm = calloc(VdWElems, sizeof(double));
        if(VdWEOSIsotherm == NULL){
            printf("Calloc failed. Ending calculations\n");
            whilmain = 0;
        }
        EOSIsotherm *RKEOSIsotherm = calloc(RKElems, sizeof(double));
        if(RKEOSIsotherm == NULL){
            printf("Calloc failed. Ending calculations\n");
            whilmain = 0;
        }
        EOSIsotherm *SRKEOSIsotherm = calloc(SRKElems, sizeof(double));
        if(SRKEOSIsotherm == NULL){
            printf("Calloc failed. Ending calculations\n");
            whilmain = 0;
        }
        EOSIsotherm *PREOSIsotherm = calloc(PRElems, sizeof(double));
        if(PREOSIsotherm == NULL){
            printf("Calloc failed. Ending calculations\n");
            whilmain = 0;
        }
        
        double Pc = 0.0;            // Critical pressure.
        double Tc = 0.0;            // Critical temperature.
        double omega = 0.0;         // Acentric factor.
        double T = 0.0;             // Isotherm temperature.
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data Collection
        CubicEOSVariable(&Pc, &Tc, &omega);
        
        control = 1;
        while(control == 1)
        {
            printf("Which equation of state would you like to calculate?\n");
            printf("1. van der Waals.\n");
            printf("2. Redlich-Kwong.\n");
            printf("3. Soave-Redlich-Kwong.\n");
            printf("4. Peng-Robinson.\n");
            printf("5. All.\n");
            printf("Selection [1 - 5]: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                    eqn = 1;
                    control = 0;
                    break;
                case '2':
                    eqn = 2;
                    control = 0;
                    break;
                case '3':
                    eqn = 3;
                    control = 0;
                    break;
                case '4':
                    eqn = 4;
                    control = 0;
                    break;
                case '5':
                    eqn = 5;
                    control = 0;
                    break;
                default:
                    printf("Input not recognised. Please enter an integer between 1 and 3.\n");
                    break;
            }
        }
        
        control = 1;
        while(control == 1)
        {
            T = inputDouble(0, "temperature of produced isotherm", "deg C");
            T = (T) + 273.15;
            
            //  Data Manipulation
            clock_getres(CLOCK_MONOTONIC, &start);
            clock_gettime(CLOCK_MONOTONIC, &start);
            
            // Calculation function(s)
            if(eqn == 1 || eqn == 5){
                VdWa = VdWcalculateA(Tc, Pc);
                VdWb = VdWcalculateB(Tc, Pc);
                *VdWEOSIsotherm = CubicEOSIsotherm(T, VdWa, VdWb, 0, 0);
            }
            if(eqn == 2 || eqn == 5){
                RKa = RKcalculateA(Tc, Pc, T);
                RKb = RKcalculateB(Tc, Pc);
                *RKEOSIsotherm = CubicEOSIsotherm(T, RKa, RKb, 1, 0);
            }
            if(eqn == 3 || eqn == 5){
                SRKa = SRKcalculateA(Tc, Pc, T, omega);
                SRKb = RKcalculateB(Tc, Pc);
                *SRKEOSIsotherm = CubicEOSIsotherm(T, SRKa, SRKb, 1, 0);
            }
            if(eqn == 4 || eqn == 5){
                PRa = PRcalculateA(Tc, Pc, T, omega);
                PRb = PRcalculateB(Tc, Pc);
                *PREOSIsotherm = CubicEOSIsotherm(T, PRa, PRb, 2, -1);
            }
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Displaying Results
            CubicEOSSwitch(1, eqn, Pc, Tc, omega, T, VdWa, VdWb, RKa, RKb, SRKa, SRKb, PRa, PRb, *VdWEOSIsotherm, *RKEOSIsotherm, *SRKEOSIsotherm, *PREOSIsotherm);
            
            //  writing results
            CubicEOSSwitch(2, eqn, Pc, Tc, omega, T, VdWa, VdWb, RKa, RKb, SRKa, SRKb, PRa, PRb, *VdWEOSIsotherm, *RKEOSIsotherm, *SRKEOSIsotherm, *PREOSIsotherm);
            
            free(VdWEOSIsotherm);
            free(RKEOSIsotherm);
            free(SRKEOSIsotherm);
            free(PREOSIsotherm);
            
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
