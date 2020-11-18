//
//  02bPolyShaftWork.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
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

#ifndef PolyShaftVar_h
#define PolyShaftVar_h

/// This subroutine is used to collect the data required to calculate shaft work associated with a polytropic process.
/// @param P1 Initial system pressure (kPa).
/// @param P2 Final system pressure (kPa).
/// @param T1 Initial system temperature (deg C).
/// @param n Moles of component in system (kmol/s).
/// @param R Specific gas constant (J/mol.K).
/// @param alpha Polytropic index.
int PolyShaftVariable(double *P1, double *P2, double *T1, double *n, double *R, double *alpha);

#endif /* _2bPolyShaftWork_h */

#ifndef IdealShaftCalc_h
#define IdealShaftCalc_h

/// This subroutine is used to calculate the shaft work associated with an isothermal process. This subroutine returns the shaft work in Watts (W).
/// @param n Moles of component in system (mol/s).
/// @param R Specific gas constant (J/mol.K).
/// @param T1 Initial system temperature (deg C).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
double IdealShaftCalculation(double n, double R, double T1, double P1, double P2);

#endif /* IdealShaftCalc_h */

#ifndef PolyShaftCalc_h
#define PolyShaftCalc_h

/// This subroutine is used to calculate the shaft work associated with a polytropic process. This subroutine returns the shaft work in Watts (W).
/// @param n Moles of component in system (mol/s).
/// @param R Specific gas constant (J/mol.K).
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param alpha Polytropic index.
double PolyShaftCalculation(double n, double R, double T1, double P1, double P2, double alpha);

#endif /* PolyShaftCalc_h */

#ifndef PolyShaftDisp_h
#define PolyShaftDisp_h

/// This subroutine is used to ouput the collected data and calculated shaft work to the user console.
/// @param n Moles of component in system (mol/s).
/// @param R Specific gas constant (J/mol.K).
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param alpha Polytropic index.
/// @param W_S Shaft Work (kW).
void PolyShaftDisplay(double n, double R, double T1, double P1, double P2, double alpha, double W_S);

#endif /* PolyShaftDisp_h */

#ifndef PolyShaftWrite_h
#define PolyShaftWrite_h

/// This subroutine is used to write the collected data and calculated shaft work into a .txt file.
/// @param n Moles of component in system (mol/s).
/// @param R Specific gas constant (J/mol.K).
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param alpha Polytropic index.
/// @param W_S Shaft Work (kW).
void PolyShaftWrite(double n, double R, double T1, double P1, double P2, double alpha, double W_S);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param n Moles of component in system (mol/s).
/// @param R Specific gas constant (J/mol.K).
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param alpha Polytropic index.
/// @param W_S Shaft Work (kW).
void PolyShaftWriteSwitch(double n, double R, double T1, double P1, double P2, double alpha, double W_S);

#endif /* PolyShaftWrite_h */
