//
//  01dSurfTens.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Custom Header Files
#include "System.h"
#include "B48BB_T1.h"
#include "01dSurfTens.h"

#define maxstrlen 128
#define PI 3.141592653

void wettabilityfacts(double cang)
{
    //cang in degrees
    char selec[maxstrlen];
    int condc = 0;
    
    condc = 1;
    while(condc == 1)
    {
        printf("\nDo you want to know more about the fluid? ");
        fgets(selec,sizeof(selec),stdin);
        switch(selec[0]){
            case 'Y':
            case 'y':
                if(cang == 0){
                    printf("Perfect Wetting\n");
                    printf("Very strong adhesive forces\n");
                    printf("Weak cohesive forces \n\n");
                }else{
                    if(cang < 90){
                        printf("High Wettability\n");
                        printf("Strong adhesive forces\n");
                        printf("Strong cohesive forces \n");
                        printf("Lower meniscus formed in a capillary tube\n\n");
                    }else{
                        if(cang == 90){
                            printf("Fluid is neither wetting nor non-wetting\n");
                            printf("No meniscus is observed within a capillary tube\n\n");
                        }else{
                            if(cang < 180){
                                printf("High non-wettability\n");
                                printf("Weak adhesive forces\n");
                                printf("Strong cohesive forces \n");
                                printf("Capillary fall observed - Entry pressure requirement for fluid\n\n");
                            }else{
                                if(cang == 180){
                                    printf("Perfect non-wetting\n");
                                    printf("Very weak adhesive forces\n");
                                    printf("Strong cohesive forces \n\n");
                                }else{
                                    printf("Contact angle exceeds 180 deg\n\n");
                                }
                            }
                        }
                    }
                }
                fflush(stdout);
                condc = 0;
            break;
            case 'N':
            case 'n':
                condc = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
        fflush(stdout);
    }
}

void duNouyVariable(double *F, double *L, double *C_F, double *cang)
{
    //Input variable declaration
    char menu[maxstrlen];   // Variable used to store keyboard input for menus.
    
    double r = 0.0;         // Variable used to collect the ring radius to infer the ring circumference.
    
    int whilvar = 0;        // Variable used to control menu input.
    
    //Collect F
    *F = inputDouble(0, "force required to break fluid surface", "N");
    
    //Collect r
    printf("Radius of ring (cm) = ");
    r = inputDouble(0, "ring radius", "cm");
    
    r = r*0.01; //Conversion (cm to m)
        //Calculating circumference of ring
    *L = 2*PI;
    *L = (*L) * (r); //m
    
    //Collect correction factor
    whilvar = 1;
    while(whilvar == 1)
    {
        printf("Use a correction factor? ");
        fgets(menu, sizeof(menu), stdin);
        switch(menu[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *C_F = inputDouble(0, "Correction factor", "[]");
                whilvar = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                *C_F = 1;
                whilvar = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    //Not freeing whilvar as going to be used in the next while loop
    //Collect contact angle
    whilvar = 1;
    while(whilvar == 1)
    {
        printf("Assume ring is made from platinum and treated properly? ");
        fgets(menu, sizeof(menu), stdin);
        switch(menu[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                *cang = 0;
                whilvar = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                *cang = inputDouble(0, "Contact angle", "deg");
                whilvar = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    wettabilityfacts(*cang);
        //Conversion (deg to rad)
    *cang = (*cang)*(PI/ 180);
    /*
    printf("Variable assignments:\n");
    printf("F = %f N\n", *F);
    printf("L = %f m\n", *L);
    printf("Correction factor = %f []\n", *C_F);
    printf("Contact angle = %f rad\n", *cang);
     */
    fflush(stdout);
}

double duNouyCalculation(double F, double L, double C_F, double cang)
{
    double top = 0.0;
    double bot = 0.0;
    
    double sigma = 0.0;
    
    top = C_F*F;
    bot = 2*L;
    bot = (bot)*cos(cang);
    
    sigma = (top)/ (bot);
    
    return sigma;
}

void duNouyDisplay(double F, double L, double C_F, double cang, double sigma)
{
    printf("_du_Nouy_Surface_Tension_\n");
    printf("\tInput Parameters:\n");
    printf("Force required to break fluid surface:\n");
    printf("F =\t%.3f\tN\n", F);
    printf("Ring Circumference:\n");
    printf("L =\t%.3f\tm3\n", L);
    printf("Correction Factor:\n");
    printf("C_F =\t%.3f\tmol\n", C_F);
    printf("Contact angle:\n");
    printf("phi =\t%.3f\trad\n\n", cang);
    
    printf("\tOutput Parameters:\n");
    printf("sigma =\t%.3f\tN/m\t= \\frac{(C_F)F}{2L\\cos\\phi}\n", sigma);
}

void duNouyWrite(double F, double L, double C_F, double cang, double sigma)
{
    //Function variables
    char filename[maxstrlen];   // Character array used to store file name as it is built.
    //char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;                   // Pointer to the file location.
    //Set file name as timestamp + du Nouy
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
    
    strcat(filename, " du Nouy");
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
    void free(void *filename);
    
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
    fprintf(fp, "_du_Nouy_Surface_Tension_\n");
    fprintf(fp, "\tInput Parameters:\n");
    fprintf(fp, "Force required to break fluid surface:\n");
    fprintf(fp, "F =\t%.3f\tN\n", F);
    fprintf(fp, "Ring Circumference:\n");
    fprintf(fp, "L =\t%.3f\tm3\n", L);
    fprintf(fp, "Correction Factor:\n");
    fprintf(fp, "C_F =\t%.3f\tmol\n", C_F);
    fprintf(fp, "Contact angle:\n");
    fprintf(fp, "phi =\t%.3f\trad\n\n", cang);
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\t= \\frac{(C_F)F}{2L\\cos\\phi}\n", sigma);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void duNouyWriteSwitch(double F, double L, double C_F, double cang, double sigma)
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
                duNouyWrite(F, L, C_F, cang, sigma);
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

void SurfaceTension()
{
    //Main Function
    int whilmain = 0;   // Variable used to control the while loop below
    
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //  Declaring variables
        double F = 0.0;
        double L = 0.0;
        double C_F = 0.0;
        double cang = 0.0;
        
        double sigma = 0.0;
        
        //  Collecting data
        duNouyVariable(&F, &L, &C_F, &cang);
        //printf("Function returns:\nF = %f\nL = %f\nC_F = %f\ncang = %f\n", F, L, C_F, cang);
        
        //  Running calculation
        sigma = duNouyCalculation(F, L, C_F, cang);
        //printf("Surface tension = %.3f N/m\n", sigma);
        
        //  Displaying results
        duNouyDisplay(F, L, C_F, cang, sigma);
        
        //  Writing to file
        duNouyWriteSwitch(F, L, C_F, cang, sigma);
        
        //  Continue function
        whilmain = Continue(whilmain);
    }
    fflush(stdout);
}
