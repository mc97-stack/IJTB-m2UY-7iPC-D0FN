//
//  01fCapp.c
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
#include <time.h>

//  Custom header files
#include "B48BB_T1.h"
#include "01dSurfTens.h"
#include "01fCapp.h"

#define maxstrlen 128
#define PI 3.141592653
#define g 9.80665

void CappVar(double *sigma, double *cang, double *rho, double *d)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Surface Tension (N/m) = ");
    *sigma = atof(fgets(input, sizeof(input), stdin));
    
    printf("Contact angle (deg) = ");
    *cang = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Cappilary tube diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    
    //Extras ^.^
    wettfacts(*cang); //Function located in 01dSurfTens
    *cang = (*cang)*(PI/ 180); //Conversion to radians
    
    *d = (*d)*0.001;
    fflush(stdout);
}

double CappCalch(double sigma, double cang, double rho, double d)
{
    double top = 0.0;
    double bot = 0.0;
    double h = 0.0;
    
    top = 2*sigma;
    top = (top)*cos(cang);
    
    bot = rho*g;
    bot = (bot)*d;
    
    h = (top)/(bot);
    
    return h;
}

double CappCalcP(double sigma, double cang, double d)
{
    double top = 0.0;
    double Pc = 0.0;
    
    top = 2*sigma;
    top = (top)*cos(cang);
    
    Pc = d/2;
    Pc = (top)/(Pc);
    
    
    return Pc;
}

void CappWrite(double sigma, double cang, double d, double h, double Pc)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Fluid Coefficient of Compressibility
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
    
    strcat(filename, " Capillarity Calculations Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
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
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filepath, "w+");
    
    //Write to file
    fprintf(fp, "_Capillarity_Calculations_\n");
    fprintf(fp, "\tInput Parameters:\n");
    fprintf(fp, "Fluid surface tension:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\n", sigma);
    fprintf(fp, "Contact angle:\n");
    fprintf(fp, "cang =\t%.3f\trad\n", cang);
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "Capillary rise:\n");
    fprintf(fp, "h =\t%.3f\tcm\t=\\frac{2\\sigma\\cos\\theta}{\\rho gr}\n",h*0.01);
    fprintf(fp, "Capillary pressure:\n");
    fprintf(fp, "Pc =\t%.3f\tPa\t=\\frac{2\\sigma\\cos\\theta}{r}\n",Pc);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void Capp()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    printf("Capillarity Calculator\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //Declaring function variables
            //Function Output
        double h = 0.0; //Capillary rise
        double Pc = 0.0; //Capillary pressure
            //Calculation Variables
        double sigma = 0.0; //Surface tension
        double cang = 0.0; //Contact angle
        double rho = 0.0; //Fluid density
        double d = 0.0; //Tube diameter
        
        int whilcont = 0;
        
        //Collecting & Manipulating data
        CappVar(&sigma, &cang, &rho, &d);
        printf("Function returns:\nsigma = %f\ncang = %f\nrho = %f\nd = %f\n", sigma, cang, rho, d);
        
        h = CappCalch(sigma, cang, rho, d);
        printf("Capillary rise = %.3f m\n", h);
        Pc  = CappCalcP(sigma, cang, d);
        printf("Capillary pressure = %.3f Pa\n", Pc);
        
        //Ask for file write (Remember while loop)
        //...
        CappWrite(sigma, cang, d, h, Pc);
        
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
