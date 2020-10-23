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

#define maxstrlen 128

char B48BCTopMenu[maxstrlen];
static int inputguard = 0; //While for topics

void B48BCTopComm(){
    printf("Please select from the following programs: \n");
}

void B48BCtopic1(){
    inputguard = 1;
    while(inputguard == 1){
        B48BCTopComm();
        printf("1. General Volume Work (Polytropic Process)\n2. Isothermal Volume Work\n3. Isobaric Volume Work\n4. Isochoric Heat\n5. Adiabatic Volume Work\n");
        printf("q. Exit topic\n\n");
        printf("Selection [1-5]: ");
        
        fgets(B48BCTopMenu, sizeof(B48BCTopMenu), stdin);
        switch(B48BCTopMenu[0]){
            case '1':
                Polytropic();
                inputguard = 0;
                break;
            case '2':
                Isothermal();
                inputguard = 0;
                break;
            case '3':
                Isobaric();
                inputguard = 0;
                break;
            case '4':
                Isochoric();
                inputguard = 0;
                break;
            case '5':
                Adiabatic();
                inputguard = 0;
                break;
            case '0':
            case 'Q':
            case 'q':
                inputguard = 0;
                break;
            default:
                printf("Input not recognised.\n");
                break;
        }
    }
}

void B48BCtopic2(){
    inputguard = 1;
    while(inputguard == 1){
        B48BCTopComm();
        printf("1. Reciprocating compressor.\n2. Polytropic process shaft work\n3. First law for open systems\n");
        printf("q. Exit topic. \n\n");
        printf("Selections [1 - 3]: ");
        fgets(B48BCTopMenu, sizeof(B48BCTopMenu), stdin);
        switch(B48BCTopMenu[0]){
            case '1':
                Compressor();
                inputguard = 0;
                break;
            case '2':
                PolyShaftWork();
                inputguard = 0;
                break;
            case '3':
                OpenFirstLaw();
                inputguard = 0;
                break;
            case '0':
            case 'Q':
            case 'q':
                inputguard = 0;
                break;
            default:
                printf("Input not recognised \n");
                break;
        }
    }
    //  Isothermal reciprocating compressor
    
    //  Shaft work for polytropic process
    
    //  First law for open systems (Different to the steady flow energy equation in B48BB)
    
    //  Irreversibilities are dealth with in Energy gen
}

void B48BCtopic3(){
    B48BCTopComm();
}

void B48BCtopic4(){
    B48BCTopComm();
}

void B48BCtopic5(){
    B48BCTopComm();
}

void B48BCtopic6(){
    B48BCTopComm();
}

void B48BC(){
    char topi[maxstrlen];
    int ConM = 0;
    
    printf("Process Engineering B - Thermodynamics Processes\n\n");
    ConM = 1;
    while(ConM == 1){
        printf("Please select from the following topics:\n");
        printf("T1: Closed systems and Processes\nT2: Open systems\nT3: Throttling and Multi-stage Compression\nT4: The Second Law of Thermodynamics\nT5: Entropy\nT6: Chemical Reactions\n\nq. Quit course\n\n");
        printf("Topic ");
        fgets(topi,sizeof(topi),stdin);
        switch(topi[0]){
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
