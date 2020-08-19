//
//  01dIsoChHeat .c
//  Process Model (MacOS Version)
//
//  Created by Matthew Cheung on 02/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BC_T1.h"
#include "IdealGasLaw.h"
#include "01dIsoChHeat.h"

#define maxstrlen 128
#define R 8.31455

//Declaring global variables and allocating memory
    //Function Output

    //Calculation Variables

    //Miscellaneous Variables

void IsoChHeatVar(double *n, double *c_v, double *V, double *P1, double *P2, double *T1, double *T2, int method)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Amount of substance in system (kmol/s) = ");
    *n = atof(fgets(input, sizeof(input), stdin));
    
    printf("Heat capacity at constant volume (J/mol.K) = ");
    *c_v = atof(fgets(input, sizeof(input), stdin));
    
    printf("System volume (m3) = ");
    *V = atof(fgets(input, sizeof(input), stdin));
    
    switch(method)
    {
        case 0:
            printf("Initial system temperature (deg C) = ");
            *T1 = atof(fgets(input, sizeof(input), stdin));
            *T1 = (*T1) + 273.15;
            
            printf("Final system temperature (deg C) = ");
            *T2 = atof(fgets(input, sizeof(input), stdin));
            *T2 = (*T2) + 273.15;
            
            *P1 = IdealPressure(*n, *T1, *V);
            *P2 = IdealPressure(*n, *T2, *V);
            
            break;
        case 1:
            printf("Initial system pressure (kPa) = ");
            *P1 = atof(fgets(input, sizeof(input), stdin));
            *P1 = 1000*(*P1);
            
            printf("Final system pressure (kPa) = ");
            *P2 = atof(fgets(input, sizeof(input), stdin));
            *P2 = 1000*(*P2);
            
            *T1 = IdealTemperature(*n, *P1, *V);
            *T2 = IdealTemperature(*n, *P2, *V);
            
            break;
    }
    //Debug script:
    printf("Function is returning:\n");
    printf("n = %.3f mol/s\n", *n);
    printf("c_v = %.3f J/(mol.K)\n", *c_v);
    printf("V = %.3f m3\n", *V);
    printf("T1 = %.3f K\n", *T1);
    printf("T2 = %.3f K\n", *T2);
    printf("P1 = %.3f Pa\n", *P1);
    printf("P2 = %.3f Pa\n", *P2);
    
    fflush(stdout);
}

double IsoChHeatCalcT(double n, double c_v, double T1, double T2)
{
    double Q = 0.0; //Process heat
    double brack = 0.0; 
    brack = T2 - T1;
    
    Q = n*c_v;
    Q = (Q)*(brack);
    
    return Q;
}

double IsoChHeatCalcP(double n, double c_v, double V, double P1, double P2) 
{
    double Q = 0.0;
    double frac = 0.0;
    double brack = 0.0;
    
    frac = (V/R);
    brack = P2 - P1;
    
    Q = n*c_v;
    Q = (Q)*frac;
    Q = (Q)*brack;
    
    return Q;
}

