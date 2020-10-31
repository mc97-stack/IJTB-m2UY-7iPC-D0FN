//
//  04aThermalEfficiency.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/10/2020.
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
#include "04aThermalEfficiency.h"

#define maxstrlen 128

void ThermEffVariable(int method, double *wnet, double *qhot, double *qcold, double *Thot, double *Tcold)
{
    printf("Process terms.\n");
    if(method == 1)
    {
        *wnet = inputDouble(1, "net work", "kJ/kg");
    }
    if(method == 2)
    {
        *qcold = inputDouble(1, "total heat sent to cold reservoir", "kJ/kg");
    }
    if(method == 1 || method == 2)
    {
        *qhot = inputDouble(1, "total heat received from hot reservoir", "kJ/kg");
        printf("\nEquivalent Carnot cycle parameters.\n");
        *Thot = inputDouble(0, "hot reservoir temperature", "K");
        *Tcold = inputDouble(0, "cold reservoir temperature", "K");
    }
}

double ThermEffCalc1(double wnet, double qhot)
{
    double eta = 0.0;
    
    wnet = fabs(wnet);
    qhot = fabs(qhot);
    
    eta = wnet/qhot;
    
    return eta;
}

double ThermEffCalc2(double qhot, double qcold)
{
    double eta = 0.0;
    
    qhot = fabs(qhot);
    qcold = fabs(qcold);
    
    eta = qhot - qcold;
    eta = (eta)/qhot;
    
    return eta;
}

double ThermEffCarnotCalculation(double THot, double TCold)
{
    double eta = 0.0;
    
    eta = THot - TCold;
    eta = (eta)/(THot);
    
    return eta;
}

void ThermEffDisplay(int method, double wnet, double qhot, double qcold, double THot, double TCold, double eta, double etac)
{
    printf("_Thermal_Efficiency_Results_\n");
    printf("\tInput parameters:\n");
    if(method == 1)
    {
        printf("Specific net work:\n");
        printf("w_net =\t%.3f\tkJ/kg\n", wnet);
    }
    if(method == 2)
    {
        printf("Specific heat sent to cold reservoir:\n");
        printf("qcold =\t%.3f\tkJ/kg\n", qcold);
    }
    if(method == 1 || method == 2)
    {
        printf("Specific heat received from hot reservoir:\n");
        printf("qhot =\t%.3f\tkJ/kg\n\n", qhot);
        
        printf("Equivalent Carnot cycle parameters.\n");
        printf("Cold reservoir Temperature:\n");
        printf("T_cold =\t%.3f\tK\n", TCold);
        printf("Hot reservoir Temperature:\n");
        printf("T_hot =\t%.3f\tK\n\n", THot);
    }
    
    printf("\tOutput parameters:\n");
    printf("Thermal efficiency of process:\n");
    printf("eta =\t%.4f\t%%\n", eta);
    printf("Equivalent Carnot cycle thermal efficiency:\n");
    printf("eta_carnot =\t%.4f\t%%\n", etac);
    
    if(eta == etac)
    {
        printf("Your process is reversible\n");
    }else{
        if(eta < etac)
        {
            printf("Your process is irreversible\n");
        }else{
            printf("Your process violates the second law.\n");
        }
    }
}

void ThermEffWrite(int method, double wnet, double qhot, double qcold, double THot, double TCold, double eta, double etac)
{
    //Function variables
    char filename[maxstrlen];   // Variable used to store the file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + Thermal Efficiency Results
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
    
    strcat(filename, " Thermal Efficiency Results");
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
    fprintf(fp, "_Thermal_Efficiency_Results_\n");
    fprintf(fp, "\tInput parameters:\n");
    if(method == 1)
    {
        fprintf(fp, "Specific net work:\n");
        fprintf(fp, "w_net =\t%.3f\tkJ/kg\n", wnet);
    }
    if(method == 2)
    {
        fprintf(fp, "Specific heat sent to cold reservoir:\n");
        fprintf(fp, "qcold =\t%.3f\tkJ/kg\n", qcold);
    }
    if(method == 1 || method == 2)
    {
        fprintf(fp, "Specific heat received from hot reservoir:\n");
        fprintf(fp, "qhot =\t%.3f\tkJ/kg\n\n", qhot);
        
        fprintf(fp, "Equivalent Carnot cycle parameters.\n");
        fprintf(fp, "Cold reservoir Temperature:\n");
        fprintf(fp, "T_cold =\t%.3f\tK\n", TCold);
        fprintf(fp, "Hot reservoir Temperature:\n");
        fprintf(fp, "T_hot =\t%.3f\tK\n\n", THot);
    }
    
    fprintf(fp, "\tOutput parameters:\n");
    fprintf(fp, "Thermal efficiency of process:\n");
    fprintf(fp, "eta =\t%.4f\t%%\n", eta);
    fprintf(fp, "Equivalent Carnot cycle thermal efficiency:\n");
    fprintf(fp, "eta_carnot =\t%.4f\t%%\n", etac);
    
    if(eta == etac)
    {
        fprintf(fp, "Your process is reversible\n");
    }else{
        if(eta < etac)
        {
            fprintf(fp, "Your process is irreversible\n");
        }else{
            fprintf(fp, "Your process violates the second law.\n");
        }
    }
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void ThermEffWriteSwitch(int method, double wnet, double qhot, double qcold, double THot, double TCold, double eta, double etac)
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
                ThermEffWrite(method, wnet, qhot, qcold, THot, TCold, eta, etac);
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

void ThermalEfficiency(void)
{
    int whilmain = 0;
    printf("Thermal Efficiency\n");
    whilmain = 1;
    while(whilmain == 1)
    {
        //  Variable declaration
        char menu[maxstrlen];
        
        double wnet = 0.0;
        double qhot = 0.0;
        double qcold = 0.0;
        double Thot = 0.0;
        double Tcold = 0.0;
        double eta = 0.0;
        double etacarnot = 0.0;
        
        int method = 0;
        int control = 0;
        
        //  Data Collection
        control = 1;
        while(control == 1){
            printf("How do you want to calculate the process' thermal efficiency?\n");
            printf("1. Heat and work.\n2. Heat\nSelection [1, 2]: ");
            fgets(menu, sizeof(menu), stdin);
            switch(menu[0])
            {
                case '1':
                    method = 1;
                    control = 0;
                    break;
                case '2':
                    method = 2;
                    control = 0;
                    break;
                default:
                    printf("Please enter either '1' or '2'\n");
                    break;
            }
        }
        ThermEffVariable(method, &wnet, &qhot, &qcold, &Thot, &Tcold);
        
        //  Data Manipulation
        clock_t start, end;
        double timeTaken = 0.0;
        
        start = clock();
        
        if(method == 1)
        {
            eta = ThermEffCalc1(wnet, qhot);
        }
        if(method == 2)
        {
            eta = ThermEffCalc2(qhot, qcold);
        }
        if(method == 1 || method == 2)
        {
            etacarnot = ThermEffCarnotCalculation(Thot, Tcold);
        }
        end = clock();
        
        timeTaken = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("Process completed in %.3f seconds.\n\n", timeTaken);
        
        //  Displaying results
        ThermEffDisplay(method, wnet, qhot, qcold, Thot, Tcold, eta, etacarnot);
        
        //  Writing to File
        ThermEffWriteSwitch(method, wnet, qhot, qcold, Thot, Tcold, eta, etacarnot);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
