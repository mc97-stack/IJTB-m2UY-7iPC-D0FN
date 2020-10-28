//
//  02cBernEqn.c
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
#include "02aMassCon.h"
#include "02cBernEqn.h"

#define maxstrlen 128
#define PI 3.141592653
#define g 9.80665

void BernEqnVariable(double *P1, double *rho, double *u1, double *u2, double *Z1, double *Z2, double *hf)
{
    //Declaring and initialising local variables
    double d1 = 0.0;
    double d2 = 0.0;
    
    *P1 = inputDouble(0, "initial pressure", "kPa");
    *P1 = *P1*1000; //Conversion (kPa to Pa)
    
    *rho = inputDouble(0, "fluid density", "kg/m3");
    
    *u1 = inputDouble(0, "initial fluid velocity", "m/s");
    
    d1 = inputDouble(0, "Pipe diameter at state 1", "mm");
    d1 = d1*0.001; //Conversion (mm to m)
    
    d2 = inputDouble(0, "Pipe diameter at state 2", "mm");
    d2 = d2*0.001; //Conversion (mm to m)
    
    *u2 = FinalVelocityCalculation(*u1, d1, d2);
    
    *Z1 = inputDouble(0, "initial fluid height", "m");
    
    *Z2 = inputDouble(0, "final fluid height", "m");
    
    *hf = inputDouble(0, "frictional pressure loss", "Pa");
    *hf = (*hf)/((*rho)*g);
    
    fflush(stdout);
}

double StaticHeadCalculation(double P, double rho)
{
    double stathead = 0.0;
    
    stathead = (rho*g);
    stathead = P/(stathead);
    
    //printf("Static head = %.3f m\n", stathead);
    return stathead;
}

double DynamicHeadCalculation(double u)
{
    double frac = 0.0;
    double dynhead = 0.0;
    
    frac = (1.0)/(2*g);
    
    dynhead = pow(u, 2);
    dynhead = (frac)*(dynhead);
    
    //printf("Dynamic head = %.3f m\n", dynhead);
    return dynhead;
}

double BernEqnCalculation(double stathead, double dynhead, double Z)
{
    double calc = 0.0;
    
    calc = stathead + dynhead;
    calc = (calc) + Z;
    
    return calc;
}

void BernEqnDisplay(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf)
{
    printf("_Bernoulli's_Equation_Results_\n");
    printf("Assuming the fluid is incompressible. \n");
    printf("g =\t%.3f\tm/s2\n\n", g);
    printf("\tInput parameters:\n");
    printf("Initial fluid pressure:\n");
    printf("P1 =\t%.3f\tkPa\n", P1*0.001);
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Initial fluid velocity:\n");
    printf("u1 =\t%.3f\tm/s\n", u1);
    printf("Final fluid velocity:\n");
    printf("u2 =\t%.3f\tm/s\n", u2);
    printf("Initial fluid height:\n");
    printf("z1 =\t%.3f\tm\n", z1);
    printf("Final fluid height:\n");
    printf("z2 =\t%.3f\tm\n\n", z2);
    printf("Fluid frictional head loss:\n");
    printf("hf =\t%.3f\tm\n\n", hf);
    
    printf("\tOutput parameters:\n");
    printf("Final fluid pressure:\n");
    printf("P2 =\t%.3f\tkPa\n", P2*0.001);
}

void BernEqnWrite(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[4];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Bernoulli Equation Results
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
    
    strcat(filename, " Bernoulli Equation Results");
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
    fprintf(fp, "_Bernoulli's_Equation_Results_\n");
    fprintf(fp, "Assuming the fluid is incompressible. \n");
    fprintf(fp, "g =\t%.3f\tm/s2\n\n", g);
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial fluid pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa\n", P1*0.001);
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Initial fluid velocity:\n");
    fprintf(fp, "u1 =\t%.3f\tm/s\n", u1);
    fprintf(fp, "Final fluid velocity:\n");
    fprintf(fp, "u2 =\t%.3f\tm/s\n", u2);
    fprintf(fp, "Initial fluid height:\n");
    fprintf(fp, "z1 =\t%.3f\tm\n", z1);
    fprintf(fp, "Final fluid height:\n");
    fprintf(fp, "z2 =\t%.3f\tm\n", z2);
    fprintf(fp, "Fluid frictional head loss:\n");
    fprintf(fp, "hf =\t%.3f\tm\n\n", hf);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Final fluid pressure:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n", P2*0.001);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void BernEqnWriteSwitch(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf)
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
                BernEqnWrite(P1, P2, rho, u1, u2, z1, z2, hf);
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

void BernoulliEquation()
{
    //Main Function
    int whilmain = 0;
    
    printf("Bernoulli's Equation\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
            //Function Output
        double P2 = 0.0;
            //Calculation Variables
        double P1 = 0.0;
        double rho = 0.0; //Remains constant as process is assumed to be isothermal
        double u1 = 0.0;
        double u2 = 0.0;
        double Z1 = 0.0;
        double Z2 = 0.0;
        double hf = 0.0;
        
        double LHS = 0.0;
        double RHS = 0.0;
        
        //  Data collection
        BernEqnVariable(&P1, &rho, &u1, &u2, &Z1, &Z2, &hf);/*
        printf("Function assignments:\n");
        printf("P1 = %f\n", P1);
        printf("rho = %f\n", rho);
        printf("u1 = %f\n", u1);
        printf("u2 = %f\n", u2);
        printf("Z1 = %f\n", Z1);
        printf("Z2 = %f\n", Z2);
        printf("hf = %f\n\n", hf);*/
        
        //  Running calculations
        LHS = BernEqnCalculation(StaticHeadCalculation(P1, rho), DynamicHeadCalculation(u1), Z1);
        //printf("Function returns: LHS = %f\n", LHS);
        
        RHS = BernEqnCalculation(0, DynamicHeadCalculation(u2), Z2);
        //printf("Function returns: RHS = %f\n\n", RHS);
        
        RHS = (RHS) + (hf);
        P2 = (LHS) - (RHS);
        P2 = (P2)*(rho);
        P2 = (P2)*g;
        
        P2 = (P2)*0.001;
        
        //printf("Bernoulli's equation estimates P2 = %.3f kPa\n\n", P2);
        //  Displaying results
        BernEqnDisplay(P1, P2, rho, u1, u2, Z1, Z2, hf);
        
        //  Writing to file
        BernEqnWriteSwitch(P1, P2, rho, u1, u2, Z1, Z2, hf);
        
        //Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
