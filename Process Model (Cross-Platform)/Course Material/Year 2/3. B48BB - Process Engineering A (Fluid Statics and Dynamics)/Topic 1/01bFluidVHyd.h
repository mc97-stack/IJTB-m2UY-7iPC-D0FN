//
//  01bFluidVHyd.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef FluidVHydVar_h
#define FluidVHydVar_h

/// Subroutine used for collecting the data required for calculating the fluid hydrostatic pressure.
/// @param rho Fluid density (kg/m3).
/// @param h Height of fluid (m).
void FluidVHydVar(double *rho, double *h);

#endif /* FluidVHydVar_h */

#ifndef FluidVHydCalc_h
#define FluidVHydCalc_h

/// Subroutine used to calculate the fluid hydrostatic pressure. The value of fluid hydrostatic pressure is returned to the calling function.
/// @param rho Fluid density (kg/m3).
/// @param h Height of fluid (m).
double FluidVHydCalc(double rho, double h);
/*  Subroutine used to calculate the fluid hydrostatic pressure. All variables used in this function have been declared previously as global variables. The function will return the hydrostatic pressure as a double value in addition to printing the hydrostatic pressure with LaTeX formatting from running the function alone. This */

#endif /* FluidVHydCalc_h */
