//
//  03dcEquivLeng.h
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

#ifndef EquivLengStruct
#define EquivLengStruct

typedef struct EquivLengthFittings{
    double data[15];
    int count[15];
    double dP_f[15];
    double h_f[15];
} EquivLenFits;

#endif /* EquivLengStruct */

#ifndef EquivLengData_h
#define EquivLengData_h

/// This subroutine is used to write the equivalent length database constants to the struct where data is being collected to.
/// @param input Struct where equivalent length data is being collected to.
EquivLenFits EquivLengData(EquivLenFits input);

/// This subroutine is used to collect the necessary data to calculate the pressure and head losses through pipe fittings through the equivalent length method.
/// @param data Struct where equivalent length data is being collected to.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Pipe diameter (mm)
/// @param mu Fluid viscosity (cP)
/// @param vareps Absolute surface roughness (mm)
/// @param phi Friction factor (This value is calculated using "phicalc(...)" from "03bGenPressureLoss.h").
EquivLenFits EquivLengVariable(EquivLenFits data, double *rho, double *u, double *d, double *mu, double *vareps, double *phi);

#endif /* EquivLengData_h */

#ifndef EquivLengCalc_h
#define EquivLengCalc_h

/// This subroutine is used to calculate the pressure loss through a specific pipe fitting. This value is then multiplied by the multiple of the specific fitting.
/// @param count Number of fittings
/// @param phi Friction factor
/// @param L_e Equivalent length (m).
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
double EquivLengCalculateLoss(int count, double phi, double L_e, double rho, double u, double d);

/// This subroutine is used to calculate the equivalent length from the database constant and internal pipe diameter.
/// @param input L_e/d value. This can be found in "[struct].data" section of the above declared struct.
/// @param d Internal pipe diameter (m)
double EquivLengCalculateL_e(double input, double d);

/// This subroutine is used to generate the calculation table for estimating the pressure and head losses through the Equivalent length method.
/// @param data Struct where data requires manipulation.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Internal pipe diameter (m).
/// @param phi Friction factor ([ ]).
EquivLenFits EquivLengFinalTable(EquivLenFits data, double rho, double u, double d, double phi);

#endif /* EquivLengCalc_h */

#ifndef EquivLengDisp_h
#define EquivLengDisp_h

/// This subroutine is used to present the collected data and calculated parameters on the console.
/// @param table Equivalent length data table.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Internal pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
/// @param vareps Pipe absolute roughness (m).
/// @param phi Friction Factor.
/// @param totalP Total pressure loss through pipe fittings.
/// @param totalh Total head loss through pipe fittings.
void EquivLengDisplay(EquivLenFits table, double rho, double u, double d, double mu, double vareps, double phi, double totalP, double totalh);

#endif /* EquivLengDisp_h */

#ifndef EquivLengWrite_h
#define EquivLengWrite_h

/// This subroutine is used to write the collected data and calculated parameters to a .txt file.
/// @param table Equivalent length data table.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Internal pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
/// @param vareps Pipe absolute roughness (m).
/// @param phi Friction Factor.
/// @param totalP Total pressure loss through pipe fittings.
/// @param totalh Total head loss through pipe fittings.
void EquivLengWrite(EquivLenFits table, double rho, double u, double d, double mu, double vareps, double phi, double totalP, double totalh);
/// This subroutine is used to ask the user if they would like to write the results to a .txt file.
/// @param table Equivalent length data table.
/// @param rho Fluid density (kg/m3).
/// @param u Fluid velocity (m/s).
/// @param d Internal pipe diameter (m).
/// @param mu Fluid viscosity (Pa.s).
/// @param vareps Pipe absolute roughness (m).
/// @param phi Friction Factor.
/// @param totalP Total pressure loss through pipe fittings.
/// @param totalh Total head loss through pipe fittings.
void EquivLengWriteSwitch(EquivLenFits table, double rho, double u, double d, double mu, double vareps, double phi, double totalP, double totalh);

#endif /* EquivLengWrite_h */

#ifndef EquivLeng_h
#define EquivLeng_h

/// This subroutine is used to guide the computer through collecting the data and performing the calculation of pressure and head losses through the Equivalent Length method.
void EquivalentLength(void);

#endif /* _3dcEquivLeng_h */
