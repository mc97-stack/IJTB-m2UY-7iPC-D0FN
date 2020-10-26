//
//  03bGenPressureLoss.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom Header Files
#include "System.h"
#include "B48BB_T3.h"
#include "03bGenPressureLoss.h"
#include "02dReyNo.h"
#include "03aFrictFactor.h"

#define maxstrlen 128

void PressLossVariable(double *rho, double *u, double *d, double *mu, double *L, double *vareps)
{
    char input[maxstrlen];  // Variable used to store keyboard input.
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid velocity (m/s) = ");
    *u = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid viscosity (cP) = ");
    *mu = atof(fgets(input, sizeof(input), stdin));
    *mu = (*mu) * 0.001;
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    *d = (*d) * 0.001;
    
    printf("Pipe length (m) = ");
    *L = atof(fgets(input, sizeof(input), stdin));
    
    if(ReyNoCalculation(*rho, *u, *d, *mu) > 2500){
        printf("Pipe absolute roughness (mm) = ");
        *vareps = atof(fgets(input, sizeof(input), stdin));
        *vareps = (*vareps) * 0.001;
    }else{ 
        *vareps = 0.0;
    }
    fflush(stdout);
}

double phiCalculation(double rho, double u, double d, double mu, double vareps)
{
    char menu[maxstrlen];
    
    double ReyNum = 0.0;
    double phi = 0.0;
    
    double phiTurb1 = 0.0;
    double phiTurb2 = 0.0;
    double phiTurb3 = 0.0;
    
    int roughcheck = 0;
    
    ReyNum = ReyNoCalculation(rho, u, d, mu);
    
    if(ReyNum < 2000){
        phi = Laminar(rho, u, d, mu);
    }else{
        if(ReyNum < 2500){
            printf("2000 < Re < 2500: Correlations are unavailable. Assuming laminar friction factor.\n");
            phi = Laminar(rho, u, d, mu);
        }else{
            roughcheck = 1;
            while(roughcheck == 1){
                printf("Is the friction factor independent of Reynolds number? [Y/N] ");
                fgets(menu, sizeof(menu), stdin);
                switch(menu[0]){
                    case '1':
                    case 'T':
                    case 'Y':
                    case 't':
                    case 'y':
                        d = d*1000;
                        vareps = vareps*1000;
                        phi = Turbulent4(d, vareps);
                        roughcheck = 0;
                        break;
                    case '0':
                    case 'F':
                    case 'N':
                    case 'f':
                    case 'n':
                        phiTurb1 = Turbulent1(rho, u, d, mu);
                        phiTurb2 = Turbulent2(rho, u, d, mu);
                        phiTurb3 = Turbulent3(rho, u, d, mu, vareps);
                        
                        if(phiTurb1 > phiTurb2 && phiTurb1 > phiTurb3)
                        {
                            printf("Turbulent1(...) provides the highest friction factor\n");
                            phi = phiTurb1;
                            vareps = 0.0;
                        }else{
                            if(phiTurb2 > phiTurb3){
                                printf("Turbulent2(...) provides the highest friction factor\n");
                                phi = phiTurb2;
                                vareps = 0.0;
                            }else{
                                printf("Turbulent3(...) provides the highest friction factor\n");
                                phi = phiTurb3;
                            }
                        }
                        roughcheck = 0;
                        break;
                    default:
                        printf("Invalid input, please try again\n");
                        break;
                }
            }
        }
    }
    fflush(stdout);
    return phi;
}

double LossCalculation(double phi, double L, double d, double rho, double u)
{
    double frac1 = 0.0;
    double frac2 = 0.0;
    double dP = 0.0;
    
    frac1 = L/d;
    
    frac2 = pow(u, 2);
    frac2 = rho*(frac2);
    frac2 = (frac2)/(2.0);
    
    dP = 8*phi;
    dP = (dP)*frac1;
    dP = (dP)*frac2;
    
    return dP;
}

void PressLossDisplay(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP)
{
    printf("_Pressure_Loss_Equation_Results_\n");
    printf("\tInput parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n\n", mu*1000);
    
    printf("Pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    printf("Pipe length:\n");
    printf("L =\t%.3f\tm\n", L);
    if(vareps == 0.0){
        printf("Pipe absolute roughness not used\n\n");
    }else{
        printf("Pipe absolute roughness:\n");
        printf("vareps =\t%.3f\tmm\n\n", vareps*1000);
    }
    
    printf("\tIntermediate parameters:\n");
    printf("Friction factor:\n");
    printf("phi =\t%.3f\t[]\n\n", phi);
    
    printf("\tOutput parameters:\n");
    printf("Fluid pressure loss:\n");
    printf("dP =\t%.3f\tPa\t= 8\\phi\\frac{L}{d}\\frac{\\rho u^2}{2}", dP);
}

void PressLossWrite(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Pressure Loss Equation Results
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
    
    strcat(filename, " Pressure Loss Equation Results");
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
    fprintf(fp, "_Pressure_Loss_Equation_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tPa.s\n\n", mu);
    
    fprintf(fp, "Pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    fprintf(fp, "Pipe length:\n");
    fprintf(fp, "L =\t%.3f\tm\n", L);
    if(vareps == 0.0){
        fprintf(fp, "Pipe absolute roughness not used\n\n");
    }else{
        fprintf(fp, "Pipe absolute roughness:\n");
        fprintf(fp, "vareps =\t%.3f\tmm\n\n", vareps*1000);
    }
    
    fprintf(fp, "\tIntermediate parameters:\n");
    fprintf(fp, "Friction factor:\n");
    fprintf(fp, "phi =\t%.3f\t[]\n", phi);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Fluid pressure loss:\n");
    fprintf(fp, "dP =\t%.3f\tPa\t= 8\\phi\\frac{L}{d}\\frac{\\rho u^2}{2}", dP);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PressLossWriteSwitch(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP)
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
                PressLossWrite(rho, u, d, mu, L, vareps, phi, dP);
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

void GeneralPressureLoss()
{
    //Main Function
    int whilmain = 1;
    printf("General Pressure Loss\n");
    
    while(whilmain == 1)
    {
        //  Variable declaration
        double rho = 0.0;
        double u = 0.0;
        double d = 0.0;
        double mu = 0.0;
        double L = 0.0;
        double vareps = 0.0;
        
        double phi = 0.0;
        double dP = 0.0;
        
        //  Data collection
        PressLossVariable(&rho, &u, &d, &mu, &L, &vareps);
        
        //  Running calculations
        phi = phiCalculation(rho, u, d, mu, vareps);
        //printf("phi = %.5f [ ]\n", phi);
        dP = LossCalculation(phi, L, d, rho, u);
        //printf("dP = %.3f kPa\n", dP*0.001);
        
        //  Displaying results
        PressLossDisplay(rho, u, d, mu, L, vareps, phi, dP);
        
        //  Writing to File
        PressLossWriteSwitch(rho, u, d, mu, L, vareps, phi, dP);
        
        //Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