void IsoChHeatPlot(double n, double c_v, double V, double P1, double P2)
{
    double incr;
    
    int reso = 50;
    
    incr = P2 - P1;
    incr = (incr)/reso;
    
    double profile[reso + 1][5];
    
    int i = 0;
    
    profile[i][0] = P1;
    profile[i][1] = V;
    profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
    profile[i][3] = 0; //No heat provided to system by definition of initial state
    profile[i][4] = 0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        profile[i][0] = profile[i - 1][0] + incr;
        profile[i][1] = V;
        profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
        profile[i][3] = IsoChHeatCalcP(n, c_v, V, profile[i - 1][0], profile[i][0]); //No heat provided to system by definition of initial state
        profile[i][4] = profile[i - 1][4] + profile[i][3];
    }
    printf("%i rows generated.\n---\n", i);
    printf("System conditions:\n");
    //Print System conditions
    printf("P (kPa)\tV (m3)\tT (deg C)\tQ (kW)\tQ (kW)\n");
    int j = 0; //Number of columns
    
    for(i = 0; i < (reso + 1); ++i){
        for(j = 0; j < 5; ++j)
        {
            if(j == 0){
                printf("%.3f", 0.001*profile[i][j]);
            }
            if(j == 1){
                printf("%.3f", profile[i][j]);
            }
            if(j == 2){
                printf("%.3f", profile[i][j] - 273.15);
            }
            if(j == 3 || j == 4){
                printf("%.3f", profile[i][j]);
            }
            if(j == 4){
                printf("\n");
            }else{
                printf("\t");
            }
        }
    }
}
/*
void [Data Plot & Write](...)
{
    char filename[maxstrlen];
    char path[maxstrlen];
    char filepath[maxstrlen*2];

    FILE *fp
    
    //Set file name as timestamp + Name of Program
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof(filename));
    
    strftime(filename, 16, "%Y%m%d %H%M%S", info);
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " (Name of Program)");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof(filepath));
    
    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");
    printf("File path: \"%s\"\n", filepath);
    
    strcat(filepath, filename);
    void free(void *filename);
    
    printf("File name: \"%s\"\n", filename);
    printf("Full file path: \"%s\"\n\n", filepath);
    
    //Testing if directory is not present
    
    if(fopen(filepath, "r") == NULL){
        printf("Directory does not exist, writing data to \"Documents\" folder instead.\n");
        strcpy(filepath, "/Users/user/Documents/");
        printf("File is now being outputted to: %s\n", filepath);
    }
    printf("Note that write sequence disabled by zsh\n");
    
    //Get file path - This step is optional
    *path = (char)malloc(sizeof(path));
    ...
    
    //Creating the full path and name through concatenation
    *filepath = (char)malloc(sizeof(filepath));
    strcpy(filepath, filepath);
    strcat(filepath, filename);
    strcat(filepath, ".txt");
    
    //Testing if directory exists
    if(fopen(filepath, "r") == NULL)
    {
            printf("Directory does not exist, writing data to \"Documents\" folder\n");
            strcpy(filepath, "/Users/user/Documents/");
            printf("Filepath: %s\n", filepath);
    }
    
    printf("Beginning file write\n");
    //File open
    fp = fopen(filepath, "w+");
    
    //Writing to file
    fprintf(fp, "...", ...);
    ...
    
    //File close
    fclose(fp);
    
    printf("Write successful\n");
    fflush(stdout);
}
*/
void IsoChHeat()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("Isochoric Process Heat\n");
    printf("No volume work is being done on or by the system\n\n");
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];
        
        double n;
        double c_v;
        double V;
        double P1;
        double P2;
        double T1;
        double T2;
        
        double heat = 0;
        
        int whilinput = 1;
        int method = 2;
        //Data collection
        while(whilinput == 1)
        {
            printf("Please choose from the following methods of calculation:\n");
            printf("1. From Temperature change\n");
            printf("2. From Pressure change\n");
            printf("Selection: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'T':
                case 't':
                    method = 0;
                    whilinput = 0;
                    break;
                case '2':
                case 'P':
                case 'p':
                    method = 1;
                    whilinput = 0;
                    break;
                default:
                    printf("Input not recognised\n");
                    break;
            }
        }
        IsoChHeatVar(&n, &c_v, &V, &P1, &P2, &T1, &T2, method);
        
        //Data manipulation
        switch(method)
        {
            case 0:
                heat = IsoChHeatCalcT(n, c_v, T1, T2);
                break;
            case 1:
                heat = IsoChHeatCalcP(n, c_v, V, P1, P2);
                break;
        }
        printf("Q = %.3f kW\n", heat*0.001);
        IsoChHeatPlot(n, c_v, V, P1, P2);
        //Ask for file write (Remember while loop)
        //...
        //Continue function
        int whilcont = 1;
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
