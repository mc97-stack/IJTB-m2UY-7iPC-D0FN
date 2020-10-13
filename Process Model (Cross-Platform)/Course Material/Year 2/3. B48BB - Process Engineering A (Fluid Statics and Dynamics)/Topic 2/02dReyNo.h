//
//  02dReyNo.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef ReyNoVar_h
#define ReyNoVar_h

/// This subroutine is used to collect the data required to calculate the Reynolds number.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (mm)
/// @param mu Fluid viscosity (cP)
void ReyNoVar(double *rho, double *u, double *d, double *mu);

#endif /* ReyNoVar_h */

#ifndef ReyNoCalc_h
#define ReyNoCalc_h

/// This subroutine is used to calculate the Reynolds number given the declared arguments. The function then returns the Reynolds number value after calculation.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
double ReyNoCalc(double rho, double u, double d, double mu);

#endif /* ReyNoCalc_h */
