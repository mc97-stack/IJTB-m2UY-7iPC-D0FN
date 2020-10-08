//
//  01eAdiabatic.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 07/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Custom Header Files
#include "B48BC_T1.h"
#include "01eAdiabatic.h"
#include "IdealGasLaw.h"

#define maxstrlen 128
#define R 8.3145 // J/mol.K

void AdiaVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T1, double *T2, double *n, double *gamma)
{
    char input[maxstrlen];
    
    if(method == 1||method == 2){
        printf("Initial Pressure (kPa) = ");
        *P1 = atof(fgets(input, sizeof(input), stdin));
        *P1 = (*P1)*1000;
    }
    if(method == 2){
        printf("Final Pressure (kPa) = ");
        *P2 = atof(fgets(input, sizeof(input), stdin));
        *P2 = (*P2)*1000;
    }
    if(method == 1){
        printf("Initial volume (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 1){
        printf("Final volume (m3) = ");
        *V2 = atof(fgets(input, sizeof(input), stdin));
    }
    if(method == 2||method == 3){
        printf("Initial Temperature (deg C) = ");
        *T1 = atof(fgets(input, sizeof(input), stdin));
        *T1 = (*T1)+273.15;
    }
    if(method == 0){
        printf("Final Temperature (deg C) = ");
        *T2 = atof(fgets(input, sizeof(input), stdin));
        *T2 = (*T2)+273.15;
    }
    if(method == 1 || method == 2){
        printf("Moles of fluid in system (kmol) = ");
        *n = atof(fgets(input, sizeof(input), stdin));
        *n = (*n)*1000;
    }
    if(method == 1 || method == 2)
    {
        printf("Heat capacity ratio ([]): ");
        *gamma = atof(fgets(input, sizeof(input), stdin));
    }
    
    fflush(stdout);
}

double AdiaVolume(double P1, double V1, double V2, double gamma)
{
    double frac1num = 0.0;
    double frac1den = 0.0;
    double frac2 = 0.0;
    double power = 0.0;
    double brack = 0.0;
    double work = 0.0;
    
    frac2 = V1/V2;
    power = gamma - 1;
    brack = pow(frac2, power);
    brack = 1 - brack; // Bracket term calculated
    
    frac1num = P1*V1;
    frac1den = 1 - gamma; 
    
    work = frac1num/frac1den; // Starting fraction calculated
    work = work*brack;
    
    return work;
}

double AdiaTemperature(double n, double T1, double P1, double P2, double gamma)
{
    double frac1num = 0.0;
    double frac1den = 0.0;
    double frac2 = 0.0;
    double power = 0.0;
    double brack = 0.0;
    double work = 0.0;
    
    frac2 = P2/P1;
    power = gamma - 1;
    power = (power)/gamma;
    
    brack = pow(frac2, power);
    brack = 1 - brack; // Bracket term calculated
    
    frac1num = n*R;
    frac1num = frac1num*T1;
    frac1den = gamma - 1; 
    
    work = frac1num/frac1den; // Starting fraction calculated
    work = work*brack; // Volume work calculated
    work = work*(-1);
    
    return work;
}

double AdiaFinalPress(double P1, double V1, double V2, double gamma)
{
    double V1f = 0.0;
    double V2f = 0.0;
    double P = 0.0;
    // Used for the Pressure-Volume relation
    V1f = pow(V1, gamma);
    V2f = pow(V2, gamma);
    
    P = P1*V1f;
    P = (P)/V2f;
    
    return P;
}

double AdiaFinalTemp(double T1, double P1, double P2, double gamma)
{
    double power = 0.0;
    double P1f = 0.0;
    double P2f = 0.0;
    double T = 0.0;
    // Calculated from Pressure-Temperature relation
    power = gamma - 1;
    power = (power)/gamma;
    
    P1f = pow(P1, power);
    P2f = pow(P2, power);
    
    T = T1*P1f;
    T = (T)/P2f;
    
    return T;
}

void AdiaProfile(int method, double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma)
{
    double incr = 0.0; // Difference between datapoints
    int reso = 50; // Resolution of dataset
    int i = 0;
    
    if(method == 1){
        // Volume work calculated from volume ratio
        incr = V2 - V1;
        incr = (incr)/reso;
    }
    if(method == 2){
        // Volume work calculated from pressure ratio
        incr = P2 - P1;
        incr = (incr)/reso;
    }
    double profile[reso+1][5];
    
    i = 0;
    if(method == 1)
    {
        profile[i][0] = P1;
        profile[i][1] = V1;
        profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
        
        profile[i][3] = 0.0;
        profile[i][4] = 0.0;
    }
    if(method == 2)
    {
        profile[i][0] = P1;
        profile[i][2] = T1;
        profile[i][1] = IdealVolume(n, profile[i][0], profile[i][2]);
        
        profile[i][3] = 0.0;
        profile[i][4] = 0.0;
    }
    for(i = 1; i< (reso+1) ; ++i)
    {
        if(method == 1)
        {
            profile[i][1] = profile[i-1][1] + incr;
            profile[i][0] = AdiaFinalPress(profile[i-1][0], profile[i-1][1], profile[i][1], gamma);
            profile[i][2] = IdealTemperature(n, profile[i][0], profile[i][1]);
            profile[i][3] = AdiaVolume(profile[i-1][0], profile[i-1][1], profile[i][1], gamma);
            profile[i][4] = profile[i-1][4] + profile[i][3];
        }
        if(method == 2)
        {
            profile[i][0] = profile[i-1][0]+incr;
            profile[i][2] = AdiaFinalTemp(profile[i-1][2], profile[i-1][0], profile[i][0], gamma);
            profile[i][1] = IdealVolume(n, profile[i][0], profile[i][2]);
            profile[i][3] = AdiaTemperature(n, profile[i-1][2], profile[i-1][0], profile[i][0], gamma);
            profile[i][4] = profile[i-1][4] + profile[i][3];
        }
    }
    printf("Total Volume work done = %.3f kW\n", (profile[i-1][4])/1000 );
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
                printf("P (kPa)\tV(m3)\tT (K)\tWork (kW)\tWork_cum. (kW)\n");
                for(int row = 0; row < i; ++row){
                    for (int col = 0; col < 5; ++col)
                    {
                        if(col == 0||col == 3||col == 4){
                            printf("%.3f", (profile[row][col])/1000);
                        }
                        if(col == 1){
                            printf("%.3f", profile[row][col]);
                        }
                        if(col == 2){
                            printf("%.3f", profile[row][col]);
                        }
                        if(col == 4){
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
void Adiabatic()
{
    //Main Function
    char ContCond[maxstrlen];
    char methodinput[maxstrlen];
    
    int whilmain = 0;
    
    printf("Adiabatic Volume Work\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        double P1 = 0.0;
        double P2 = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        double T1 = 0.0;
        double T2 = 0.0;
        double n = 0.0;
        double gamma = 0.0;
        
        //Data collection
        int whilmethod = 0;
        int method = 0;
        int whilcont = 0;
        
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please select from the following calculation methods:\n1. Pressure-Volume\n2. Pressure-Temperature\n");
            printf("Selection [1 - 2]: ");
            fgets(methodinput, sizeof(methodinput), stdin);
            switch(methodinput[0])
            {
                case '1':
                case 'V':
                case 'v':
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
        if(method == 1||method == 2){
            AdiaVariable(method, &P1, &P2, &V1, &V2, &T1, &T2, &n, &gamma);
            
            //Data manipulation
            AdiaProfile(method, P1, P2, V1, V2, T1, T2, n, gamma);
            
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
    }
    fflush(stdout);
}
