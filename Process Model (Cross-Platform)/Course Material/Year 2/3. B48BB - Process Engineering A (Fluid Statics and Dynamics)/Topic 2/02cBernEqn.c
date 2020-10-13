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

//  Custom header files
#include "B48BB_T2.h"
#include "02cBernEqn.h"
#include "02aMassCon.h"

#define maxstrlen 128
#define PI 3.141592653
#define g 9.80665

//Declaring global variables

    //Miscellaneous Variables


void BernEqnVar(double *P1, double *rho, double *u1, double *u2, double *Z1, double *Z2, double *hf)
{
    //Declaring input variable
    char input[maxstrlen];
    
    //Declaring and initialising local variables
    double d1 = 0.0;
    double d2 = 0.0;
    
    printf("Initial pressure (kPa) = ");
    *P1 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    *P1 = *P1*1000; //Conversion (kPa to Pa)
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Initial fluid velocity (m/s) = ");
    *u1 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Pipe diameter at state 1 (mm) = ");
    d1 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    d1 = d1*0.001; //Conversion (mm to m)
    
    printf("Pipe diameter at state 2 (mm) = ");
    d2 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    d2 = d2*0.001; //Conversion (mm to m)
    
    *u2 = VelCalc(*u1, d1, d2);
    
    printf("Initial fluid height from reference point (m) = ");
    *Z1 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Final fluid height from reference point (m) = ");
    *Z2 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Frictional pressure loss (Pa) = ");
    *hf = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    *hf = (*hf)/((*rho)*g);
    
    printf("Variable assignments:\n");
    printf("P1 = %.3f Pa\n", *P1);
    printf("rho = %.3f kg/m3\n", *rho);
    printf("u1 = %.3f m/s\n", *u1);
    printf("u2 = %.3f m/s\n", *u2);
    printf("Z1 = %.3f m\n", *Z1);
    printf("Z2 = %.3f m\n", *Z2);
    printf("hf = %.3f m\n\n", *hf);
    fflush(stdout);
}

double StatHeadCalc(double P, double rho)
{
    double stathead = 0.0;
    
    stathead = (rho*g);
    stathead = P/(stathead);
    
    printf("Static head = %.3f m\n", stathead);
    return stathead;
}

double DynHeadCalc(double u)
{
    double frac = 0.0;
    double dynhead = 0.0;
    
    frac = (1.0)/(2*g);
    
    dynhead = pow(u, 2);
    dynhead = (frac)*(dynhead);
    
    printf("Dynamic head = %.3f m\n", dynhead);
    
    return dynhead;
}

double BernEqnCalc(double stathead, double dynhead, double Z)
{
    double calc = 0.0;
    
    calc = stathead + dynhead;
    calc = (calc) + Z;
    
    return calc;
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
void BernEqn()
{
    //Main Function
    char ContCond[maxstrlen];
    
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
        
        //Data collection
        BernEqnVar(&P1, &rho, &u1, &u2, &Z1, &Z2, &hf);
        printf("Function assignments:\n");
        printf("P1 = %f\n", P1);
        printf("rho = %f\n", rho);
        printf("u1 = %f\n", u1);
        printf("u2 = %f\n", u2);
        printf("Z1 = %f\n", Z1);
        printf("Z2 = %f\n", Z2);
        printf("hf = %f\n\n", hf);
        //Data manipulation
        LHS = BernEqnCalc(StatHeadCalc(P1, rho), DynHeadCalc(u1), Z1);
        printf("Function returns: LHS = %f\n", LHS);
        
        RHS = BernEqnCalc(0, DynHeadCalc(u2), Z2);
        printf("Function returns: RHS = %f\n\n", RHS);
        
        RHS = (RHS) + (hf);
        P2 = (LHS) - (RHS);
        P2 = (P2)*(rho);
        P2 = (P2)*g;
        
        P2 = (P2)*0.001;
        
        printf("Bernoulli's equation estimates P2 = %.3f kPa\n\n", P2);
        //Ask for file write (Remember while loop)
        //...
        
        //Continue function
        int whilcont;
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
