//
//  02hHagPois.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 21/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef HagPoisVar_h
#define HagPoisVar_h

/// This subroutine is used to collect the data required to calculate the pressure loss of a fluid flowing with laminar properties through the Hagen-Poiseuille equation.
/// @param u Fluid velocity (m/ s).
/// @param mu Fluid viscosity (cP).
/// @param L Horizontal pipe length (m).
/// @param d Pipe diameter  (mm).
void HagPoisVariable(double *u, double *mu, double *L, double *d);

#endif /* HagPoisVar_h */

#ifndef HagPoisCalc_h
#define HagPoisCalc_h

/// This subroutine is used to collect the data required to calculate the pressure loss of a fluid flowing with laminar properties through the Hagen-Poiseuille equation.
/// @param u Fluid velocity (m/ s).
/// @param mu Fluid viscosity (Pa. s).
/// @param L Horizontal pipe length (m).
/// @param d Pipe diameter  (m).
double HagPoisCalculation(double u, double mu, double L, double d);

#endif /* HagPoisCalc_h */

#ifndef HagPoisDisp_h
#define HagPoisDisp_h

/// This subroutine is used to output the data collected and calculated pressure loss to the user console.
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param dP Fluid pressure loss (Pa).
void HagPoisDisplay(double u, double mu, double L, double d, double dP);

#endif /* HagPoisDisp_h */

#ifndef HagPoisWrite_h
#define HagPoisWrite_h

/// This subroutine is used to write the data collected and calculated pressure loss to a .txt file
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param dP Fluid pressure loss (Pa).
void HagPoisWrite(double u, double mu, double L, double d, double dP);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param u Fluid velocity (m/s).
/// @param mu Fluid viscosity (Pa.s).
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param dP Fluid pressure loss (Pa).
void HagPoisWriteSwitch(double u, double mu, double L, double d, double dP);

#endif /* HagPoisWrite_h */
