//
//  02fViscCorr.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
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

#ifndef ViscCorrVar_h
#define ViscCorrVar_h

/// This subroutine is used to collect the data required for standard fluid viscosity correlations.
/// @param a Parameter 1 for correlation.
/// @param b Parameter 2 for correlation.
/// @param T System temperature (Units dependent on correlation  being used).
/// @param rho Fluid density.
void ViscCorrVariable(double *a, double *b, double *T, double *rho);

#endif /* ViscCorrVar_h */

#ifndef LiqViscCalc_h
#define LiqViscCalc_h

/// This subroutine is used to calculate the liquid viscosity.
/// @param a Parameter 1 for correlation.
/// @param b Parameter 2 for correlation.
/// @param T System temperature (Units dependent on correlation  being used).
double LiquidViscCalculation(double a, double b, double T);

#endif /* LiqViscCalc_h */

#ifndef VapViscCalc_h
#define VapViscCalc_h

/// This subroutine is used to calculate the vapour viscosity.
/// @param a Parameter 1 for correlation.
/// @param b Parameter 2 for correlation.
/// @param T System temperature (Units dependent on correlation  being used).
double VapourViscCalculation(double a, double b, double T);

#endif /* VapViscCalc_h */

#ifndef KinVisc_h
#define KinVisc_h

/// This subroutine is used to calculate the kinematic viscosity.
/// @param mu Dynamic viscosity.
/// @param rho Fluid density.
double KineticVisc(double mu, double rho);

#endif /* KinVisc_h */

#ifndef ViscDisp_h
#define ViscDisp_h

/// This subroutine is used to output the viscosity correlation results to the user console.
/// @param method Variable used to tell the subroutine whether the liquid or vapour correlation was used in the program. This subroutine then modifies behaviour accordingly.
/// @param a Correlation constant.
/// @param b Correlation constant.
/// @param T Temperature.
/// @param rho Fluid density.
/// @param mu Fluid dynamic viscosity.
/// @param upsi Fluid kinematic viscosity.
void ViscDisplay(int method, double a, double b, double T, double rho, double mu, double upsi);

#endif /* ViscDisp_h */

#ifndef ViscWrite_h
#define ViscWrite_h

/// This subroutine is used to write the viscosity correlation results to a .txt file.
/// @param method Variable used to tell the subroutine whether the liquid or vapour correlation was used in the program. This subroutine then modifies behaviour accordingly.
/// @param a Correlation constant.
/// @param b Correlation constant.
/// @param T Temperature.
/// @param rho Fluid density.
/// @param mu Fluid dynamic viscosity.
/// @param upsi Fluid kinematic viscosity.
void ViscWrite(int method, double a, double b, double T, double rho, double mu, double upsi);

/// This subroutine is used to ask the user if they would like to save the results of this program to a file.
/// @param method Variable used to tell the subroutine whether the liquid or vapour correlation was used in the program. This subroutine then modifies behaviour accordingly.
/// @param a Correlation constant.
/// @param b Correlation constant.
/// @param T Temperature.
/// @param rho Fluid density.
/// @param mu Fluid dynamic viscosity.
/// @param upsi Fluid kinematic viscosity.
void ViscWriteSwitch(int method, double a, double b, double T, double rho, double mu, double upsi);

#endif /* ViscWrite_h */
