//
//  B48BC.c
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 23/06/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <stdio.h>
#include <stdlib.h>

//  Custom header files
#include "Courses.h"
#include "B48BCMenu.h"
#include "B48BC_T1.h"
#include "B48BC_T2.h"
#include "B48BC_T3.h"
#include "B48BC_T4.h"

#define maxstrlen 128

void B48BCTopComm(){
    printf("Please select from the following programs: \n");
}

void B48BCtopic1(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BCTopComm();
        printf("1. General Volume Work (Polytropic Process)\n2. Isothermal Volume Work\n3. Isobaric Volume Work\n4. Isochoric Heat\n5. Adiabatic Volume Work.\n");
        printf("q. Exit topic\n\n");
        printf("Selection [1 - 5]: ");
        
        fgets(input, sizeof(input), stdin);
        switch(input[0]){
            case '1':
                Polytropic();
                break;
            case '2':
                Isothermal();
                break;
            case '3':
                Isobaric();
                break;
            case '4':
                Isochoric();
                break;
            case '5':
                Adiabatic();
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
    }
}

void B48BCtopic2(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BCTopComm();
        printf("1. Reciprocating compressor.\n2. Polytropic process shaft work\n3. First law for open systems.\n");
        printf("q. Exit topic. \n\n");
        printf("Selections [1 - 3]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0]){
            case '1':
                Compressor();
                break;
            case '2':
                PolyShaftWork();
                break;
            case '3':
                OpenFirstLaw();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 3.\n");
                break;
        }
    }
}

void B48BCtopic3(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BCTopComm();
        printf("1. Joule-Thomson Effect.\n2. Multistage Gas Compression.\n3. Multistage Gas Compression Shaft Work Estimation\n");
        printf("q. Exit topic. \n\n");
        printf("Selections [1 - 3]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0]){
            case '1':
                JouleThomsonEffect();
                break;
            case '2':
                MultistageCompressor();
                break;
            case '3':
                MultistageShaftWork();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 3.\n");
                break;
        }
    }
}

void B48BCtopic4(){
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1){
        B48BCTopComm();
        printf("1. Thermal Efficiency.\n2. Coefficient of Performance.\n3. Carnot Cycle\n4. The Clausius Inequality\n");
        printf("q. Exit topic. \n\n");
        printf("Selection [1 - 4]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0]){
            case '1':
                ThermalEfficiency();
                break;
            case '2':
                CoefficientofPerformance();
                break;
            case '3':
                CarnotCycle();
                break;
            case '4':
                ClausiusInequality();
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer between 1 and 4.\n");
                break;
        }
    }
}

void B48BCtopic5(){
    B48BCTopComm();
}

void B48BCtopic6(){
    B48BCTopComm();
}

void B48BC(){
    char input[maxstrlen];      // Variable where character input is stored.
    int control = 0;            // Variable used to control user input.
    printf("Process Engineering B - Thermodynamics Processes\n\n");
    
    control = 1;
    while(control == 1){
        printf("Please select from the following topics:\n");
        printf("T1: Closed systems and Processes\nT2: Open systems\nT3: Throttling and Multi-stage Compression\nT4: The Second Law of Thermodynamics\nT5: Entropy\nT6: Chemical Reactions\n\nq. Quit course\n\n");
        printf("Topic ");
        fgets(input,sizeof(input),stdin);
        switch(input[0]){
            case '1':
                B48BCtopic1();
                break;
            case '2':
                B48BCtopic2();
                break;
            case '3':
                B48BCtopic3();
                break;
            case '4':
                B48BCtopic4();
                break;
            case '5':
                B48BCtopic5();
                break;
            case '6':
                B48BCtopic6();
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
        fflush(stdout);
    }
}
