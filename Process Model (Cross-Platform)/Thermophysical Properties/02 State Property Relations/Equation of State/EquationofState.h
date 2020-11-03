//
//  EquationofState.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 01/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef EquationofState_h
#define EquationofState_h

typedef struct EOSDiagram{
    double P[1000];
    double V[1000];
    double T[1000];
    double Z[1000];
} EOSIsotherm;

#endif /* EquationofState_h */
