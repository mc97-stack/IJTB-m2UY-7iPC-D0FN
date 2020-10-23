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

EquivLenFits EquivLengVar(EquivLenFits data, double *rho, double *u, double *d, double *mu, double *vareps, double *phi)
{
    char input[maxstrlen];
    
    //  Loading database into the data struct
    data = EquivLengData(data);
    
    //  Gathering data needed to calculate phi
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid velocity (m/s) = ");
    *u = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid viscosity (cP) = ");
    *mu = atof(fgets(input, sizeof(input), stdin));
    *mu = (*mu)*0.001;
    
    printf("Pipe internal diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    *d = (*d)*0.001;
    
    printf("Pipe absolute roughness (mm) = ");
    *vareps = atof(fgets(input, sizeof(input), stdin));
    *vareps = (*vareps)*0.001;
    
    *phi = phicalc((*rho), (*u), (*d), (*mu), (*vareps));
    
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

double EquivLengCalcP(int count, double phi, double L_e, double rho, double u, double d)
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

double EquivLengCalcL(double input, double d)
{
    return input*d;
}

EquivLenFits EquivLengFinalTable(EquivLenFits data, double rho, double u, double d, double phi)
{
    for(int i = 0; i < 15; ++i){
        data.dP_f[i] = EquivLengCalcP(data.count[i], phi, EquivLengCalcL(data.data[i], d), rho, u, d);
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
}

void EquivLeng()
{
    double rho = 0.0;
    double u = 0.0;
    double d = 0.0;
    double mu = 0.0;
    double vareps = 0.0;
    double phi = 0.0;
    
    double totalP = 0.0;
    double totalH = 0.0;
    
    EquivLenFits EquivLengTable;
    
    // Initialising the struct
    for(int i = 0; i < 15; ++i)
    {
        EquivLengTable.data[i] = 0.0;
        EquivLengTable.count[i] = 0;
        EquivLengTable.dP_f[i] = 0.0;
        EquivLengTable.h_f[i] = 0.0;
    }
    
    //  Collecting data
    EquivLengTable = EquivLengVar(EquivLengTable, &rho, &u, &d, &mu, &vareps, &phi);
    printf("\n");
    
    //  Performing calculations
    EquivLengTable = EquivLengFinalTable(EquivLengTable, rho, u, d, phi);
    
    //  Calculating total pressure and head loss
    for(int i = 0; i < 15; ++i)
    {
        totalP += EquivLengTable.dP_f[i];
        totalH += EquivLengTable.h_f[i];
    }
    
    //  Displaying data
    EquivLengDisplay(EquivLengTable, rho, u, d, mu, vareps, phi, totalP, totalH);
}

