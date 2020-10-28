//
//  03dbthreeK.c
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
#include "03dThreeK.h"
#include "02dReyNo.h"

#define maxstrlen 128
#define g 9.80665

ThreeKFittings ThreeKData(ThreeKFittings input)
{
    //  Setting k_1 values
    input.k1[0] = 800;
    input.k1[1] = 800;
    input.k1[2] = 800;
    input.k1[3] = 800;
    input.k1[4] = 800;
    input.k1[5] = 800;
    input.k1[6] = 1000;
    input.k1[7] = 800;
    input.k1[8] = 800;
    input.k1[9] = 500;
    input.k1[10] = 500;
    input.k1[11] = 500;
    input.k1[12] = 500;
    input.k1[13] = 1000;
    input.k1[14] = 1000;
    input.k1[15] = 1000;
    input.k1[16] = 500;
    input.k1[17] = 800;
    input.k1[18] = 800;
    input.k1[19] = 1000;
    input.k1[20] = 200;
    input.k1[21] = 150;
    input.k1[22] = 100;
    input.k1[23] = 950;
    input.k1[24] = 1000;
    input.k1[25] = 1500;
    input.k1[26] = 500;
    input.k1[27] = 300;
    input.k1[28] = 300;
    input.k1[29] = 300;
    input.k1[30] = 300;
    input.k1[31] = 1000;
    input.k1[32] = 1500;
    input.k1[33] = 2000;
    
    //  Setting kinf values
    input.kinf[0] = 0.14;
    input.kinf[1] = 0.071;
    input.kinf[2] = 0.091;
    input.kinf[3] = 0.056;
    input.kinf[4] = 0.066;
    input.kinf[5] = 0.075;
    input.kinf[6] = 0.27;
    input.kinf[7] = 0.068;
    input.kinf[8] = 0.035;
    input.kinf[9] = 0.071;
    input.kinf[10] = 0.052;
    input.kinf[11] = 0.086;
    input.kinf[12] = 0.052;
    input.kinf[13] = 0.23;
    input.kinf[14] = 0.12;
    input.kinf[15] = 0.1;
    input.kinf[16] = 0.274;
    input.kinf[17] = 0.14;
    input.kinf[18] = 0.28;
    input.kinf[19] = 0.34;
    input.kinf[20] = 0.091;
    input.kinf[21] = 0.05;
    input.kinf[22] = 0.0;
    input.kinf[23] = 0.25;
    input.kinf[24] = 0.69;
    input.kinf[25] = 1.7;
    input.kinf[26] = 0.41;
    input.kinf[27] = 0.084;
    input.kinf[28] = 0.14;
    input.kinf[29] = 0.037;
    input.kinf[30] = 0.017;
    input.kinf[31] = 0.69;
    input.kinf[32] = 0.46;
    input.kinf[33] = 2.85;
    
    //  Setting k_d values (inches)
    input.Impkd[0] = 4.0;
    input.Impkd[1] = 4.2;
    input.Impkd[2] = 4.0;
    input.Impkd[3] = 3.9;
    input.Impkd[4] = 3.9;
    input.Impkd[5] = 4.2;
    input.Impkd[6] = 4.0;
    input.Impkd[7] = 4.1;
    input.Impkd[8] = 4.2;
    input.Impkd[9] = 4.2;
    input.Impkd[10] = 4.0;
    input.Impkd[11] = 4.0;
    input.Impkd[12] = 4.0;
    input.Impkd[13] = 4.0;
    input.Impkd[14] = 4.0;
    input.Impkd[15] = 4.0;
    input.Impkd[16] = 4.0;
    input.Impkd[17] = 4.0;
    input.Impkd[18] = 4.0;
    input.Impkd[19] = 4.0;
    input.Impkd[20] = 4.0;
    input.Impkd[21] = 4.0;
    input.Impkd[22] = 0.0;
    input.Impkd[23] = 4.0;
    input.Impkd[24] = 4.0;
    input.Impkd[25] = 3.6;
    input.Impkd[26] = 4.0;
    input.Impkd[27] = 3.9;
    input.Impkd[28] = 4.0;
    input.Impkd[29] = 3.9;
    input.Impkd[30] = 3.5;
    input.Impkd[31] = 4.9;
    input.Impkd[32] = 4.0;
    input.Impkd[33] = 3.8;
    
    //  Setting k_d values (mm)
    input.Metkd[0] = 10.6;
    input.Metkd[1] = 11.1;
    input.Metkd[2] = 10.6;
    input.Metkd[3] = 10.3;
    input.Metkd[4] = 10.3;
    input.Metkd[5] = 11.1;
    input.Metkd[6] = 10.6;
    input.Metkd[7] = 10.8;
    input.Metkd[8] = 11.1;
    input.Metkd[9] = 11.1;
    input.Metkd[10] = 10.6;
    input.Metkd[11] = 10.6;
    input.Metkd[12] = 10.6;
    input.Metkd[13] = 10.6;
    input.Metkd[14] = 10.6;
    input.Metkd[15] = 10.6;
    input.Metkd[16] = 10.6;
    input.Metkd[17] = 10.6;
    input.Metkd[18] = 10.6;
    input.Metkd[19] = 10.6;
    input.Metkd[20] = 10.6;
    input.Metkd[21] = 10.6;
    input.Metkd[22] = 0.0;
    input.Metkd[23] = 10.6;
    input.Metkd[24] = 10.6;
    input.Metkd[25] = 9.5;
    input.Metkd[26] = 10.6;
    input.Metkd[27] = 10.3;
    input.Metkd[28] = 10.6;
    input.Metkd[29] = 10.3;
    input.Metkd[30] = 9.2;
    input.Metkd[31] = 12.9;
    input.Metkd[32] = 10.6;
    input.Metkd[33] = 10.0;
    
    return input;
}

