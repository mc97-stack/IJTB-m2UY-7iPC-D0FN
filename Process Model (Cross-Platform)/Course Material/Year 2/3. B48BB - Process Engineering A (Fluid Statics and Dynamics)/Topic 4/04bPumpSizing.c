//
//  04bPumpSizing.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 07/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "B48BB_T4.h"
#include "04bPumpSizing.h"

#define maxstrlen 128
#define g 9.80665

void PumpVar(double *Q, double *rho, double *Psat, double *NPSHr, double *eta)
{
    char input[maxstrlen];
    
    printf("Volumetric flowrate (m3/s) = ");
    *Q = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid vapour pressure (kPa) = ");
    *Psat = atof(fgets(input, sizeof(input), stdin));
    *Psat = (*Psat)*1000;
    
    printf("Required NPSH (m) = ");
    *NPSHr = atof(fgets(input, sizeof(input), stdin));
    
    printf("Pump efficiency (0 pct - 100 pct) = ");
    *eta = atof(fgets(input, sizeof(input), stdin));
    *eta = (*eta)*0.01; // Conversion to decimal
}

head PumpHeadVar(int type, head var)
{
    char input[maxstrlen];
    
    if(type == 1){
        printf("Suction head parameters\n");
    }
    if(type == 2){
        printf("Discharge head parameters\n");
    }
    
    if(type == 1){
        printf("Suction vessel pressure (kPa) = ");
    }
    if(type == 2){
        printf("Discharge vessel pressure (kPa) = ");
    }
    var.P = atof(fgets(input, sizeof(input), stdin));
    var.P = (var.P)*1000;
    
    if(type == 1){
        printf("Liquid level in Suction-side vessel (m) = ");
    }
    if(type == 2){
        printf("Liquid level in Discharge-side vessel (m) = ");
    }
    var.h1 = atof(fgets(input, sizeof(input), stdin));
    
    if(type == 1){
        printf("Liquid elevation above pump inlet (m) = ");
    }
    if(type == 2){
        printf("Liquid elevation above pump outlet (m) = ");
    }
    var.h2 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid frictional head loss (m) = ");
    var.hf = atof(fgets(input, sizeof(input), stdin));
    
    return var;
}

double HeadCalc(head var, double rho)
{
    double output = 0.0;
    
    output = rho*g;
    output = var.P/(output);
    
    output = (output) + var.h1;
    output = (output) + var.h2;
    output = (output) - var.hf;
    
    return output;
}

double NPSHCalc(head var, double Psat, double rho)
{
    double output = 0.0;
    
    output = rho*g;
    output = (var.P - Psat)/(output);
    
    output = (output) + var.h1;
    output = (output) + var.h2;
    output = (output) - var.hf;
    
    return output;
}

double PumpHeadCalc(double hs, double hd)
{
    return hd - hs;
}

double PumpPressureCalc(double rho, double hp)
{
    double pressure = 0.0;
    
    pressure = rho*g;
    pressure = (pressure)*hp;
    
    return pressure;
}

double PumpPower(double dP_p, double Q, double eta)
{
    double power = 0.0;
    
    power = dP_p * Q;
    power = (power)/eta;
    
    return power;
}

void PumpDisplay(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower)
{
    printf("Suction-side parameters.\n");
    printf("Suction vessel pressure:\n");
    printf("P =\t%.3f\tkPa\n", (suction.P)*0.001);
    printf("Liquid level in Suction-side vessel:\n");
    printf("h_s1 =\t%.3f\tm\n", suction.h1);
    printf("Liquid level above pump inlet:\n");
    printf("h_s2 =\t%.3f\tm\n", suction.h2);
    printf("Suction side frictional losses:\n");
    printf("h_f,s =\t%.3f\tm\n\n", suction.hf);
    
    printf("Discharge-side parameters.\n");
    printf("Discharge vessel pressure:\n");
    printf("P =\t%.3f\tkPa\n", (discharge.P)*0.001);
    printf("Liquid level in Discharge-side vessel:\n");
    printf("h_d1 =\t%.3f\tm\n", discharge.h1);
    printf("Liquid level above pump outlet:\n");
    printf("h_d2 =\t%.3f\tm\n", discharge.h2);
    printf("Discharge side frictional losses:\n");
    printf("h_f,d =\t%.3f\tm\n\n", discharge.hf);
    
    printf("Fluid-specific parameters\n");
    printf("Volmetric flowrate:\n");
    printf("Q =\t%.3f\tm3/s\n", Q);
    printf("Fluid density:\n");
    printf("rho =\t%.3f\tkg/m3\n", rho);
    printf("Fluid saturated vapour pressure:\n");
    printf("Psat =\t%.3f\tkPa\n\n", Psat*0.001);
    
    printf("Pump-specific parameters\n");
    printf("Required NPSH:\n");
    printf("NPSHr =\t%.2f\tm\n", NPSHr);
    printf("Available NPSH:\n");
    printf("NPSHa =\t%.2f\tm\n", NPSHa);
    printf("Pump efficiency:");
    printf("eta =\t%.1f\t%%\n\n", eta*100);
    
    printf("Pump head:\n");
    printf("phead =\t%.3f\tm\n", phead);
    printf("Pump pressure:\n");
    printf("dP_P =\t%.3f\tkPa\n", ppressure*0.001);
    printf("Pump power:\n");
    printf("W_h =\t%.3f\tkW\n", ppower*0.001);
}

void PumpSizing()
{
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    printf("Pump Sizing Calculator.\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        double Q = 0.0;
        double rho = 0.0;
        double Psat = 0.0;
        double NPSHr = 0.0;
        double eta = 0.0;
        
        double shead = 0.0;
        double dhead = 0.0;
        double NPSHa = 0.0;
        
        double phead = 0.0;
        double ppressure = 0.0;
        double ppower = 0.0;
        
        int whilcont = 0;
        
        head suction;
        head discharge;
        
        //Initialising struct values
        suction.P = 0.0;
        suction.h1 = 0.0;
        suction.h2 = 0.0;
        suction.hf = 0.0;
        
        discharge.P = 0.0;
        discharge.h1 = 0.0;
        discharge.h2 = 0.0;
        discharge.hf = 0.0;
        
        //  Data collection
        PumpVar(&Q, &rho, &Psat, &NPSHr, &eta);
        suction = PumpHeadVar(1, suction);
        discharge = PumpHeadVar(2, discharge);
        
        //  Calculations
        shead = HeadCalc(suction, rho);
        dhead = HeadCalc(discharge, rho);
        
        NPSHa = NPSHCalc(suction, Psat, rho);
        if(NPSHa > NPSHr){
            phead = PumpHeadCalc(shead, dhead);
            ppressure = PumpPressureCalc(rho, phead);
            ppower = PumpPower(ppressure, Q, eta);
            
            //  Display
            PumpDisplay(suction, discharge, Q, rho, Psat, NPSHr, NPSHa, eta, phead, ppressure, ppower);
        }else{
            printf("Insufficient Net Positive Suction Head. Ending calculations.\n");
        }
        //  Continue?
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
    }
}
