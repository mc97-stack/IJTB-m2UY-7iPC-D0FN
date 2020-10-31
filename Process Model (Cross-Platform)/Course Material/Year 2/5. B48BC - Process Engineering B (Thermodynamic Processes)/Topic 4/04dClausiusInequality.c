//
//  04dClausiusInequality.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 31/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "System.h"
#include "B48BC_T4.h"
#include "04dClausiusInequality.h"

#define maxstrlen 128

T4EntropyDef EntropyVariable(int i, T4EntropyDef data)
{
    printf("Please enter the following variables true at state %d.\n", i + 1);
    
    data.q[i] = inputDouble(0, "heat change", "kJ/kg");
    data.T[i] = inputDouble(0, "Average temperature", "deg C");
    data.T[i] = data.T[i] + 273.15;
    
    return data;
}

T4EntropyDef EntropyCalculation(int i, T4EntropyDef data)
{
    data.s[i] = (data.q[i])/(data.T[i]);
    return data;
}

double EntropyCalc(double q, double T)
{
    double s = 0.0;
    
    s = q/T;
    
    return s;
}

void EntropyDisplay(int imax, T4EntropyDef data)
{
    printf("_Clausius_Inequality_Results_\n");
    printf("q (kJ/kg)\tT (K)\ts (kJ/kg.K)\t\\sum_i\\frac{q_i}{T_i}\n");
    for(int i = 0; i < imax; ++i)
    {
        printf("%.3f\t", data.q[i]);
        printf("%.2f\t", data.T[i]);
        printf("%.3f\t", data.s[i]);
        printf("%.3f\n", data.sum[i]);
        if( i == (imax - 1))    // Testing for final element
        {
            if(data.sum[i] < 0)
            {
                printf("This process does not violate the second law of thermodynamics.\n");
            }else{
                if(data.sum[i] == 0)
                {
                    printf("This process is reversible.\n");
                }else{
                    printf("This process violates the second law of thermodynamics.\n");
                }
            }
        }
    }
}

void EntropyWrite(int imax, T4EntropyDef data)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Clausius Inequality Results
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
    
    strcat(filename, " Clausius Inequality Results");
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
    fprintf(fp, "_Clausius_Inequality_Results_\n");
    fprintf(fp, "q (kJ/kg)\tT (K)\ts (kJ/kg.K)\t\\sum_i\\frac{q_i}{T_i}\n");
    for(int i = 0; i < imax; ++i)
    {
        fprintf(fp, "%.3f\t", data.q[i]);
        fprintf(fp, "%.2f\t", data.T[i]);
        fprintf(fp, "%.3f\t", data.s[i]);
        fprintf(fp, "%.3f\n", data.sum[i]);
        if( i == (imax - 1))    // Testing for final element
        {
            if(data.sum[i] > 0)
            {
                fprintf(fp, "This process does not violate the second law of thermodynamics.\n");
            }else{
                if(data.sum[i] == 0)
                {
                    fprintf(fp, "This process is reversible.\n");
                }else{
                    fprintf(fp, "This process violates the second law of thermodynamics.\n");
                }
            }
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void EntropyWriteSwitch(int imax, T4EntropyDef data)
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
                EntropyWrite(imax, data);
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

void ClausiusInequality(void)
{
    int whilmain = 0;
    printf("Clausius Inequality Calculation\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        static T4EntropyDef data;
        
        //  Initialising all values in the struct
        for(int i = 0; i < 2500; ++i)
        {
            data.q[i] = 0.0;
            data.T[i] = 0.0;
            data.s[i] = 0.0;
        }
        clock_t timer = clock();
        int i = 0;
        int control = 0;
        control = 1;
        while(control == 1)
        {
            //  Data Collection
            data = EntropyVariable(i, data);
            //  Data Manipulation
            data = EntropyCalculation(i, data);
            
            for(int j = 0; j <= i; ++j)
            {
                data.sum[i] += data.s[j];
            }
            if(i == 2499)
            {
                // Last element has been reached. While loop is now broken.
                control = 0;
            }else{
                ++i;
                control = Continue(control);
            }
        }
        timer = clock() - timer;
        
        int calctime = 0;
        calctime = ((int)timer*1000)/CLOCKS_PER_SEC;
        printf("%d entries were made.\n", i);
        printf("Process completed in %d seconds and %d milliseconds.\n\n", calctime/1000, calctime%1000);
        
        //  Displaying results
        EntropyDisplay(i, data);
        
        //  Writing to File
        EntropyWriteSwitch(i, data);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
