//
//  03gRotameter.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef RotameterVar_h
#define RotameterVar_h

/// This subroutine is used to collect data such that the mass flow rate can be predicted from a theoretical rotameter.
/// @param C_d Discharge coefficient.
/// @param V_f Float volume (m3).
/// @param rho_f Float density (kg/m3).
/// @param rho Fluid density (kg/m3).
/// @param A_f Maximum cross-sectional area of the float (m2).
/// @param are1 Cross-sectional area of tube at point of float (m2).
/// @param are2 Annular area between float and tube at the point (m2).
void RotameterVariable(double *C_d, double *V_f, double *rho_f, double *rho, double *A_f, double *are1, double *are2);

#endif /* RotameterVar_h */

#ifndef RotameterCalc_h
#define RotameterCalc_h

/// This subroutine is used to calculate the pressure drop, mass flow rate, volumetric flow rate and fluid velocity through a rotameter.
/// @param C_d Discharge coefficient.
/// @param V_f Float volume (m3).
/// @param rho_f Float density (kg/m3).
/// @param rho Fluid density (kg/m3).
/// @param A_f Maximum cross-sectional area of the float (m2).
/// @param are1 Cross-sectional area of tube at point of float (m2).
/// @param are2 Annular area between float and tube at the point (m2).
/// @param dP Pressure loss (Pa).
/// @param m Mass flowrate (kg/ s).
/// @param Q Volumetric flowrate (m3/ s).
/// @param u Fluid velocity (m/ s).
void RotameterCalculation(double C_d, double V_f, double rho_f, double rho, double A_f, double are1, double are2, double *dP, double *m, double *Q, double *u);

#endif /* RotameterCalc_h */

#ifndef RotameterDisp_h
#define RotameterDisp_h

/// This subroutine is used to output the collected data and calculated variables to the user console.
/// @param rho Fluid density (kg/m3).
/// @param V_f Float volume (m3).
/// @param rho_f Float density (kg/m3).
/// @param A_f Maximum cross-sectional area of the float (m2).
/// @param are1 Cross-sectional area of tube at point of float (m2).
/// @param are2 Annular area between float and tube at the point (m2).
/// @param C_d Discharge Coefficient.
/// @param dP Pressure loss (Pa).
/// @param m Mass flowrate (kg/ s).
/// @param Q Volumetric flowrate (m3/ s).
/// @param u Fluid velocity (m/ s).
void RotameterDisplay(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u);

#endif /* RotameterDisp_h */

#ifndef RotameterWrite_h
#define RotameterWrite_h

/// This subroutine is used to output the collected data and calculated variables to a .txt file.
/// @param rho Fluid density (kg/m3).
/// @param V_f Float volume (m3).
/// @param rho_f Float density (kg/m3).
/// @param A_f Maximum cross-sectional area of the float (m2).
/// @param are1 Cross-sectional area of tube at point of float (m2).
/// @param are2 Annular area between float and tube at the point (m2).
/// @param C_d Discharge Coefficient.
/// @param dP Pressure loss (Pa).
/// @param m Mass flowrate (kg/ s).
/// @param Q Volumetric flowrate (m3/ s).
/// @param u Fluid velocity (m/ s).
void RotameterWrite(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u);

/// This subroutine is used to ask the user if they would like to save the results of this program to a file.
/// @param rho Fluid density (kg/m3).
/// @param V_f Float volume (m3).
/// @param rho_f Float density (kg/m3).
/// @param A_f Maximum cross-sectional area of the float (m2).
/// @param are1 Cross-sectional area of tube at point of float (m2).
/// @param are2 Annular area between float and tube at the point (m2).
/// @param C_d Discharge Coefficient.
/// @param dP Pressure loss (Pa).
/// @param m Mass flowrate (kg/ s).
/// @param Q Volumetric flowrate (m3/ s).
/// @param u Fluid velocity (m/ s).
void RotameterWriteSwitch(double rho, double V_f, double rho_f, double A_f, double are1, double are2, double C_d, double dP, double m, double Q, double u);

#endif /* RotameterWrite_h */
