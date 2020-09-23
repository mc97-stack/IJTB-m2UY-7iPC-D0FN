//
//  02bEnerCon.c
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

//  Custom header files
#include "B48BB_T2.h"
#include "02bEnerCon.h"

#define maxstrlen 128
#define g 9.80665

double EnthalpyConv(double u, double P, double rho)
{
    double h = 0.0; //Declaring and initialising
    
    h = P/rho;
    h = u + (h);
    
    return h;
}


void EnerConVar(double *h1, double *h2, double *u1, double *u2, double *z1, double *z2, double *q, double *w)
{
    //Main input variables
    char input[maxstrlen];
    
    double inteng1 = 0.0;
    double inteng2 = 0.0;
    double pres1 = 0.0;
    double pres2 = 0.0;
    double rho1 = 0.0;
    double rho2 = 0.0;
    
    //Function variables
    char method[maxstrlen];
    int whilmeth = 0;
    
    whilmeth = 1;
    while(whilmeth == 1)
    {
        printf("Which definition do you want to use:\n");
        printf("1. Internal Energy (u)\n2. Enthalpy (h)\n\n");
        printf("Selection: ");
        fgets(method, sizeof(method), stdin);
        switch(method[0])
        {
            case '1':
            case 'I':
            case 'U':
            case 'i':
            case 'u':
                printf("Initial internal energy (kJ/kg) = ");
                inteng1 = atof(fgets(input, sizeof(input), stdin));
                
                printf("Final internal energy (kJ/kg) = ");
                inteng2 = atof(fgets(input, sizeof(input), stdin));
                
                printf("Initial pressure (kPa) = ");
                pres1 = atof(fgets(input, sizeof(input), stdin));
                
                printf("Final pressure (kPa) = ");
                pres2 = atof(fgets(input, sizeof(input), stdin));
                
                printf("Initial density (kg/m3) = ");
                rho1 = atof(fgets(input, sizeof(input), stdin));
                
                printf("Final density (kg/m3) = ");
                rho2 = atof(fgets(input, sizeof(input), stdin));
                
                //Converting through to enthalpy using definition
                *h1 = EnthalpyConv(inteng1, pres1, rho1);                
                *h2 = EnthalpyConv(inteng2, pres2, rho2);
                
                whilmeth = 0;
            break;
            case '2':
            case 'E':
            case 'H':
            case 'e':
            case 'h':
                printf("Initial enthalpy (kJ/kg) = ");
                *h1 = atof(fgets(input, sizeof(input), stdin));
                
                printf("Final enthalpy (kJ/kg) = ");
                *h2 = atof(fgets(input, sizeof(input), stdin));
                
                whilmeth = 0;
            break;
            default:
                printf("Input not recognised\n\n");
            break;
        }
        fflush(stdout);
    }
    
    printf("Initial velocity (m/s) = ");
    *u1 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Final velocity (m/s) = ");
    *u2 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Initial height (m) = ");
    *z1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Final height (m) = ");
    *z2 = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Process heat (kJ/ kg) = ");
    *q = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Process work (kJ/ kg) = ");
    *w = atof(fgets(input, sizeof(input), stdin));
    fflush(stdout);
    
    printf("Function assignments:\n");
    printf("h1 = %.3f kJ/kg\n", *h1);
    printf("h2 = %.3f kJ/kg\n", *h2);
    printf("u1 = %.3f m/s\n", *u1);
    printf("u2 = %.3f m/s\n", *u2);
    printf("z1 = %.3f m\n", *z1);
    printf("z2 = %.3f m\n", *z2);
    printf("q = %.3f kJ/kg\n", *q);
    printf("w = %.3f kJ/kg\n", *w);
    fflush(stdout);
}

double EnerConFluCalc(double h, double u, double z)
{
    double kin = 0.0;
    double pot = 0.0;
    
    double EnerCont = 0.0;
    
    kin = pow(u, 2);
    kin = (kin)/2;
    
    pot = z*g;
    
    EnerCont = h + (kin);
    
    EnerCont = (EnerCont) + (pot);
    
    printf("State energy content = %.3f kJ/kg\n", EnerCont);
    
    return EnerCont;
}

double EnerConProCalc(double q, double w)
{
    double Energy = 0.0;
    
    Energy  = q + w;
    return Energy;
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
void EnerCon()
{
    //First law states that energy is always conserved, This has mathematical implications when designing processes
    //Condition can be checked by using the definition from internal energy (C_v) or enthalpy (C_P)
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Energy Conservation Check\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //Variable declaration
        double h1 = 0.0;
        double h2 = 0.0;
        double u1 = 0.0;
        double u2 = 0.0;
        double z1 = 0.0;
        double z2 = 0.0;
        double q = 0.0;
        double w = 0.0;
        
        double state1 = 0.0;
        double state2 = 0.0;
        double process = 0.0;
        
        //Data collection
        EnerConVar(&h1, &h2, &u1, &u2, &z1, &z2, &q, &w);
        printf("\nFunction assignments:\n");
        printf("h1 = %f \n", h1);
        printf("h2 = %f \n", h2);
        printf("u1 = %f \n", u1);
        printf("u2 = %f \n", u2);
        printf("z1 = %f \n", z1);
        printf("z2 = %f \n", z2);
        printf("q = %f \n", q);
        printf("w = %f \n\n", w);
        
        //Data manipulation
        state1 = EnerConFluCalc(h1, u1, z1);
        printf("Function returns: state1 = %f\n", state1);
        
        state2 = EnerConFluCalc(h2, u2, z2);
        printf("Function returns: state2 = %f\n\n", state2);
        
        process = EnerConProCalc(q, w);
        printf("Function returns: Process = %f\n\n", process);
        
        //Checking for a violation of the first law
        double check;
        
        check = state2 - state1;
        check = process - check;
        if(check <= 0.001)
        {
            printf("Your process should work in reality\n");
        }else{
            printf("Your process breaks the first law\n");
        }
        //Ask for file write (Remember while loop)
        //...
        
        //Continue function
        int whilcont;
        whilcont = 1;
        while(whilcont == 1)
        {
            printf("Do you want to continue? ");
            fgets(ContCond, sizeof(ContCond), stdin);
            printf("\n");
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
