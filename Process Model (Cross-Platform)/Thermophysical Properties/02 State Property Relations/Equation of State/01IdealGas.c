//
//  01IdealGas.c
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
#include "01IdealGas.h"

#define maxstrlen 128
#define R 83.145    // (bar.cm3)/(mol.K)

void IdealEOSVariable(double *T)
{
    *T = inputDouble(1, "Temperature of isotherm", "deg C");
    *T = (*T) + 273.15;
}

double IdealEOSCalculation(double V, double T)
{
    double P = 0.0;
    
    P = R*T;
    P = (P)/V;
    
    return P;
}

EOSIsotherm IdealEOSIsotherm(double T)
{
    double incr = 0.0;
    EOSIsotherm Isotherm = {0.0};
    
    incr = 0.5;
    
    //  Values have already been initialised to 0
    for(int i = 1; i < 1000; ++i)
    {
        Isotherm.V[i] = Isotherm.V[i - 1] + incr;
        Isotherm.T[i] = T;
        Isotherm.P[i] = IdealEOSCalculation(Isotherm.V[i], Isotherm.T[i]);
    }
    
    return Isotherm;
}

void IdealEOSDisplay(double T, EOSIsotherm data)
{
    printf("_Ideal_Gas_Equation_of_State_Results_\n");
    printf("\tInput parameters:\n");
    printf("Isotherm produced at:");
    printf("T =\t%.3f\tK\n\n", T);
    
    printf("\tOutput parameters:\n");
    printf("P (bar)\tV_m (cm3/mol)\tT (K)\tZ ([ ])\n");
    for(int i = 0; i < 1000; ++i)
    {
        printf("%.3f\t", data.P[i]);
        printf("%.3f\t", data.V[i]);
        printf("%.3f\t", data.T[i]);
        printf("%.3f\n", ( (data.P[i])*(data.V[i]) )/( R*(data.T[i]) ));
    }
}

void IdealEOSWrite(double T, EOSIsotherm data)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    char filetemp[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Ideal Gas EOS T ... K Results
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
    
    strcat(filename, " Ideal Gas EOS");
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
    fprintf(fp, "_Ideal_Gas_Equation_of_State_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Isotherm produced at:");
    fprintf(fp, "T =\t%.3f\tK\n\n", T);
    
    fprintf(fp, "\tOutput parameters:\n");
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

void IdealEOSWriteSwitch(double T, EOSIsotherm data)
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
                IdealEOSWrite(T, data);
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

void IdealEOS(void)
{
    int whilmain = 0;
    int control = 0;
    printf("Ideal Gas Equation of State\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        control = 1;
        while(control == 1)
        {
            //  Variable declaration
            double T = 0.0;
            
            EOSIsotherm data = {0.0};
            
            //  Data Collection
            IdealEOSVariable(&T);
            
            //  Data Manipulation
            clock_t start, end;
            double timeTaken = 0.0;
            
            start = clock();
            
            data = IdealEOSIsotherm(T);
            
            end = clock();
            
            timeTaken = ((double)(end - start))/CLOCKS_PER_SEC;
            printf("Process completed in %.3f seconds.\n\n", timeTaken);
            
            //  Displaying results
            IdealEOSDisplay(T, data);
            
            //  Writing to File
            IdealEOSWriteSwitch(T, data);
            
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
