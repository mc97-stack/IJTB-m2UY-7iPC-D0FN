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

void PumpWrite(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
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
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " Pump Sizing");
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

void PumpWriteCheck(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower)
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
