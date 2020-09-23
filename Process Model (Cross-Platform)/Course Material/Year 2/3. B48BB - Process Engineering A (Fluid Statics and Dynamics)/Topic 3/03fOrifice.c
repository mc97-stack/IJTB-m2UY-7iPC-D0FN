//
//  03fOrifice.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T3.h"
#include "03fOrifice.h"

#define maxstrlen 128
#define g 9.80665
#define PI 3.14159265

//Declaring global variables and allocating memory
    //Function Output
double u = 0.0;
double Q = 0.0;
double m = 0.0;
    //Calculation Variables
double C_d = 0.0;
double d1 = 0.0;
double d2 = 0.0;
double rho = 0.0;
double P1 = 0.0;
double P2 = 0.0;
double h_f = 0.0;

    //Miscellaneous Variables


void OrificeVar(double *C_d, double *d1, double *d2, double *rho, double *P1, double *P2, double *h_f)
{
    char input[maxstrlen];
    
    printf("Discharge coefficient (C_d) = ");
    *C_d = atof(fgets(input, sizeof(input), stdin));
    
    printf("Pipe diameter (mm) = ");
    *d1 = atof(fgets(input, sizeof(input), stdin));
    
    *d1 = (*d1)*0.001; //Conversion (mm to m)
    
    printf("Vena Contracta diameter (mm) = ");
    *d2 = atof(fgets(input, sizeof(input), stdin));
    
    *d2 = (*d2)*0.001; //Conversion (mm to m)
    
    printf("Process fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Initial system pressure (kPa) = ");
    *P1 = atof(fgets(input, sizeof(input), stdin));
    
    *P1 = (*P1)*1000;
    
    printf("Final system pressure (kPa) = ");
    *P2 = atof(fgets(input, sizeof(input), stdin));
    
    *P2 = (*P2)*1000;
    
    printf("Frictional head loss (m) = ");
    *h_f = atof(fgets(input, sizeof(input), stdin));
    /*
    printf("Function has assigned:\n");
    printf("C_d = %.6f\n", C_d);
    printf("d1 = %.6f m", d1);
    printf("d2 = %.6f m", d2);
    printf("rho = %.6f kg/m3\n", rho);
    */
    
    fflush(stdout);
}

void OrificeCalc(double C_d, double d1, double d2, double rho, double P1, double P2, double h_f, double *u, double *Q, double *m)
{
    //Preparing variables for calculation
    double are1 = 0.0;
    double are2 = 0.0;
    
    are1 = d1/2;
    are1 = pow(are1, 2);
    are1 = PI*(are1);
    printf("are1 = %f\n", are1);
    
    are2 = d2/2;
    are2 = pow(are2, 2);
    are2 = PI*(are2);
    printf("are2 = %f\n", are2);
    
    double top = 0.0;
    double bot = 0.0;
    double frac = 0.0;
    
    top = P1 - P2;
    top = 2 * (top);
    top = top - g*h_f;
    printf("top = %f\n", top);
    
    bot = pow(are1, 2);
    bot = (bot)/(pow(are2, 2));
    bot = (bot) - 1;
    bot = rho * (bot);
    printf("bot = %f\n", bot);
    
    frac = (top)/(bot);
    printf("frac = %f\n", frac);
    
    *u = pow(frac, 0.5);
    *u = C_d * (*u); //Average fluid velocity solved
    printf("u = %f\n", *u);
    
    *Q = (*u) * are1;
    printf("Q = %f\n", *Q);
    
    *m = rho * (*Q);
    printf("m = %f\n", *m);
    //return [Function Output];
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
void Orifice()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("Program Title\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        
        
        //Data collection
        OrificeVar(&C_d, &d1, &d2, &rho, &P1, &P2, &h_f);
        //Data manipulation
        OrificeCalc(C_d, d1, d2, rho, P1, P2, h_f, &u, &Q, &m);
        printf("Average fluid velocity = %.3f m/s\n", u);
        printf("Volumetric flow rate = %.3f m3/s\n", Q);
        printf("Mass flowrate = %.3f kg/s\n\n", m);
        
        //Ask for file write (Remember while loop)
        //...
        //Continue function
        int whilcont = 1;
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
