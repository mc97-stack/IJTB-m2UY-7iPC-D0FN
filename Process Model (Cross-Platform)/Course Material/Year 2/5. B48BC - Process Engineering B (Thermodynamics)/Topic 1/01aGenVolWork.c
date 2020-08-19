//
//  01aGenVolWork.c
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
#include "01aGenVolWork.h"

#define maxstrlen 128
#define R 8.31455

void GenVolWorkVar(double *n, double *T1, double *T2, double *V1, double *V2)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Moles of substance (kmol/s) = ");
    *n = atof(fgets(input, sizeof(input), stdin));
    
    *n = (*n)*1000;
    
    printf("Initial system temperature (deg C) = ");
    *T1 = atof(fgets(input, sizeof(input), stdin));
    
    *T1 = (*T1)+273.15;
    
    printf("Final system temperature (deg C) = ");
    *T2 = atof(fgets(input, sizeof(input), stdin));
    
    *T2 = (*T2)+273.15;
    
    printf("Initial system volume (m3) = ");
    *V1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Final system volume (m3) = ");
    *V2 = atof(fgets(input, sizeof(input), stdin));
    
    fflush(stdout);
}

double GenVolWorkCalc(double n, double T1, double T2, double V1, double V2)
{
    double term1 = 0.0;
    double term2 = 0.0;
    
    term1 = pow(T2, 2);
    term1 = (1.0)/(2.0)*term1;
    term1 = term1 - ((1.0)/(2.0))*pow(T1, 2);
    
    term2 = V2/ V1;
    term2 = log(term2);
    
    double VolWork = 0.0;
    
    VolWork = term1*term2;
    VolWork = (VolWork)*n*R;
    VolWork = -1 * (VolWork);
    
    return VolWork;
}

void GenVolWorkPlot(double n, double T1, double T2, double V1, double V2)
{
    //Profile is the results array containing the results matrix
    double incr1 = 0.0;
    double incr2 = 0.0;
    
    int reso = 50;
    
    incr1 = T2 - T1;
    incr1 = (incr1)/(double)reso;
    
    incr2 = V2 - V1;
    incr2 = (incr2)/(double)reso;
    
    double profile[reso + 1][5];
    
    printf("For %.3f kmol of substance\n", n*0.001);
    
    int i = 0;
    profile[i][0] = T1;
    profile[i][1] = V1;
    profile[i][2] = IdealPressure(n, T1, V1);
    profile[i][3] = 0; //No volume work done to get to the initial state
    profile[i][4] = 0;
    
    for(i = 1; i < reso + 1; ++i)
    {
        profile[i][0] = profile[i - 1][0] + incr1;
        profile[i][1] = profile[i - 1][1] + incr2;
        profile[i][2] = IdealPressure(n, profile[i][0], profile[i][1]);
        profile[i][3] = GenVolWorkCalc(n, profile[i - 1][0], profile[i][0], profile[i - 1][1], profile[i][1]);
        profile[i][4] = profile[i - 1][4] + profile[i][3];
    }
    printf("%i rows generated.\n", i);
    
    printf("T (deg C)\tV (m3)\tP (kPa)\tW_V (kW)\tW_V (kW)\n");
    int j = 0; //Number of columns
    
    for(i = 0; i < (reso+1); ++i){
        for(j = 0; j < 5; ++j)
        {
            if(j == 0){
                printf("%.3f", profile[i][j] - 273.15);
            }
            if(j == 1){
                printf("%.3f", profile[i][j]);
            }
            if(j == 2){
                printf("%.3f", profile[i][j]*0.001);
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
    //return profile;
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
void GenVolWork()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("General Volume Work\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        double n = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        
        double VolWork = 0.0;
        
        //Data collection
        GenVolWorkVar(&n, &T1, &T2, &V1, &V2);
        //Data manipulation
        VolWork = GenVolWorkCalc(n, T1, T2, V1, V2);
        printf("Work estimate: W_V = %.3f kW\n\n", VolWork*0.001);
        
        GenVolWorkPlot(n, T1, T2, V1, V2);
        
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
    printf("\n");
    fflush(stdout);
}
