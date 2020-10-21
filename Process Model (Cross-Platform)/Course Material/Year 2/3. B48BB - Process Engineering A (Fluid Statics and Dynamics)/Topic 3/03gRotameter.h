//
//  03gRotameter.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 dP = Pressure differential across the float (Pa)
 m = Mass flowrate (kg/s)
 Q = Volumetric flowrate (m3/s)
 u = Fluid point velocity (m/s)
 C_d = Discharge coefficient
 V_f = Float volume (m3)
 rho_f = Float density (kg/m3)
 rho = Fluid density (kg/m3)
 A_f = Maximum cross-sectional area of the float
 are1 = Cross-sectional area of tube at point of float (m2)
 are2 = Annular area between float and tube at the point (m2)
 */
#ifndef RotameterVar_h
#define RotameterVar_h

/// This subroutine is used to collect data such that the mass flowrate can be predicted from a theoretical rotameter.
/// @param C_d Discharge coefficient
/// @param V_f Float volume (m3)
/// @param rho_f Float density (kg/m3)
/// @param rho Fluid density (kg/m3)
/// @param A_f Maximum cross-sectional area of the float (m2)
/// @param are1 Cross-sectional area of tube at point of float (m2)
/// @param are2 Annular area between float and tube at the point (m2)
void RotameterVar(double *C_d, double *V_f, double *rho_f, double *rho, double *A_f, double *are1, double *are2);

#endif /* RotameterVar_h */

#ifndef RotameterCalc_h
#define RotameterCalc_h

/// This subroutine is used to calculate the pressure drop, mass flowrate, volumetric flowrate and fluid velocity through a rotameter.
/// @param C_d Discharge coefficient
/// @param V_f Float volume (m3)
/// @param rho_f Float density (kg/m3)
/// @param rho Fluid density (kg/m3)
/// @param A_f Maximum cross-sectional area of the float (m2)
/// @param are1 Cross-sectional area of tube at point of float (m2)
/// @param are2 Annular area between float and tube at the point (m2)
/// @param dP Pressure loss (Pa)
/// @param m Mass flowrate (kg/ s)
/// @param Q Volumetric flowrate (m3/ s)
/// @param u Fluid velocity (m/ s)
void RotameterCalc(double C_d, double V_f, double rho_f, double rho, double A_f, double are1, double are2, double *dP, double *m, double *Q, double *u);

#endif /* RotameterCalc_h */

#ifndef RotameterWrite_h
#define RotameterWrite_h

/// This subroutine is used to output the collected data and calculated variables to a .txt file.
/// @param rho Fluid density (kg/m3)
/// @param V_f Float volume (m3)
/// @param rho_f Float density (kg/m3)
/// @param A_f Maximum cross-sectional area of the float (m2)
/// @param are1 Cross-sectional area of tube at point of float (m2)
/// @param are2 Annular area between float and tube at the point (m2)
/// @param C_d Discharge Coefficient
/// @param dP Pressure loss (Pa)
/// @param m Mass flowrate (kg/ s)
/// @param Q Volumetric flowrate (m3/ s)
/// @param u Fluid velocity (m/ s)
void RotameterWrite(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u);

#endif /* RotameterWrite_h */
