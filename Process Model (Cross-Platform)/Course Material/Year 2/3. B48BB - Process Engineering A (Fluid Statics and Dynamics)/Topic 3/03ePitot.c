//
//  03ePitot.c
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
#include "B48BB_T3.h"
#include "03ePitot.h"
#include "01cMano.h"

#define maxstrlen 128
#define PI 3.14159265

void PitotVar(double *P2, double *rho1, double *rho2, double *h1, double *h2, double *d)
{
    char input[maxstrlen];
    
    printf("Static pressure on connection (kPa) = ");
    *P2 = atof(fgets(input, sizeof(input), stdin));
    
    *P2 = (*P2)*1000; //Conversion (kPa to Pa)
    
    printf("Process fluid density (kg/m3) = ");
    *rho1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Manometer fluid density (kg/m3) = ");
    *rho2 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Process fluid height in manometer (cm) = ");
    *h1 = atof(fgets(input, sizeof(input), stdin));
    
    *h1 = (*h1)*0.01; //Conversion (cm to m)
    
    printf("Manometer fluid height in manometer (cm) = ");
    *h2 = atof(fgets(input, sizeof(input), stdin));
    
    *h2 = (*h2)*0.01; //Conversion (cm to m)
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    
    *d = (*d)*0.001; //Conversion (mm to m)
    
    fflush(stdout);
}

void PitotCalc(double P2, double rho1, double rho2, double h1, double h2, double d, double *P1, double *v, double *Q)
{
    //P1 = Process fluid pressure
    double dP = 0.0;
    double frac = 0.0;
    double pare = 0.0;
    
    //Manometer calculations - Get dP
    *P1 = ManoMeasCal(P2, rho1, h1, rho2, h2);
    dP = P2 - (*P1);
    
    //Velocity calculation
    frac = 2*dP;
    frac = (frac)/(rho1);
    printf("frac = %f\n", frac);
    *v = pow((frac), 0.5);
    //Volumetric flowrate calculation
        //Calculating pipe area
    pare = d/(2.0); //Getting pipe radius
    pare = pow(pare, 2);
    pare = PI*(pare);
    
    *Q = (*v) * (pare);
    //return [Function Output];
}

void PitotWrite(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Pitot Static Tube Results
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
    
    strcat(filename, " Pitot Static Tube Results");
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
    fp = fopen(filepath, "w+");
    
    //Write to file
    fprintf(fp, "_Pitot_Static_Tube_Results_\n");
    
    //Write to file
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Static pressure on connection:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa\n", P2*0.001);
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Process fluid height in manometer element:\n");
    fprintf(fp, "h1 =\t%.3f\tcm\n", h1*100);
    fprintf(fp, "Manometer fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n", rho2);
    fprintf(fp, "Manometer fluid height:\n");
    fprintf(fp, "h2 =\t%.3f\tcm\n", h2*100);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Process fluid pressure:\n");
    fprintf(fp, "P1 =\t%.3f\tPa\n", P1*1000);
    fprintf(fp, "Process fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tPa\n", v);
    fprintf(fp, "Process fluid volumetric flowrate:\n");
    fprintf(fp, "Q =\t%.3f\tPa\n", Q);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PitotWriteCheck(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q)
{
    int SaveC;
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
                PitotWrite(P1, P2, rho1, rho2, h1, h2, d, v, Q);
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

void Pitot()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Pitot static tube calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
            //Function Output
        double P1 = 0.0;
        double v = 0.0;
        double Q = 0.0;
            //Calculation Variables
        double P2 = 0.0;
        double rho1 = 0.0;
        double rho2 = 0.0;
        double h1 = 0.0;
        double h2 = 0.0;
        double d = 0.0;
        
        int whilcont = 0;
        
        //Data collection
        PitotVar(&P2, &rho1, &rho2, &h1, &h2, &d);
        
        //Data manipulation
        printf("Assuming skin friction losses can be ignored.\n");
        printf("tfr assuming that the impact connection is located on the pipe centreline\n\n");
        PitotCalc(P2, rho1, rho2, h1, h2, d, &P1, &v, &Q);
        printf("P1 = %.3f kPa\n", P1*0.001); //Function will return pressure in Pa.
        printf("v = %.3f m/s\n", v);
        printf("Q = %.3f m3/s\n\n", Q);
        
        //Ask for file write (Remember while loop)
        PitotWriteCheck(P1, P2, rho1, rho2, h1, h2, d, v, Q);
        
        //Continue function
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
