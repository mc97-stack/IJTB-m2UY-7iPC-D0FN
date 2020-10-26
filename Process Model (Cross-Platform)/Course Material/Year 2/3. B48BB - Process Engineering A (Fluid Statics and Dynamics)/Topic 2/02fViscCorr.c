//
//  02fViscCorr.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 29/06/2020.
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
#include "02fViscCorr.h"

#define maxstrlen 128
#define exp 2.718281828459045

void ViscCorrVariable(double *a, double *b, double *T, double *rho)
{
    //How constants are used will vary on the correlation being utilised to estimate the fluid viscosity;
    //Declaring input variables
    char input[maxstrlen];  // Variable used to store keyboard input.
    char menu[maxstrlen];
    
    int control = 0;
    
    printf("a = ");
    *a = atof(fgets(input, sizeof(input), stdin));
    
    printf("b = ");
    *b = atof(fgets(input, sizeof(input), stdin));
    
    printf("System temperature (deg C) = ");
    *T = atof(fgets(input, sizeof(input), stdin));
    
    control = 1;
    while(control == 1)
    {
        printf("Does temperature need converting to K? ");
        fgets(menu, sizeof(menu), stdin);
        switch(menu[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *T = (*T) + 273.15;
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
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    /*
    printf("Function assignments:\n");
    printf("a = %.3f\n", *a);
    printf("b = %.3f\n", *b);
    printf("T = %.3f\n", *T);
    printf("rho = %.3f kg/m3\n", *rho);
    */
    fflush(stdout);
}

double LiquidViscCalculation(double a, double b, double T)
{
    double frac = 0.0;
    double mu = 0.0;
    
    frac = b/T;
    mu = pow(exp, (frac));
    
    mu = a*(mu);
    
    printf("Liquid viscosity = %.3f [Units]\n", mu);
    return mu;
}

double VapourViscCalculation(double a, double b, double T)
{
    double top = 0.0;
    double bot = 0.0;
    
    double mu = 0.0;
    
    top = pow(T, (1.5));
    top = a * (top);
    
    bot = b + T;
    
    mu = (top)/(bot);
    
    printf("Vapour viscosity = %.3f [Units]\n", mu);
    return mu;
}

double KineticVisc(double mu, double rho)
{
    double upsi = 0.0;
    
    upsi = (mu)/(rho);
    printf("Kinematic viscosity = %.3f [Units]\n", upsi);
    return upsi;
}

void ViscDisplay(int method, double a, double b, double T, double rho, double mu, double upsi)
{
    if(method == 1){
        printf("_Liquid_Viscosity_Correlation_\n");
    }
    if(method == 2){
        printf("_Vapour_Viscosity_Correlation_\n");
    }
    printf("\tInput parameters:\n");
    printf("a =\t%.3f\n", a);
    printf("b =\t%.3f\n", b);
    printf("Temperature:\n");
    printf("T =\t%.3f\t\n", T);
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n\n", rho);
    
    printf("\tOutput parameters:\n");
    if(method == 1){
        printf("mu =\t%.3f\t...\t=ae^{\\frac{b}{T}}\n", mu);
    }
    if(method == 2){
        printf("mu =\t%.3f\t...\t=\\frac{aT^{1.5}}{(b + T)\n", mu);
    }
    printf("upsilon =\t%.3f\t...\t=\\frac{\\mu}{\\rho}\n", upsi);
}

void ViscWrite(int method, double a, double b, double T, double rho, double mu, double upsi)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + ... Viscosity Correlation Results
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
    
    if(method == 1){
        strcat(filename, " Liquid Viscosity Correlation Results");
        printf("File name: \"%s\"\n", filename);
    }
    if(method == 2){
        strcat(filename, " Vapour Viscosity Correlation Results");
        printf("File name: \"%s\"\n", filename);
    }
    
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
    if(method == 1){
        fprintf(fp, "_Liquid_Viscosity_Correlation_\n");
    }
    if(method == 2){
        fprintf(fp, "_Vapour_Viscosity_Correlation_\n");
    }
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "a =\t%.3f\n", a);
    fprintf(fp, "b =\t%.3f\n", b);
    fprintf(fp, "Temperature:\n");
    fprintf(fp, "T =\t%.3f\t\n", T);
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n\n", rho);
    
    fprintf(fp, "\tOutput parameters:\n");
    if(method == 1){
        fprintf(fp, "mu =\t%.3f\t...\t=ae^{\\frac{b}{T}}\n", mu);
    }
    if(method == 2){
        fprintf(fp, "mu =\t%.3f\t...\t=\\frac{aT^{1.5}}{(b + T)\n", mu);
    }
    fprintf(fp, "upsilon =\t%.3f\t...\t=\\frac{\\mu}{\\rho}\n", upsi);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ViscWriteSwitch(int method, double a, double b, double T, double rho, double mu, double upsi)
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
                ViscWrite(method, a, b, T, rho, mu, upsi);
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

void ViscosityCorrelation()
{
    //Main Function
    int whilmain = 0;
    printf("Viscosity Correlation Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        char input[maxstrlen];
        
        double mu = 0.0;    //Fluid viscosity
        double upsi = 0.0;  //Fluid kinematic viscosity
        
        double a = 0.0;
        double b = 0.0;
        double T = 0.0;
        double rho = 0.0;
        
        int method = 0;
        int whilmethod = 0;
        whilmethod = 1;
        
        //  Data collection
        while(whilmethod == 1)
        {
            printf("Please select from the following types of calculation:\n");
            printf("1. Liquid Viscosity\n2. Vapour Viscosity\n");
            printf("Selection ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
            {
                case '1':
                case 'L':
                case 'l':
                    printf("Liquid viscosity correlation selected.\n");
                    method = 1;
                    whilmethod = 0;
                break;
                case '2':
                case 'V':
                case 'v':
                    printf("Vapour viscosity correlation selected\n");
                    method = 2;
                    whilmethod = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        printf("\n");
        
        ViscCorrVariable(&a, &b, &T, &rho);/*
        printf("Function returns:\n");
        printf("a = %f\n", a);
        printf("b = %f\n", b);
        printf("T = %f\n", T);
        printf("rho = %f\n", rho);*/
        printf("\n");
        //  Running calculations
        mu = 0; //Initialising viscosity variable
        switch(method)
        {
            case '1':
                mu = LiquidViscCalculation(a, b, T);
                //printf("Function returns: mu = %f [Units]\n", mu);
                break;
            case '2':
                mu = VapourViscCalculation(a, b, T);
                //printf("Function returns: mu = %f [Units]\n", mu);
                break;
            //Default case is not needed as input is checked earlier in function
        }
        printf("\n");
        upsi = KineticVisc(mu, rho);
        //printf("Function returns: upsi = %f [Units]\n", upsi);
        //  Displaying results
        ViscDisplay(method, a, b, T, rho, mu, upsi);
        
        //  Writing to File
        ViscWriteSwitch(method, a, b, T, rho, mu, upsi);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    printf("\n");
    fflush(stdout);
}
