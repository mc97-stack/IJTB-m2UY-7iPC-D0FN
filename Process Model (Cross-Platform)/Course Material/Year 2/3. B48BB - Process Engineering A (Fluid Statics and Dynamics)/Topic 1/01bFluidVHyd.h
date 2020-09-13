//
//  01bFluidVHyd.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global Variables
/*
 P = Hydrostatic pressure of fluid
 rho = Fluid density
 h = Height of fluid in vessel
 */

#ifndef FluidVHydVar_h
#define FluidVHydVar_h

void FluidVHydVar(double *rho, double *h);
/*  Subroutine used for data collection. Variables called within this subroutine have been defined previously as global variables. Variables local to this function are:
 input = character array for user input prior to conversion to float value
 */

#endif /* FluidVHydVar_h */

#ifndef FluidVHydCalc_h
#define FluidVHydCalc_h

double FluidVHydCalc(double rho, double h, double *P);
/*  Subroutine used to calculate the fluid hydrostatic pressure. All variables used in this function have been declared previously as global variables. The function will return the hydrostatic pressure as a double value in addition to printing the hydrostatic pressure with LaTeX formatting from running the function alone. This */

#endif /* FluidVHydCalc_h */

#ifndef FluidVHydWrite_h
#define FluidVHydWrite_h

void FluidVHydWrite(void);
/*  Subroutine used to write the program output to a file stored at any location residing in pernament memory. */

#endif /* FluidVHydWrite_h */
