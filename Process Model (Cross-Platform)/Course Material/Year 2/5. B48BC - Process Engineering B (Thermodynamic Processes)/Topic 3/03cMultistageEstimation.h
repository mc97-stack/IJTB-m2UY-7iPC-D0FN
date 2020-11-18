//
//  03cMultistageEstimation.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 28/10/2020.
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

#ifndef _3cMultistageEstimationVariable_h
#define _3cMultistageEstimationVariable_h

/// This subroutine is used to collect the required data to estimate the total shaft work required by a multistage gas compression.
/// @param P1 Initial system pressure (kPa).
/// @param P2 Final system pressure (kPa).
/// @param T1 System temperature before compression (deg C).
/// @param mol Molar flowrate through the compressor (kmol/s).
/// @param N Number of compression stages (up to and including 6 stages).
/// @param gamma Heat capacity ratio ([ ]).
void MSShaftWorkVariable(double *P1, double *P2, double *T1, double *mol, int *N, double *gamma);

#endif /* _3cMultistageEstimationVariable_h */

#ifndef _3cMultistageEstimationCalculation_h
#define _3cMultistageEstimationCalculation_h

/// This subroutine is used to calculate the shaft work contribution attributed to a pressure ratio assuming complete intercooling between stages..
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param T1 System temperature before compression (K).
/// @param mol Molar flowrate through the compressor (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param N Number of compression stages.
double MSShaftWorkEquation(double P1, double P2, double T1, double mol, double gamma, double N);

/// This subroutine is used to split the given pressure ratio into smaller segments to improve the accuracy of the equation.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param T1 System temperature before compression (K).
/// @param mol Molar flowrate through the compressor (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param N Number of compression stages.
double MSShaftWorkCalculation(double P1, double P2, double T1, double mol, double gamma, double N);

#endif /* _3cMultistageEstimationCalculation_h */

#ifndef _3cMultistageEstimationDisplay_h
#define _3cMultistageEstimationDisplay_h

/// This subroutine is used to display the results of this program on the user console.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param T1 System temperature before compression (K).
/// @param mol Molar flowrate through the compressor (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param N Number of compression stages.
/// @param shaftwork Total shaft work calculated with "MSShaftWorkCalculation(...)".
void MSShaftWorkDisplay(double P1, double P2, double T1, double mol, double gamma, double N, double shaftwork);

#endif /* _3cMultistageEstimationDisplay_h */

#ifndef _3cMultistageEstimationWrite_h
#define _3cMultistageEstimationWrite_h

/// This subroutine is used to write this subroutine's collected data and calculated results to a .txt file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param T1 System temperature before compression (K).
/// @param mol Molar flowrate through the compressor (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param N Number of compression stages.
/// @param shaftwork Total shaft work calculated with "MSShaftWorkCalculation(...)".
void MSShaftWorkWrite(double P1, double P2, double T1, double mol, double gamma, double N, double shaftwork);

/// This subroutine is used to check whether the user would like to write the results of this subroutine to a .txt file or not.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param T1 System temperature before compression (K).
/// @param mol Molar flowrate through the compressor (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param N Number of compression stages.
/// @param shaftwork Total shaft work calculated with "MSShaftWorkCalculation(...)".
void MSShaftWorkWriteSwitch(double P1, double P2, double T1, double mol, double gamma, double N, double shaftwork);

#endif /* _3cMultistageEstimationWrite_h */
