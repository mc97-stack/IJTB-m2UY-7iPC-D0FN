//
//  01aFluComp.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/08/2020.
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

#ifndef FluCompVar_h
#define FluCompVar_h

/// This subroutine is used to collect the data to required calculate the fluid coefficient of compressibility.
/// @param P Absolute system pressure (Pa).
/// @param V System volume (m3).
/// @param n Moles of component (mol).
/// @param T Absolute system temperatre (K).
void FluCompVariable(double *P, double *V, double *n, double *T);

#endif /* FluCompVar_h */

#ifndef FluCompCalc_h
#define FluCompCalc_h

/// This subroutine is used to calculate the fluid compressibility factor from the ideal gas law.
/// @param P Absolute system pressure (Pa).
/// @param V System volume (m3).
/// @param n Moles of component (mol).
/// @param T Absolute system temperatre (K).
double FluCompCalculation(double P, double V, double n, double T);

#endif /* FluCompCalc_h */

#ifndef FluCompDisp_h
#define FluCompDisp_h

/// This subroutine is used to output the inputted variables and program results to the user console.
/// @param P Absolute system pressure (Pa).
/// @param V System volume (m3).
/// @param n Moles of component (mol).
/// @param T Absolute system temperatre (K).
/// @param c Fluid coefficient of compressibility.
void FluCompDisplay(double P, double V, double n, double T, double c);

#endif /* FluCompDisp_h */

#ifndef FluCompWrite_h
#define FluCompWrite_h

/// This subroutine is used to write the results of this program to a text file.
/// @param P Absolute system pressure (Pa).
/// @param V System volume (m3).
/// @param n Moles of component (mol).
/// @param T Absolute system temperatre (K).
/// @param c Fluid coefficient of compressibility.
void FluCompWrite(double P, double V, double n, double T, double c);

/// This subroutine is used to ask the user if they would like to save the results of this program to a file.
/// @param P Absolute system pressure (Pa).
/// @param V System volume (m3).
/// @param n Moles of component (mol).
/// @param T Absolute system temperatre (K).
/// @param c Fluid coefficient of compressibility.
void FluCompWriteSwitch(double P, double V, double n, double T, double c);

#endif /* FluCompWrite_h */
