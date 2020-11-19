//
//  02bEnerCon.h
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

#ifndef EnerConVar_h
#define EnerConVar_h

/// This subroutine is used for collecting the data required to validate the steady-flow energy equation.
/// @param h1 Initial stream enthalpy (kJ/ kg).
/// @param h2 Final stream enthalpy (kJ/ kg).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param q Process heat (kJ/ kg).
/// @param w Process work (kJ/ kg).
void EnerConVariable(double *h1, double *h2, double *u1, double *u2, double *z1, double *z2, double *q, double *w);

#endif /* EnerConVar_h */

#ifndef EnthalpyConv_h
#define EnthalpyConv_h

/// This subroutine is used to convert between internal energy and enthalpy. After calculation, the subroutine returns the value of enthalpy to the calling function.
/// @param u Internal energy (kJ/ kg).
/// @param P Fluid pressure (Pa).
/// @param rho Fluid density (kg/m3).
double EnthalpyConversion(double u, double P, double rho);

#endif /* EnthalpyConv_h */

#ifndef EnerConFluCalc_h
#define EnerConFluCalc_h

/// This subroutine used to calculate the fluid intensive portion at a process time state. The subroutine returns the energy content of the fluid after some manipulation of the required arguments.
/// @param h Enthalpy (J/kg).
/// @param u Fluid velocity (m/s).
/// @param z Relative height (m).
double EnerConFluidCalculation(double h, double u, double z);

#endif /* EnerConFluCalc_h */

#ifndef EnerConProCalc_h
#define EnerConProCalc_h

/// This subroutine is used to determine the total energy input into the open system. The subroutine, after calculation, returns to sum of the heat and work inputted into the system.
/// @param q Process heat (J/kg).
/// @param w Process work (J/kg).
double EnerConProcessCalculation(double q, double w);

#endif /* EnerConProCalc_h */

#ifndef EnerConProDisp_h
#define EnerConProDisp_h

/// This subroutine is used to output the results of this program to the user console.
/// @param h1 Initial stream enthalpy (J/ kg).
/// @param h2 Final stream enthalpy (J/ kg).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param q Process heat (J/ kg).
/// @param w Process work (J/ kg).
/// @param state1 Total energy content at state 1 (J/kg).
/// @param state2 Total energy content at state 2 (J/kg)
/// @param process Net energy into/out of process (J/kg).
/// @param check Value of inequality.
void EnerConDisplay(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double state1, double state2, double process, double check);

#endif /* EnerConProDisp_h */

#ifndef EnerConProWrite_h
#define EnerConProWrite_h

/// This subroutine is used to save the results of this program to a .txt file.
/// @param h1 Initial stream enthalpy (J/ kg).
/// @param h2 Final stream enthalpy (J/ kg).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param q Process heat (J/ kg).
/// @param w Process work (J/ kg).
/// @param state1 Total energy content at state 1 (J/kg).
/// @param state2 Total energy content at state 2 (J/kg)
/// @param process Net energy into/out of process (J/kg).
/// @param check Value of inequality.
void EnerConWrite(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double state1, double state2, double process, double check);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param h1 Initial stream enthalpy (J/ kg).
/// @param h2 Final stream enthalpy (J/ kg).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param q Process heat (J/ kg).
/// @param w Process work (J/ kg).
/// @param state1 Total energy content at state 1 (J/kg).
/// @param state2 Total energy content at state 2 (J/kg)
/// @param process Net energy into/out of process (J/kg).
/// @param check Value of inequality.
void EnerConWriteSwitch(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double state1, double state2, double process, double check);

#endif /* EnerConProWrite_h */
