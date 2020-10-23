//
//  03dTwoK.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 22/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "02dReyNo.h"
#include "03dTwoK.h"

#define maxstrlen 128
#define g 9.80665

TwoKFittings TwoKData(TwoKFittings input)
{
    //  Loading k_1 values
    input.k1[0] = 800;
    input.k1[1] = 800;
    input.k1[2] = 800;
    
    input.k1[3] = 1000;
    input.k1[4] = 800;
    input.k1[5] = 800;
    input.k1[6] = 800;
    input.k1[7] = 800;
    
    input.k1[8] = 500;
    input.k1[9] = 500;
    
    input.k1[10] = 500;
    input.k1[11] = 500;
    
    input.k1[12] = 1000;
    input.k1[13] = 1000;
    input.k1[14] = 1000;
    
    input.k1[15] = 500;
    input.k1[16] = 800;
    input.k1[17] = 800;
    input.k1[18] = 1000;
    
    input.k1[19] = 200;
    input.k1[20] = 150;
    input.k1[21] = 100;
    
    input.k1[22] = 300;
    input.k1[23] = 500;
    input.k1[24] = 1000;
    
    input.k1[25] = 1500;
    input.k1[26] = 1000;
    input.k1[27] = 1000;
    input.k1[28] = 800;
    
    input.k1[29] = 2000;
    input.k1[30] = 1500;
    input.k1[31] = 1000;
    
    //  Loading k_inf values
    input.kinf[0] = 0.4;
    input.kinf[1] = 0.25;
    input.kinf[2] = 0.2;
    
    input.kinf[3] = 1.15;
    input.kinf[4] = 0.35;
    input.kinf[5] = 0.3;
    input.kinf[6] = 0.27;
    input.kinf[7] = 0.25;
    
    input.kinf[8] = 0.2;
    input.kinf[9] = 0.15;
    
    input.kinf[10] = 0.25;
    input.kinf[11] = 0.15;
    
    input.kinf[12] = 0.6;
    input.kinf[13] = 0.35;
    input.kinf[14] = 0.3;
    
    input.kinf[15] = 0.7;
    input.kinf[16] = 0.4;
    input.kinf[17] = 0.8;
    input.kinf[18] = 1;
    
    input.kinf[19] = 0.1;
    input.kinf[20] = 0.05;
    input.kinf[21] = 0;
    
    input.kinf[22] = 0.1;
    input.kinf[23] = 0.15;
    input.kinf[24] = 0.25;
    
    input.kinf[25] = 4;
    input.kinf[26] = 2;
    input.kinf[27] = 2;
    input.kinf[28] = 0.25;
    
    input.kinf[29] = 10;
    input.kinf[30] = 1.5;
    input.kinf[31] = 0.5;
    
    return input;
}

