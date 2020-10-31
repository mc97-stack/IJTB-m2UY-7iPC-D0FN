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
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T3.h"
#include "03gRotameter.h"

#define maxstrlen 128
#define g 9.80665
#define PI 3.14159265

void RotameterVariable(double *C_d, double *V_f, double *rho_f, double *rho, double *A_f, double *are1, double *are2)
{
    *C_d = inputDouble(0, "discharge coefficient", "[ ]");
    
    *V_f = inputDouble(0, "float volume", "m3");
    
    *rho_f = inputDouble(0, "float density", "kg/m3");
    
    *rho = inputDouble(0, "process fluid density", "kg/m3");
    
    *A_f = inputDouble(0, "maximum Cross-sectional area of float", "m2");
    
    *are1 = inputDouble(0, "cross-sectional area of tube at point of float", "m2");
    
    *are2 = inputDouble(0, "annular area between float and tube at the point", "m2");
}

void RotameterCalculation(double C_d, double V_f, double rho_f, double rho, double A_f, double are1, double are2, double *dP, double *m, double *Q, double *u)
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

void RotameterDisplay(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u)
{
    printf("_Rotameter_Results_\n");
    printf("\tInput parameters:\n");
    printf("Fluid parameters:\n");
    printf("Process fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n\n", rho);
    
    printf("Float parameters:\n");
    printf("Float volume:\n");
    printf("V_f =\t%.3f\tm3\n", V_f);
    printf("Float density:\n");
    printf("rho_f =\t%.3f\tkg/m3\n", rho_f);
    printf("Maximum cross-sectional area of float:\n");
    printf("A_f =\t%.3f\tm2\n", A_f);
    printf("Cross-sectional area of tube at point of float:\n");
    printf("are1 =\t%.3f\tm2\n", are1);
    printf("Annular area between float and tube at point:\n");
    printf("are2 =\t%.3f\tm2\n\n", are2);
    
    printf("Device parameters:\n");
    printf("Discharge Coefficient:\n");
    printf("C_d =\t%.3f\t[ ]\n\n", C_d);
    
    printf("\tOutput parameters:\n");
    printf("Fluid pressure loss:\n");
    printf("dP =\t%.3f\tPa\n", dP);
    printf("Mass flowrate of process fluid:\n");
    printf("m =\t%.3f\tkg/s\n", m);
    printf("Volumetric flowrate of process fluid:\n");
    printf("Q =\t%.3f\tm3/s\n", Q);
    printf("Process fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
}

void RotameterWrite(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Rotameter Results
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
    
    strcat(filename, " Rotameter Results");
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
    fprintf(fp, "_Rotameter_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid parameters:\n");
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n\n", rho);
    
    fprintf(fp, "Float parameters:\n");
    fprintf(fp, "Float volume:\n");
    fprintf(fp, "V_f =\t%.3f\tm3\n", V_f);
    fprintf(fp, "Float density:\n");
    fprintf(fp, "rho_f =\t%.3f\tkg/m3\n", rho_f);
    fprintf(fp, "Maximum cross-sectional area of float:\n");
    fprintf(fp, "A_f =\t%.3f\tm2\n", A_f);
    fprintf(fp, "Cross-sectional area of tube at point of float:\n");
    fprintf(fp, "are1 =\t%.3f\tm2\n", are1);
    fprintf(fp, "Annular area between float and tube at point:\n");
    fprintf(fp, "are2 =\t%.3f\tm2\n\n", are2);
    
    fprintf(fp, "Device parameters:\n");
    fprintf(fp, "Discharge Coefficient:\n");
    fprintf(fp, "C_d =\t%.3f\t[ ]\n\n", C_d);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Fluid pressure loss:\n");
    fprintf(fp, "dP =\t%.3f\tPa\n", dP);
    fprintf(fp, "Mass flowrate of process fluid:\n");
    fprintf(fp, "m =\t%.3f\tkg/s\n", m);
    fprintf(fp, "Volumetric flowrate of process fluid:\n");
    fprintf(fp, "Q =\t%.3f\tm3/s\n", Q);
    fprintf(fp, "Process fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void RotameterWriteSwitch(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u)
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
                RotameterWrite(rho, V_f, rho_f, A_f, are1, are2, C_d, dP, m, Q, u);
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

void Rotameter()
{
    //Main Function
    int whilmain = 0;
    printf("Rotameter Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
            //Function Output
        double dP = 0.0;
        double m = 0.0;
        double Q = 0.0;
        double u = 0.0;
            //Calculation Variables
        double C_d = 0.0;
        double V_f = 0.0;
        double rho_f = 0.0;
        double rho = 0.0;
        double A_f = 0.0;
        double are1 = 0.0;
        double are2 = 0.0;
        
        //  Data collection
        RotameterVariable(&C_d, &V_f, &rho_f, &rho, &A_f, &are1, &are2);
        
        //  Running calculations
        clock_t start, end;
        double timeTaken = 0.0;
        
        start = clock();
        
        RotameterCalculation(C_d, V_f, rho_f, rho, A_f, are1, are2, &dP, &m, &Q, &u);
        /*
        printf("Buoyant force = %.3f Pa\n", dP);
        printf("Fluid velocity = %.3f m/s\n", u);
        printf("Volumetric flow = %.3f m3/s\n", Q);
        printf("Mass flowrate = %.3f kg/s\n", m);
        */
        end = clock();
        
        timeTaken = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Process completed in %.3f seconds.\n\n", timeTaken);
        
        //  Displaying results
        RotameterDisplay(rho, V_f, rho_f, A_f, are1, are2, C_d, dP, m, Q, u);
        
        //  Writing to File
        RotameterWriteSwitch(rho, V_f, rho_f, A_f, are1, are2, C_d, dP, m, Q, u);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
