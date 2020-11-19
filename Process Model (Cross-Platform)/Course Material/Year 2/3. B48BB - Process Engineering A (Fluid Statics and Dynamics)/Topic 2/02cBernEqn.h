//
//  02cBernEqn.h
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

#ifndef BernEqnVar_h
#define BernEqnVar_h

/// This subroutine is used for data collection to calculate the end pressure through Bernoulli's equation. The water hammer effect is observed is u2 is set to 0 m/s.
/// @param P1 Initial fluid pressure (kPa).
/// @param rho Fluid density (kg/ m3).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s). This value is inferred using velcalc(...) in "02aMassCon.h".
/// @param Z1 Initial fluid height (m).
/// @param Z2 Final fluid height (m).
/// @param hf Frictional head loss between points '1' and '2' (m).
void BernEqnVariable(double *P1, double *rho, double *u1, double *u2, double *Z1, double *Z2, double *hf);
 
#endif /* BernEqnVar_h */

#ifndef StatHeadCalc_h
#define StatHeadCalc_h

/// This subroutine is used to calculate the static head of a fluid (m).
/// @param P Vessel pressure (Pa).
/// @param rho Fluid density (kg/ m3).
double StaticHeadCalculation(double P, double rho);

#endif /* StatHeadCalc_h */

#ifndef DynHeadCalc_h
#define DynHeadCalc_h

/// This subroutine is used to calculate the dynamic head of a fluid (m).
/// @param u Fluid velocity (m/ s).
double DynamicHeadCalculation(double u);

#endif /* DynHeadCalc_h */

#ifndef BernEqnCalc_h
#define BernEqnCalc_h

/// This subroutine is used to calculate the total head contribution of a fluid at a process time state (m).
/// @param stathead Static head (m).
/// @param dynhead Dynamic head (m).
/// @param Z Potential head (m).
double BernEqnCalculation(double stathead, double dynhead, double Z);

#endif /* BernEqnCalc_h */

#ifndef BernEqnDisp_h
#define BernEqnDisp_h

/// This subroutine is used to output the collected data and final result to the user console.
/// @param P1 Initial fluid pressure (Pa).
/// @param P2 Final fluid pressure (Pa).
/// @param rho Fluid density (kg/ m3).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s). This value is inferred using velcalc(...).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param hf Frictional head loss between points '1' and '2' (m).
void BernEqnDisplay(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf);

#endif /* BernEqnDisp_h */

#ifndef BernEqnWrite_h
#define BernEqnWrite_h

/// This subroutine is used to output the collected data and final result to a .txt file.
/// @param P1 Initial fluid pressure (Pa).
/// @param P2 Final fluid pressure (Pa).
/// @param rho Fluid density (kg/ m3).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s). This value is inferred using velcalc(...).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param hf Frictional head loss between points '1' and '2' (m).
void BernEqnWrite(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param P1 Initial fluid pressure (Pa).
/// @param P2 Final fluid pressure (Pa).
/// @param rho Fluid density (kg/ m3).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s). This value is inferred using velcalc(...).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param hf Frictional head loss between points '1' and '2' (m).
void BernEqnWriteSwitch(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf);

#endif /* BernEqnWrite_h */
