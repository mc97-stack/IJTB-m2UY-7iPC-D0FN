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
    final = (final) + state2.potenergy;
    
    initial = state1.enthalpy + state1.kinenergy;
    initial = (initial) + state1.potenergy;
    
    fluid = final - initial;
    
    inequality = fluid - process;
    
    return inequality;
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
        
        if(sysstate < 0.005){
            printf("This unit operation is operating at steady-state conditions.\n");
        }else{
            printf("This unit operation is operating at unsteady-state conditions.\n");
        }
        
        //Ask for file write (Remember while loop)
        
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
