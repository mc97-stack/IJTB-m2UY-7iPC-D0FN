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

//  Custom header files
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

/*
void [Data Plot & Write](...)
{
    char filename[maxstrlen];
    char path[maxstrlen];
    char filepath[maxstrlen*2];

    FILE *fp
    
    //Get file name
    *filename = (char)malloc(sizeof(filename);
    ...
    
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
void Mano()
{
    //Main Function
    char CalcSelec[maxstrlen];
    char ContCond[maxstrlen];
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
        
        int whilcont = 0;
        int whilside = 0;
        
        whilside = 1;
        while(whilside == 1)
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
                    whilside = 0;
                break;
                case '2':
                case 'E':
                case 'e':
                    printf("\n");
                    ManoEstiVar(&P1, &P2, &rho1, &rho2, &h1);
                    printf("Function returns:\nP1 = %f\nP2 = %f\nrho1 = %f\nh1 = %f\nrho2 = %f\n\n", P1, P2, rho1, h1, rho2);
                    h2 = ManoEstiCal(P1, P2, rho1, h1, rho2);
                    printf("Function returns: %f\n", h2);
                    whilside = 0;
                break;
                default:
                    printf("Input not recognised. \n");
                break;
            }
        }
        
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
        printf("\n");
    }
    fflush(stdout);
}
