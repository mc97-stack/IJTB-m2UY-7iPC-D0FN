//
//  03dcEquivLeng.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/07/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//  Custom header files
#include "03dcEquivLeng.h"

#define maxstrlen 128
#define g 9.80665

//Declaring global variables and allocating memory
    //Function Output

    //Calculation Variables

    //Miscellaneous Variables

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
void EquivLeng()
{
    char input[maxstrlen];
    
    double velocityheadel[15][4];
    
    //Initialising lost velocity heads
    velocityheadel[0][0] = 15;
    velocityheadel[1][0] = 35;
    velocityheadel[2][0] = 75;
    velocityheadel[3][0] = 60;
    velocityheadel[4][0] = 90;
    velocityheadel[5][0] = 25;
    velocityheadel[6][0] = 50;
    velocityheadel[7][0] = 2;
    velocityheadel[8][0] = 450;
    velocityheadel[9][0] = 7.5;
    velocityheadel[10][0] = 40;
    velocityheadel[11][0] = 200;
    velocityheadel[12][0] = 800;
    velocityheadel[13][0] = 18;
    velocityheadel[14][0] = 18;
    
    //Getting counts
    printf("Standard 45 deg elbow: ");
    velocityheadel[0][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg elbow standard radius: ");
    velocityheadel[1][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg square elbow: ");
    velocityheadel[2][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry from leg T-piece: ");
    velocityheadel[3][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry into leg T-piece: ");
    velocityheadel[4][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Reduction (Tank outlet): ");
    velocityheadel[5][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Expansion (Tank Inlet): ");
    velocityheadel[6][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Unions and Couplings: ");
    velocityheadel[7][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve fully open: ");
    velocityheadel[8][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (100 pct): ");
    velocityheadel[9][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (75 pct): ");
    velocityheadel[10][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (50 pct): ");
    velocityheadel[11][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (25 pct): ");
    velocityheadel[12][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve (100 pct): ");
    velocityheadel[13][1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve open: ");
    velocityheadel[14][1] = atoi(fgets(input, sizeof(input), stdin));
    
    //Calculating pressure loss through fittings
    int row = 0;
        //Total lost velocity heads by component
    for(row = 0; row < 15; ++row){
        velocityheadel[row][2] = ((double)velocityheadel[row][0])*((double)velocityheadel[row][1]);
    }
    velocityheadel[0][3] = velocityheadel[0][2];
        //Cumulative lost velocity heads
    for(row = 1; row < 15; ++row){
        velocityheadel[row][3] = (velocityheadel[row - 1][3])+(velocityheadel[row][2]);
    }
    printf("\n-----\n\n");
    printf("L_e/d = %.3f []\n", velocityheadel[14][3]);
    
    
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
                printf("Fitting\tL_e/d []\tCount\t(L_e/d).Count\tSum\n");
                int col = 0;
                for(row = 0; row < 15; ++row){
                    for(col = 0; col < 4; ++col)
                    {
                        if(row == 0 && col == 0){
                            printf("Standard 45 deg elbow\t");
                        }
                        if(row == 1 && col == 0){
                            printf("90 deg elbow standard radius\t");
                        }
                        if(row == 2 && col == 0){
                            printf("90 deg square elbow\t");
                        }
                        if(row == 3 && col == 0){
                            printf("Entry from leg T-piece\t");
                        }
                        if(row == 4 && col == 0){
                            printf("Entry into leg T-piece\t");
                        }
                        if(row == 5 && col == 0){
                            printf("Sudden Reduction (Tank outlet)\t");
                        }
                        if(row == 6 && col == 0){
                            printf("Sudden Expansion (Tank Inlet)\t");
                        }
                        if(row == 7 && col == 0){
                            printf("Unions and Couplings\t");
                        }
                        if(row == 8 && col == 0){
                            printf("Globe valve fully open\t");
                        }
                        if(row == 9 && col == 0){
                            printf("Gate valve (100 pct)\t");
                        }
                        if(row == 10 && col == 0){
                            printf("Gate valve (75 pct)\t");
                        }
                        if(row == 11 && col == 0){
                            printf("Gate valve (50 pct)\t");
                        }
                        if(row == 12 && col == 0){
                            printf("Gate valve (25 pct)\t");
                        }
                        if(row == 13 && col == 0){
                            printf("Ball valve (100 pct)\t");
                        }
                        if(row == 14 && col == 0){
                            printf("Plug valve open\t");
                        }
                        
                        if(col == 0 || col == 2 ||col == 3)
                        {
                            printf("%.2f", velocityheadel[row][col]);
                        }
                        if(col == 1)
                        {
                            printf("%.0f", velocityheadel[row][col]);
                        }
                        if(col == 3)
                        {
                            printf("\n");
                        }else{
                            printf("\t");
                        }
                    }
                }
                printf("L_e/d = %.3f []\n", velocityheadel[14][3]);
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
