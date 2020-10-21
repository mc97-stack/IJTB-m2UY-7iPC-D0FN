//
//  03dbthreeK.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "03dbthreeK.h"

#define maxstrlen 128
#define g 9.80665


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

double threeKcalc(double K1, double Kinf, double Kd, double Re, double NPS)
{
    //NPS = Nominal Pipe Size
    double frac = 0.0;
    double brack = 0.0;
    
    double K = 0.0;
    
    frac = K1/Re;
    
    brack = pow(NPS, 0.3);
    brack = Kd/(brack);
    brack = 1 + (brack);
    
    K = Kinf*(brack);
    K = frac + (K);
    
    return K;
}

void threeK()
{
    //Source: neutrium.net/fluid_flow/pressure-loss-from-fittings-3k-method/
    char input[maxstrlen];
    
    double velocityheadthreek[34][9];
    
    //Initialising lost velocity heads
        //k_1
    int coli = 0;
    velocityheadthreek[0][coli] = 800;
    velocityheadthreek[1][coli] = 800;
    velocityheadthreek[2][coli] = 800;
    velocityheadthreek[3][coli] = 800;
    velocityheadthreek[4][coli] = 800;
    velocityheadthreek[5][coli] = 800;
    velocityheadthreek[6][coli] = 1000;
    velocityheadthreek[7][coli] = 800;
    velocityheadthreek[8][coli] = 800;
    velocityheadthreek[9][coli] = 500;
    velocityheadthreek[10][coli] = 500;
    velocityheadthreek[11][coli] = 500;
    velocityheadthreek[12][coli] = 500;
    velocityheadthreek[13][coli] = 1000;
    velocityheadthreek[14][coli] = 1000;
    velocityheadthreek[15][coli] = 1000;
    velocityheadthreek[16][coli] = 500;
    velocityheadthreek[17][coli] = 800;
    velocityheadthreek[18][coli] = 800;
    velocityheadthreek[19][coli] = 1000;
    velocityheadthreek[20][coli] = 200;
    velocityheadthreek[21][coli] = 150;
    velocityheadthreek[22][coli] = 100;
    velocityheadthreek[23][coli] = 950;
    velocityheadthreek[24][coli] = 1000;
    velocityheadthreek[25][coli] = 1500;
    velocityheadthreek[26][coli] = 500;
    velocityheadthreek[27][coli] = 300;
    velocityheadthreek[28][coli] = 300;
    velocityheadthreek[29][coli] = 300;
    velocityheadthreek[30][coli] = 300;
    velocityheadthreek[31][coli] = 1000;
    velocityheadthreek[32][coli] = 1500;
    velocityheadthreek[33][coli] = 2000;
    
        //k_inf
    coli = 1;
    velocityheadthreek[0][coli] = 0.14;
    velocityheadthreek[1][coli] = 0.071;
    velocityheadthreek[2][coli] = 0.091;
    velocityheadthreek[3][coli] = 0.056;
    velocityheadthreek[4][coli] = 0.066;
    velocityheadthreek[5][coli] = 0.075;
    velocityheadthreek[6][coli] = 0.27;
    velocityheadthreek[7][coli] = 0.068;
    velocityheadthreek[8][coli] = 0.035;
    velocityheadthreek[9][coli] = 0.071;
    velocityheadthreek[10][coli] = 0.052;
    velocityheadthreek[11][coli] = 0.086;
    velocityheadthreek[12][coli] = 0.052;
    velocityheadthreek[13][coli] = 0.23;
    velocityheadthreek[14][coli] = 0.12;
    velocityheadthreek[15][coli] = 0.1;
    velocityheadthreek[16][coli] = 0.274;
    velocityheadthreek[17][coli] = 0.14;
    velocityheadthreek[18][coli] = 0.28;
    velocityheadthreek[19][coli] = 0.34;
    velocityheadthreek[20][coli] = 0.091;
    velocityheadthreek[21][coli] = 0.05;
    velocityheadthreek[22][coli] = 0;
    velocityheadthreek[23][coli] = 0.25;
    velocityheadthreek[24][coli] = 0.69;
    velocityheadthreek[25][coli] = 1.7;
    velocityheadthreek[26][coli] = 0.41;
    velocityheadthreek[27][coli] = 0.084;
    velocityheadthreek[28][coli] = 0.14;
    velocityheadthreek[29][coli] = 0.037;
    velocityheadthreek[30][coli] = 0.017;
    velocityheadthreek[31][coli] = 0.69;
    velocityheadthreek[32][coli] = 0.46;
    velocityheadthreek[33][coli] = 2.85;
    
        //k_d (inches)
    coli = 2;
    velocityheadthreek[0][coli] = 4;
    velocityheadthreek[1][coli] = 4.2;
    velocityheadthreek[2][coli] = 4;
    velocityheadthreek[3][coli] = 3.9;
    velocityheadthreek[4][coli] = 3.9;
    velocityheadthreek[5][coli] = 4.2;
    velocityheadthreek[6][coli] = 4;
    velocityheadthreek[7][coli] = 4.1;
    velocityheadthreek[8][coli] = 4.2;
    velocityheadthreek[9][coli] = 4.2;
    velocityheadthreek[10][coli] = 4;
    velocityheadthreek[11][coli] = 4;
    velocityheadthreek[12][coli] = 4;
    velocityheadthreek[13][coli] = 4;
    velocityheadthreek[14][coli] = 4;
    velocityheadthreek[15][coli] = 4;
    velocityheadthreek[16][coli] = 4;
    velocityheadthreek[17][coli] = 4;
    velocityheadthreek[18][coli] = 4;
    velocityheadthreek[19][coli] = 4;
    velocityheadthreek[20][coli] = 4;
    velocityheadthreek[21][coli] = 4;
    velocityheadthreek[22][coli] = 0;
    velocityheadthreek[23][coli] = 4;
    velocityheadthreek[24][coli] = 4;
    velocityheadthreek[25][coli] = 3.6;
    velocityheadthreek[26][coli] = 4;
    velocityheadthreek[27][coli] = 3.9;
    velocityheadthreek[28][coli] = 4;
    velocityheadthreek[29][coli] = 3.9;
    velocityheadthreek[30][coli] = 3.5;
    velocityheadthreek[31][coli] = 4.9;
    velocityheadthreek[32][coli] = 4;
    velocityheadthreek[33][coli] = 3.8;
    
        //k_d (mm)
    coli = 3;
    velocityheadthreek[0][coli] = 10.6;
    velocityheadthreek[1][coli] = 11.1;
    velocityheadthreek[2][coli] = 10.6;
    velocityheadthreek[3][coli] = 10.3;
    velocityheadthreek[4][coli] = 10.3;
    velocityheadthreek[5][coli] = 11.1;
    velocityheadthreek[6][coli] = 10.6;
    velocityheadthreek[7][coli] = 10.8;
    velocityheadthreek[8][coli] = 11.1;
    velocityheadthreek[9][coli] = 11.1;
    velocityheadthreek[10][coli] = 10.6;
    velocityheadthreek[11][coli] = 10.6;
    velocityheadthreek[12][coli] = 10.6;
    velocityheadthreek[13][coli] = 10.6;
    velocityheadthreek[14][coli] = 10.6;
    velocityheadthreek[15][coli] = 10.6;
    velocityheadthreek[16][coli] = 10.6;
    velocityheadthreek[17][coli] = 10.6;
    velocityheadthreek[18][coli] = 10.6;
    velocityheadthreek[19][coli] = 10.6;
    velocityheadthreek[20][coli] = 10.6;
    velocityheadthreek[21][coli] = 10.6;
    velocityheadthreek[22][coli] = 0;
    velocityheadthreek[23][coli] = 10.6;
    velocityheadthreek[24][coli] = 10.6;
    velocityheadthreek[25][coli] = 9.5;
    velocityheadthreek[26][coli] = 10.6;
    velocityheadthreek[27][coli] = 10.3;
    velocityheadthreek[28][coli] = 10.6;
    velocityheadthreek[29][coli] = 10.3;
    velocityheadthreek[30][coli] = 9.2;
    velocityheadthreek[31][coli] = 12.9;
    velocityheadthreek[32][coli] = 10.6;
    velocityheadthreek[33][coli] = 10;
    //Getting counts
    
    coli = 4;
    printf("90 deg Elbow, Threaded, Standard Radius (R/D = 1): ");
    velocityheadthreek[0][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Threaded, Long Radius (R/D = 1): ");
    velocityheadthreek[1][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Standard Radius (R/D = 1): ");
    velocityheadthreek[2][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 2): ");
    velocityheadthreek[3][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 4): ");
    velocityheadthreek[4][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 6): ");
    velocityheadthreek[5][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Mitered, 1 weld 90 deg: ");
    velocityheadthreek[6][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Mitered, 2 weld 45 deg: ");
    velocityheadthreek[7][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg Elbow, Mitered, 3 weld 30 deg: ");
    velocityheadthreek[8][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Threaded, Standard Radius (R/D = 1): ");
    velocityheadthreek[9][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Threaded, Long Radius (R/D = 1.5): ");
    velocityheadthreek[10][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Mitered, 1 weld 45 deg: ");
    velocityheadthreek[11][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("45 deg Elbow, Mitered, 2 weld 22.5 deg: ");
    velocityheadthreek[12][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg Bend, threaded, close-return (R/D = 1): ");
    velocityheadthreek[13][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg Bend, threaded, flanged (R/D = 1): ");
    velocityheadthreek[14][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("180 deg Bend, threaded, All types (R/D = 1.5): ");
    velocityheadthreek[15][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, threaded (R/D = 1): ");
    velocityheadthreek[16][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, threaded (R/D = 1.5): ");
    velocityheadthreek[17][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, flanged (R/D = 1): ");
    velocityheadthreek[18][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Through-branch as an Elbow, stub-in branch: ");
    velocityheadthreek[19][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Run-through, threaded (R/D = 1): ");
    velocityheadthreek[20][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Run-through, flanged (R/D = 1): ");
    velocityheadthreek[21][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Tee Run-through, stub-in branch: ");
    velocityheadthreek[22][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Angle valve, 45 deg, full line size \\beta = 1: ");
    velocityheadthreek[23][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Angle valve, 90 deg, full line size \\beta = 1: ");
    velocityheadthreek[24][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve, standard, \\beta = 1: ");
    velocityheadthreek[25][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve, branch flow: ");
    velocityheadthreek[26][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve, straight through: ");
    velocityheadthreek[27][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve, three-way (flow through): ");
    velocityheadthreek[28][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve, standard, \\beta = 1: ");
    velocityheadthreek[29][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve, standard, \\beta = 1: ");
    velocityheadthreek[30][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Diaphragm valve, dam type: ");
    velocityheadthreek[31][coli] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Swing check valve: ");
    velocityheadthreek[32][coli] = atoi(fgets(input, sizeof(input), stdin));
    printf("N.B. V_{min} = 35\\left(\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    
    printf("Lift check valve: ");
    velocityheadthreek[33][coli] = atoi(fgets(input, sizeof(input), stdin));
    printf("N.B. V_{min} = 40\\left(\\frac{(lb_m)}{ft^3} \\right)^{-\\frac{1}{2}}\n");
    
    //Calculating pressure loss through fittings
    //Collecting inputs for 3K - correlation
    double Reynolds = 0.0;
    double NPS = 0.0;
    double vel = 0.0;
    double h_f = 0.0;
    
    printf("Reynolds Number: ");
    Reynolds = atof(fgets(input, sizeof(input), stdin));
    
    printf("Nominal Pipe Size (NPS) (inches) = ");
    NPS = atof(fgets(input, sizeof(input), stdin));
    
    printf("Average fluid velocity (m/s) = ");
    vel = atof(fgets(input, sizeof(input), stdin));
    
    h_f = pow(vel, 2); //m/s
    h_f = (h_f)/(2*g); //(m/s)/(m2/s) = m
    
    int row = 0;
    //Calculating K-value by component then multiplying by count
    for(row = 0; row < 34; ++row)
    {
        velocityheadthreek[row][5] = threeKcalc(velocityheadthreek[row][0], velocityheadthreek[row][1], velocityheadthreek[row][2], Reynolds, NPS); //K-value by fitting
        velocityheadthreek[row][6] = (velocityheadthreek[row][5])*(h_f); //Fitting head loss
        velocityheadthreek[row][7] = ((double)velocityheadthreek[row][4])*(velocityheadthreek[row][6]); //Total group head loss
    }
    
    velocityheadthreek[0][8] = velocityheadthreek[0][7];
    //  Calculating the cumulative head loss
    for(row = 1; row < 34; ++row)
    {
        velocityheadthreek[row][8] = velocityheadthreek[row - 1][8] + velocityheadthreek[row][7];
    }
    printf("\n-----\n\n");
    
    printf("h_f = %.3f m\n", velocityheadthreek[33][8]);
    
    int whilcalc = 1;
    while(whilcalc == 1)
    {
        printf("Do you want to show the calculation sheet? ");
        char input[maxstrlen];
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
            case 'T':
            case 'Y':
            case 't':
            case 'y':
                //Displaying calculation sheet
                printf("Fitting\tk_1 []\tk_inf []\tk_d (inches)\tk_d (mm)\tCount\tK\th_f (m)\tTotal h_f (m)\tSum\n");
                int col = 0;
                for(row = 0; row < 34; ++row){
                    for(col = 0; col < 9; ++col)
                    {
                        if(row == 0 && col == 0){
                            printf("90 deg Elbow, Threaded, Standard Radius (R/D = 1)\t");
                        }
                        if(row == 1 && col == 0){
                            printf("90 deg Elbow, Threaded, Long Radius (R/D = 1)\t");
                        }
                        if(row == 2 && col == 0){
                            printf("90 deg Elbow, Flanged or Welded, Standard Radius (R/D = 1)\t");
                        }
                        if(row == 3 && col == 0){
                            printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 2)\t");
                        }
                        if(row == 4 && col == 0){
                            printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 4)\t");
                        }
                        if(row == 5 && col == 0){
                            printf("90 deg Elbow, Flanged or Welded, Long Radius (R/D = 6)\t");
                        }
                        if(row == 6 && col == 0){
                            printf("90 deg Elbow, Mitered, 1 weld 90 deg)\t");
                        }
                        if(row == 7 && col == 0){
                            printf("90 deg Elbow, Mitered, 2 weld 45 deg\t");
                        }
                        if(row == 8 && col == 0){
                            printf("90 deg Elbow, Mitered, 3 weld 30 deg\t");
                        }
                        if(row == 9 && col == 0){
                            printf("45 deg Elbow, Threaded, Standard Radius (R/D = 1)\t");
                        }
                        if(row == 10 && col == 0){
                            printf("45 deg Elbow, Threaded, Long Radius (R/D = 1.5)\t");
                        }
                        if(row == 11 && col == 0){
                            printf("45 deg Elbow, Mitered, 1 weld 45 deg\t");
                        }
                        if(row == 12 && col == 0){
                            printf("45 deg Elbow, Mitered, 2 weld 22.5 deg\t");
                        }
                        if(row == 13 && col == 0){
                            printf("180 deg Bend, threaded, close-return (R/D = 1)\t");
                        }
                        if(row == 14 && col == 0){
                            printf("180 deg Bend, threaded, flanged (R/D = 1)\t");
                        }
                        if(row == 15 && col == 0){
                            printf("180 deg Bend, threaded, All types (R/D = 1.5)\t");
                        }
                        if(row == 16 && col == 0){
                            printf("Tee Through-branch as an Elbow, threaded (R/D = 1)\t");
                        }
                        if(row == 17 && col == 0){
                            printf("Tee Through-branch as an Elbow, threaded (R/D = 1.5)\t");
                        }
                        if(row == 18 && col == 0){
                            printf("Tee Through-branch as an Elbow, flanged (R/D = 1)\t");
                        }
                        if(row == 19 && col == 0){
                            printf("Tee Through-branch as an Elbow, stub-in branch\t");
                        }
                        if(row == 20 && col == 0){
                            printf("Tee Run-through, threaded (R/D = 1)\t");
                        }
                        if(row == 21 && col == 0){
                            printf("Tee Run-through, flanged (R/D = 1)\t");
                        }
                        if(row == 22 && col == 0){
                            printf("Tee Run-through, stub-in branch\t");
                        }
                        if(row == 23 && col == 0){
                            printf("Angle valve, 45 deg, full line size \\beta = 1\t");
                        }
                        if(row == 24 && col == 0){
                            printf("Angle valve, 90 deg, full line size \\beta = 1\t");
                        }
                        if(row == 25 && col == 0){
                            printf("Globe valve, standard, \\beta = 1\t");
                        }
                        if(row == 26 && col == 0){
                            printf("Plug valve, branch flow\t");
                        }
                        if(row == 27 && col == 0){
                            printf("Plug valve, straight through\t");
                        }
                        if(row == 28 && col == 0){
                            printf("Plug valve, three-way (flow through)\t");
                        }
                        if(row == 29 && col == 0){
                            printf("Gate valve, standard, \\beta = 1\t");
                        }
                        if(row == 30 && col == 0){
                            printf("Ball valve, standard, \\beta = 1\t");
                        }
                        if(row == 31 && col == 0){
                            printf("Diaphragm valve, dam type\t");
                        }
                        if(row == 32 && col == 0){
                            printf("Swing check valve\t");
                        }
                        if(row == 33 && col == 0){
                            printf("Lift check valve\t");
                        }
                        //k_1 and counts
                        if(col == 0 || col == 4)
                        {
                            printf("%.0f", velocityheadthreek[row][col]);
                        }
                        //k_inf
                        if(col == 1 )
                        {
                            printf("%.3f", velocityheadthreek[row][col]);
                        }
                        //k_d (inches) and k_d (mm)
                        if(col == 2 || col == 3)
                        {
                            printf("%.1f", velocityheadthreek[row][col]);
                        }
                        if(col == 5 || col == 6 || col == 7 || col == 8)
                        {
                            printf("%.3f", velocityheadthreek[row][col]);
                        }
                        
                        if(col == 8)
                        {
                            printf("\n");
                        }else{
                            printf("\t");
                        }
                    }
                }
                printf("h_f = %.3f m\n", h_f);
                whilcalc = 0;
            break;
            case '0':
            case 'F':
            case 'N':
            case 'f':
            case 'n':
                whilcalc = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    
    
    //return [Function Output];
}