ThreeKFittings ThreeKVariable(ThreeKFittings table, double *DN, double *rho, double *u, double *d, double *mu)
{
    char input[maxstrlen];  // Variable used to store keyboard input.
    
    //  Loading in the 3K database
    table = ThreeKData(table);
    
    //  Getting variables to calculate Reynolds number
    *rho = inputDouble(0, "fluid density", "kg/m3");
    
    *u = inputDouble(0, "average fluid velocity", "m/s");
    
    *d = inputDouble(0, "internal pipe diameter", "mm");
    
    *mu = inputDouble(0, "fluid viscosity", "cP");
    *mu = (*mu)*0.001; //Conversion (cP to Pa.s)
    
    int check = 0;
    
    check = 1;
    while(check == 1){
        printf("Diameter Nominal (mm) = DN");
        *DN = atoi(fgets(input, sizeof(input), stdin));
        
        // Check that Nominal pipe size is smaller than internal diameter
        if((*DN) < (*d)){
            // Pipe internal diameter is bigger than DN size. Subroutine allowed to proceed
            check = 0;
        }else{
            // DN size is bigger than pipe internal diameter. Not possible.
            printf("Given diameter nominal exceeds internal pipe diameter. Please re-enter DN size.\n");
        }
    }
    *d = (*d)*0.001; //Conversion (mm to m)
    
    printf("90 deg Elbow, Threaded, Standard Radius (R/D = 1): ");
    table.count[0] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Threaded, Long Radius (R/D = 1): ");
    table.count[1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Standard Radius (R/D = 1): ");
    table.count[2] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 2): ");
    table.count[3] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 4): ");
    table.count[4] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 6): ");
    table.count[5] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Mitered, 1 weld 90 deg: ");
    table.count[6] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Mitered, 2 weld 45 deg: ");
    table.count[7] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Mitered, 3 weld 30 deg: ");
    table.count[8] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Threaded, Standard Radius (R/D = 1): ");
    table.count[9] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Threaded, Long Radius (R/D = 1.5): ");
    table.count[10] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Mitered, 1 weld 45 deg: ");
    table.count[11] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Mitered, 2 weld 22.5 deg: ");
    table.count[12] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg Bend, threaded, close-return (R/D = 1): ");
    table.count[13] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg Bend, threaded, flanged (R/D = 1): ");
    table.count[14] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg Bend, threaded, All types (R/D = 1.5): ");
    table.count[15] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, threaded (R/D = 1): ");
    table.count[16] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, threaded (R/D = 1.5): ");
    table.count[17] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, flanged (R/D = 1): ");
    table.count[18] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, stub-in branch: ");
    table.count[19] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Run-through, threaded (R/D = 1): ");
    table.count[20] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Run-through, flanged (R/D = 1): ");
    table.count[21] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Run-through, stub-in branch: ");
    table.count[22] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Angle valve, 45 deg, full line size \\beta = 1: ");
    table.count[23] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Angle valve, 90 deg, full line size \\beta = 1: ");
    table.count[24] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve, standard, \\beta = 1: ");
    table.count[25] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve, branch flow: ");
    table.count[26] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve, straight through: ");
    table.count[27] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve, three-way (flow through): ");
    table.count[28] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve, standard, \\beta = 1: ");
    table.count[29] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve, standard, \\beta = 1: ");
    table.count[30] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Diaphragm valve, dam type: ");
    table.count[31] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("N.B. V_{min} = 35\\left(\\rho\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    printf("Swing check valve Type: Vmin = 40: ");
    table.count[32] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("N.B. V_{min} = 40\\left(\\rho\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    printf("Lift check valve, Type: Vmin = 40: ");
    table.count[33] = atoi(fgets(input, sizeof(input), stdin));
    
    return table;
}

double ThreeKCalculateK(double Re, double DN, int k1, double kinf, double kd)
{
    double K = 0.0;
    double term1 = 0.0;
    double term2 = 0.0;
    
    term1 = k1/Re;
    
    term2 = pow(DN, 0.3);
    term2 = kd/(term2);
    term2 = 1 + (term2);
    term2 = kinf*(term2);
    
    K = term1 + term2;
    
    return K;
}

double ThreeKCalculateHead(double count, double K, double u)
{
    double hf = 0.0;
    
    hf = pow(u, 2);
    hf = (hf)/(2 * g);
    hf = K * (hf);
    
    hf = count*(hf);
    
    return hf;
}

double ThreeKCalculatePLoss(double h, double rho)
{
    double P = 0.0;
    
    P = rho*g;
    P = (P)*h;
    
    return P;
}

ThreeKFittings ThreeKFinalTable(ThreeKFittings data, double rho, double u, double d, double mu, double DN, double *Re)
{
    double ReyNo = 0.0;
    
    *Re = ReyNoCalculation(rho, u, d, mu);
    ReyNo = (*Re);
    
    for(int i = 0; i < 34; ++i){
        data.headloss[i] = ThreeKCalculateHead(data.count[i], ThreeKCalculateK(ReyNo, DN, data.k1[i], data.kinf[i], data.Metkd[i]), u);
        data.dP_f[i] = ThreeKCalculatePLoss(data.headloss[i], rho);
    }
    
    return data;
}

void ThreeKDisplay(ThreeKFittings data, double rho, double u, double d, double mu, double Re, double DN, double TotalH, double TotalP)
{
    int i = 0;
    
    printf("Inputted parameters.\n");
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tkg/m3\n", u);
    printf("Fluid viscosity:\n");
    printf("mu =\t%.3f\tcP\n\n", mu*1000);
    
    printf("Internal pipe diameter:\n");
    printf("d =\t%.3f\tmm\n", d*1000);
    printf("Diameter Nominal:\n");
    printf("DN\t%.0f\t(mm)\n\n", DN);
    
    printf("Reynold's number:\n");
    printf("Re =\t%.0f\t[ ]\n\n", Re);
    
    printf("Total head loss:\n");
    printf("total =\t%.3f\tm\n\n", TotalH);
    printf("Total pressure loss:\n");
    printf("total =\t%.3f\tPa\n\n", TotalP);
    
    printf("K = \\frac{ K_1 }{ \\textrm{Re} } + K_{ \\infty }\\left(1 + \\frac{K_d}{D_n^{0.3}}\\right)\n");
    printf("h_L = K \\frac{u^2}{2*g}\n");
    printf("Fitting\tK_1\tK_inf\tK_d (in^{0.3})\tK_d (mm^{0.3})\tCount\tHead loss (m)\tdP_f (Pa)");
    
    i = 0;
    printf("90 deg Elbow, Threaded, Standard Radius (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Threaded, Long Radius (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Flanged or Welded, Standard Radius (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 2)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 4)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 6)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Mitered, 1 weld 90 deg\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Mitered, 2 weld 45 deg\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("90 deg Elbow, Mitered, 3 weld 30 deg\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("45 deg Elbow, Threaded, Standard Radius (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("45 deg Elbow, Threaded, Long Radius (R/D = 1.5)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("45 deg Elbow, Mitered, 1 weld 45 deg\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("45 deg Elbow, Mitered, 2 weld 22.5 deg\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("180 deg Bend, threaded, close-return (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("180 deg Bend, threaded, flanged (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("180 deg Bend, threaded, All types (R/D = 1.5)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Through-branch as an Elbow, threaded (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Through-branch as an Elbow, threaded (R/D = 1.5)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Through-branch as an Elbow, flanged (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Through-branch as an Elbow, stub-in branch\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Run-through, threaded (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Run-through, flanged (R/D = 1)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Tee Run-through, stub-in branch\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Angle valve, 45 deg, full line size \\beta = 1\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Angle valve, 90 deg, full line size \\beta = 1\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Globe valve, standard, \\beta = 1\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Plug valve, branch flow\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Plug valve, straight through\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Plug valve, three-way (flow through)\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Gate valve, standard, \\beta = 1\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Ball valve, standard, \\beta = 1\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Diaphragm valve, dam type\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\n", data.dP_f[i]);
    ++i;
    
    printf("Swing check valve\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\t", data.dP_f[i]);
    printf("N.B. V_{min} = 35\\left(\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    ++i;
    
    printf("Lift check valve\t");
    printf("%i\t", data.k1[i]);
    printf("%.3f\t", data.kinf[i]);
    printf("%.1f\t", data.Impkd[i]);
    printf("%.1f\t", data.Metkd[i]);
    printf("%i\t", data.count[i]);
    printf("%.3f\t", data.headloss[i]);
    printf("%.3f\t", data.dP_f[i]);
    printf("N.B. V_{min} = 40\\left(\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
}

void ThreeKWrite(ThreeKFittings data, double rho, double u, double d, double mu, double Re, double DN, double TotalH, double TotalP)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + 3K Results
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
    
    strcat(filename, " 3K Results");
    //printf("File name: \"%s\"\n", filename);
    
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
    fprintf(fp, "_Pressure_Loss_Through_Pipe_Fittings_(3K_Method)_Results_\n");
    
    //Write to file
    int i = 0;
    
    fprintf(fp, "Inputted parameters.\n");
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid velocity:\n");
    fprintf(fp, "u =\t%.3f\tkg/m3\n", u);
    fprintf(fp, "Fluid viscosity:\n");
    fprintf(fp, "mu =\t%.3f\tcP\n\n", mu*1000);
    
    fprintf(fp, "Internal pipe diameter:\n");
    fprintf(fp, "d =\t%.3f\tmm\n", d*1000);
    fprintf(fp, "Diameter Nominal:\n");
    fprintf(fp, "DN\t%.0f\t(mm)\n\n", DN);
    
    fprintf(fp, "Reynold's number:\n");
    fprintf(fp, "Re =\t%.0f\t[ ]\n\n", Re);
    
    fprintf(fp, "Total head loss:\n");
    fprintf(fp, "total =\t%.3f\tm\n\n", TotalH);
    fprintf(fp, "Total pressure loss:\n");
    fprintf(fp, "total =\t%.3f\tPa\n\n", TotalP);
    
    fprintf(fp, "K = \\frac{ K_1 }{ \\textrm{Re} } + K_{ \\infty }\\left(1 + \\frac{K_d}{D_n^{0.3}}\\right)\n");
    fprintf(fp, "h_L = K \\frac{u^2}{2*g}\n");
    fprintf(fp, "Fitting\tK_1\tK_inf\tK_d (in^{0.3})\tK_d (mm^{0.3})\tCount\tHead loss (m)\n");
    
    i = 0;
    fprintf(fp, "90 deg Elbow, Threaded, Standard Radius (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Threaded, Long Radius (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Flanged or Welded, Standard Radius (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Flanged or Welded, Long Radius (R/D = 2)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Flanged or Welded, Long Radius (R/D = 4)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Flanged or Welded, Long Radius (R/D = 6)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Mitered, 1 weld 90 deg\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Mitered, 2 weld 45 deg\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "90 deg Elbow, Mitered, 3 weld 30 deg\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "45 deg Elbow, Threaded, Standard Radius (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "45 deg Elbow, Threaded, Long Radius (R/D = 1.5)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "45 deg Elbow, Mitered, 1 weld 45 deg\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "45 deg Elbow, Mitered, 2 weld 22.5 deg\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "180 deg Bend, threaded, close-return (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "180 deg Bend, threaded, flanged (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "180 deg Bend, threaded, All types (R/D = 1.5)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Through-branch as an Elbow, threaded (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Through-branch as an Elbow, threaded (R/D = 1.5)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Through-branch as an Elbow, flanged (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Through-branch as an Elbow, stub-in branch\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Run-through, threaded (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Run-through, flanged (R/D = 1)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Tee Run-through, stub-in branch\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Angle valve, 45 deg, full line size \\beta = 1\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Angle valve, 90 deg, full line size \\beta = 1\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Globe valve, standard, \\beta = 1\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Plug valve, branch flow\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Plug valve, straight through\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Plug valve, three-way (flow through)\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Gate valve, standard, \\beta = 1\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Ball valve, standard, \\beta = 1\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Diaphragm valve, dam type\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\n", data.dP_f[i]);
    ++i;
    
    fprintf(fp, "Swing check valve\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\t", data.dP_f[i]);
    fprintf(fp, "N.B. V_{min} = 35\\left(\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    ++i;
    
    fprintf(fp, "Lift check valve\t");
    fprintf(fp, "%i\t", data.k1[i]);
    fprintf(fp, "%.3f\t", data.kinf[i]);
    fprintf(fp, "%.1f\t", data.Impkd[i]);
    fprintf(fp, "%.1f\t", data.Metkd[i]);
    fprintf(fp, "%i\t", data.count[i]);
    fprintf(fp, "%.3f\t", data.headloss[i]);
    fprintf(fp, "%.3f\t", data.dP_f[i]);
    fprintf(fp, "N.B. V_{min} = 40\\left(\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ThreeKWriteSwitch(ThreeKFittings data, double rho, double u, double d, double mu, double Re, double DN, double TotalH, double TotalP)
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
                ThreeKWrite(data, rho, u, d, mu, Re, DN, TotalH, TotalP);
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

void ThreeK()
{
    double rho = 0.0;
    double u = 0.0;
    double d = 0.0;
    double mu = 0.0;
    double DN = 0.0;
    double Re = 0.0;
    
    double TotalH = 0.0;
    double TotalP = 0.0;
    
    printf("Source: https://neutrium.net/fluid-flow/pressure-loss-from-fittings-3k-method/\n");
    static ThreeKFittings ThreeKTable;
    
    // Initialising all values in the struct
    for(int i = 0; i < 34; ++i){
        ThreeKTable.k1[i] = 0;
        ThreeKTable.kinf[i] = 0.0;
        ThreeKTable.Impkd[i] = 0.0;
        ThreeKTable.Metkd[i] = 0.0;
        ThreeKTable.count[i] = 0;
        ThreeKTable.headloss[i] = 0.0;
        ThreeKTable.dP_f[i] = 0.0;
    }
    
    //  Collecting data
    ThreeKTable = ThreeKVariable(ThreeKTable, &DN, &rho, &u, &d, &mu);
    printf("\n");
    
    //  Performing calculations
    ThreeKTable = ThreeKFinalTable(ThreeKTable, rho, u, d, mu, DN, &Re);
    
    for(int i = 0; i < 34; ++i)
    {
        TotalH += ThreeKTable.headloss[i];
        TotalP += ThreeKTable.dP_f[i];
    }
    
    //  Displaying results
    ThreeKDisplay(ThreeKTable, rho, u, d, mu, Re, DN, TotalH, TotalP);
    
    //  Writing results
    ThreeKWriteSwitch(ThreeKTable, rho, u, d, mu, Re, DN, TotalH, TotalP);
}
