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

#ifndef ReyNoWrite_h
#define ReyNoWrite_h

/// This subroutine is used to output the collected data and calculated Reynolds number to a .txt file.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param ReyNum Reynold's Number
void ReyNoWrite(double rho, double u, double d, double mu, double ReyNum);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param ReyNum Reynold's Number
void ReyNoWriteCheck(double rho, double u, double d, double mu, double ReyNum);

#endif /* ReyNoWrite_h */
