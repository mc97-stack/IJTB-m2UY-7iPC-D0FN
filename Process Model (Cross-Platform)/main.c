//
//  main.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define maxstrlen 64

void MinorUnitOps()
{
    printf("Minor\n\n");
}

void MajorUnitOps()
{
    printf("Major\n\n");
}

void CourseSelection()
{
    char yearselect[maxstrlen];
    
    int whilcourse = 0;
    whilcourse = 1;
    
    while(whilcourse == 1)
    {
        printf("Which year would you like to enter or 'q' to exit selection? [1 - 4]\n\n");
        printf("Year ");
        fgets(yearselect, sizeof(yearselect), stdin);
        switch(yearselect[0])
        {
            case '1':
                Year1();
            break;
            case '2':
                Year2();
            break;
            case '3':
                Year3();
            break;
            case '4':
                Year4();
            break;
            case '0':
            case 'q':
                whilcourse = 0;
            break;
            default:
                printf("Input not recognised\n\n");
            break;
        }
        fflush(stdout);
    }
    fflush(stdout);
}

void ThermoProps()
{
    printf("Thermodynamic Properties\n\n");
}

void DynProcessSim()
{
    printf("Dynamic Process Simulator\n\n");
}

void NiceThings()
{
    printf("Bonus Content!\n\n");
}

int main()
{
    printf("_Just Another Model (JAM) - alpha build_\n");
    printf("Made by Matthew Cheung\n");
    
    char MainSelect[maxstrlen];
    
    int whilmain = 0;
    
    //Main menu for program
    whilmain = 1;
    while(whilmain == 1)
    {
        printf("Please select from the following options:\n");
        printf("1. Minor Unit Operations\n");
        printf("2. Major Unit Operations\n");
        printf("3. Course Files\n");
        printf("4. Thermophysical Properties\n");
        printf("5. Dynamic Process Simulation\n");
        printf("6. Other nice things\n");
        printf("q. Exit Program\n\n");
        printf("Selection [1 - 6]: ");
        fflush(stdout);
        fgets(MainSelect, sizeof(MainSelect), stdin);
        switch(MainSelect[0])
        {
            case '1':
                MinorUnitOps();
            break;
            case '2':
                MajorUnitOps();
            break;
            case '3':
                CourseSelection();
            break;
            case '4':
                ThermoProps();
            break;
            case '5':
                DynProcessSim();
            break;
            case '6':
                NiceThings();
            break;
            case '0':
            case 'q':
                whilmain = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
    }
    return 0;
}
