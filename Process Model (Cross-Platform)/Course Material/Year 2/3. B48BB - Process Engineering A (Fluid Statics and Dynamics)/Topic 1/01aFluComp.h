//
//  01aFluComp.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef FluCompVar_h
#define FluCompVar_h

/// Subroutine used for collecting data to calculate the fluid coefficient of compressibility
/// @param P Absolute system pressure (Pa)
/// @param V System volume (m3)
/// @param n Moles of component (mol)
/// @param T Absolute system temperatre (K)
void FluCompVar(double *P, double *V, double *n, double *T);

#endif /* FluCompVar_h */

#ifndef FluCompCalc_h
#define FluCompCalc_h

/// Subroutine used to calculate the fluid compressibility factor from the ideal gas law.
/// @param P Absolute system pressure (Pa)
/// @param V System volume (m3)
/// @param n Moles of component (mol)
/// @param T Absolute system temperatre (K)
double FluCompCalc(double P, double V, double n, double T);

#endif /* FluCompCalc_h */

#ifndef FluCompWrite_h
#define FluCompWrite_h

/// Subroutine used to write results of this program to a text file.
/// @param P Absolute system pressure (Pa)
/// @param V System volume (m3)
/// @param n Moles of component (mol)
/// @param T Absolute system temperatre (K)
/// @param c Fluid coefficient of compressibility
void FluCompWrite(double P, double V, double n, double T, double c);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param P Absolute system pressure (Pa)
/// @param V System volume (m3)
/// @param n Moles of component (mol)
/// @param T Absolute system temperatre (K)
/// @param c Fluid coefficient of compressibility
void FluCompWriteCheck(double P, double V, double n, double T, double c);

#endif /* FluCompWrite_h */
