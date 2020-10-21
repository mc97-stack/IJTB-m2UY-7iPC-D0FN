//
//  02bPolyShaftWork.c
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
#include "B48BC_T2.h"
#include "02bPolyShaftWork.h"

#define maxstrlen 128

int PolyShaftVar(double *P1, double *P2, double *T1, double *n, double *R, double *alpha)
{
    char input[maxstrlen];
    int ideal = 0;
    
    printf("Initial system pressure (kPa) = ");
    *P1 = atof(fgets(input, sizeof(input), stdin));
    *P1 = (*P1)*1000;
    
    printf("Final system pressure (kPa) = ");
    *P2 = atof(fgets(input, sizeof(input), stdin));
    *P2 = (*P2)*1000;
    
    printf("Initial system temperature (deg C) = ");
    *T1 = atof(fgets(input, sizeof(input), stdin));
    *T1 = (*T1) + 273.15;
    
    printf("Moles of component in system (kmol/ s) = ");
    *n = atof(fgets(input, sizeof(input), stdin));
    *n = (*n) * 1000;
    
    printf("Gas constant, R (J/ mol.K) = ");
    *R = atof(fgets(input, sizeof(input), stdin));
    
    printf("Polytropic Index ([ ]) = ");
    *alpha = atof(fgets(input, sizeof(input), stdin));
    
    if((*alpha - 1.0) < 0.005){
        // Polytropic index is pretty much 1
        ideal = 1;
    }else{
        // Polytropic index is not 1
        ideal = 2;
    }
    
    return ideal;
}

double IdealShaftCalc(double n, double R, double T1, double P1, double P2)
{
    double W_S = 0.0;
    double frac = 0.0;
    
    frac = P2/P1;
    frac = log(frac);
    
    W_S = n*R;
    W_S = (W_S)*T1;
    W_S = (W_S)*frac;
    
    return W_S;
}

double PolyShaftCalc(double n, double R, double T1, double P1, double P2, double alpha)
{
    double W_S = 0.0;
    double power = 0.0;
    double brack = 0.0;
    
    power = alpha - 1;
    power = (power)/alpha;
    
    brack = P2/P1;
    brack = pow(brack, power);
    brack = 1 - brack;
    
    power = 1/power;
    W_S = n*R;
    W_S = (W_S)*T1;
    W_S = (W_S)*(power);
    W_S = (W_S)*(brack);
    W_S = -1 * (W_S);
    
    return W_S;
}

void PolyShaftWrite(double n, double R, double T1, double P1, double P2, double alpha, double W_S)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Polytropic Shaft Work Results
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
    
    strcat(filename, " Polytropic Shaft Work Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
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
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filepath, "w+");
    
    //Write to file
    fprintf(fp, "_Polytropic_Shaft_Work_Results_\n");
    
    //Write to file
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial System Pressure:\n");
    fprintf(fp, "P_1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Final System Pressure:\n");
    fprintf(fp, "P_2 =\t%.3f\tkPa\n", P2*0.001);
    
    fprintf(fp, "Initial System Temperature:\n");
    fprintf(fp, "T_1 =\t%.3f\tdeg C\n", T1 - 273.15);
    
    fprintf(fp, "Molar flowrate of component i:\n");
    fprintf(fp, "n =\t%.3f\tkmol/s\n\n", n);
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
    fprintf(fp, "Shaft Work:\n");
    fprintf(fp, "W_S =\t%.3f\tkW\t= -\\frac{\\gamma}{\\gamma - 1}P_1V_1\\left[1 - \\left(\\frac{P_2}{P_1}\\right)^{\\frac{\\gamma - 1}{\\gamma}}\\right]", W_S*0.001);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PolyShaftWriteCheck(double n, double R, double T1, double P1, double P2, double alpha, double W_S)
{
    int SaveC;
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
                PolyShaftWrite(n, R, T1, P1, P2, alpha, W_S);
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

void PolyShaftWork()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("Polytropic Shaft Work\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        double P1 = 0.0;
        double P2 = 0.0;
        double T1 = 0.0;
        double n = 0.0;
        double R = 0.0;
        double alpha = 0.0;
        
        double W_S = 0.0;
        
        int ideal = 0;
        int whilcont = 0;
        
        //Data collection
        ideal = PolyShaftVar(&P1, &P2, &T1, &n, &R, &alpha);
        //Data manipulation
        if(ideal == 1){
            // Ideal
            printf("Isothermal process has been specified.\n");
            W_S = IdealShaftCalc(n, R, T1, P1, P2);
        }
        if(ideal == 2){
            // Normal polytropic
            printf("Polytropic process has been specified.\n");
            W_S = PolyShaftCalc(n, R, T1, P1, P2, alpha);
        }
        printf("Shaft work = %.3f kW\n", W_S*0.001);
        
        //Ask for file write (Remember while loop)
        PolyShaftWriteCheck(n, R, T1, P1, P2, alpha, W_S);
        
        //Continue function
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
    }
    fflush(stdout);
}
