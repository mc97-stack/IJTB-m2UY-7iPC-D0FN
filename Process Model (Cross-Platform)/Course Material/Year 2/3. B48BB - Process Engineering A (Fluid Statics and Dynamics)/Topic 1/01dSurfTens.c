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

//  Custom Header Files
#include "B48BB_T1.h"
#include "01dSurfTens.h"
#include "01eBubPres.h"
#include "01fCapp.h"

#define maxstrlen 128
#define PI 3.141592653

//Declaring global variables and allocating memory

    //Miscellaneous Variables

void wettfacts(double cang)
{
    //cang in degrees
    char selec[maxstrlen];
    int condc;
    
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
    
    int whilvar;
    
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
    
    printf("Surface tension = %.3f N/m\n", sigma);
    return sigma;
}
/*
void [Data Plot & Write](...)
{
    char filename[maxstrlen];
    char path[maxstrlen];
    char filepath[maxstrlen*2];

    FILE *fp
    
    //Get file name
    *filename = (char)malloc(sizeof(filename);
    ...
    
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
void SurfTens()
{
    //Main Function
    char ContCond[maxstrlen];
    char DropCond[maxstrlen];
    char input[maxstrlen];
    
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
        double rad = 0.0;
        double rho = 0.0; //Fluid density
        double d = 0.0; //Tube diameter
        
        //Declaring output variables
        double sigma = 0.0;
        double ch = 0.0; // Capillary rise
        double cp = 0.0; // Capillary pressure
        
        //Optional function variables
        
        
        int DropCal = 0;
        
        duNouyVar(&F, &L, &C_F, &cang);
        printf("Function returns:\nF = %f\nL = %f\nC_F = %f\ncang = %f\n", F, L, C_F, cang);
        sigma = duNouyCalc(F, L, C_F, cang);
        
        printf("Function returns: %f\n", sigma);
        
        DropCal = 1;
        while(DropCal == 1)
        {
            printf("Do you want to calculate the internal pressure of a droplet? ");
            fgets(DropCond, sizeof(DropCond), stdin);
            switch(DropCond[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    printf("Droplet radius (mm) = ");
                    rad = atof(fgets(input, sizeof(input), stdin));
                    
                    rad = (rad)*0.001; //Conversion to m
                    BubPresCalc(sigma, rad);
                    DropCal = 0;
                break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    DropCal = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        
        DropCal = 1; //Reusing DropCal to ask another question
        while(DropCal == 1)
        {
            printf("Do you want to estimate Capillarity effects? ");
            fgets(DropCond, sizeof(DropCond), stdin);
            switch(DropCond[0])
            {
                case '1':
                case 'T':
                case 'Y':
                case 't':
                case 'y':
                    //Collect fluid density
                    printf("Fluid Density (kg/m3) = ");
                    rho = atof(fgets(input, sizeof(input), stdin));
                    
                    //Collect tube diameter
                    printf("Capillary tube diameter (mm) = ");
                    d = atof(fgets(input, sizeof(input), stdin));
                    
                    d = (d)*0.001; //Conversion (mm to m)
                    //Calculate Capillary rise
                        //Leaving the function outputs unassigned
                    ch = CappCalch(sigma, cang, rho, d);
                    printf("Function returns: ch = %f\n\n", ch);
                    //Calculate Capillary pressure
                    cp = CappCalcP(sigma, cang, d);
                    printf("Function returns: cp = %f\n\n", cp);
                    //Not freeing double variables as they were assigned outside of the loop
                    
                    DropCal = 0;
                break;
                case '0':
                case 'F':
                case 'N':
                case 'f':
                case 'n':
                    DropCal = 0;
                break;
                default:
                    printf("Input not recognised\n");
                break;
            }
        }
        //Ask for file write (Remember while loop)
        //...
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
