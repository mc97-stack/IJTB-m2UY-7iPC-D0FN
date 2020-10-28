//
//  01eBubPres.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T1.h"
#include "01eBubPres.h"

#define maxstrlen 128

void BubPresVariable(double *sigma, double *r)
{
    *sigma = inputDouble(0, "surface tension", "N/m");
    
    *r = inputDouble(0, "radius of fluid droplet", "mm");
    *r = (*r)*0.001; //Conversion (mm to m)
    //printf("Function assignments:\nsigma = %f N/m\nr = %f m\n", *sigma, *r);
    fflush(stdout);
}

double BubPresCalculation(double sigma, double r) 
{
    double top = 0.0;
    double P = 0.0; // Bubble pressure.
    
    top = 0.0; //Initialising variable
    
    top = 2*sigma;
    P = (top)/r;
    
    return P;
}

void BubPresDisplay(double sigma, double r, double P)
{
    printf("_Bubble_Pressure_Calculations_\n");
    printf("\tInput Parameters:\n");
    printf("Surface tension:\n");
    printf("sigma =\t%.3f\tN/m\n", sigma);
    printf("Bubble radius:\n");
    printf("r =\t%.3f\tmm\n\n", r*1000);
    
    printf("\tOutput Parameters:\n");
    printf("P =\t%.3f\tPa\t=\\frac{2\\sigma}{r}\n", P);
}

void BubPresWrite(double sigma, double r, double P)
{
    //Function variables
    char filename[maxstrlen];   // Character array used to store file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Bubble Pressure Results
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
    
    strcat(filename, " Bubble Pressure Results");
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
    void free(void *filename);
    
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
    fprintf(fp, "_Bubble_Pressure_Calculations_\n");
    fprintf(fp, "\tInput Parameters:\n");
    fprintf(fp, "Surface tension:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\n", sigma);
    fprintf(fp, "Bubble radius:\n");
    fprintf(fp, "r =\t%.3f\tmm\n\n", r*1000);
    
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "P =\t%.3f\tPa\t=\\frac{2\\sigma}{r}\n", P);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}
void BubPresWriteSwitch(double sigma, double r, double P)
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
                BubPresWrite(sigma, r, P);
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

void BubblePressure()
{
    // "BubblePressure" is abbreviated to "BubPres" for this file.
    //Main Function
    int whilmain = 0;
    
    printf("Bubble Pressure Calculator\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //  Declaring variables
        double sigma = 0.0;
        double r = 0.0;
        double P = 0.0;
        
        //  Collecting data
        BubPresVariable(&sigma, &r);
        printf("Function returns:\nsigma = %f\nr = %f\n", sigma, r);
        
        //  Running calculations
        P = BubPresCalculation(sigma, r);
        printf("Bubble pressure = %.3f Pa\n", P);
        
        //  Displaying results
        BubPresDisplay(sigma, r, P);
        
        //  Writing to file
        BubPresWriteSwitch(sigma, r, P);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
