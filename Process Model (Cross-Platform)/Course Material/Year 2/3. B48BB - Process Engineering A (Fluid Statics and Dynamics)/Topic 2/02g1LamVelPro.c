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
#include <time.h>

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

LamVelProf LamVelProfCalc(double dP, double L, double d, double mu, int *rows) 
{
    double interval = 0.0; // Interval between radius data entries used to calculate the point velocities.
    double frad = 0.0; // Absolute pipe radius. (N.B. This is different to the variable 'r'.)
    double r = 0.0; // Point radius.
    
    int i = 0;
    
    static LamVelProf profile;
    // Initialising all elements in the struct
    for(int i = 0; i < 5000; ++i){
        profile.r[i] = 0.0;
        profile.v_x[i] = 0.0;
        profile.ratio[i] = 0.0;
    }
    
    interval = 0.0001; // m
    
    frad = d/2;
    *rows = ((frad)/ (interval)) + 1; //Calculating number of rows for the profile results matrix
    
    printf("%i rows required\n", *rows);
    
    for(r = 0.0; r < (frad + (interval/2)); r += interval)
    {
        profile.r[i] = r; //Displaying point radius
        profile.v_x[i] = LamVelCalc(dP, L, d, mu, r); //Calculating point velocity
        profile.ratio[i] = LamGenCalc(r, d);
        ++i;
    }
    printf("%i rows successfully generated\n\n", i);
    *rows = i;
    
    return profile;
}

void LamVelProWrite(double dP, double L, double d, double mu, int rows, LamVelProf profile)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Laminar Velocity Profile Results
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
    
    strcat(filename, " Laminar Velocity Profile Results");
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
    fprintf(fp, "_Laminar_Velocity_Profile_Calculation_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid pressure loss:\n");
    fprintf(fp, "dP =\t%.3f\tPa\n", dP);
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "L =\t%.3f\tm\n", L);
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    fprintf(fp, "Fluid dynamic viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tPa\n\n", dP);
    
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "r (mm)\tv_x (m/s)\tv_x/v_{max}\n");
    for(int i = 0; i < ++rows; ++i){
        fprintf(fp, "%.3f\t", 1000*profile.r[i]);
        fprintf(fp, "%.3f\t", profile.v_x[i]);
        fprintf(fp, "%.3f\n", profile.ratio[i]);
    }
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void LamVelProWriteCheck(double dP, double L, double d, double mu, int rows, LamVelProf profile)
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
                LamVelProWrite(dP, L, d, mu, rows, profile);
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
        LamVelProf profile;
        
        // Initialising all elements in the struct
        for(int i = 0; i < 5000; ++i){
            profile.r[i] = 0.0;
            profile.v_x[i] = 0.0;
            profile.ratio[i] = 0.0;
        }
        
        int rows = 0;
        
        //Data collection
        LamVelProVar(&dP, &L, &d, &mu);
        //Data manipulation
        profile = LamVelProfCalc(dP, L, d, mu, &rows);
        
        printf("r (mm)\tv_x (m/s)\tv/v_max\n");
        for(int i = 0; i < rows; ++i){
            printf("%f\t%f\t%f\n", profile.r[i]*1000, profile.v_x[i], profile.ratio[i]);
        }
        
        //Ask for file write (Remember while loop)
        LamVelProWriteCheck(dP, L, d, mu, rows, profile);
        
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
