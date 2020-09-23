//
//  02aMassCon.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 26/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T2.h"
//#include "02aMassCon.h"

#define maxstrlen 128
#define PI 3.141592653

void MassConVar(double *rho1, double *rho2, double *d1, double *d2, double *u1)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Initial fluid density (kg/m3) = ");
    *rho1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Final fluid density (kg/m3) = ");
    *rho2 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Initial pipe diameter (mm) = ");
    *d1 = atof(fgets(input, sizeof(input), stdin));
    
    *d1 = (*d1)*0.001; //Conversion (mm to m)
    
    printf("Final pipe diameter (mm) = ");
    *d2 = atof(fgets(input, sizeof(input), stdin));
    
    *d2 = (*d2)*0.001; //Conversion (mm to m)
    
    printf("Initial fluid velocity (m/s) = ");
    *u1 = atof(fgets(input, sizeof(input), stdin));
    
    fflush(stdout);
}

double VelCalc(double u1, double d1, double d2)
{
    double frac = 0.0;
    double u2 = 0.0;
    
    frac = d1/d2;
    frac = pow((frac), 2);
    
    u2 = u1*(frac);
    
    printf("Final fluid velocity = %.3f m/s\n", u2);
    return u2;
}

double VolFloCalc(double u, double d)
{
    double A = 0.0; //Area of cross-section
    double q = 0.0; //Volumetric flow rate
    
    A = d/2;
    A = pow((A), 2);
    A = PI*(A);
    
    q = u*(A);
    
    printf("Volumetric flow rate = %.3f m3/s\n", q);
    return q;
}

double MassFloCalc(double rho, double d, double u)
{
    double A = 0.0; //Area of cross-section
    double m = 0.0; //Mass flowrate
    
    A = d/2;
    A = pow((A), 2);
    A = PI * (A);
    
    m = rho * (A);
    m = (m) * u;
    
    printf("Mass flow rate = %.3f kg/s\n", m);
    return m;
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

void MassCon()
{
    //Thought experiment
    /* Imagine pouring a fluid into a closed system and allowing it to flow freely 
     around the system capacity. Does the mass contained within the system fluctuate
     about or does it remain constant? Assuming that temperature is being held constant
     then the weight of the total system (Ignoring the surroundings) should not change
     as there are no other inputs or outputs to/from the system*/
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain;
    printf("Mass Conservation Principle\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //Variable declaration & Allocation
        double rho1 = 0.0;
        double rho2 = 0.0;
        double d1 = 0.0;
        double d2 = 0.0;
        double u1 = 0.0;
        double u2 = 0.0;
        
        double m1 = 0.0;
        double m2 = 0.0;
        double q1 = 0.0;
        double q2 = 0.0;
        
        int whilcont = 0;
        
        //Data collection
        MassConVar(&rho1, &rho2, &d1, &d2, &u1);
        printf("Function returns:\nrho1 = %f\nrho2 = %f\nd1 = %f\nd2 = %f\nu1 = %f\n\n", rho1, rho2, d1, d2, u1);
        //Data manipulation
        u2 = VelCalc(u1, d1, d2);
        printf("Function returns: u2 = %f\n\n", u2);
        
        q1 = VolFloCalc(u1, d1);
        printf("Function returns: q1 = %f\n\n", q1);
        q2 = VolFloCalc(u2, d2);
        printf("Function returns: q2 = %f\n\n", q2);
        
        m1 = MassFloCalc(rho1, d1, u1);
        printf("Function returns: m1 = %f\n\n", m1);
        m2 = MassFloCalc(rho2, d2, u2);
        printf("Function returns: m2 = %f\n\n", m2);
        
        double error;
        error = m1 - m2;
        if(error < 0.001)
        {
            printf("Mass balances.\n\n");
        }else{
            printf("Mass does not balance.\n\n");
            if(rho1 != rho2)
            {
                printf("This program is under the assumption that the fluid is incompressible so density cannot fluctuate\n");
            }
        }
        //Ask for file write (Remember while loop)
        //...
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