//
//  03gRotameter.c
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
#include "03gRotameter.h"

#define maxstrlen 128
#define g 9.80665
#define PI 3.14159265

//Declaring global variables and allocating memory
    //Function Output
double dP;
double m;
double Q;
double u;
    //Calculation Variables
double C_d;
double V_f;
double rho_f;
double rho;
double A_f;
double are1;
double are2;

    //Miscellaneous Variables


void RotameterVar(double *C_d, double *V_f, double *rho_f, double *rho, double *A_f, double *are1, double *are2)
{
    char input[maxstrlen];
    
    printf("Discharge coefficient (C_d) = ");
    *C_d = atof(fgets(input, sizeof(input), stdin));
    
    printf("Float Volume (m3) = ");
    *V_f = atof(fgets(input, sizeof(input), stdin));
    
    printf("Float density (kg/m3) = ");
    *rho_f = atof(fgets(input, sizeof(input), stdin));
    
    printf("Process fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Maximum Cross-sectional area of float (m2) = ");
    *A_f = atof(fgets(input, sizeof(input), stdin));
    
    printf("Cross-sectional area of tube at point of float (m2) = ");
    *are1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Annular area between float and tube at the point (m2) = ");
    *are2 = atof(fgets(input, sizeof(input), stdin));
    
    fflush(stdout);
}

void RotameterCalc(double C_d, double V_f, double rho_f, double rho, double A_f, double are1, double are2, double *dP, double *m, double *Q, double *u)
{
    //Calculating pressure drop
    double top = 0.0;
    
    top = (rho_f - rho);
    top = (top)*g;
    top = V_f*(top);
    
    *dP = (top)/A_f;
    
    //Calculation of mass flowrate
    double bot = 0.0;
    double frac = 0.0;
    
    bot = pow(are1, 2);
    bot = (bot)/(pow(are2,2));
    bot = (bot) - 1;
    
    top = 2*rho*(*dP);
    
    frac = (top)/(bot);
    *m = pow((frac), 0.5);
    *m = are1 * (*m);
    *m = C_d * (*m);
    
    *Q = (*m)/rho;
    *u = (*Q)/(are1);
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
void Rotameter()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("Program Title\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        
        //Data collection
        RotameterVar(&C_d, &V_f, &rho_f, &rho, &A_f, &are1, &are2);
        
        //Data manipulation
        RotameterCalc(C_d, V_f, rho_f, rho, A_f, are1, are2, &dP, &m, &Q, &u);
        
        printf("Buoyant force = %.3f Pa\n", dP);
        printf("Fluid velocity = %.3f m/s\n", u);
        printf("Volumetric flow = %.3f m3/s\n", Q);
        printf("Mass flowrate = %.3f kg/s\n", m);
        
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
