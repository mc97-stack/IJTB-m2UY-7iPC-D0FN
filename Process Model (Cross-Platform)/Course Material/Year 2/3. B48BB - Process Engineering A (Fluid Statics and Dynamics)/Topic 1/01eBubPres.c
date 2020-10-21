//
//  01eBubPres.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom header files
#include "B48BB_T1.h"
#include "01eBubPres.h"

#define maxstrlen 128

void BubPresVar(double *sigma, double *r)
{
    //Declaring input variable
    char input[maxstrlen];
    
    printf("Surface tension (N/m) = ");
    *sigma = atof(fgets(input, sizeof(input), stdin));
    
    printf("Radius of fluid droplet (mm) = ");
    *r = atof(fgets(input, sizeof(input), stdin));
    
    *r = (*r)*0.001; //Conversion (mm to m)
    printf("Function assignments:\nsigma = %f N/m\nr = %f m\n", *sigma, *r);
    fflush(stdout);
}

double BubPresCalc(double sigma, double r) 
{
    double top = 0.0;
    double P = 0.0;
    
    top = 0.0; //Initialising variable
    
    top = 2*sigma;
    P = (top)/r;
    
    return P;
}

void BubPresWrite(double sigma, double r, double P)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Bubble Pressure Results
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
    
    strcat(filename, " Bubble Pressure Results");
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    
    //driveloc is not suitable when determining the file path for mac
    *filepath = (char)malloc(sizeof *filepath);
    
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
    printf("Note that write sequence may be disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filepath, "w+");
    
    //Write to file
    fprintf(fp, "_Bubble_Pressure_Calculations_\n");
    fprintf(fp, "\tInput Parameters:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\n", sigma);
    fprintf(fp, "r =\t%.3f\tmm\n", r*1000);
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "P =\t%.3f\tPa\t=\\frac{2\\sigma}{r}\n", P);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void BubPres()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    printf("Bubble Pressure Calculator\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //Declaring & Allocating main variables
        double sigma = 0.0;
        double r = 0.0;
        double P = 0.0;
        
        int whilcont = 0;
        
        BubPresVar(&sigma, &r);
        printf("Function returns:\nsigma = %f\nr = %f\n", sigma, r);
        P = BubPresCalc(sigma, r);
        printf("Bubble pressure = %.3f Pa\n", P);
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
