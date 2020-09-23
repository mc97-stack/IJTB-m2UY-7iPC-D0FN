//
//  01aFluComp .c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "B48BB_T1.h"
#include "01aFluComp.h"

#define maxstrlen 128
#define R 8.31455
#define BST (+1)

void FluCompVar(double *P, double *V, double *n, double *T)
{
    //Input variables
    char pres[maxstrlen];
    char vol[maxstrlen];
    char mol[maxstrlen];
    char temp[maxstrlen];
    
    //Pressure
    printf("Absolute system pressure (kPa) = ");
    *P = atof(fgets(pres, sizeof(pres), stdin));
    
    *P = *P * 1000.0;
    //Volume
    printf("System volume (m3) = ");
    *V = atof(fgets(vol, sizeof(vol), stdin));
    
    //moles
    printf("Amount of Substance in System (kmol) = ");
    *n = atof(fgets(mol, sizeof(mol), stdin));
    
    *n = *n * 1000.0; //Conversion to mol
    
    //Temperature
    printf("System Temperature (deg C) = ");
    *T = atof(fgets(temp, sizeof(temp), stdin));
    
    *T = *T + 273.15; //Conversion to K
    
    printf("You have entered:\n%f Pa\n%f m3\n%f mol\n%f K\n\n", *P, *V, *n, *T);
    fflush(stdout);
}

double FluCompCalc(double P, double V, double n, double T)
{
    double top;
    double bot;
    double frac;
    
    double c; // Fluid compressibility factor
    
    frac = (1.0)/V;
    frac = (-1.0)*(frac);
    
    top = (-1.0)*n;
    top = (top)*R;
    top = (top)*T;
    
    bot = pow(P, 2);
    
    c = (top)/(bot);
    
    c = (frac)*(c);
    
    printf("c = %f m3/ Pa \n", c);
    return c;
}

void FluCompWrite(double P, double V, double n, double T, double c)
{
    //Function variables
    char filename[67];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Fluid Coefficient of Compressibility
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof *filename);
    
    strftime(filename, 16, "%Y%m%d %H%M%S", info);
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Fluid Coefficient of Compressibility Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
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
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filepath, "w+");
    
    //Write to file
    fprintf(fp, "P = %.3f kPa\n", P*0.001);
    fprintf(fp, "V = %.3f m3\n", V);
    fprintf(fp, "n = %.3f mol\n", n);
    fprintf(fp, "T = %.3f deg C\n\n", (T - 273.15));
    fprintf(fp, "c = $$-\\frac{1}{V}\\left(\\frac{\\delta{V}}{\\delta{P}}\\right))_T$$ = %.3f m3/Pa\n", c);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
    
}

void FluComp()
{
    char SaveQ[maxstrlen];
    char ContIn[maxstrlen];
    
    int WhilFlu;
    
    printf("Fluid Coefficient of Compressibility\n");
    
    WhilFlu = 1;
    while(WhilFlu == 1)
    {
        //Declaring variables used
        double FCompCoeff;
        double P;
        double V;
        double n;
        double T;
        
        FluCompVar(&P, &V, &n, &T);
        printf("Function has outputted:\n%f Pa\n%f m3\n%f mol\n%f K\n\n", P, V, n, T);
        
        FCompCoeff = FluCompCalc(P, V, n, T);
        printf("Function has outputted = %f m3/ Pa\n\n", FCompCoeff);
        
        int SaveC;
        SaveC = 1;
        while(SaveC == 1)
        {
            //*SaveQ = (char)malloc(sizeof(SaveQ));
            printf("Do you want to save results to file? ");
            fgets(SaveQ, sizeof(SaveQ), stdin);
            switch(SaveQ[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    FluCompWrite(P, V, n, T, FCompCoeff);
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
        
        
        int ContCond;
        ContCond = 1;
        while(ContCond == 1)
        {
            printf("Do you want to continue? ");
            *ContIn = (char)malloc(sizeof *ContIn);
            fgets(ContIn, sizeof(ContIn), stdin);
            switch(ContIn[0])
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
                    ContCond = 0;
                    WhilFlu = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
            void free(void *ContIn);
        }
        printf("\n");
        fflush(stdout);
    }
    //fflush(stdout);
}
