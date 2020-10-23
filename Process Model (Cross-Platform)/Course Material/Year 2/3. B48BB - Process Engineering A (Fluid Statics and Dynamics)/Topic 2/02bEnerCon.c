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
#include <time.h>

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
    kin = (kin)*0.001;
    
    pot = z*g;
    pot = (pot)*0.001;
    
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

void EnerConWrite(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double check)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + Steady Flow Energy Equation Results
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
    
    strcat(filename, " Steady Flow Energy Equation Results");
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
    fprintf(fp, "_Steady-Flow_Energy_Equation_\n");
    fprintf(fp, "Assuming the fluid is incompressible. \n");
    fprintf(fp, "g =\t%.3f\tm/s2\n\n", g);
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial fluid enthalpy:\n");
    fprintf(fp, "h1 =\t%.3f\tkJ/kg\n", h1);
    fprintf(fp, "Final fluid enthalpy:\n");
    fprintf(fp, "h2 =\t%.3f\tkJ/kg\n", h2);
    fprintf(fp, "Initial fluid velocity:\n");
    fprintf(fp, "u1 =\t%.3f\tm/s\n", u1);
    fprintf(fp, "Final fluid velocity:\n");
    fprintf(fp, "u2 =\t%.3f\tm/s\n", u2);
    fprintf(fp, "Initial fluid height:\n");
    fprintf(fp, "z1 =\t%.3f\tm\n", z1);
    fprintf(fp, "Final fluid height:\n");
    fprintf(fp, "z2 =\t%.3f\tm\n\n", z2);
    
    fprintf(fp, "Specific process heat:\n");
    fprintf(fp, "q =\t%.3f\tkJ/kg\n", q);
    fprintf(fp, "Specific process work:\n");
    fprintf(fp, "w =\t%.3f\tkJ/kg\n", w);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "check =\t%.3f\tkJ/kg\n", check);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EnerConWriteCheck(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double check)
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
                EnerConWrite(h1, h2, u1, u2, z1, z2, q, w, check);
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
        
        double check = 0.0;
        
        int whilcont = 0;
        
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
        check = state2 - state1;
        check = process - check;
        if(fabs(check) <= 0.001)
        {
            printf("Your process should work in reality\n");
        }else{
            printf("Your process breaks the first law\n");
        }
        //Ask for file write (Remember while loop)
        EnerConWriteCheck(h1, h2, u1, u2, z1, z2, q, w, check);
        
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
