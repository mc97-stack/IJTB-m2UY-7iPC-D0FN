//
//  02cOpenFirstLaw.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "B48BC_T2.h"
#include "02cOpenFirstLaw.h"

#define maxstrlen 128

void OpenFirstLawVarProc(double *q, double *w_s)
{
    char input[maxstrlen];
    
    printf("Specific process heat (kJ/ kmol) = ");
    *q = atof(fgets(input, sizeof(input), stdin));
    
    printf("Specific shaft work (kJ/ kmol) = ");
    *w_s = atof(fgets(input, sizeof(input), stdin));
    
    fflush(stdout);
}

T2StateEnergy OpenFirstLawVar(int ins)
{
    char input[maxstrlen];
    
    double g = 9.80665;
    
    double u = 0.0;
    double z = 0.0;
    
    T2StateEnergy state;
    // Initialising the struct
    state.enthalpy = 0.0;
    state.kinenergy = 0.0;
    state.potenergy = 0.0;
    
    printf("Stream enthalpy at state %i (kJ/kmol) = ", ins);
    state.enthalpy = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid velocity at state %i (m/s) = ", ins);
    u = atof(fgets(input, sizeof(input), stdin));
    u = pow(u, 2);
    state.kinenergy = u/2;
    
    printf("Vertical elevation at state %i above reference point (m) = ", ins);
    z = atof(fgets(input, sizeof(input), stdin));
    state.potenergy = z*g;
    
    fflush(stdout);
    return state;
}

double OpenFirstLawCalc(double q, double w_s, T2StateEnergy state1, T2StateEnergy state2)
{
    double inequality = 0.0;
    
    double initial = 0.0;
    double final = 0.0;
    double fluid = 0.0;
    double process = 0.0;
    
    process = q + w_s;
    
    final = state2.enthalpy + state2.kinenergy;
    printf("final = %f\n", final);
    final = (final) + state2.potenergy;
    printf("final = %f\n\n", final);
    
    initial = state1.enthalpy + state1.kinenergy;
    printf("initial = %f\n", initial);
    initial = (initial) + state1.potenergy;
    printf("initial = %f\n\n", initial);
    
    fluid = final - initial;
    
    inequality = fluid - process;
    
    return inequality;
}

void InitialValue(T2StateEnergy state, double *u, double *z)
{
    *u = state.kinenergy *2;
    *u = (*u)*1000;
    *u = pow((*u), 0.5);
    
    *z = state.potenergy*1000;
    *z = (*z)/(9.80665);
}

void OpenFirstLawWrite(T2StateEnergy state1,T2StateEnergy state2, double q, double w_s, double sysstate)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
    //Set file name as timestamp + First Law Equation applied to Open Systems
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
    
    strcat(filename, " First Law Results");
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
    double u1 = 0.0;
    double u2 = 0.0;
    double z1 = 0.0;
    double z2 = 0.0;
    InitialValue(state1, &u1, &z1);
    InitialValue(state2, &u2, &z2);
    
    fprintf(fp, "_First_Law_Applied_to_Open_Systems_\n");
    fprintf(fp, "Assuming the fluid is incompressible. \n");
    fprintf(fp, "g =\t9.80665\tm/s2\n\n");
    fprintf(fp, "\tInput parameters:\n");
    fprintf(fp, "Initial fluid enthalpy:\n");
    fprintf(fp, "h1 =\t%.3f\tkJ/kg\n", state1.enthalpy);
    fprintf(fp, "Final fluid enthalpy:\n");
    fprintf(fp, "h2 =\t%.3f\tkJ/kg\n", state2.enthalpy);
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
    fprintf(fp, "Specific shaft work:\n");
    fprintf(fp, "w =\t%.3f\tkJ/kg\n", w_s);
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "System state =\t%.3f\tkJ/kg\n", sysstate);
    if(fabs(sysstate) < 0.005){
        fprintf(fp, "This unit operation is operating at steady-state conditions.\n");
    }else{
        fprintf(fp, "This unit operation is operating at unsteady-state conditions.\n");
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void OpenFirstLawWriteCheck(T2StateEnergy state1,T2StateEnergy state2, double q, double w_s, double sysstate)
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
                OpenFirstLawWrite(state1, state2, q, w_s, sysstate);
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

void OpenFirstLaw()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 1;
    printf("First Law for Open Systems\nN.B. This is very similar to B48BB's Steady-flow energy equation but with some improvements\n\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        double q = 0.0;
        double w_s = 0.0;
        
        double sysstate = 0.0;
        
        int whilcont = 0;
        
        T2StateEnergy state1;
        T2StateEnergy state2;
        
        // Initialising structs
        state1.enthalpy = 0.0;
        state1.kinenergy = 0.0;
        state1.potenergy = 0.0;
        state2.enthalpy = 0.0;
        state2.kinenergy = 0.0;
        state2.potenergy = 0.0;
        
        //Data collection
        OpenFirstLawVarProc(&q, &w_s);
        state1 = OpenFirstLawVar(1);
        state2 = OpenFirstLawVar(2);
        
        //Data manipulation
        sysstate = OpenFirstLawCalc(q, w_s, state1, state2);
        
        if(fabs(sysstate) < 0.005){
            printf("This unit operation is operating at steady-state conditions.\n");
        }else{
            printf("This unit operation is operating at unsteady-state conditions.\n");
        }
        
        //Ask for file write (Remember while loop)
        OpenFirstLawWriteCheck(state1, state2, q, w_s, sysstate);
        
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
