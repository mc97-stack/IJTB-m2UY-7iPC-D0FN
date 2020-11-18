//
//  B48BB.c
//  Process Model (Cross-platform)
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>
#include <stdlib.h>

//  Custom header files
#include "Courses.h"
#include "B48BBMenu.h"
#include "B48BB_T1.h"
#include "B48BB_T2.h"
#include "B48BB_T3.h"
#include "B48BB_T4.h"
//#include "B48BB_T5.h"

#define maxstrlen 16

void B48BBTopComm()
{
    printf("Please select from the following programs: \n");
}

void B48BBtopic1()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        B48BBTopComm();
        printf("1. Fluid Coefficient of Compressibility\n");
        printf("2. Hydrostatic Pressure Theorems\n");
        printf("3. Manometer calculations\n");
        printf("4. Surface tension and Capillary action\n");
        printf("5. Bubble Pressure\n");
        printf("6. Capillarity\n");
        //printf("7. Pendant Drop Method\n");
        printf("q. Exit topic\n");
        printf("Selection [1 - 6]: ");
        
        fgets(input,sizeof(input),stdin);
        fflush(stdout);
        printf("\n");
        switch(input[0])
        {
            case '1':
                CoefficientofCompressibility();
                break;
            case '2':
                FluidVerticalHydrostaticPressure();
                break;
            case '3':
                Manometer();
                break;
            case '4':
                SurfaceTension();
            break;
            case '5':
                BubblePressure();
                break;
            case '6':
                Cappilarity();
                break;
            case '7':
                printf("This program isn't quite there yet, try something else meanwhile.\n");
                //PenDrop();
                control = 0;
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 6.\n");
                break;
        }
        printf("\n");
        fflush(stdout);
    }
}


void B48BBtopic2()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        B48BBTopComm();
        printf("1. Mass Continuity Equation\n");
        printf("2. Steady-Flow energy equation\n");
        printf("3. Bernoulli's Equation\n");
        printf("4. Reynolds Number\n");
        printf("5. Dynamic and Kinematic Viscosity Correlations\n");
        printf("6. Velocity Profiles (Laminar and Turbulent Flow)\n");
        printf("7. Hagen-Poiseuille Equation\n");
        printf("q. Exit topic\n");
        printf("Selection [1 - 7]: ");
        
        fgets(input,sizeof(input),stdin);
        fflush(stdout);
        printf("\n");
        switch(input[0])
        {
            case '1':
                MassConservation();
                break;
            case '2':
                EnergyConservation();
                break;
            case '3':
                BernoulliEquation();
                break;
            case '4':
                ReynoldsNumber();
                break;
            case '5':
                ViscosityCorrelation();
                break;
            case '6':
                VelocityProfileMenu();
                break;
            case '7':
                HagenPoiseuille();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 7.\n");
                break;
        }
        
        fflush(stdout);
    }
}

void B48BBtopic3()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BBTopComm();
        printf("1. Laminar flow Frictional Pressure Loss\n");
        printf("2. General Frictional Pressure Loss\n");
        printf("3. Hydraulic mean diameter\n");
        printf("4. Pressure loss through Pipe fittings\n");
        printf("5. Pitot Static Tube\n");
        printf("6. Orifice plate meter/ Venturi Meter\n");
        printf("7. Rotameter\n");
        printf("q. Exit topic\n\n");
        printf("Selection [1 - 7]: ");
        
        fgets(input,sizeof(input),stdin);
        printf("\n");
        switch(input[0]){
            case '1':
                HagenPoiseuille();
                break;
            case '2':
                GeneralPressureLoss();
                break;
            case '3':
                HydraulicDiameter();
                break;
            case '4':
                Fittings();
                break;
            case '5':
                PitotStaticTube();
                break;
            case '6':
                OrificePlateMeter();
                break;
            case '7':
                Rotameter();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 7.\n");
                break;
        }
        fflush(stdout);
    }
}

void B48BBtopic4()
{
    PumpSizing();
}
/*
void B48BBtopic5()
{
    //B48BBTopComm();
    printf("Bear with me, this is still being written...\n");
}

*/
void B48BB(){
    char input[maxstrlen];
    int control = 0;        // Variable used to control user input.
    
    printf("Process Engineering A - Fluid Dynamics\n\n");
    control = 1;
    while(control == 1){
        printf("Please select which topic you want to access:\n");
        printf("T1: Fluid Statics\nT2: Fluid Dynamics\nT3: Frictional Pressure Loss and Flow Measurement\nT4: Pumping Systems and Pump Sizing\nT5: Non-Newtonian Fluids\nq. Exit course\n\n");
        printf("Topic ");
        fgets(input,sizeof(input),stdin);
        switch(input[0]){
            case '1':
                B48BBtopic1();
                break;
            case '2':
                B48BBtopic2();
                break;
            case '3':
                B48BBtopic3();
                break;
            case '4':
                B48BBtopic4();
                break;
            case '5':
                //B48BBtopic5();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 5.\n");
                break;
        }
        fflush(stdout);
    }
}
