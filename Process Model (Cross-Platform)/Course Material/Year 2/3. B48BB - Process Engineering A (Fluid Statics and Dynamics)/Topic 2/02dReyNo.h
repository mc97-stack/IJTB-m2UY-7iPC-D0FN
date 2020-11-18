//
//  02dReyNo.h
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

#ifndef ReyNoVar_h
#define ReyNoVar_h

/// This subroutine is used to collect the data required to calculate the Reynolds number.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Pipe diameter (mm).
/// @param mu Fluid viscosity (cP).
void ReyNoVariable(double *rho, double *u, double *d, double *mu);

#endif /* ReyNoVar_h */

#ifndef ReyNoCalc_h
#define ReyNoCalc_h

/// This subroutine is used to calculate the Reynolds number given the declared arguments. The function then returns the Reynolds number value after calculation.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
double ReyNoCalculation(double rho, double u, double d, double mu);

#endif /* ReyNoCalc_h */

#ifndef ReyNoDisp_h
#define ReyNoDisp_h

/// This subroutine is used to output the collected data and calculated Reynolds number to the user console.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
/// @param ReyNum Reynold's Number.
void ReyNoDisplay(double rho, double u, double d, double mu, double ReyNum);

#endif /* ReyNoDisp_h */

#ifndef ReyNoWrite_h
#define ReyNoWrite_h

/// This subroutine is used to output the collected data and calculated Reynolds number to a .txt file.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
/// @param ReyNum Reynold's Number.
void ReyNoWrite(double rho, double u, double d, double mu, double ReyNum);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
/// @param ReyNum Reynold's Number.
void ReyNoWriteSwitch(double rho, double u, double d, double mu, double ReyNum);

#endif /* ReyNoWrite_h */
