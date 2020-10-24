//
//  01cMano.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
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
#include "B48BB_T1.h"
#include "01cMano.h"

//  Fixed variable definitions
#define maxstrlen 128
#define g 9.80665
#define PI 3.14159265

void ManoMeasVar(double *P2, double *rho1, double *h1, double *rho2, double *h2)
{
    //Declaring input variables
    char input[maxstrlen];
    
    //Misc function variables
    char abspres[maxstrlen];
    char inclcon[maxstrlen];
    
    double L = 0.0;
    double incl = 0.0;
    
    int PresCheck = 0;
    int InclCheck = 0;
    
    PresCheck = 1;
    while(PresCheck == 1)
    {
        printf("Take reference pressure as absolute atmospheric pressure? ");
        fgets(abspres, sizeof(abspres), stdin);
        
        switch(abspres[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *P2 = 101.325;
                PresCheck = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                printf("P_2 (kPa_{abs}) = ");
                *P2 = atof(fgets(input, sizeof(input), stdin));
            
                if(*P2 == 0) // Double checking in case a gauge pressure is inputted
                {
                    *P2 = *P2 + 101.325;
                }
                PresCheck = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    
    *P2 = *P2 * 1000; //Conversion (kPa to Pa)
    printf("\n");
    
    printf("Density of process fluid (kg/m3) = ");
    *rho1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Height of process fluid in manometer (cm) = ");
    *h1 = atof(fgets(input, sizeof(input), stdin));
    
    *h1 = *h1 * 0.01; //Conversion (cm to m)
    
    printf("\n");
    printf("Density of manometer fluid (kg/m3) = ");
    *rho2 = atof(fgets(input, sizeof(input), stdin));
    
    //Check for an inclined manometer
    InclCheck = 1;
    while(InclCheck == 1)
    {
        printf("Is the manometer inclined? ");
        fgets(inclcon, sizeof(inclcon), stdin);
        switch(inclcon[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                //Length along arm
                printf("Length of manometer fluid in inclined arm (cm) = ");
                L = atof(fgets(input, sizeof(input), stdin));
                
                //Degree of inclination
                printf("Degree of inclination (deg) = ");
                incl = atof(fgets(input, sizeof(input), stdin));
                
                incl = (incl)*(PI/180); //Conversion to radians
                *h2 = (L)*sin( (incl) );
                InclCheck = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                printf("Height of manometer fluid (cm) = ");
                *h2 = atof(fgets(input, sizeof(input), stdin));
                InclCheck = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    
    *h2 = *h2 * 0.01; //Conversion (cm to m)
    printf("\n");
    printf("Function assignments:\nP2 = %f\nrho1 = %f\nh1 = %f\nrho2 = %f\nh2 = %f\n\n", *P2, *rho1, *h1, *rho2, *h2);
    
    fflush(stdout);
}

void ManoEstiVar(double *P1, double *P2, double *rho1, double *rho2, double *h1)
{
    //Declaring input variables
    char input[maxstrlen];
    
    //Misc function variables
    char abspres[maxstrlen];
    
    int PresCheck = 0;
    
    printf("P_1 (kPa_{abs}) = ");
    *P1 = atof(fgets(input, sizeof(input), stdin));
    
    *P1 = (*P1)*1000; //Conversion (kPa to Pa)
    
    PresCheck = 1;
    //P2 variable collection
    while(PresCheck == 1)
    {
        printf("Take reference pressure as absolute atmospheric pressure? ");
        fgets(abspres, sizeof(abspres), stdin);
        
        switch(abspres[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *P2 = 101.325;
                PresCheck = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                printf("P_2 (kPa_{abs}) = ");
                *P2 = atof(fgets(input, sizeof(input), stdin));
                
                if(*P2 == 0)
                {
                    *P2 = *P2 + 101.325;
                }
                PresCheck = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    *P2 = (*P2) *1000; //Conversion (kPa to Pa)
    
    printf("\n");
    printf("Density of process fluid (kg/m3) = ");
    *rho1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Height of process fluid in manometer (cm) = ");
    *h1 = atof(fgets(input, sizeof(input), stdin));
    
    *h1 = (*h1)*0.01; //Conversion (cm to m)
    
    printf("\n");
    printf("Density of manometer fluid (kg/m3) = ");
    *rho2 = atof(fgets(input, sizeof(input), stdin));
    
    fflush(stdout);
}

double ManoMeasCal(double P2, double rho1, double h1, double rho2, double h2)
{
    double brack = 0.0;
    double P1 = 0.0;
    
    brack = rho2 * h2;
    brack = brack - rho1 * h1;
    
    P1 = g*(brack); //Calling *brack before running the calculation
    
    P1 = P2 + (P1); //Calling the intermediate P1 first
    printf("Pipe pressure = %.3f kPa\n", (P1 * 0.001));
    return P1;
}

double ManoEstiCal(double P1, double P2, double rho1, double h1, double rho2)
{
    char inclcheck[maxstrlen];
    char deg[maxstrlen];
    
    double dP = 0.0;
    double top = 0.0;
    double bot = 0.0;
    double rad = 0.0;
    double incl = 0.0;
    
    double h2 = 0.0;
    
    int InclCheck;
    
    dP = P1 - P2;
    top = rho1*g;
    top = (top) * h1;
    top = (top) + dP;
    
    bot = rho2*g;
    
    h2 = (top)/(bot);
    
    InclCheck = 1;
    while(InclCheck == 1)
    {
        printf("Is the manometer inclined? ");
        fgets(inclcheck, sizeof(inclcheck), stdin);
        switch(inclcheck[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                //Degree of inclination
                printf("Degree of Inclination (deg) = ");
                incl = atof(fgets(deg, sizeof(deg), stdin));
                
                incl = (incl)*(PI/180.0); //Conversion to radians
                rad = sin(incl);
                printf("Degree of inclination in radians = %f rad\n", rad);
                h2 = (h2)/(rad);
                printf("Length of manometer fluid in the inclined arm = %.3f cm\n", ((h2)*100));
                InclCheck = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                printf("Manometer fluid height = %.3f cm\n", ((h2)*100) ); //Conversion (cm to m)
                InclCheck = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    return h2;
}

void ManoMeasWrite(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Manometer Measurement Results
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
    
    strcat(filename, " Manometer Measurement Results");
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
    fprintf(fp, "Manometer Estimation Calculations\n\n");
    fprintf(fp, "_Input_Parameters:_\n");
    fprintf(fp, "\tProcess Fluid:\n");
    fprintf(fp, "P1 =\t%.3f\tkPa_abs\n", P1*0.001);
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Process fluid height:\n");
    fprintf(fp, "h1 =\t%.3f\tm\n", h1);
    fprintf(fp, "\tManometer Fluid:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa_abs\n", P2*0.001);
    fprintf(fp, "Manometer fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n\n", rho2);
    
    fprintf(fp, "_Output_Values:_\n");
    fprintf(fp, "Manometer fluid height:\n");
    fprintf(fp, "h2 =\t%.3f\tm\t= \\frac{\\rho_1gh_1 - \\Delta{P}}{\\rho_2g}\n", h2);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ManoMeasWriteCheck(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    int SaveC;
    SaveC = 1;
    while(SaveC == 1)
    {
        char input[maxstrlen];
        //*SaveQ = (char)malloc(sizeof(SaveQ));
        printf("Do you want to save results to file? ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                ManoMeasWrite(P1, P2, rho1, h1, rho2, h2);
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

void ManoEstiWrite(double P1, double P2, double rho1, double h1, double rho2, double h2)
{
    //Function variables
    char filename[maxstrlen];
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Manometer Height Estimation Results
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
    
    strcat(filename, " Manometer Height Estimation Results");
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
    void free(void *filename);
    
    printf("File name: \"%s\"\n", filename);
    printf("Full file path: \"%s\"\n\n", filepath);
    
    //Testing if directory is not present
    
    if(fopen(filepath, "r") == NULL){
        printf("Directory does not exist, writing data to \"Documents\" folder instead.\n");
        strcpy(filepath, "/Users/user/Documents/");
        printf("File is now being outputted to: %s\n", filepath);
    }
    */
    printf("Note that write sequence disabled by zsh\n");
    
    printf("Beginning file write...\n");
    
    //Open file
    fp = fopen(filename, "w+");
    
    //Write to file
    fprintf(fp, "Manometer Measurement Calculations\n\n");
    fprintf(fp, "_Input_Parameters:_\n");
    fprintf(fp, "\tProcess Fluid:\n");
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho1 =\t%.3f\tkg/m3\n", rho1);
    fprintf(fp, "Process fluid height:\n");
    fprintf(fp, "h1 =\t%.3f\tm\n", h1);
    fprintf(fp, "\tManometer Fluid:\n");
    fprintf(fp, "P2 =\t%.3f\tkPa_abs\n", P2*0.001);
    fprintf(fp, "Process fluid density:\n");
    fprintf(fp, "rho2 =\t%.3f\tkg/m3\n", rho2);
    fprintf(fp, "Process fluid height:\n");
    fprintf(fp, "h2 =\t%.3f\tm\n\n", h2);
    
    fprintf(fp, "_Output_Values:_\n");
    fprintf(fp, "P1 =\t%.3f\tkPa_abs\t= P2 + g(\\rho_2h_2 - \\rho_1h_1)\n", P1*0.001);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ManoEstiWriteCheck(double P1, double P2, double rho1, double h1, double rho2, double h2)
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
                ManoEstiWrite(P1, P2, rho1, h1, rho2, h2);
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

void Mano()
{
    //Main Function
    char CalcSelec[maxstrlen];
    int whilmain = 1;
    
    printf("Manometer calculations\n");
    while(whilmain == 1)
    {
        double P1 = 0.0;
        double P2 = 0.0;
        double rho1 = 0.0;
        double rho2 = 0.0;
        double h1 = 0.0;
        double h2 = 0.0;
        
        int whilfunc = 0;
        
        whilfunc = 1;
        while(whilfunc == 1)
        {
            printf("Please make a selection: \n");
            printf("1. Pressure Measurement\n");
            printf("2. Manometer fluid height estimation\n");
            printf("Selection [1 - 2]: ");
            
            fgets(CalcSelec, sizeof(CalcSelec), stdin);
            switch(CalcSelec[0])
            {
                case '1':
                case 'M':
                case 'm':
                    printf("\n");
                    ManoMeasVar(&P2, &rho1, &h1, &rho2, &h2);
                    printf("Function returns:\nP2 = %f\nrho1 = %f\nh1 = %f\nrho2 = %f\nh2 = %f\n\n", P2, rho1, h1, rho2, h2);
                    P1 = ManoMeasCal(P2, rho1, h1, rho2, h2);
                    printf("Function returns: %f\n", P1);
                    
                    ManoMeasWriteCheck(P1, P2, rho1, h1, rho2, h2);
                    whilfunc = 0;
                break;
                case '2':
                case 'E':
                case 'e':
                    printf("\n");
                    ManoEstiVar(&P1, &P2, &rho1, &rho2, &h1);
                    printf("Function returns:\nP1 = %f\nP2 = %f\nrho1 = %f\nh1 = %f\nrho2 = %f\n\n", P1, P2, rho1, h1, rho2);
                    h2 = ManoEstiCal(P1, P2, rho1, h1, rho2);
                    printf("Function returns: %f\n", h2);
                    ManoEstiWriteCheck(P1, P2, rho1, h1, rho2, h2);
                    whilfunc = 0;
                break;
                default:
                    printf("Input not recognised. \n");
                break;
            }
        }
        //  Continue function
        whilmain = Continue(whilmain);
        printf("\n");
    }
    fflush(stdout);
}
