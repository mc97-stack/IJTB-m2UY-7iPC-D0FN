//
//  02aMassCon.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef MasConVarCol_h
#define MasConVarCol_h

/// This subroutine is used to collect the data required to determine the average fluid velocity, volumetric flowrate and mass flowrate.
/// @param rho1 Initial fluid density (kg/ m3)
/// @param rho2 Final fluid density (kg/ m3)
/// @param d1 Initial pipe diameter (mm)
/// @param d2 Final pipe diameter (mm)
/// @param u1 Initial fluid velocity (m/ s)
void MassConVar(double *rho1, double *rho2, double *d1, double *d2, double *u1);

#endif /* MasConVarCol_h */

#ifndef VeloCalc_h
#define VeloCalc_h

/// This subroutine is used to calculate the final fluid velocity at some point past the initial measurement. After calculation, this function returns the value of u2 to the calling funtion.
/// @param u1 Initial fluid velocity (m/s)
/// @param d1 Pipe diameter at starting point (m)
/// @param d2 Pipe diameter at endpoint (m)
double VelCalc(double u1, double d1, double d2);

#endif /* VeloCalc_h */

#ifndef VoluFloCalc_h
#define VoluFloCalc_h

/// This subroutine is used to calculate the volumetric flowrate from the fluid velocity and pipe diameter. This calculated value is then returned to the calling function.
/// @param u Average fluid velocity (m/ s)
/// @param d Pipe diameter (m)
double VolFloCalc(double u, double d);

#endif /* VoluFloCalc_h */

#ifndef MassFloCalc_h
#define MassFloCalc_h

/// This subroutine is used to calculate the mass flowrate from the given arguments. This calculated value is then returned to the calling function.
/// @param rho fluid density (kg/m3)
/// @param d Pipe diameter (m)
/// @param u Fluid velocity (m/s)
double MassFloCalc(double rho, double d, double u);

#endif /* MassFloCalc_h */
