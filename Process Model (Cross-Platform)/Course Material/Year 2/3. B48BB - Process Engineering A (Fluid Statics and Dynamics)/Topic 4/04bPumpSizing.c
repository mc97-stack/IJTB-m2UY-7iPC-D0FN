//
//  04bPumpSizing.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 07/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Cusom header files
#include "System.h"
#include "B48BB_T4.h"
#include "04bPumpSizing.h"

#define maxstrlen 128
#define g 9.80665

void PumpVariable(double *Q, double *rho, double *Psat, double *NPSHr, double *eta)
{
    *Q = inputDouble(0, "volumetric flowrate", "m3/s");
    
    *rho = inputDouble(0, "fluid density", "kg/m3");
    
    *Psat = inputDouble(0, "fluid vapour pressure", "kPa");
    *Psat = (*Psat)*1000;
    
    *NPSHr = inputDouble(0, "required NPSH", "m");
    
    *eta = inputDouble(0, "pump efficiency", "0 %% - 100 %%");
    *eta = (*eta)*0.01; // Conversion to decimal
}

head PumpHeadVariable(int type, head var)
{
    switch(type)
    {
        case '1':
            printf("Suction head parameters\n");
            var.P = inputDouble(0, "suction vessel pressure", "kPa");
            var.P = (var.P)*1000;
            
            var.h1 = inputDouble(0, "liquid level in Suction-side vessel", "m");
            
            var.h2 = inputDouble(0, "liquid elevation above pump inlet", "m");
            break;
        case '2':
            printf("Discharge head parameters\n");
            var.P = inputDouble(0, "discharge vessel pressure", "kPa");
            var.P = (var.P)*1000;
            
            var.h1 = inputDouble(0, "Liquid level in Discharge-side vessel", "m");
            
            var.h2 = inputDouble(0, "liquid elevation above pump outlet", "m");
            break;
        default:
            printf("Type integer invalid\n");
            break;
    }
    var.hf = inputDouble(0, "fluid frictional head loss", "m");
    
    return var;
}

double HeadCalculation(head var, double rho)
{
    double output = 0.0;
    
    output = rho*g;
    output = var.P/(output);
    
    output = (output) + var.h1;
    output = (output) + var.h2;
    output = (output) - var.hf;
    
    return output;
}

double NPSHCalculation(head var, double Psat, double rho)
{
    double output = 0.0;
    
    output = rho*g;
    output = (var.P - Psat)/(output);
    
    output = (output) + var.h1;
    output = (output) + var.h2;
    output = (output) - var.hf;
    
    return output;
}

double PumpHeadCalculation(double hs, double hd)
{
    return hd - hs;
}

double PumpPressureCalculation(double rho, double hp)
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
    fflush(stdout);
}

