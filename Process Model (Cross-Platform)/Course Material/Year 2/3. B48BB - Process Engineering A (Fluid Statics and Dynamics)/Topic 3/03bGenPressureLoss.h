//
//  03bGenPressureLoss.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef PressLossVariable_h
#define PressLossVariable_h

/// This subroutine is used to collect the data required for estimating the pressure loss of any incompressible fluid generally flowing within the range of 0 < Re < 10,000,000
/// @param rho Fluid density (kg/ m3).
/// @param u Fluid velocity (m/ s).
/// @param d Pipe diameter (mm).
/// @param mu Fluid viscosity (Pa. s).
/// @param L Pipe length (m).
/// @param vareps Absolute roughness (mm). This value is only asked for if Reynolds Number exceeds 2500.
void PressLossVariable(double *rho, double *u, double *d, double *mu, double *L, double *vareps);

#endif /* PressLossVariable_h */

#ifndef phi_h
#define phi_h

/// This subroutine is used to calculate the friction factor dependent on the Reynolds number and absolute roughness of the pipe. After finding the friction factor, the value is returned to the calling function.
/// @param rho Fluid density (kg/ m3).
/// @param u Fluid velocity (m/ s).
/// @param d Pipe diameter (m).
/// @param mu Fluid viscosity (Pa. s).
/// @param vareps Absolute roughness (mm).
double phicalc(double rho, double u, double d, double mu, double vareps);

#endif /* phi_h */

#ifndef LossCalculation_h
#define LossCalculation_h

/// This subroutine is used to estimate the frictional pressure loss given the stated arguments. This subroutine then returns the pressure loss to the calling function.
/// @param phi Friction factor ([ ])
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param rho Fluid density (kg/ m3).
/// @param u Fluid velocity (m/ s).
double LossCalculation(double phi, double L, double d, double rho, double u);

#endif /* LossCalculation_h */

#ifndef PressLossWrite_h
#define PressLossWrite_h

/// Subroutine used to write the collected data and calculated values for pressure loss and friction factor to a .txt file
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param L Pipe length (m)
/// @param vareps Pipe absolute roughness (m)
/// @param phi Friction factor
/// @param dP Frictional Pressure Loss (Pa)
void PressLossWrite(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param L Pipe length (m)
/// @param vareps Pipe absolute roughness (m)
/// @param phi Friction factor
/// @param dP Frictional Pressure Loss (Pa)
void PressLossWriteCheck(double rho, double u, double d, double mu, double L, double vareps, double phi, double dP);

#endif /* PressLossWrite_h */
