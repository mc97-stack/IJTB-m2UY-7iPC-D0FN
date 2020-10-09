//
//  03daoneK.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Standard Header Files
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Custom Header Files
#include "03daoneK.h"

#define maxstrlen 128
#define g 9.80665

double OneKCalc(int count, int i, double u)
{
    double data[15] = {0.35, 0.8, 1.5, 1.2, 1.8, 0.5, 1.0, 0.04, 6.0, 0.15, 1.0, 4.0, 16.0, 0.4, 0.4};
    
    double hf = 0.0;
    
    hf = pow(u, 2);
    hf = (hf)/(2*g);
    hf = (data[i])*(hf);
    hf = count *(hf);
    
    return hf;
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
double OneK()
{
    //Main Function
    
    
    printf("OneK Pressure Loss\n");
    
    //Variable declaration
    char input[maxstrlen];
    
    double counts[15];
    double u = 0.0;
    double total = 0.0;
    
    //Data collection
    printf("Fluid velocity (m/s) = ");
    u = atof(fgets(input, sizeof(input), stdin));
    
    printf("Standard 45 deg elbow = ");
    counts[0] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg elbow standard radius = ");
    counts[1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg square elbow = ");
    counts[2] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry from leg T-piece = ");
    counts[3] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry into leg T-piece = ");
    counts[4] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Reduction (Tank outlet) = ");
    counts[5] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Expansion (Tank Inlet) = ");
    counts[6] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Unions and Couplings = ");
    counts[7] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve fully open = ");
    counts[8] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (100 pct) = ");
    counts[9] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (75 pct) = ");
    counts[10] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (50 pct) = ");
    counts[11] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (25 pct) = ");
    counts[12] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve (100 pct) = ");
    counts[13] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve open = ");
    counts[14] = atoi(fgets(input, sizeof(input), stdin));
    
    //Data manipulation
    double run = 0.0;
    
    for(int i = 0; i < 15; ++i)
    {
        run = OneKCalc(counts[i], i, u);
        total = run + total;
    }
    printf("Total head loss, hf = %.3f m\n", total);
    //Ask for file write (Remember while loop)
    //...
    
    return total;
}
