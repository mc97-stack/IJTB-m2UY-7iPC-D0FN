//
//  03aJTEffect.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 27/10/2020.
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

#ifndef _3aJTEffectVariable_h
#define _3aJTEffectVariable_h

/// This subroutine is used to collect the data required to calculate the Van der Waals statement of the Joule-Thomson coefficient and associated variables.
/// @param Tc Critical temperature (deg C).
/// @param Pc Critical pressure (bar).
/// @param T System temperature (deg C).
/// @param P System pressure (kPa).
/// @param v Molar volume (m3/kmol).
/// @param c_p Heat capacity at constant pressure (J/mol.K).
void JTEffectVariable(double *Tc, double *Pc, double *T, double *P, double *v, double *c_p);

#endif /* _3aJTEffectVariable_h */

#ifndef _3aJTEffectCalculation_h
#define _3aJTEffectCalculation_h

/// This subroutine is used to calculate the Joule-Thomson coefficient using the Van der Waals equation of state.
/// @param v Molar volume (m3/mol).
/// @param c_p Heat capacity at constant pressure (J/mol.K).
/// @param T System temperature (deg C)
/// @param P System pressure (Pa)
/// @param a VdW equation repulsive term (J.m3/mol2)
/// @param b VdW equation actual molecular volume term (m3/mol)
double JTCoefficientCalculation(double v, double c_p, double T, double P, double a, double b);

/// This subroutine is used to calculate the Joule-Thomson Inversion temperature. At which point the gas will neither heat up nor cool as it expands through a Joule-Thomson device.
/// @param P System pressure (Pa)
/// @param v Molar volume (m3/mol).
/// @param a VdW equation repulsive term (J.m3/mol2)
/// @param b VdW equation actual molecular volume term (m3/mol)
double JTInvTemperatureCalculation(double P, double v, double a, double b);

#endif /* _3aJTEffectCalculation_h */

#ifndef _3aJTEffectDisplay_h
#define _3aJTEffectDisplay_h

/// This subroutine is used to display the collect and calculated data within this file.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (Pa).
/// @param T System temperature (K).
/// @param P System pressure (Pa).
/// @param v Molar volume (m3/mol).
/// @param c_p Heat capacity at constant volume (J/mol.K).
/// @param a VdW equation repulsive term (J.m3/mol2).
/// @param b VdW equation actual molecular volume term (m3/mol).
/// @param mu_JT Joule-Thomson coefficient.
/// @param Tinv Inversion temperature.
void JTEffectDisplay(double Tc, double Pc, double T, double P, double v, double c_p, double a, double b, double mu_JT, double Tinv);

#endif /* _3aJTEffectDisplay_h */

#ifndef _3aJTEffectWrite_h
#define _3aJTEffectWrite_h

/// This subroutine is used to write the inputted parameters and calculated data to a .txt file.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (Pa).
/// @param T System temperature (K).
/// @param P System pressure (Pa).
/// @param v Molar volume (m3/mol).
/// @param c_p Heat capacity at constant volume (J/mol.K).
/// @param a VdW equation repulsive term (J.m3/mol2).
/// @param b VdW equation actual molecular volume term (m3/mol).
/// @param mu_JT Joule-Thomson coefficient.
/// @param Tinv Inversion temperature.
void JTEffectWrite(double Tc, double Pc, double T, double P, double v, double c_p, double a, double b, double mu_JT, double Tinv);

/// This subroutine is used to ask the user whether they would like to save the inputted parameters and calculated data to a .txt file.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (Pa).
/// @param T System temperature (K).
/// @param P System pressure (Pa).
/// @param v Molar volume (m3/mol).
/// @param c_p Heat capacity at constant volume (J/mol.K).
/// @param a VdW equation repulsive term (J.m3/mol2).
/// @param b VdW equation actual molecular volume term (m3/mol).
/// @param mu_JT Joule-Thomson coefficient.
/// @param Tinv Inversion temperature.
void JTEffectWriteSwitch(double Tc, double Pc, double T, double P, double v, double c_p, double a, double b, double mu_JT, double Tinv);

#endif /* _3aJTEffectWrite_h */
