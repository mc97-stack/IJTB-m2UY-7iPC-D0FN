//
//  03dcEquivLeng.c
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
#include "System.h"
#include "03dEquivLeng.h"
#include "03bGenPressureLoss.h"

#define maxstrlen 128
#define g 9.80665

EquivLenFits EquivLengData(EquivLenFits input)
{
    input.data[0] = 15;
    input.data[1] = 35;
    input.data[2] = 75;
    input.data[3] = 60;
    input.data[4] = 90;
    input.data[5] = 25;
    input.data[6] = 50;
    input.data[7] = 2;
    input.data[8] = 450;
    input.data[9] = 7.5;
    input.data[10] = 40;
    input.data[11] = 200;
    input.data[12] = 800;
    input.data[13] = 18;
    input.data[14] = 18;
    
    return input;
}

EquivLenFits EquivLengVariable(EquivLenFits data, double *rho, double *u, double *d, double *mu, double *vareps, double *phi)
{
    char input[maxstrlen];  // Variable used to store keyboard input.
    
    //  Loading database into the data struct
    data = EquivLengData(data);
    
    //  Gathering data needed to calculate phi
    *rho = inputDouble(0, "fluid density", "kg/m3");
    
    *u = inputDouble(0, "fluid velocity", "m/s");
    
    *mu = inputDouble(0, "fluid viscosity", "cP");
    *mu = (*mu)*0.001;
    
    *d = inputDouble(0, "pipe internal diameter", "mm");
    *d = (*d)*0.001;
    
    *vareps = inputDouble(0, "pipe absolute roughness", "mm");
    *vareps = (*vareps)*0.001;
    
    *phi = phiCalculation((*rho), (*u), (*d), (*mu), (*vareps));
    
    //  Getting counts
    printf("\nPlease enter the counts of each fitting:\n");
    printf("Standard 45 deg elbow: ");
    data.count[0] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg elbow standard radius: ");
    data.count[1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg square elbow: ");
    data.count[2] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry from leg T-piece: ");
    data.count[3] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry into leg T-piece: ");
    data.count[4] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Reduction (Tank outlet): ");
    data.count[5] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Expansion (Tank Inlet): ");
    data.count[6] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Unions and Couplings: ");
    data.count[7] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve fully open: ");
    data.count[8] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (100 pct): ");
    data.count[9] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (75 pct): ");
    data.count[10] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (50 pct): ");
    data.count[11] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (25 pct): ");
    data.count[12] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve (100 pct): ");
    data.count[13] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve open: ");
    data.count[14] = atoi(fgets(input, sizeof(input), stdin));
    
    return data;
}

double EquivLengCalculateLoss(int count, double phi, double L_e, double rho, double u, double d)
{
    double dP_f = 0.0;
    double term1 = 0.0;
    double term2 = 0.0;
    
    dP_f = 8*phi;
    
    term1 = L_e / d;
    
    term2 = pow(u, 2);
    term2 = rho * (term2);
    term2 = (term2)/2;
    
    dP_f = (dP_f)*term1;
    dP_f = (dP_f)*term2;
    
    dP_f = (dP_f)*count;
    
    return dP_f;
}

double EquivLengCalculateL_e(double input, double d)
{
    return input*d;
}

EquivLenFits EquivLengFinalTable(EquivLenFits data, double rho, double u, double d, double phi)
{
    for(int i = 0; i < 15; ++i){
        data.dP_f[i] = EquivLengCalculateLoss(data.count[i], phi, EquivLengCalculateL_e(data.data[i], d), rho, u, d);
        data.h_f[i] = (data.dP_f[i])/(rho*g);
    }
    return data;
}

void EquivLengDisplay(EquivLenFits table, double rho, double u, double d, double mu, double vareps, double phi, double totalP, double totalh)
{
    int i = 0;
    
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    
    printf("Fluid velocity (m/s):\n");
    printf("u =\t%.3f\tm/s\n", u);
    
    printf("Fluid viscosity (cP):\n");
    printf("mu =\t%.3f\tcP\n", mu*1000);
    
    printf("Pipe internal diameter (mm):\n");
    printf("d =\t%.1f\tmm\n", d*1000);
    
    printf("Pipe absolute roughness (mm):\n");
    printf("vareps =\t%.5f\tmm\n", vareps*1000);
    
    printf("Friction Factor:\n");
    printf("phi =\t%.5f\t[ ]\n\n", phi);
    
    printf("Total pressure loss:\n");
    printf("dP_f =\t%.3f\tPa\n", totalP);
    
    printf("Total head loss:\n");
    printf("h_L =\t%3f\tm\n\n", totalh);
    
    printf("Fitting\tL_e/d\tCount\tdP_f (Pa)\th_L (m)\n");
    
    i = 0;
    printf("Standard 45 deg elbow\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("90 deg elbow standard radius\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("90 deg square elbow\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Entry from leg T-piece\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Entry into leg T-piece\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Sudden Reduction (Tank outlet)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Sudden Expansion (Tank Inlet)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Unions and Couplings\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Globe valve fully open\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Gate valve (100 pct)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Gate valve (75 pct)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Gate valve (50 pct)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Gate valve (25 pct)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Ball valve (100 pct)\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    ++i;
    
    printf("Plug valve open\t");
    printf("%.1f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\t", table.dP_f[i]);
    printf("%.3f\n", table.h_f[i]);
    fflush(stdout);
}

void EquivLengWrite(EquivLenFits table, double rho, double u, double d, double mu, double vareps, double phi, double totalP, double totalh)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Equivalent Length Results
        //Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
        //Creating file name with base format "YYYYmmDD HHMMSS "
    //Allocating memory for the file name
    *filename = (char)malloc(sizeof *filename);
    
    strftime(filename, 15, "%Y%m%d %H%M%S", info);
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Equivalent Length");
    //printf("File name: \"%s\"\n", filename);
    
    strcat(filename,".txt");
    printf("File name: \"%s\"\n", filename);
    /*
    //driveloc is not suitable when determining the file path for mac

    //printf("Save file to: /Users/user/Documents/ ");
    strcpy(filepath, "/Users/user/Documents/ModelFiles/");

    strcat(filepath, filename);

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
    fprintf(fp, "_Pressure_Loss_Through_Pipe_Fittings_(Equivalent_Length_Method)_Results_\n");
    
    int i = 0;
    
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    
    fprintf(fp, "Fluid velocity (m/s):\n");
    fprintf(fp, "u =\t%.3f\tm/s\n", u);
    
    fprintf(fp, "Fluid viscosity (cP):\n");
    fprintf(fp, "mu =\t%.3f\tcP\n", mu*1000);
    
    fprintf(fp, "Pipe internal diameter (mm):\n");
    fprintf(fp, "d =\t%.1f\tmm\n", d*1000);
    
    fprintf(fp, "Pipe absolute roughness (mm):\n");
    fprintf(fp, "vareps =\t%.5f\tmm\n", vareps*1000);
    
    fprintf(fp, "Friction Factor:\n");
    fprintf(fp, "phi =\t%.5f\t[ ]\n\n", phi);
    
    fprintf(fp, "Total pressure loss:\n");
    fprintf(fp, "dP_f =\t%.3f\tPa\n", totalP);
    
    fprintf(fp, "Total head loss:\n");
    fprintf(fp, "h_L =\t%3f\tm\n\n", totalh);
    
    fprintf(fp, "Fitting\tL_e/d\tCount\tdP_f (Pa)\th_L (m)\n");
    
    i = 0;
    fprintf(fp, "Standard 45 deg elbow\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "90 deg elbow standard radius\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "90 deg square elbow\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Entry from leg T-piece\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Entry into leg T-piece\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Sudden Reduction (Tank outlet)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Sudden Expansion (Tank Inlet)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Unions and Couplings\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Globe valve fully open\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Gate valve (100 pct)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Gate valve (75 pct)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Gate valve (50 pct)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Gate valve (25 pct)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Ball valve (100 pct)\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    ++i;
    
    fprintf(fp, "Plug valve open\t");
    fprintf(fp, "%.1f\t", table.data[i]);
    fprintf(fp, "%i\t", table.count[i]);
    fprintf(fp, "%.3f\t", table.dP_f[i]);
    fprintf(fp, "%.3f\n", table.h_f[i]);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EquivLengWriteSwitch(EquivLenFits table, double rho, double u, double d, double mu, double vareps, double phi, double totalP, double totalh)
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
                EquivLengWrite(table, rho, u, d, mu, vareps, phi, totalP, totalh);
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

void EquivalentLength()
{
    //  Variable declaration
    double totalP = 0.0;    // Total pressure loss through all stated fittings.
    double totalH = 0.0;    // Total head loss through all stated fittings.
    
    double rho = 0.0;       // Fluid density.
    double u = 0.0;         // Fluid velocity.
    double d = 0.0;         // Internal pipe diameter.
    double mu = 0.0;        // Fluid viscosity.
    double vareps = 0.0;    // Pipe absolute roughness.
    double phi = 0.0;       // Friction factor.
    
    EquivLenFits EquivLengTable = {0.0};
    
        //  Variables for timing function
    struct timespec start, end;
    double elapsed = 0.0;
    
    //  Collecting data
    EquivLengTable = EquivLengVariable(EquivLengTable, &rho, &u, &d, &mu, &vareps, &phi);
    printf("\n");
    
    //  Performing calculations
    clock_getres(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    EquivLengTable = EquivLengFinalTable(EquivLengTable, rho, u, d, phi);
    
    //  Calculating total pressure and head loss
    for(int i = 0; i < 15; ++i)
    {
        totalP += EquivLengTable.dP_f[i];
        totalH += EquivLengTable.h_f[i];
    }
    clock_getres(CLOCK_MONOTONIC, &end);
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = timer(start, end);

    printf("Calculations completed in %.6f seconds.\n", elapsed);
    
    //  Displaying data
    EquivLengDisplay(EquivLengTable, rho, u, d, mu, vareps, phi, totalP, totalH);
    
    //  Writing data to file
    EquivLengWriteSwitch(EquivLengTable, rho, u, d, mu, vareps, phi, totalP, totalH);
}

