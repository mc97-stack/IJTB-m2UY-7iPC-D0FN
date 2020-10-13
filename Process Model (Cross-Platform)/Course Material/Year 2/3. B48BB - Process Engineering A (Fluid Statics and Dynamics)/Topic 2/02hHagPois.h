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
/// @param u Fluid velocity (m/ s)
/// @param mu Fluid viscosity (cP)
/// @param L Horizontal pipe length (m)
/// @param d Pipe diameter  (mm)
void HagPoisVar(double *u, double *mu, double *L, double *d);

#endif /* HagPoisVar_h */

#ifndef HagPoisCalc_h
#define HagPoisCalc_h

/// This subroutine is used to collect the data required to calculate the pressure loss of a fluid flowing with laminar properties through the Hagen-Poiseuille equation.
/// @param u Fluid velocity (m/ s)
/// @param mu Fluid viscosity (Pa. s)
/// @param L Horizontal pipe length (m)
/// @param d Pipe diameter  (m)
double HagPoisCalc(double u, double mu, double L, double d);

#endif /* HagPoisCalc_h */
