//
//  02dReyNo.c
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
#include "B48BB_T2.h"
#include "02dReyNo.h"

#define maxstrlen 128

void ReyNoVar(double *rho, double *u, double *d, double *mu)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Fluid Density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Average fluid velocity (m/s) = ");
    *u = atof(fgets(input, sizeof(input), stdin));
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    
    *d = (*d)*0.001; //Conversion (mm to m)
    
    printf("Fluid Viscosity (cP) = ");
    *mu = atof(fgets(input, sizeof(input), stdin));
    
    *mu = (*mu)*0.001; //Conversion (cP to Pa.s)
    
    printf("Function assignments:\n");
    printf("rho = %.3f kg/m3\n", *rho);
    printf("u = %.3f m/s\n", *u);
    printf("d = %.3f m\n", *d);
    printf("mu = %.3f Pa.s\n\n", *mu);
    fflush(stdout);
}

double ReyNoCalc(double rho, double u, double d, double mu)
{
    double ReyNum = 0.0;
    
    ReyNum = rho * u;
    ReyNum = (ReyNum)*d;
    ReyNum = (ReyNum)/mu;
    
    return ReyNum;
}

void ReyNoWrite(double rho, double u, double d, double mu, double ReyNum)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Reynolds Number Results
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
    
    strcat(filename, " Reynolds Number Results");
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
    fp = fopen(filename, "w+");
    
    //Write to file
    fprintf(fp, "_Mass_Conservation_Principle_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Pipe internal diameter:");
    fprintf(fp, "d =\t%.3f\tmm\n\n", d*1000);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "ReyNum =\t%.3f\t[ ]\t=\\frac{\\rho ud}{\\mu}\n", ReyNum);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ReyNoWriteCheck(double rho, double u, double d, double mu, double ReyNum)
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
                ReyNoWrite(rho, u, d, mu, ReyNum);
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

void ReyNo()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    printf("Reynold's Number Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
            //Function Output
        double ReyNum = 0.0;
            //Calculation Variables
        double rho = 0.0;
        double u = 0.0;
        double d = 0.0;
        double mu = 0.0;
        
        int whilcont = 0;
        
        //Data collection
        ReyNoVar(&rho, &u, &d, &mu);
        printf("Function returns:\n");
        printf("rho = %f \n", rho);
        printf("u = %f \n", u);
        printf("d = %f \n", d);
        printf("mu = %f \n\n", mu);
        
        //Data manipulation
        ReyNum = ReyNoCalc(rho, u, d, mu);
        
        printf("Reynolds Number = %.3f []\n", ReyNum);
        if(ReyNum < 2000)
        {
            printf("Flow regime is laminar \n");
        }else{
            if(ReyNum <3000){
                printf("Flow regime lies within the transition region. Consider using experimental data going forward.\n");
            }else{
                printf("Flow regime is turbulent. \n");
            }
        }
        
        printf("Function returns: ReyNum = %f \n", ReyNum);
        //Ask for file write (Remember while loop)
        ReyNoWriteCheck(rho, u, d, mu, ReyNum);
        
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
