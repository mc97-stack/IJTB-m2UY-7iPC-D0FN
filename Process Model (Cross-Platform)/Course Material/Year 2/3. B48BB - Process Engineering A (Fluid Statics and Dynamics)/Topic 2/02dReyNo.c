//
//  02dReyNo.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 28/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T2.h"
#include "02dReyNo.h"

#define maxstrlen 128

void ReyNoVariable(double *rho, double *u, double *d, double *mu)
{
    *rho = inputDouble(0, "fluid density", "kg/m3");
    
    *u = inputDouble(0, "average fluid velocity", "m/s");
    
    *d = inputDouble(0, "pipe diameter", "mm");
    *d = (*d)*0.001; //Conversion (mm to m)
    
    *mu = inputDouble(0, "fluid viscosity", "cP");
    *mu = (*mu)*0.001; //Conversion (cP to Pa.s)
    
    /*
    printf("Function assignments:\n");
    printf("rho = %.3f kg/m3\n", *rho);
    printf("u = %.3f m/s\n", *u);
    printf("d = %.3f m\n", *d);
    printf("mu = %.3f Pa.s\n\n", *mu);
     */
    fflush(stdout);
}

double ReyNoCalculation(double rho, double u, double d, double mu)
{
    double ReyNum = 0.0;
    
    ReyNum = rho * u;
    ReyNum = (ReyNum)*d;
    ReyNum = (ReyNum)/mu;
    
    return ReyNum;
}

void ReyNoDisplay(double rho, double u, double d, double mu, double ReyNum)
{
    printf("_Reynold's_Number_Calculation_\n");
    printf("\tInput parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Pipe internal diameter:");
    printf("d =\t%.3f\tmm\n\n", d*1000);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n", mu*1000);
    
    printf("\tOutput parameters:\n");
    printf("ReyNum =\t%.3f\t[ ]\t=\\frac{\\rho ud}{\\mu}\n", ReyNum);
    if(ReyNum < 2000)
    {
        printf("Flow regime is laminar \n");
    }else{
        if(ReyNum <3000){
            printf("Flow regime lies within the transition region. Consider using experimental data going forward.\n");
        }else{
            printf("Flow regime is turbulent. \n");
        }
    }
}

void ReyNoWrite(double rho, double u, double d, double mu, double ReyNum)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Reynolds Number Results
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
    
    strcat(filename, " Reynolds Number Results");
    //printf("File name: \"%s\"\n", filename);
    
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
    fprintf(fp, "_Reynold's_Number_Calculation_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Pipe internal diameter:");
    fprintf(fp, "d =\t%.3f\tmm\n\n", d*1000);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tcP\n", mu*1000);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "ReyNum =\t%.3f\t[ ]\t=\\frac{\\rho ud}{\\mu}\n", ReyNum);
    if(ReyNum < 2000)
    {
        fprintf(fp, "Flow regime is laminar \n");
    }else{
        if(ReyNum <3000){
            fprintf(fp, "Flow regime lies within the transition region. Consider using experimental data going forward.\n");
        }else{
            fprintf(fp, "Flow regime is turbulent. \n");
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ReyNoWriteSwitch(double rho, double u, double d, double mu, double ReyNum)
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
                ReyNoWrite(rho, u, d, mu, ReyNum);
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

void ReynoldsNumber()
{
    //Main Function
    int whilmain = 0;
    
    printf("Reynold's Number Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Function Output
        double ReyNum = 0.0;
        //Calculation Variables
        double rho = 0.0;
        double u = 0.0;
        double d = 0.0;
        double mu = 0.0;
        
        //Data collection
        ReyNoVariable(&rho, &u, &d, &mu);
        /*
        printf("Function returns:\n");
        printf("rho = %f \n", rho);
        printf("u = %f \n", u);
        printf("d = %f \n", d);
        printf("mu = %f \n\n", mu);
         */
        
        //  Running calculations
        clock_t timer = clock();
        ReyNum = ReyNoCalculation(rho, u, d, mu);
        //printf("Function returns: ReyNum = %f \n", ReyNum);
        timer = clock() - timer;
        
        int calctime = 0;
        calctime = ((int)timer*1000)/CLOCKS_PER_SEC;
        printf("Calculation completed in %d seconds and %d milliseconds.\n\n", calctime/1000, calctime%1000);
        
        //  Displaying results
        ReyNoDisplay(rho, u, d, mu, ReyNum);
        
        //  Writing to File
        ReyNoWriteSwitch(rho, u, d, mu, ReyNum);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
