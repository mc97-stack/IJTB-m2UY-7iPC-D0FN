//
//  03cHydrDiam.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/07/2020.
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
#include "03cHydrDiam.h"

#define maxstrlen 128

void HydrDiamVar(double *A_F, double *P_W)
{
    //Input variables
    char input[maxstrlen];
    
    double convfactor = 0.0;
    
    printf("Cross-sectional flow area (mm2) = ");
    *A_F = atof(fgets(input, sizeof(input), stdin));
    
    convfactor = pow(1000,2);
    convfactor = 1/(convfactor);
    *A_F = (*A_F)*convfactor;
    
    printf("Wetted perimeter (cm) = ");
    *P_W = atof(fgets(input, sizeof(input), stdin));
    
    *P_W = (*P_W)*0.01;
    
    fflush(stdout);
}

double HydrDiamCalc(double A_F, double P_W)
{
    double d_H = 0.0;
    double top = 0.0;
    double bot = 0.0;
    
    top = 4*A_F;
    bot = P_W;
    d_H = (top)/(bot);
    
    return d_H;
}

void HydrDiamWrite(double A_F, double P_W, double d_H)
{
    //Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Hydraulic Diameter Results
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
    
    strcat(filename, " Hydraulic Diameter Results");
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
    fprintf(fp, "_Hydraulic_Diameter_Results_\n");
    
    //Write to file
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Cross-sectional flow area:\n");
    fprintf(fp, "A_F =\t%.3f\tmm2\n", A_F*pow(1000,2));
    fprintf(fp, "Wetted perimeter:\n");
    fprintf(fp, "P_W =\t%.3f\tcm\n", P_W*100);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Hydraulic diameter:\n");
    fprintf(fp, "d_H =\t%.3f\tmm\t= \\frac{4A_F}{P_W}", d_H*1000);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void HydrDiamWriteCheck(double A_F, double P_W, double d_H)
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
                HydrDiamWrite(A_F, P_W, d_H);
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

void HydrDiam()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Hydraulic diameter calculation\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Declaring variables
        double A_F = 0.0; //Cross-sectional flow area
        double P_W = 0.0; //Wetted perimeter
        
        double d_H = 0.0; //Hydraulic diameter
        
        int whilcont = 0;
        //Data collection
        HydrDiamVar(&A_F, &P_W);
        
        //Data manipulation
        d_H = HydrDiamCalc(A_F, P_W);
        
        printf("d_H = %.3f mm\n\n", d_H*1000);
        
        //Ask for file write
        HydrDiamWriteCheck(A_F, P_W, d_H);
        
        //Continue function
        whilcont = 0;
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
