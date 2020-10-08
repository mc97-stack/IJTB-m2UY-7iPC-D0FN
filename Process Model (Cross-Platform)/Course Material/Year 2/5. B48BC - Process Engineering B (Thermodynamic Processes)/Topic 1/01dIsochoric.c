//
//  01dIsochoric Process.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "B48BC_T1.h"
#include "01dIsochoric.h"
#include "IdealGasLaw.h"

#define maxstrlen 128
#define R 8.3145

void IsocVariable(int method, double *P1, double *P2, double *V, double *T1, double *T2, double *n, double *cv)
{
    char input[maxstrlen];
    
    if(method == 1){
        printf("Initial system pressure (kPa) = ");
        *P1 = atof(fgets(input, sizeof(input), stdin));
        *P1 = (*P1)*1000;
        
        printf("Final system pressure (kPa) = ");
        *P2 = atof(fgets(input, sizeof(input), stdin));
        *P2 = (*P2)*1000;
        
        printf("System volume (m3) = ");
        *V = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 2){
        printf("Initial system temperature (deg C) = ");
        *T1 = atof(fgets(input, sizeof(input), stdin));
        *T1 = (*T1) + 273.15;
        
        printf("Final system temperature (deg C) = ");
        *T2 = atof(fgets(input, sizeof(input), stdin));
        *T2 = (*T2) + 273.15;
    }
    if(method == 1 || method == 2){
        printf("Moles of substance (kmol/s) = ");
        *n = atof(fgets(input, sizeof(input), stdin));
        *n = (*n)*1000;
        
        printf("Heat capacity at constant volume (J/mol.K) = ");
        *cv = atof(fgets(input, sizeof(input), stdin));
    }
    fflush(stdout);
}

double IsocPressure(double P1, double P2, double V, double n, double cv)
{
    double brack = 0.0;
    double heat = 0.0;
    
    brack = P2 - P1;
    
    heat = V/R;
    heat = (heat)*brack;
    heat = (heat)*n;
    heat = (heat)*cv;
    
    return heat;
}

double IsocTemperature(double T1, double T2, double n, double cv)
{
    double heat = 0.0;
    
    heat = T2 - T1;
    heat = cv*(heat);
    heat = n*(heat);
    
    return heat;
}

void IsocProfile(int method, double P1, double P2, double V, double T1, double T2, double n, double cv)
{
    double incr = 0.0; // Increment between data points
    int reso = 0; // Resolution of the generated plot
    int i = 0; // Row controller
    
    reso = 50;
    double profile[reso + 1][6];
    
    if(method == 1){
        incr = P2 - P1;
        incr = (incr)/reso;
    }
    if(method == 2){
        incr = T2 - T1;
        incr = (incr)/reso;
    }
    
    // Setting the initial system conditions
    i = 0;
    if(method == 1){
        profile[i][0] = P1;
        profile[i][1] = V;
        profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
    }
    if(method == 2){
        profile[i][0] = 0.0;
        profile[i][1] = 0.0;
        profile[i][2] = T1;
    }
    profile[i][3] = 0.0;
    profile[i][4] = 0.0;
    profile[i][5] = 0.0;
    
    for(i = 1; i < (reso + 1); ++i)
    {
        if(method == 1){
            profile[i][0] = profile[i - 1][0] + incr;
            profile[i][1] = V;
            profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
            profile[i][3] = 0.0;
            profile[i][4] = IsocPressure(profile[i - 1][0], profile[i][0], profile[i][1], n, cv);
            profile[i][5] = profile[i - 1][5] + profile[i][4];
        }
        if(method == 2){
            profile[i][0] = 0.0;
            profile[i][1] = 0.0;
            profile[i][2] = profile[i - 1][2] + incr;
            profile[i][3] = 0.0;
            profile[i][4] = IsocTemperature(profile[i - 1][2], profile[i][2], n, cv);
            profile[i][5] = profile[i - 1][5] + profile[i][4];
        }
    }
    printf("Total heat required = %.3f kW\n", (profile[i-1][5])/1000 );
    printf("Profile calculated in %d rows\n\n", i);
    
    int whildisplay = 0;
    whildisplay = 1;
    
    while(whildisplay == 1)
    {
        printf("Do you want to display the final profile? [Y/N] ");
        char display[maxstrlen];
        fgets(display, sizeof(display), stdin);
        switch(display[0]){
            case '1':
            case 'Y':
            case 'y':
                printf("P (kPa)\tV(m3)\tT (K)\tWork (kW)\tQ (kW)\tQ_cum. (kW)\n");
                for(int row = 0; row < i; ++row){
                    for (int col = 0; col < 6; ++col)
                    {
                        if(col == 0||col == 3||col == 4||col == 5){
                            printf("%.3f", (profile[row][col])/1000);
                        }
                        if(col == 1){
                            printf("%.3f", profile[row][col]);
                        }
                        if(col == 2){
                            printf("%.3f", profile[row][col]);
                        }
                        if(col == 5){
                            printf("\n");
                        }else{
                            printf("\t");
                        }
                    }
                }
                whildisplay = 0;
                break;
            case '0':
            case 'N':
            case 'n':
                // code
                whildisplay = 0;
                break;
            default:
                printf("Invalid input.\n");
                break;
        }
    }
    fflush(stdout);
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
void Isochoric()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("Isochoric Process\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        char methodinput[maxstrlen];
        
        double P1 = 0.0;
        double P2 = 0.0;
        double V = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        double n = 0.0;
        double cv = 0.0;
        
        int method = 0;
        
        int whilmethod = 0;
        int whilcont = 0;
        
        //Data Collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure\n2. Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(methodinput, sizeof(methodinput), stdin);
            switch(methodinput[0])
            {
                case '1':
                case 'P':
                case 'p':
                    //code
                    method  = 1;
                    whilmethod = 0;
                    break;
                case '2':
                case 'T':
                case 't':
                    //code
                    method = 2;
                    whilmethod = 0;
                    break;
                case 'Q':
                case 'q':
                    whilmethod = 0;
                    break;
                default:
                    printf("Invalid input, please try again");
                    break;
            }
        }
        if(method == 1 || method == 2){
            //Data collection
            IsocVariable(method, &P1, &P2, &V, &T1, &T2, &n, &cv);
            
            //Data manipulation
            IsocProfile(method, P1, P2, V, T1, T2, n, cv);
            
            //Ask for file write (Remember while loop)
            
            
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
        }else{
            whilmain = 0;
        }
        fflush(stdout);
    }
}
