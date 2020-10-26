//
//  02bEnerCon.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef EnthalpyConv_h
#define EnthalpyConv_h

/// This subroutine is used to convert between internal energy and enthalpy, After calculation, the subroutine returns the value of enthalpy to the calling function.
/// @param u Internal energy (kJ/ kg)
/// @param P Fluid pressure (Pa)
/// @param rho Fluid density (kg/m3)
double EnthalpyConversion(double u, double P, double rho);

#endif /* EnthalpyConv_h */

#ifndef EnerConVar_h
#define EnerConVar_h

/// Subroutine used for collecting the data required to validate the steady-flow energy equation.
/// @param h1 Initial stream enthalpy. (kJ/ kg)
/// @param h2 Final stream enthalpy. (kJ/ kg)
/// @param u1 Initial fluid velocity. (m/ s)
/// @param u2 Final fluid velocity. (m/ s)
/// @param z1 Initial fluid height. (m)
/// @param z2 Final fluid height. (m)
/// @param q Process heat. (kJ/ kg)
/// @param w Process work. (kJ/ kg)
void EnerConVariable(double *h1, double *h2, double *u1, double *u2, double *z1, double *z2, double *q, double *w);

#endif /* EnerConVar_h */

#ifndef EnerConFluCalc_h
#define EnerConFluCalc_h

/// This subroutine used to calculate the fluid intensive portion at a process endstate. The subroutine returns the energy content of the fluid after some manipulation of the required arguments.
/// @param h Enthalpy (kJ/kg)
/// @param u Fluid velocity (m/s)
/// @param z Relative height (m)
double EnerConFluidCalculation(double h, double u, double z);

#endif /* EnerConFluCalc_h */

#ifndef EnerConProCalc_h
#define EnerConProCalc_h

/// This subroutine is used to determine the total energy input into the open system. The subroutine, after calculation, returns to sum of the heat and work inputted into the system.
/// @param q Process heat. (kJ/kg)
/// @param w Process work. (kJ/kg)
double EnerConProcessCalculation(double q, double w);

#endif /* EnerConProCalc_h */

#ifndef EnerConProDisp_h
#define EnerConProDisp_h

/// This subroutine is used to output the results of this program to the user console.
/// @param h1 Initial stream enthalpy. (kJ/ kg)
/// @param h2 Final stream enthalpy. (kJ/ kg)
/// @param u1 Initial fluid velocity. (m/ s)
/// @param u2 Final fluid velocity. (m/ s)
/// @param z1 Initial fluid height. (m)
/// @param z2 Final fluid height. (m)
/// @param q Process heat. (kJ/ kg)
/// @param w Process work. (kJ/ kg)
/// @param check Value of inequality
void EnerConDisplay(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double check);

#endif /* EnerConProDisp_h */

#ifndef EnerConProWrite_h
#define EnerConProWrite_h

/// This subroutine is used to save the results of this program to a .txt file.
/// @param h1 Initial stream enthalpy. (kJ/ kg)
/// @param h2 Final stream enthalpy. (kJ/ kg)
/// @param u1 Initial fluid velocity. (m/ s)
/// @param u2 Final fluid velocity. (m/ s)
/// @param z1 Initial fluid height. (m)
/// @param z2 Final fluid height. (m)
/// @param q Process heat. (kJ/ kg)
/// @param w Process work. (kJ/ kg)
/// @param check Value of inequality
void EnerConWrite(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double check);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param h1 Initial stream enthalpy. (kJ/ kg)
/// @param h2 Final stream enthalpy. (kJ/ kg)
/// @param u1 Initial fluid velocity. (m/ s)
/// @param u2 Final fluid velocity. (m/ s)
/// @param z1 Initial fluid height. (m)
/// @param z2 Final fluid height. (m)
/// @param q Process heat. (kJ/ kg)
/// @param w Process work. (kJ/ kg)
/// @param check Value of inequality
void EnerConWriteSwitch(double h1, double h2, double u1, double u2, double z1, double z2, double q, double w, double check);

#endif /* EnerConProWrite_h */
