//
//  01fCapp.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
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

#ifndef CappVar_h
#define CappVar_h

/// Subroutine used to collect the data required to determine the capillary rise and pressure.
/// @param sigma Surface tension (N/m).
/// @param cang Contact angle (deg).
/// @param rho Fluid density (kg/m3).
/// @param d Cappillary tube diameter (mm).
void CappVariable(double *sigma, double *cang, double *rho, double *d);

#endif /* _1fCapp_h */

#ifndef CappCalch_h
#define CappCalch_h

/// Subroutine used to calculate the capillary rise given the arguments required. This subroutine, after calculation, returns the capillary rise (m) to the calling function.
/// @param sigma Surface tension (N/m).
/// @param cang Contact angle (rad).
/// @param rho Fluid density (kg/m3).
/// @param d Capillary tube diameter (m).
double CappCalculateHeight(double sigma, double cang, double rho, double d);

#endif /* CappCalch_h */

#ifndef CappCalcP_h
#define CappCalcP_h

/// Subroutine used to calculate the capillary pressure given the required arguments. This subroutine, after calculation, returns the capillary pressure (Pa) to the calling function.
/// @param sigma Surface tension (N/m).
/// @param cang Contact angle (rad).
/// @param d Capillary tube diameter (m).
double CappCalculatePressure(double sigma, double cang, double d);

#endif /* CappCalcP_h */

#ifndef CappDisp_h
#define CappDisp_h

/// Subroutine used to output the results of capillary rise and pressure from capillarity calculations to the user console.
/// @param sigma Surface Tension (N/m).
/// @param cang Contact angle (rad).
/// @param d Capillary tube diameter.
/// @param h Capillary rise (m).
/// @param Pc Capillary pressure (Pa). 
void CappDisplay(double sigma, double cang, double d, double h, double Pc);

#endif /* CappDisp_h */

#ifndef CappWrite_h
#define CappWrite_h

/// Subroutine used to output the results of capillary rise and pressure from capillarity calculations to a .txt file.
/// @param sigma Surface Tension (N/m).
/// @param cang Contact angle (rad).
/// @param d Capillary tube diameter (m).
/// @param h Capillary rise (m).
/// @param Pc Capillary pressure (Pa).
void CappWrite(double sigma, double cang, double d, double h, double Pc);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param sigma Surface Tension (N/m).
/// @param cang Contact angle (rad).
/// @param d Capillary tube diameter (m)
/// @param h Capillary rise (m).
/// @param Pc Capillary pressure (Pa). 
void CappWriteSwitch(double sigma, double cang, double d, double h, double Pc);

#endif /* CappWrite_h */
