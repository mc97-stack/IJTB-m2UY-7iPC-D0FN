//
//  02g1LamVelPro.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "02g1LamVelPro.h"

#define maxstrlen 128

void LamVelProVar(double *dP, double *L, double *d, double *mu)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    
    *d = (*d)*0.001;
    
    printf("Pipe length (m) = ");
    *L = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid pressure loss (Pa) = ");
    *dP = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid viscosity (cP) = ");
    *mu = atof(fgets(input, sizeof(input), stdin));
    
    *mu = (*mu)*0.001;
    
    fflush(stdout);
}

double LamVelCalc(double dP, double L, double d, double mu, double r) 
{
    //Calculation of the theoretical velocity profile with the flow possessing laminar characteristics
    double frac1 = 0.0;
    double frac2 = 0.0;
    double frac3 = 0.0;
    
    double v_x = 0.0;
    
    frac1 = (dP/L);
    
    frac2 = pow(d,2);
    frac2 = (frac2)/(16*mu);
    
    frac3 = 2*r;
    frac3 = (frac3)/d;
    frac3 = pow(frac3, 2);
    frac3 = 1 - (frac3);
    
    v_x = frac1 * frac2;
    v_x = (v_x) * frac3;
    
    return v_x;
}

double LamGenCalc(double r, double d)
{
    //Calculation of the general velocity profile with the flow possessing laminar characteristics
    double func = 0.0;
    
    func = 2*r;
    func = (func)/d;
    func = pow(func, 2);
    func = 1 - (func);
    return func; //Returns v/v_max
}

void LamVelProfCalc(double dP, double L, double d, double mu) 
{
    char display[maxstrlen];
    
    double interval = 0.0; // Interval between radius data entries used to calculate the point velocities.
    double prad = 0.0; // Absolute pipe radius. (N.B. This is different to the variable 'r'.)
    double r = 0.0; // Point radius.
    
    int rows = 0;
    int i = 0;
    int whildisp = 0;
    
    interval = 0.001;
    
    prad = d/2;
    rows = ((prad)/ (interval)) + 1; //Calculating number of rows for the profile results matrix
    
    printf("%i rows required\n", rows); 
    double profile[rows][3];
    
    for(r = 0.0; r < (prad + (interval/2)); r += interval)
    {
        profile[i][0] = r; //Displaying point radius
        profile[i][1] = LamVelCalc(dP, L, d, mu, r); //Calculating point velocity
        profile[i][2] = LamGenCalc(r, d);
        //profile[i][3] = i + 1;
        ++i;
    }
    printf("%i rows successfully generated\n\n", i);
    
    whildisp = 1;
    while(whildisp == 1)
    {
        printf("Do you want to display the generated data? ");
        fgets(display, sizeof(display), stdin);
        switch(display[0])
        {
            case '1':
            case 'Y':
            case 'y':
                printf("Displaying data\n");
                printf("Inputted variables:\n");
                printf("dP =\t%.3f\tPa\n", dP);
                printf("L =\t%.3f\tm\n", L);
                printf("d =\t%.1f\tmm\n", d*1000);
                printf("mu =\t%.3f\tPa.s\n", mu);
                printf("v_max =\t%.3f\tm/s\n\n", LamVelCalc(dP, L, d, mu, 0));
                
                printf("r (m)\tv_x (m/s)\tv/v_max\n");
                int row = 0;
                int col = 0;
                for(row = 0; row < i; ++row)
                {
                    for(col = 0; col < 3; ++col)
                    {
                        printf("%.5f", profile[row][col]);
                        if(col == 2)
                        {
                            printf("\n");
                        }else{
                            printf("\t");
                        }
                    }
                }
                whildisp = 0;
            break;
            case '0':
            case 'N':
            case 'n':
                whildisp = 0;
            break;
            default:
                printf("Input not recognised.\n");
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
void LamVelPro()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    int whilcont = 0;
    printf("Laminar flow velocity profile\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
            //Calculation Variables
        double dP = 0.0;
        double L = 0.0;
        double d = 0.0;
        double mu = 0.0;
        
        //Data collection
        LamVelProVar(&dP, &L, &d, &mu);
        //Data manipulation
        LamVelProfCalc(dP, L, d, mu);
        
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
