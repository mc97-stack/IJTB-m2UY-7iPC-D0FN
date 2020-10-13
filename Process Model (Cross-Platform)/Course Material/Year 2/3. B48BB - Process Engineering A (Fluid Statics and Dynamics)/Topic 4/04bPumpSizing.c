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

#include "04bPumpSizing.h"

#define maxstrlen 128
#define g 9.80665

void PumpVar(double *Q, double *rho, double *Psat, double *SucVesselP, double *hs1, double *hs2, double *dPsuction, double *DisVesselP, double *hd1, double *hd2, double *dPdischarge, double *eta)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Fluid Properties:\n");
    printf("Volumetric flowrate (m3/s) = ");
    *Q = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid vapour pressure (kPa) = ");
    *Psat = atof(fgets(input, sizeof(input), stdin));
    *Psat = (*Psat)*1000;
    
    printf("\n");
    fflush(stdout);
    
    printf("Suction Side:\n");
    printf("Suction vessel Pressure (kPa) = ");
    *SucVesselP = atof(fgets(input, sizeof(input), stdin));
    *SucVesselP = (*SucVesselP)*1000;
    
    printf("Liquid level in Suction-side vessel (m) = ");
    *hs1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Liquid elevation above pump inlet (m) = ");
    *hs2 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid frictional head loss (m) = ");
    *dPsuction = atof(fgets(input, sizeof(input), stdin));
    printf("\n");
    fflush(stdout);
    
    printf("Discharge Side:\n");
    printf("Discharge vessel Pressure (kPa) = ");
    *DisVesselP = atof(fgets(input, sizeof(input), stdin));
    *DisVesselP = (*DisVesselP)*1000;
    
    printf("Liquid level in Dischrge-side vessel (m) = ");
    *hd1 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Liquid elevation above pump outlet (m) = ");
    *hd2 = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid frictional head loss (m) = ");
    *dPdischarge = atof(fgets(input, sizeof(input), stdin));
    //If pressure loss on discharge < pressure loss on suction, recommend moving pump closer to suction vessel
    printf("\n");
    fflush(stdout);
    printf("Pump Properties:\n");
    printf("Pump efficiency (0 pct - 100 pct) = ");
    *eta = atof(fgets(input, sizeof(input), stdin));
}

double PumpInitialCalc(double P, double rho, double h1, double h2, double fric)
{
    double head = 0.0;
    
    head = rho * g;
    head = P/(head);
    head = (head) + h1;
    head = (head) + h2;
    head = (head) - fric;
    
    return head;
}

double PumpNPSHCalc(double P, double Phat, double rho, double hs1, double hs2, double hfric)
{
    double NPSH = 0.0; //Net Positive Suction Head & Initialising
    
    NPSH = P - Phat;
    NPSH = (NPSH)/(rho*g);
    NPSH = (NPSH) + hs1;
    NPSH = (NPSH) + hs2;
    NPSH = (NPSH) - hfric;
    
    return NPSH;
}

double PumpHeadCalc(double hs, double hd)
{
    //Returns the pump head in metres
    return hd - hs;
}

double PumpPressureCalc(double rho, double dHp)
{
    double pressure = 0.0; //Pump pressure
    
    pressure = rho*g;
    pressure = (pressure)*dHp;
    
    return pressure;
}

double PumpPowerCalc(double dPp, double Q, double eta)
{
    //Returns the power power required to achieve the specified pressure drop
    //eta is the efficiency of the pump (Value between 0 and 1)
    double power = 0.0;
    
    power = dPp*Q;
    power = (power)/eta;
    return power;
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
void PumpSizing()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Pump Sizing Calculator\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        double Q = 0.0; // Volumetric flowrate
        double rho = 0.0; // Fluid density
        double Psat = 0.0; // Fluid Saturated Vapour Pressure
        double SuctionVessP = 0.0; // Pressure in suction side vessel
        double hs1 = 0.0; // Liquid level in suction side vessel
        double hs2 = 0.0; // Vertical elevation of fluid in pipe from vessel to pump
        double dPsuction = 0.0; // Suction side frictional pressure loss
        double DischargeVessP = 0.0; // Pressure in discharge side vessel
        double hd1 = 0.0; // Liquid level in discharge side vessel
        double hd2 = 0.0; // Vertical elevation of fluid in pipe from pump to discharge vessel
        double dPdischarge = 0.0; // Discharge side frictional pressure loss
        double eta = 0.0; // Pump efficiency
        
        double suctionhead = 0.0;
        double dischargehead = 0.0;
        double AvailNPSH = 0.0; //Available NPSH
        double pumphead = 0.0;
        double pumppower = 0.0;
        
        int whilcont = 0;
        
        //Data collection
        PumpVar(&Q, &rho, &Psat, &SuctionVessP, &hs1, &hs2, &dPsuction, &DischargeVessP, &hd1, &hd2, &dPdischarge, &eta);
        
        printf("Function returns:\n");
        printf("Fluid properties:\n");
        printf("Q = %.3f m3/s\n",Q);
        printf("rho = %.3f kg/m3\n", rho);
        printf("Psat = %.3f Pa\n\n", Psat);
        
        printf("Suction/ Discharge side properties:\n");
        printf("SuctionVessP = %.3f Pa\n", SuctionVessP);
        printf("hs1 = %.3f m\n", hs1);
        printf("hs2 = %.3f m\n", hs2);
        printf("dPsuction = %.3f m3/s\n", dPsuction);
        printf("DischargeVessP = %.3f Pa\n", DischargeVessP);
        printf("hd1 = %.3f m\n", hd1);
        printf("hd2 = %.3f m\n", hd2);
        printf("dPdischarge = %.3f m3/s\n\n", dPdischarge);
        
        printf("Pump characteristics:\n");
        printf("eta = %.1f pct \n\n", eta*100);
        
        //Data manipulation
            //Calculation of suction & discharge head
        suctionhead = PumpInitialCalc(SuctionVessP, rho, hs1, hs2, dPsuction);
        dischargehead = PumpInitialCalc(DischargeVessP, rho, hd1, hd2, dPdischarge);
        
        pumphead = PumpHeadCalc(suctionhead, dischargehead);
        
        printf("suctionhead = %.3f m\n", suctionhead);
        printf("dischargehead = %.3f m\n", dischargehead);
        printf("pumphead = %.3f m\n", pumphead);
        
            //Calculating Available NPSH
        AvailNPSH = PumpNPSHCalc(SuctionVessP, Psat, rho, hs1, hs2, dPsuction);
        
        printf("Available NPSH = %.1f m\n", AvailNPSH);
        printf("N.B. Check that this value is > Required NPSH from the manufacturer\n\n");
        
            //Calculating pump power
        pumppower = PumpPowerCalc(PumpPressureCalc(rho, pumphead), Q, eta);
        printf("Pump power at %.1f pct efficiency = %.3f\n", eta, pumppower);
        //Ask for file write (Remember while loop)
        //...
        //Continue function
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
    fflush(stdout);
}
