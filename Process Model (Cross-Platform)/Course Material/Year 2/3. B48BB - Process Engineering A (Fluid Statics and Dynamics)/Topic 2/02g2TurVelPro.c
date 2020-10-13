//
//  02g2TurVelPro.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "02g2TurVelPro.h"

#define maxstrlen 128

void TurVelProVar(double *umax, double *d)
{
    char input[maxstrlen];
    
    double u = 0.0;
    
    printf("Average fluid velocity (m/s) = ");
    u = atof(fgets(input, sizeof(input), stdin));
    
    *umax = (49.0)/(60.0);
    *umax = (*umax) * u;
    
    printf("Pipe diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    *d = (*d) * 0.001;
    
    fflush(stdout);
}

double TurVelProCalc(double vmax, double r, double d, double *gen) 
{
    //Calculated using Prandtl's one-seventh law
    double bot = 0.0;
    double y = 0.0;
    double frac1 = 0.0;
    double frac2 = 0.0;
    double v_x = 0.0;
    
    bot = d/2;
    frac2 = (1.0)/(7.0);
    
    y = bot - r;
    frac1 = y/(bot);
    v_x = pow(frac1, frac2);
    *gen = v_x;
    
    v_x = vmax*(v_x);
    
    return v_x;
}

void TurVelProfCalc(double vmax, double d) 
{
    char display[maxstrlen];
    
    double interval = 0.0;
    double prad = 0.0;
    
    int whildisp = 0;
    
    int rows = 0;
    
    interval = 0.001;
    prad = d/2;
    
    rows = ((prad)/ (interval)) + 1;
    
    printf("%i rows required\n", rows); 
    double profile[rows][3];
    
    int i = 0;
    for(double r = 0.0; r < (prad + (interval/2)); r += interval)
    {
        profile[i][0] = r; //Displaying point radius
        profile[i][1] = TurVelProCalc(vmax, r, d, &profile[i][2]);
        //profile[i][3] = i + 1;
        ++i;
    }
    printf("%i rows successfully generated\n\n", i);
    
    whildisp = 1;
    while(whildisp == 1)
    {
        printf("Do you want to display the generated data? ");
        fgets(display, sizeof(display), stdin);
        switch(display[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                printf("Displaying data\n");
                printf("Inputted variables:\n");
                printf("d =\t%.1f\tmm\n", d*1000);
                printf("v_max =\t%.3f\tm/s\n\n", vmax);
                
                printf("r (m)\tv_x (m/s)\tv/v_max\n");
                int row = 0;
                int col = 0;
                for(row = 0; row < i; ++row)
                {
                    for(col = 0; col < 3; ++col)
                    {
                        printf("%.5f", profile[row][col]);
                        if(col == 2)
                        {
                            printf("\n");
                        }else{
                            printf("\t");
                        }
                    }
                }
                whildisp = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                whildisp = 0;
            break;
            default:
                printf("Input not recognised.\n");
            break;
        }
    }
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
void TurVelPro()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    printf("Prandtl's One-Seventh Law Velocity Profile\n");
    
    whilmain = 1;
    while(whilmain == 1)
    {
        //Variable declaration
        double vmax = 0;
        double d = 0;
        
        //Data collection
        TurVelProVar(&vmax, &d);
        //Data manipulation
        TurVelProfCalc(vmax, d);
        
        //Ask for file write (Remember while loop)
        //...
        //Continue function
        int whilcont = 1;
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