void PumpWrite(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Pump Sizing
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
    
    strcat(filename, " Pump Sizing");
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
    fprintf(fp, "_Hydraulic_Diameter_Results_\n");
    
    //Write to file
    fprintf(fp, "Suction-side parameters.\n");
    fprintf(fp, "Suction vessel pressure:\n");
    fprintf(fp, "P =\t%.3f\tkPa\n", (suction.P)*0.001);
    fprintf(fp, "Liquid level in Suction-side vessel:\n");
    fprintf(fp, "h_s1 =\t%.3f\tm\n", suction.h1);
    fprintf(fp, "Liquid level above pump inlet:\n");
    fprintf(fp, "h_s2 =\t%.3f\tm\n", suction.h2);
    fprintf(fp, "Suction side frictional losses:\n");
    fprintf(fp, "h_f,s =\t%.3f\tm\n\n", suction.hf);
    
    fprintf(fp, "Discharge-side parameters.\n");
    fprintf(fp, "Discharge vessel pressure:\n");
    fprintf(fp, "P =\t%.3f\tkPa\n", (discharge.P)*0.001);
    fprintf(fp, "Liquid level in Discharge-side vessel:\n");
    fprintf(fp, "h_d1 =\t%.3f\tm\n", discharge.h1);
    fprintf(fp, "Liquid level above pump outlet:\n");
    fprintf(fp, "h_d2 =\t%.3f\tm\n", discharge.h2);
    fprintf(fp, "Discharge side frictional losses:\n");
    fprintf(fp, "h_f,d =\t%.3f\tm\n\n", discharge.hf);
    
    fprintf(fp, "Fluid-specific parameters\n");
    fprintf(fp, "Volmetric flowrate:\n");
    fprintf(fp, "Q =\t%.3f\tm3/s\n", Q);
    fprintf(fp, "Fluid density:\n");
    fprintf(fp, "rho =\t%.3f\tkg/m3\n", rho);
    fprintf(fp, "Fluid saturated vapour pressure:\n");
    fprintf(fp, "Psat =\t%.3f\tkPa\n\n", Psat*0.001);
    
    fprintf(fp, "Pump-specific parameters\n");
    fprintf(fp, "Required NPSH:\n");
    fprintf(fp, "NPSHr =\t%.2f\tm\n", NPSHr);
    fprintf(fp, "Available NPSH:\n");
    fprintf(fp, "NPSHa =\t%.2f\tm\n", NPSHa);
    fprintf(fp, "Pump efficiency:");
    fprintf(fp, "eta =\t%.1f\t%%\n\n", eta*100);
    
    fprintf(fp, "Pump head:\n");
    fprintf(fp, "phead =\t%.3f\tm\n", phead);
    fprintf(fp, "Pump pressure:\n");
    fprintf(fp, "dP_P =\t%.3f\tkPa\n", ppressure*0.001);
    fprintf(fp, "Pump power:\n");
    fprintf(fp, "W_h =\t%.3f\tkW\n", ppower*0.001);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void PumpWriteSwitch(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower)
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

void PumpSizing()
{
    int whilmain = 0;
    printf("Pump Sizing Calculator.\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        head suction = {0.0};   // Struct used to store the variables related to the suction head.
        head discharge = {0.0}; // Struct used to store the variables related to the discharge head.
        double shead = 0.0;     // Suction head.
        double dhead = 0.0;     // Discharge head.
        double NPSHa = 0.0;     // Net Positive Suction Head (NPSH) available.
        double phead = 0.0;     // Pump head.
        double ppressure = 0.0; // Pressure 'drop'(sic) through pump. 
        double ppower = 0.0;    // Pump power requirement.
        
        double Q = 0.0;         // Volumetric flowrate.
        double rho = 0.0;       // Fluid density.
        double Psat = 0.0;      // Saturated vapour pressure.
        double NPSHr = 0.0;     // Pump required NPSH.
        double eta = 0.0;       // Pump efficiency.
        
            //  Variables for timing function
        struct timespec start, end;
        double elapsed = 0.0;
        
        //  Data collection
        PumpVariable(&Q, &rho, &Psat, &NPSHr, &eta);
        suction = PumpHeadVariable(1, suction);
        discharge = PumpHeadVariable(2, discharge);
        
        //  Running calculations
        clock_getres(CLOCK_MONOTONIC, &start);
        clock_gettime(CLOCK_MONOTONIC, &start);
        
        shead = HeadCalculation(suction, rho);
        dhead = HeadCalculation(discharge, rho);
        
        NPSHa = NPSHCalculation(suction, Psat, rho);
        if(NPSHa > NPSHr){
            phead = PumpHeadCalculation(shead, dhead);
            ppressure = PumpPressureCalculation(rho, phead);
            ppower = PumpPower(ppressure, Q, eta);
            
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            //  Display
            PumpDisplay(suction, discharge, Q, rho, Psat, NPSHr, NPSHa, eta, phead, ppressure, ppower);
            
            PumpWriteSwitch(suction, discharge, Q, rho, Psat, NPSHr, NPSHa, eta, phead, ppressure, ppower);
        }else{
            clock_getres(CLOCK_MONOTONIC, &end);
            clock_gettime(CLOCK_MONOTONIC, &end);

            elapsed = timer(start, end);

            printf("Calculations completed in %.6f seconds.\n", elapsed);
            
            printf("Insufficient Net Positive Suction Head. Ending calculations.\n");
        }
        //  Continue?
        whilmain = Continue(whilmain);
    }
}
