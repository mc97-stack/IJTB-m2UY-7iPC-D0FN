//
//  02g2TurVelPro.c
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
#include "02g2TurVelPro.h"

#define maxstrlen 128

void TurVelProVar(double *umax, double *d)
{
    char input[maxstrlen];
    
    double u = 0.0;
    
    printf("Average fluid velocity (m/s) = ");
    u = atof(fgets(input, sizeof(input), stdin));
    
    *umax = (49.0)/(60.0);
    *umax = (*umax) * u;
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    *d = (*d) * 0.001;
    
    fflush(stdout);
}

double TurVelProCalc(double vmax, double r, double d, double *gen) 
{
    //Calculated using Prandtl's one-seventh law
    double bot = 0.0;
    double y = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    double v_x = 0.0;
    
    bot = d/2;
    frac2 = (1.0)/(7.0);
    
    y = bot - r;
    frac1 = y/(bot);
    v_x = pow(frac1, frac2);
    *gen = v_x;
    
    v_x = vmax*(v_x);
    
    return v_x;
}

TurVelProf TurVelProfCalc(double vmax, double d, int *rows) 
{
    double interval = 0.0;
    double prad = 0.0;
    
    static TurVelProf profile;
    // Initialising all elements in the struct
    for(int i = 0; i < 5000; ++i){
        profile.r[i] = 0.0;
        profile.v_x[i] = 0.0;
        profile.ratio[i] = 0.0;
    }
    
    interval = 0.001;
    prad = d/2;
    
    *rows = ((prad)/ (interval)) + 1;
    
    printf("%i rows required\n", *rows);
    
    int i = 0;
    for(double r = 0.0; r < (prad + (interval/2)); r += interval)
    {
        profile.r[i] = r; //Displaying point radius
        profile.v_x[i] = TurVelProCalc(vmax, r, d, &profile.ratio[i]);
        ++i;
    }
    printf("%i rows successfully generated\n\n", i);
    *rows = i;
    return profile;
}

void TurVelProDisp(double umax, double d, int rows, TurVelProf profile)
{
    printf("_Turbulent_Velocity_Profile_(Prandtl's_One-Seventh_Law)_Results_\n");
    
    //Write to file
    printf("\tInput parameters:\n");
    printf("Maximum fluid velocity:");
    printf("u_{max.} =\t%.3f\tm/s\n", umax);
    printf("Pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    
    printf("\tOutput parameters:\n");
    printf("r (mm)\tv_x (m/s)\tv_x/v_{max}\n");
    for(int i = 0; i < ++rows; ++i){
        printf("%.3f\t", 1000*profile.r[i]);
        printf("%.3f\t", profile.v_x[i]);
        printf("%.3f\n", profile.ratio[i]);
    }
}

void TurVelProWrite(double umax, double d, int rows, TurVelProf profile)
{
    //Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Turbulent Velocity Profile Results
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
    
    strcat(filename, " Turbulent Velocity Profile Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
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
    fprintf(fp, "_Turbulent_Velocity_Profile_(Prandtl's_One-Seventh_Law)_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Maximum fluid velocity:");
    fprintf(fp, "u_{max.} =\t%.3f\tm/s\n", umax);
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    
    fprintf(fp, "\tOutput parameters:\n");
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

void TurVelProWriteCheck(double umax, double d, int rows, TurVelProf profile)
{
    int SaveC = 0;
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
                TurVelProWrite(umax, d, rows, profile);
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

void TurVelPro()
{
    //Main Function
    int whilmain = 0;
    printf("Prandtl's One-Seventh Law Velocity Profile\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        double vmax = 0;
        double d = 0;
        TurVelProf profile;
        
        // Initialising all elements in the struct
        for(int i = 0; i < 5000; ++i){
            profile.r[i] = 0.0;
            profile.v_x[i] = 0.0;
            profile.ratio[i] = 0.0;
        }
        
        int rows = 0;
        
        //  Data collection
        TurVelProVar(&vmax, &d);
        
        //  Running calculations
        profile = TurVelProfCalc(vmax, d, &rows);
        
        //  Displaying results
        TurVelProDisp(vmax, d, rows, profile);
        
        //  Writing to File
        TurVelProWriteCheck(vmax, d, rows, profile);
    }
    fflush(stdout);
}
