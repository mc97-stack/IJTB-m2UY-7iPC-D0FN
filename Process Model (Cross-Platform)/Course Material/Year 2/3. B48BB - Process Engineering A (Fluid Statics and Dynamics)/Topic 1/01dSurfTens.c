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
#include "B48BB_T1.h"
#include "01dSurfTens.h"

#define maxstrlen 128
#define PI 3.141592653

void wettfacts(double cang)
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

void duNouyVar(double *F, double *L, double *C_F, double *cang)
{
    //Input variable declaration
    char input[maxstrlen];
    char corcheck[maxstrlen];
    
    double r = 0.0;
    
    int whilvar = 0;
    
    //Collect F
    printf("Force required to break fluid surface (N) = ");
    *F = atof(fgets(input, sizeof(input), stdin));
    
    //Collect r
    printf("Radius of ring (cm) = ");
    r = 0.0; //Initialising variable
    r = atof(fgets(input, sizeof(input), stdin));
    
    r = r*0.01; //Conversion (cm to m)
        //Calculating circumference of ring
    *L = 2*PI;
    *L = (*L) * (r); //m
    
    //Collect correction factor
    whilvar = 1;
    while(whilvar == 1)
    {
        printf("Use a correction factor? ");
        fgets(corcheck, sizeof(corcheck), stdin);
        switch(corcheck[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                printf("Correction factor = ");
                *C_F = atof(fgets(input, sizeof(input), stdin));
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
        fgets(corcheck, sizeof(corcheck), stdin);
        switch(corcheck[0])
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
                printf("Contact angle (deg) = ");
                *cang = atof(fgets(input, sizeof(input), stdin));
                whilvar = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    
    wettfacts(*cang);
        //Conversion (deg to rad)
    *cang = (*cang)*(PI/ 180);
    printf("Variable assignments:\n");
    printf("F = %f N\n", *F);
    printf("L = %f m\n", *L);
    printf("Correction factor = %f []\n", *C_F);
    printf("Contact angle = %f rad\n", *cang);
    fflush(stdout);
}

double duNouyCalc(double F, double L, double C_F, double cang)
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


void duNouyWrite(double F, double L, double C_F, double cang, double sigma)
{
    //Function variables
    char filename[maxstrlen];
    char filepath[maxstrlen*(2)];
    //char driveloc[maxstrlen];
    
    FILE *fp;
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
    printf("File name: \"%s\"\n", filename);
    
    strcat(filename, " du Nouy");
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
    fprintf(fp, "F = %.3f N\n", F);
    fprintf(fp, "Ring Circumference:\n");
    fprintf(fp, "L = %.3f m3\n", L);
    fprintf(fp, "Correction Factor:\n");
    fprintf(fp, "C_F = %.3f mol\n", C_F);
    fprintf(fp, "Contact angle:\n");
    fprintf(fp, "phi = %.3f rad\n\n", cang);
    fprintf(fp, "\tOutput Parameters:\n");
    fprintf(fp, "sigma =\t%.3f\tN/m\t= \\frac{(C_F)F}{2L\\cos\\phi}\n", sigma);
    
    //Close file
    fclose(fp);
     
    printf("Write Complete\n");
}

void duNouyWriteCheck(double F, double L, double C_F, double cang, double sigma)
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
                duNouyWrite(F, L, C_F, cang, sigma);
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

void SurfTens()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    whilmain = 1;
    
    while(whilmain == 1)
    {
        /*
        printf("Quick Experiment!\n");
        printf("1. Get some newtonian fluid (e.g. water) in a glass/ bowl (something with some form of capacity and a spoon\n");
        printf("2. Dip the spoon below the surface of the fluid\n");
        printf("3. SLOWLY raise the spoon and closely watch the free liquid surface until it separates from the spoon\n");
        printf("Q: How do you model this fluid behaviour?\n\n");
         */
        //Declaring calculation variables
        double F = 0.0;
        double L = 0.0;
        double C_F = 0.0;
        double cang = 0.0;
        
        //Declaring output variables
        double sigma = 0.0;
        
        duNouyVar(&F, &L, &C_F, &cang);
        printf("Function returns:\nF = %f\nL = %f\nC_F = %f\ncang = %f\n", F, L, C_F, cang);
        sigma = duNouyCalc(F, L, C_F, cang);
        printf("Surface tension = %.3f N/m\n", sigma);
        
        //Ask for file write (Remember while loop)
        duNouyWriteCheck(F, L, C_F, cang, sigma);
        
        //Continue function
        int whilcont;
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
                    printf("\n");
                    whilcont = 0;
                break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    printf("\n");
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
