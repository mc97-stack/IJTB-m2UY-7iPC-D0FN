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

OneKFittings OneKData(OneKFittings input)
{
    input.data[0] = 0.35;
    input.data[1] = 0.8;
    input.data[2] = 1.5;
    input.data[3] = 1.2;
    input.data[4] = 1.8;
    input.data[5] = 0.5;
    input.data[6] = 1.0;
    input.data[7] = 0.04;
    input.data[8] = 6.0;
    input.data[9] = 0.15;
    input.data[10] = 1.0;
    input.data[11] = 4.0;
    input.data[12] = 16.0;
    input.data[13] = 0.4;
    input.data[14] = 0.4;
    
    return input;
}

OneKFittings OneKVar(OneKFittings table, double *u)
{
    char input[maxstrlen];
    
    //  Setting data to data column
    table = OneKData(table);
    
    //  Collecting fluid velocity
    printf("Fluid velocity (m/s) = ");
    *u = atof(fgets(input, sizeof(input), stdin));
    
    //  Collecting table.count
    printf("Standard 45 deg elbow = ");
    table.count[0] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg elbow standard radius = ");
    table.count[1] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("90 deg square elbow = ");
    table.count[2] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry from leg T-piece = ");
    table.count[3] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Entry into leg T-piece = ");
    table.count[4] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Reduction (Tank outlet) = ");
    table.count[5] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Sudden Expansion (Tank Inlet) = ");
    table.count[6] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Unions and Couplings = ");
    table.count[7] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Globe valve fully open = ");
    table.count[8] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (100 pct) = ");
    table.count[9] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (75 pct) = ");
    table.count[10] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (50 pct) = ");
    table.count[11] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Gate valve (25 pct) = ");
    table.count[12] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Ball valve (100 pct) = ");
    table.count[13] = atoi(fgets(input, sizeof(input), stdin));
    
    printf("Plug valve open = ");
    table.count[14] = atoi(fgets(input, sizeof(input), stdin));
    
    return table;
}

double OneKCalc(int count, double data, double u)
{
    double hf = 0.0;
    
    hf = pow(u, 2);
    hf = (hf)/(2*g);
    hf = data*(hf);
    hf = count *(hf);
    
    return hf;
}

OneKFittings OneKFinalTable(OneKFittings data, double u)
{
    // Counts and database should already be specified prior to this function being run
    for(int i = 0; i < 15; ++i){
        data.headloss[i] = OneKCalc(data.count[i], data.data[i], u);
    }
    return data;
}

void OneKDisplay(OneKFittings table, double u, double total)
{
    int i = 0;
    
    printf("Fluid velocity:\n");
    printf("u =\t%.3f\tm/s\n", u);
    
    printf("Total Head Loss:\n");
    printf("total =\t%.3f\tm\n\n", total);
    
    printf("h_L = K \\frac{u^2}{2*g}\n");
    printf("Fitting\tk\tCount\tHead loss (m)\n");
    i = 0;
    printf("Standard 45 deg elbow\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 1;
    printf("90 deg elbow standard radius\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 2;
    printf("90 deg square elbow\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 3;
    printf("Entry from leg T-piece\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 4;
    printf("Entry into leg T-piece\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 5;
    printf("Sudden Reduction (Tank outlet)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 6;
    printf("Sudden Expansion (Tank Inlet)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 7;
    printf("Unions and Couplings\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 8;
    printf("Globe valve fully open\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 9;
    printf("Gate valve (100 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 10;
    printf("Gate valve (75 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 11;
    printf("Gate valve (50 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 12;
    printf("Gate valve (25 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 13;
    printf("Ball valve (100 pct)\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
    
    i = 14;
    printf("Plug valve open\t");
    printf("%.2f\t", table.data[i]);
    printf("%i\t", table.count[i]);
    printf("%.3f\n", table.headloss[i]);
}

void OneK()
{
    double u = 0.0;
    
    OneKFittings OneKTable;
    
    // Initializing the struct
    for(int i = 0; i < 15; ++i)
    {
        OneKTable.count[i] = 0;
        OneKTable.data[i] = 0.0;
        OneKTable.headloss[i] = 0.0;
    }
    //  Collecting data
    OneKTable = OneKVar(OneKTable, &u);
    
    //  Performing calculations
    OneKTable = OneKFinalTable(OneKTable, u);
    
    //  Calculating total head loss
    double total = 0.0;
    
    for(int i = 0; i < 15; ++i)
    {
        total += OneKTable.headloss[i];
    }
    
    // Displaying data
    OneKDisplay(OneKTable, u, total);
}
