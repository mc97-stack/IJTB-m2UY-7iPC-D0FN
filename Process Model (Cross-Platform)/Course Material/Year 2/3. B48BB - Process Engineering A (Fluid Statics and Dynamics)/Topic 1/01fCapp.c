//
//  01fCapp.c
//  Process Model (Cross-Platform)
//  
//  Created by Matthew Cheung on 26/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

/// MARK: HEADER DECLARATIONS
//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "System.h"
#include "B48BB_T1.h"
#include "01dSurfTens.h"
#include "01fCapp.h"

/// MARK: SUBROUTINE DEFINITIONS
#define maxstrlen 128
#define PI 3.141592653
#define g 9.80665

/// MARK: VARIABLE INPUT
void CappVariable(double *sigma, double *cang, double *rho, double *d)
{
    *sigma = inputDouble(0, 0, "Surface Tension", "N/m");
    
    *cang = inputDouble(0, 0, "contact angle", "deg");
    
    *rho = inputDouble(0, 0, "fluid density", "kg/m3");
    
    *d = inputDouble(0, 0, "Capillary tube diameter", "mm");
    
    wettabilityfacts(*cang);    //Function located in 01dSurfTens
    *cang = (*cang)*(PI/ 180);  //Conversion to radians
    
    *d = (*d)*0.001;
}

/// MARK: GENERAL CALCULATIONS
double CappCalculateHeight(double sigma, double cang, double rho, double d)
{
    double top = 0.0;
    double bot = 0.0;
    double h = 0.0; // Capillary rise.
    
    top = 2*sigma;
    top = (top)*cos(cang);
    
    bot = rho*g;
    bot = (bot)*d;
    
    h = (top)/(bot);
    
    return h;
}

double CappCalculatePressure(double sigma, double cang, double d)
{
    double top = 0.0;
    double Pc = 0.0;    // Capillary pressure.
    
    top = 2*sigma;
    top = (top)*cos(cang);
    
    Pc = d/2;
    Pc = (top)/(Pc);
    
    return Pc;
}

/// MARK: DISPLAY AND WRITE
void CappDisplay(double sigma, double cang, double d, double h, double Pc)
{
    printf("_Capillarity_Calculations_\n");
    printf("\tInput Parameters:\n");
    printf("Fluid surface tension:\n");
    printf("sigma =\t%.3f\tN/m\n", sigma);
    printf("Contact angle:\n");
    printf("cang =\t%.3f\trad\n\n", cang);
    
    printf("\tOutput Parameters:\n");
    printf("Capillary rise:\n");
    printf("h =\t%.3f\tcm\t=\\frac{2\\sigma\\cos\\theta}{\\rho gr}\n",h*0.01);
    printf("Capillary pressure:\n");
    printf("Pc =\t%.3f\tPa\t=\\frac{2\\sigma\\cos\\theta}{r}\n",Pc);
    fflush(stdout);
}

void CappWrite(double sigma, double cang, double d, double h, double Pc)
{
    //  Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    
    //  Set file name as timestamp + Capillarity Calculation Results
        //  Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //  Creating file name
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Capillarity Calculations Results");
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
    
    //  Open file
    fp = fopen(filename, "w+");
    
    //  Write to file
    fprintf(fp, "_Capillarity_Calculations_\n");
    fprintf(fp, "\tInput Parameters:\n");
    fprintf(fp, "Fluid surface tension:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\n", sigma);
    fprintf(fp, "Contact angle:\n");
    fprintf(fp, "cang =\t%.3f\trad\n\n", cang);
    
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "Capillary rise:\n");
    fprintf(fp, "h =\t%.3f\tcm\t=\\frac{2\\sigma\\cos\\theta}{\\rho gr}\n",h*0.01);
    fprintf(fp, "Capillary pressure:\n");
    fprintf(fp, "Pc =\t%.3f\tPa\t=\\frac{2\\sigma\\cos\\theta}{r}\n",Pc);
    
    //  Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void CappWriteSwitch(double sigma, double cang, double d, double h, double Pc)
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
/// MARK: PSEUDO-MAIN FUNCTION
void Cappilarity()
{
    //  Pseudo-main function.
    int whilmain = 0;
    printf("Capillarity Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Declaring variables
        double h = 0.0;     //Capillary rise.
        double Pc = 0.0;    //Capillary pressure.
        
        double sigma = 0.0; //Surface tension.
        double cang = 0.0;  //Contact angle.
        double rho = 0.0;   //Fluid density.
        double d = 0.0;     //Tube diameter.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Collecting data
        CappVariable(&sigma, &cang, &rho, &d);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        h = CappCalculateHeight(sigma, cang, rho, d);
        Pc  = CappCalculatePressure(sigma, cang, d);
        
        clock_getres(CLOCK_MONOTONIC, &end);
        clock_gettime(CLOCK_MONOTONIC, &end);

        elapsed = timer(start, end);

        printf("Calculations completed in %.6f seconds.\n", elapsed);
        
        //  Displaying results
        CappDisplay(sigma, cang, d, h, Pc);
        
        //  Writing to file
        CappWriteSwitch(sigma, cang, d, h, Pc);
        
        //Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
