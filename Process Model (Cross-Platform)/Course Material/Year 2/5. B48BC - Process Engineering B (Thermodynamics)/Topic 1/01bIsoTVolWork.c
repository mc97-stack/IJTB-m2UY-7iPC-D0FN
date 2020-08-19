//
//  01bIsoTVolWork.c
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BC_T1.h"
#include "IdealGasLaw.h"
#include "01bIsoTVolWork.h"

#define maxstrlen 128
#define R 8.31455

//Declaring global variables and allocating memory
    //Function Output

    //Calculation Variables

    //Miscellaneous Variables


void IsoTVolWorkVar(double *n, double *T, double *P1, double *P2, double *V1, double *V2, int method)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Moles of substance (kmol/s) = ");
    *n = atof(fgets(input, sizeof(input), stdin));
    
    *n = (*n) * 1000;
    
    printf("System temperature (deg C) = ");
    *T = atof(fgets(input, sizeof(input), stdin));
    
    *T = (*T)+273.15;
    
    if(method == 1){
        printf("Initial system volume (m3) = ");
        *V1 = atof(fgets(input, sizeof(input), stdin));
        
        printf("Final system volume (m3) = ");
        *V2 = atof(fgets(input, sizeof(input), stdin));
        
        *P1 = IdealPressure(*n, *T, *V1);
        *P2 = IdealPressure(*n, *T, *V2);
    }else{
        printf("Initial system pressure (kPa) = ");
        *P1 = atof(fgets(input, sizeof(input), stdin));
        *P1 = (*P1) * 1000;
        
        printf("Final system pressure (kPa) = ");
        *P2 = atof(fgets(input, sizeof(input), stdin));
        *P2 = (*P2) * 1000;
        
        *V1 = IdealVolume(*n, *P1, *T);
        *V2 = IdealVolume(*n, *P2, *T);
    }
    fflush(stdout);
}

double IsoTVolWorkV(double n, double T, double V1, double V2)
{
    double frac;
    double work;
    
    frac = V2/V1;
    
    work = log(frac);
    work = T*(work);
    work = n*R*(work);
    work = -1*(work);
    
    return work;
}

double IsoTVolWorkP(double n, double T, double P1, double P2) //No Memory allocation required - Remember to do it within your main function
{
    double frac;
    double work;
    
    frac = P2/P1;
    
    work = log(frac);
    work = T*(work);
    work = n*R*(work);
    
    return work;
}

void IsoTVolWorkPlot(double n, double T, double P1, double P2)
{
    double incr;
    
    int reso = 50;
    
    incr = P2 - P1;
    incr = (incr)/reso;
    
    double profile[reso + 1][4];
    
    int i = 0;
    profile[i][0] = P1;
    profile[i][1] = IdealVolume(n, T, profile[i][0]);
    profile[i][2] = 0; //No volume work done by definition at the initial state
    profile[i][3] = 0;
    
    for(i = 1; i < (reso + 1) ; ++i)
    {
        profile[i][0] = profile[i - 1][0] + incr;
        profile[i][1] = IdealVolume(n, T, profile[i][0]);
        profile[i][2] = 0.001*IsoTVolWorkP(n, T, profile[i - 1][0], profile[i][0]);
        profile[i][3] = profile[i - 1][3] + profile[i][2];
    }
    printf("%i rows generated.\n---\n", i);
    
    printf("System conditions:\n");
    printf("n = %f kmol/s\n", n*0.001);
    printf("T = %f deg C\n\n", T - 273.15);
    
    printf("P (kPa)\tV (m3)\tW_V (kW)\tW_V (kW)\n");
    int j = 0; //Number of columns
    
    for(i = 0; i < (reso + 1); ++i){
        for(j = 0; j < 4; ++j)
        {
            if(j == 0){
                printf("%.3f", 0.001*profile[i][j]);
            }
            if(j == 1){
                printf("%.3f", profile[i][j]);
            }
            if(j == 2 || j == 3){
                printf("%.3f", profile[i][j]);
            }
            if(j == 3){
                printf("\n");
            }else{
                printf("\t");
            }
        }
    }
    //return profile; //Return a 2D array
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
void IsoTVolWork()
{
    //Main Function
    char input[maxstrlen];
    
    int whilmain = 1;
    int whilmethod;
    printf("Isothermal Volume Work\n");
    
    while(whilmain == 1)
    {
        //Variable declaration
        double n = 0.0;
        double T = 0.0;
        double P1 = 0.0;
        double P2 = 0.0;
        double V1 = 0.0;
        double V2 = 0.0;
        
        int method = 0;
        
        //Data collection
        whilmethod = 1;
        while(whilmethod == 1)
        {
            printf("Please choose from the following methods of calculation:\n");
            printf("1. From Volume change\n");
            printf("2. From Pressure change\n");
            printf("Selection: ");
            fgets(input, sizeof(input), stdin);
            switch(input[0]){
                case '1':
                case 'V':
                case 'v':
                    method = 1;
                    whilmethod = 0;
                break;
                case '2':
                case 'P':
                case 'p':
                    method = 0;
                    whilmethod = 0;
                break;
                default:
                    printf("Input not Recognised\n");
                break;
            }
        }
        IsoTVolWorkVar(&n, &T, &P1, &P2, &V1, &V2, method);
        printf("\n Initial estimate for volume work:\n");
        //Data manipulation
        if(method == 1)
        {
            printf("Volume Work = %.3f kW\n", IsoTVolWorkV(n, T, V1, V2));
        }else{
            //  if(method == 0)
            printf("Volume Work = %.3f kW\n", IsoTVolWorkP(n, T, P1, P2));
        }
        
        if(method == 1)
        {
            //For the profile calculator, an input of pressure is required so converting V's to P's
            IsoTVolWorkPlot(n, T, IdealPressure(n, T, V1), IdealPressure(n, T, V2));
        }else{
            //  if(method == 0)
            IsoTVolWorkPlot(n, T, P1, P2);
        }
        
        //Ask for file write (Remember while loop)
        //...
        //Continue function
        int whilcont = 1;
        while(whilcont == 1)
        {
            printf("Do you want to continue? ");
            fgets(input, sizeof(input), stdin);
            switch(input[0])
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