TwoKFittings TwoKVar(TwoKFittings table, double *rho, double *u, double *d, double *mu, double *Impd)
{
    char input[maxstrlen];
    
    table = TwoKData(table);
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid velocity (m/s) = ");
    *u = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid viscosity (cP) = ");
    *mu = atof(fgets(input, sizeof(input), stdin));
    *mu = (*mu)*0.001;
    
    printf("Internal pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    *d = (*d)*0.1; // Conversion to cm
    *Impd = (*d)/(2.54); // Conversion to inches
    *d = (*d)*0.01; // Conversion to m
    
    printf("\nPlease enter the counts of each fitting:\n");
    printf("90 deg Elbow, Threaded (Standard Radius) (R/D = 1): ");
    table.count[0] = atoi(fgets(input, sizeof(input), stdin));
    printf("90 deg Elbow, Flanged/Welded (Standard Radius) (R/D = 1): ");
    table.count[1] = atoi(fgets(input, sizeof(input), stdin));
    printf("90 deg Elbow, All types (Long Radius) (R/D = 1.5): ");
    table.count[2] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow Mitered (R/D = 1.5), 1 Weld (90 deg angle): ");
    table.count[3] = atoi(fgets(input, sizeof(input), stdin));
    printf("90 deg Elbow Mitered (R/D = 1.5), 2 Weld (45 deg angle): ");
    table.count[4] = atoi(fgets(input, sizeof(input), stdin));
    printf("90 deg Elbow Mitered (R/D = 1.5), 3 Weld (30 deg angle): ");
    table.count[5] = atoi(fgets(input, sizeof(input), stdin));
    printf("90 deg Elbow Mitered (R/D = 1.5), 4 Weld (22.5 deg angle): ");
    table.count[6] = atoi(fgets(input, sizeof(input), stdin));
    printf("90 deg Elbow Mitered (R/D = 1.5), 5 Weld (18 deg angle): ");
    table.count[7] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, All types (Standard Radius) (R/D = 1): ");
    table.count[8] = atoi(fgets(input, sizeof(input), stdin));
    printf("45 deg Elbow, All types (Long Radius) (R/D = 1.5): ");
    table.count[9] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow Mitered, 1 Weld (45 deg angle): ");
    table.count[10] = atoi(fgets(input, sizeof(input), stdin));
    printf("45 deg Elbow Mitered, 2 Weld (45 deg angle): ");
    table.count[11] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg bend, Screwed (Standard Radius) (R/D = 1): ");
    table.count[12] = atoi(fgets(input, sizeof(input), stdin));
    printf("180 deg bend, Flanged/Welded (Standard Radius) (R/D = 1): ");
    table.count[13] = atoi(fgets(input, sizeof(input), stdin));
    printf("180 deg bend, All types (Long Radius) (R/D = 1.5): ");
    table.count[14] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee (used as elbow), Screwed (Standard Radius) (R/D = 1): ");
    table.count[15] = atoi(fgets(input, sizeof(input), stdin));
    printf("Tee (used as elbow), Screwed (Long Radius): ");
    table.count[16] = atoi(fgets(input, sizeof(input), stdin));
    printf("Tee (used as elbow), Flanged/Welded (Standard Radius) (R/D = 1): ");
    table.count[17] = atoi(fgets(input, sizeof(input), stdin));
    printf("Tee (used as elbow), Stub-in-type Branch: ");
    table.count[18] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee (Run Through), Screwed: ");
    table.count[19] = atoi(fgets(input, sizeof(input), stdin));
    printf("Tee (Run Through), Flanged/Welded: ");
    table.count[20] = atoi(fgets(input, sizeof(input), stdin));
    printf("Tee (Run Through), Stub-in-type Branch: ");
    table.count[21] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Valves (Gate/ Ball/ Plug), Full Line Size (Beta = 1): ");
    table.count[22] = atoi(fgets(input, sizeof(input), stdin));
    printf("Valves (Gate/ Ball/ Plug), Reduced Trim (Beta = 0.9): ");
    table.count[23] = atoi(fgets(input, sizeof(input), stdin));
    printf("Valves (Gate/ Ball/ Plug), Reduced Trum (Beta = 0.8): ");
    table.count[24] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe Valve, Standard: ");
    table.count[25] = atoi(fgets(input, sizeof(input), stdin));
    printf("Globe Valve, Angle: ");
    table.count[26] = atoi(fgets(input, sizeof(input), stdin));
    printf("Diaphragm Valve, Dam Type: ");
    table.count[27] = atoi(fgets(input, sizeof(input), stdin));
    printf("Butterfly Valve: ");
    table.count[28] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Check Valves, Lift: ");
    table.count[29] = atoi(fgets(input, sizeof(input), stdin));
    printf("Check Valves, Swing: ");
    table.count[30] = atoi(fgets(input, sizeof(input), stdin));
    printf("Check Valves, Tilting-disk: ");
    table.count[31] = atoi(fgets(input, sizeof(input), stdin));
    
    return table;
}

double TwoKCalcK(double Re, double d, double k1, double kinf)
{
    double term1 = 0.0;
    double term2 = 0.0;
    
    term1 = k1/Re;
    
    term2 = 1/(d);
    term2 = 1 + (term2);
    term2 = kinf*(term2);
    
    return term1 + term2;
}

double TwoKCalcH(int count, double K, double u)
{
    double h = 0.0;
    
    h = pow(u, 2);
    h = (h)/(2*g);
    h = K*(h);
    
    h = count*(h);
    
    return h;
}

double TwoKCalcP(double h, double rho)
{
    double P = 0.0;
    
    P = rho*g;
    P = (P)*h;
    
    return P;
}

TwoKFittings TwoKFinalTable(TwoKFittings data, double rho, double u, double d, double mu, double Impd, double *Re)
{
    double ReyNum = 0.0;
    *Re = ReyNoCalc(rho, u, d, mu);
    
    ReyNum = (*Re);
    
    for(int i = 0; i < 32; ++i)
    {
        data.headloss[i] = TwoKCalcH(data.count[i], TwoKCalcK(ReyNum, Impd, data.k1[i], data.kinf[i]), u);
        data.dP_f[i] = TwoKCalcP(data.headloss[i], rho);
    }
    return data;
}

void TwoKDisplay(TwoKFittings data, double rho, double u, double d, double mu, double Re, double TotalP, double TotalH)
{
    int i = 0;
    
    printf("Inputted parameters:\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tkg/m3\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n\n", mu*1000);
    
    printf("Internal pipe diameter:\n");
    printf("d =\t%.3f\tmm\n\n", d*1000);
    
    printf("Calculated parameters:\n");
    printf("Reynold's number:\n");
    printf("Re =\t%.0f\t[ ]\n", Re);
    
    printf("Total head loss:\n");
    printf("total =\t%.3f\tm\n\n", TotalH);
    printf("Total pressure loss:\n");
    printf("total =\t%.3f\tPa\n\n", TotalP);
    
    printf("K = \\frac{ K_1 }{ \\textrm{Re} } + K_{ \\infty }\\left(1 + \\frac{1}{D}\\right)\n");
    printf("h_L = K \\frac{u^2}{2*g}\n");
    printf("dP_f = \\rho g h_L\n\n");
    
    printf("Fitting\tK_1\tK_inf\tCount\tHead loss (m)\tPressure Loss (Pa)\n");
    i = 0;
    printf("90 deg Elbow, Threaded (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Flanged/Welded (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, All types (Long Radius) (R/D = 1.5)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("90 deg Elbow Mitered (R/D = 1.5), 1 Weld (90 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow Mitered (R/D = 1.5), 2 Weld (45 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow Mitered (R/D = 1.5), 3 Weld (30 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow Mitered (R/D = 1.5), 4 Weld (22.5 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow Mitered (R/D = 1.5), 5 Weld (18 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("45 deg Elbow, All types (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("45 deg Elbow, All types (Long Radius) (R/D = 1.5)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("45 deg Elbow Mitered, 1 Weld (45 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("45 deg Elbow Mitered, 2 Weld (45 deg angle)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("180 deg bend, Screwed (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("180 deg bend, Flanged/Welded (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("180 deg bend, All types (Long Radius) (R/D = 1.5)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("Tee (used as elbow), Screwed (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee (used as elbow), Screwed (Long Radius)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee (used as elbow), Flanged/Welded (Standard Radius) (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee (used as elbow), Stub-in-type Branch\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("Tee (Run Through), Screwed\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee (Run Through), Flanged/Welded\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee (Run Through), Stub-in-type Branch\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("Valves (Gate/ Ball/ Plug), Full Line Size (Beta = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Valves (Gate/ Ball/ Plug), Reduced Trim (Beta = 0.9)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Valves (Gate/ Ball/ Plug), Reduced Trum (Beta = 0.8)\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("Globe Valve, Standard\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Globe Valve, Angle\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Diaphragm Valve, Dam Type\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Butterfly Valve\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n\n", data.dP_f[i]);
    ++i;
    
    
    printf("Check Valves, Lift\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Check Valves, Swing\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Check Valves, Tilting-disk\t");
    printf("%i\t", data.k1[i]);
    printf("%.2f\t", data.kinf[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
}

void TwoK()
{
    double rho = 0.0;
    double u = 0.0;
    double d = 0.0;
    double mu = 0.0;
    double impd = 0.0;
    double Re = 0.0;
    
    double TotalP = 0.0;
    double TotalH = 0.0;
    
    TwoKFittings TwoKTable;
    
    // Initialising the struct
    for(int i = 0; i < 32; ++i)
    {
        TwoKTable.k1[i] = 0;
        TwoKTable.kinf[i] = 0.0;
        TwoKTable.count[i] = 0;
        TwoKTable.headloss[i] = 0.0;
        TwoKTable.dP_f[i] = 0.0;
    }
    
    //  Collecting data
    TwoKTable = TwoKVar(TwoKTable, &rho, &u, &d, &mu, &impd);
    
    //  Performing calculations
    TwoKTable = TwoKFinalTable(TwoKTable, rho, u, d, mu, impd, &Re);
    
    //  Calculating total head and pressure losses
    for(int i = 0; i < 32; ++i)
    {
        TotalH += TwoKTable.headloss[i];
        TotalP += TwoKTable.dP_f[i];
    }
    
    TwoKDisplay(TwoKTable, rho, u, d, mu, Re, TotalP, TotalH);
}
