//
//  01fCapp.c
//  Process Model (Cross-Platform)
//  
//  Created by Matthew Cheung on 26/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Custom header files
#include "B48BB_T1.h"
#include "01dSurfTens.h"
#include "01fCapp.h"

#define maxstrlen 128
#define PI 3.141592653
#define g 9.80665

void CappVar(double *sigma, double *cang, double *rho, double *d)
{
    //Declaring input variables
    char input[maxstrlen];
    
    printf("Surface Tension (N/m) = ");
    *sigma = atof(fgets(input, sizeof(input), stdin));
    
    printf("Contact angle (deg) = ");
    *cang = atof(fgets(input, sizeof(input), stdin));
    
    printf("Fluid density (kg/m3) = ");
    *rho = atof(fgets(input, sizeof(input), stdin));
    
    printf("Cappilary tube diameter (mm) = ");
    *d = atof(fgets(input, sizeof(input), stdin));
    
    //Extras ^.^
    wettfacts(*cang); //Function located in 01dSurfTens
    *cang = (*cang)*(PI/ 180); //Conversion to radians
    
    *d = (*d)*0.001;
    fflush(stdout);
}

double CappCalch(double sigma, double cang, double rho, double d)
{
    double top = 0.0;
    double bot = 0.0;
    double h = 0.0;
    
    top = 2*sigma;
    top = (top)*cos(cang);
    
    bot = rho*g;
    bot = (bot)*d;
    
    h = (top)/(bot);
    
    printf("Capillary rise = %.3f m\n", h);
    return h;
}

double CappCalcP(double sigma, double cang, double d)
{
    double top = 0.0;
    double Pc = 0.0;
    
    top = 2*sigma;
    top = (top)*cos(cang);
    
    Pc = d/2;
    Pc = (top)/(Pc);
    
    printf("Capillary pressure = %.3f Pa\n", Pc);
    
    return Pc;
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
void Capp()
{
    //Main Function
    char ContCond[maxstrlen];
    
    int whilmain = 0;
    
    printf("Capillarity Calculator\n");
    whilmain = 1;
    
    while(whilmain == 1)
    {
        //Declaring function variables
            //Function Output
        double h = 0.0; //Capillary rise
        double Pc = 0.0; //Capillary pressure
            //Calculation Variables
        double sigma = 0.0; //Surface tension
        double cang = 0.0; //Contact angle
        double rho = 0.0; //Fluid density
        double d = 0.0; //Tube diameter
        
        int whilcont = 0;
        
        //Collecting & Manipulating data
        CappVar(&sigma, &cang, &rho, &d);
        printf("Function returns:\nsigma = %f\ncang = %f\nrho = %f\nd = %f\n", sigma, cang, rho, d);
        
        h = CappCalch(sigma, cang, rho, d);
        
        printf("Function returns: h = %f\n", h);
        Pc  = CappCalcP(sigma, cang, d);
        
        printf("Function returns: Pc = %f\n", Pc);
        
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
