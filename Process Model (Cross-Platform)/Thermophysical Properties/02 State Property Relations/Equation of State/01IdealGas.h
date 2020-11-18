//
//  01IdealGas.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 01/11/2020.
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

#ifndef _1IdealGasVariable_h
#define _1IdealGasVariable_h

/// This subroutine is used to collect the temperature at which the isotherm according to the Ideal Gas law.
/// @param T Temperature at which the isotherm should be generated (deg C).
void IdealEOSVariable(double *T);

#endif /* _1IdealGasVariable_h */

#ifndef _1IdealGasCalculation_h
#define _1IdealGasCalculation_h

/// This subroutine is used to calculate the pressure according to the Ideal Gas law.
/// @param V Molar volume (cm3/mol).
/// @param T Isotherm Temperature (K).
double IdealEOSCalculation(double V, double T);

/// This subroutine is used to generate the isotherm along which the ideal gas law is true.
/// @param T Isotherm temperature (K).
EOSIsotherm IdealEOSIsotherm(double T);

#endif /* _1IdealGasCalculation_h */

#ifndef _1IdealGasDisplay_h
#define _1IdealGasDisplay_h

/// This subroutine is used to display the inputted parameter and generated isotherm on the user console.
/// @param T Isotherm temperature (K).
/// @param data Isotherm.
void IdealEOSDisplay(double T, EOSIsotherm data);

#endif /* _1IdealGasDisplay_h */

#ifndef _1IdealGasWrite_h
#define _1IdealGasWrite_h

/// This subroutine is used to write the inputted parameter and generated isotherm to a .txt file.
/// @param T Isotherm temperature (K).
/// @param data Isotherm.
void IdealEOSWrite(double T, EOSIsotherm data);

/// This subroutine is used to ask the user whether they would like to save the inputted parameter and generated isotherm to a .txt file.
/// @param T Isotherm temperature (K).
/// @param data Isotherm.
void IdealEOSWriteSwitch(double T, EOSIsotherm data);

#endif /* _1IdealGasWrite_h */
