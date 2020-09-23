//
//  01cIsoBVolWork .c
//  Process Model (MacOS Version)
//
//  Created by Matthew Cheung on 01/07/2020.
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
#include "01cIsoBVolWork.h"

#define maxstrlen 128
#define R 8.31455

void IsoBVolWorkVar(double *n, double *P, double *V1, double *V2, double *T1, double *T2, int method)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Moles of substance (kmol/s) = ");
    *n = atof(fgets(input, sizeof(input), stdin));
    
    *n = (*n)*1000;
    
    printf("System pressure (kPa) = ");
    *P = atof(fgets(input, sizeof(input), stdin));
    
    *P = (*P)*1000;
    
    if(method == 1)
    {
        printf("Initial system volume (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
        
        printf("Final system volume (m3) = ");
        *V2 = atof(fgets(input, sizeof(input), stdin));
        
        *T1 = IdealTemperature(*n, *P, *V1);
        *T2 = IdealTemperature(*n, *P, *V2);
    }else{
        printf("Initial system temperature (deg C) = ");
        *T1 = atof(fgets(input, sizeof(input), stdin));
        
        *T1 = (*T1) + 273.15;
        
        printf("Final system temperature (deg C) = ");
        *T2 = atof(fgets(input, sizeof(input), stdin));
        
        *T2 = (*T2) + 273.15;
        
        *V1 = IdealVolume(*n, *P, *T1);
        //printf("V1 = %.3f  m3\n", *V1);
        *V2 = IdealVolume(*n, *P, *T2);
    }
    
    printf("System Conditions:\n");
    printf("n = %.3f mol/s \n", *n);
    printf("P = %.5f Pa\n", *P);
    printf("V1 = %.3f m3\n", *V1);
    printf("V2 = %.3f m3\n", *V2);
    printf("T1 = %.3f K\n", *T1);
    printf("T2 = %.3f K\n", *T2);
    
    fflush(stdout);
}

double IsoBVolWorkCalcV(double P, double V1, double V2)
{
    double work = 0.0;
    
    work = V2 - V1;
    work = (work)*P;
    work = -1*(work);
    return work;
}

double IsoBVolWorkCalcT(double n, double T1, double T2)
{
    double work = 0.0;
    
    work = T2 - T1;
    work = n*R*(work);
    
    return work;
}

void IsoBVolWorkPlot(double n, double P, double V1, double V2)
{
    double incr = 0.0;
    
    int reso = 0;
    
    reso = 50;
    
    incr = V2 - V1;
    incr = (incr)/reso;
    
    double profile[reso + 1][5];
    
    int i = 0;
    profile[i][0] = P;
    profile[i][1] = V1;
    profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]); //System temperature
    profile[i][3] = 0; //Section work
    profile[i][4] = 0; //Cumulative work
    
    for(i = 1; i < (reso + 1); ++i)
    {
        profile[i][0] = P;
        profile[i][1] = profile[i - 1][1] + incr;
        profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
        profile[i][3] = IsoBVolWorkCalcV(P, profile[i - 1][1], profile[i][1]);
        profile[i][4] = (profile[i - 1][4] + profile[i][3]);
    }
    printf("%i rows generated.\n---\n", i);
    printf("System conditions:\n");
    //Print System conditions
    printf("P (kPa)\tV (m3)\tT (deg C)\tW_V (kW)\tW_V (kW)\n");
    
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
    //return [Function Output];
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
void IsoBVolWork()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Isobaric Process\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];
        
        double n = 0.0;
        double P = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        
        int selec = 0;
        int method = 0; //Variable initialised as 2 to avoid triggering an unwanted behaviour
        int whilcont = 0;
        
        selec = 1;
        method = 2;
        //Data collection
        while(selec == 1)
        {
            printf("Please choose from the following methods of Calculation:\n");
            printf("1. From Volume Change\n");
            printf("2. From Temperature Change\n");
            printf("Selection: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'V':
                case 'v':
                    method = 1;
                    selec = 0;
                break;
                case '2':
                case 'T':
                case 't':
                    method = 0;
                    selec = 0;
                break;
                default:
                    printf("Input not recognised.\n");
                break;
            }
        }
        printf("method  = %i\n", method);
        IsoBVolWorkVar(&n, &P, &V1, &V2, &T1, &T2, method);
        printf("Function returns:\n");
        printf("n = %.3f mol/s \n", n);
        printf("P = %.5f Pa\n", P);
        printf("V1 = %.3f m3\n", V1);
        printf("V2 = %.3f m3\n", V2);
        printf("T1 = %.3f K\n", T1);
        printf("T2 = %.3f K\n", T2);
        
        //Data manipulation
        if(method == 1)
        {
            printf("W_V = %.3f kW\n", IsoBVolWorkCalcV(P, V1, V2));
        }else{
            if(method == 0)
            {
                printf("W_V = %.3f kW\n", IsoBVolWorkCalcT(n, T1, T2));
            }
        }
        
        IsoBVolWorkPlot(n, P, V1, V2);
        //Ask for file write (Remember while loop)
        //...
        
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
