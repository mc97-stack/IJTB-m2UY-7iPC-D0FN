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
#include "03aFrictFactor.h"
//#include "B48BB_T5.h"

#define maxstrlen 16

char B48BBMenu[maxstrlen];
int whiltop;

void B48BBTopComm()
{
    printf("Please select from the following programs: \n");
}

void B48BBtopic1()
{
    int whiltop = 0;
    whiltop = 1;
    while(whiltop == 1)
    {
        B48BBTopComm();
        printf("1. Fluid Coefficient of Compressibility\n");
        printf("2. Hydrostatic Pressure Theorems\n");
        printf("3. Manometer calculations\n");
        printf("4. Surface tension and Capillary action\n");
        printf("5. Bubble Pressure\n");
        printf("6. Capillarity\n");
        printf("7. Pendant Drop Method\n");
        printf("q. Exit topic\n");
        printf("Selection [1 - 4]: ");
        //Allocating memory for the menu
        
        fgets(B48BBMenu,sizeof(B48BBMenu),stdin);
        fflush(stdout);
        printf("\n");
        switch(B48BBMenu[0])
        {
            case '1':
                FluComp();
            break;
            case '2':
                FluidVHyd();
            break;
            case '3':
                Mano();
            break;
            case '4':
                SurfTens();
            break;
            case '5':
                BubPres();
            break;
            case '6':
                Capp();
            break;
            case '7':
                printf("This program isn't quite there yet, try something else meanwhile :) \n");
                //PenDrop();
            break;
            case 'q':
                whiltop = 0;
            break;
            default:
                printf("Invalid input\n");
            break;
        }
        printf("\n");
        fflush(stdout);
    }
}


void B48BBtopic2()
{
    int whiltop;
    whiltop = 1;
    
    while(whiltop == 1)
    {
        B48BBTopComm();
        printf("1. Mass Continuity Equation\n");
        printf("2. Steady-Flow energy equation\n");
        printf("3. Bernoulli's Equation\n");
        printf("4. Reynolds Number\n");
        printf("5. Newton's Law of Viscosity (Description)\n");
        printf("6. Dynamic and Kinematic Viscosity Correlations\n");
        printf("7. Velocity Profiles (Laminar and Turbulent Flow)\n");
        printf("8. Hagen-Poiseuille Equation\n");
        printf("q. Exit topic\n");
        printf("Selection [1 - 8]: ");
        
        //Allocating memory for the menu variable
        
        fgets(B48BBMenu,sizeof(B48BBMenu),stdin);
        fflush(stdout);
        printf("\n");
        switch(B48BBMenu[0])
        {
            case '1':
                MassCon();
            break;
            case '2':
                EnerCon();
            break;
            case '3':
                BernEqn();
            break;
            case '4':
                ReyNo();
            break;
            case '5':
                //NewVisc();
            break;
            case '6':
                ViscCorr();
            break;
            case '7':
                VelProfile();
            break;
            case '8':
                HagPois();
            break;
            case 'q':
                whiltop = 0;
            break;
            default:
            printf("Invalid input\n");
            break;
        }
        
        fflush(stdout);
    }
}

void B48BBtopic3()
{
    int whiltop;
    whiltop = 1;
    
    while(whiltop == 1){
        B48BBTopComm();
        printf("1. Laminar flow Frictional Pressure Loss\n");
        printf("2. General Frictional Pressure Loss\n");
        printf("3. Hydraulic mean diameter\n");
        printf("4. Pressure loss through Pipe fittings\n");
        printf("5. Pitot Static Tube\n");
        printf("6. Orifice plate meter/ Venturi Meter\n");
        printf("q. Exit topic\n\n");
        printf("Selection [1-6]: ");
        
        fgets(B48BBMenu,sizeof(B48BBMenu),stdin);
        printf("\n");
        switch(B48BBMenu[0]){
            case '1':
                HagPois();
            break;
            case '2':
                //printf("Currently under construction\n");
                //Turbulent3(1000, 0.041, 16.2, 0.01, 0.0015);
                GenPressureLoss();
            break;
            case '3':
                HydrDiam();
            break;
            case '4':
                Fittings();
            break;
            case '5':
                Pitot();
            break;
            case '6':
                Orifice();
            break;
            case '7':
                Rotameter();
            break;
            case 'q':
                whiltop = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
        fflush(stdout);
    }
}

void B48BBtopic4()
{
    B48BBTopComm();
    printf("1. Pump Selector\n");
    printf("2. Pump Sizing\n");
    printf("Selection [1 - 2]: ");
    fgets(B48BBMenu,sizeof(B48BBMenu),stdin);
    printf("\n");
    switch(B48BBMenu[0]){
        case '1':
            //Code
            break;
        case '2':
            PumpSizing();
            break;
        default:
            printf("Input not recognised\n");
            break;
    }
}
/*
void B48BBtopic5()
{
    //B48BBTopComm();
    printf("Bear with me, this is still being written...\n");
}

*/
void B48BB(){
    char topi[maxstrlen];
    int ConM; //While condition
    
    printf("Process Engineering A - Fluid Dynamics\n\n");
    ConM = 1;
    while(ConM == 1){
        printf("Please select which topic you want to access:\n");
        printf("T1: Fluid Statics\nT2: Fluid Dynamics\nT3: Frictional Pressure Loss and Flow Measurement\nT4: Pumping Systems and Pump Sizing\nT5: Non-Newtonian Fluids\nq. Exit course\n\n");
        printf("Topic ");
        fgets(topi,sizeof(topi),stdin);
        switch(topi[0]){
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
            case 'q':
                ConM = 0;
            break;
            default:
                printf("Input not recognised\n");
            break;
        }
        fflush(stdout);
    }
}
