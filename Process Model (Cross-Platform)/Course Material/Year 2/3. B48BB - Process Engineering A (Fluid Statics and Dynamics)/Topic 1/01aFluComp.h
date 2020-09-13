//
//  01aFluComp.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 25/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef FluCompVar_h
#define FluCompVar_h

void FluCompVar(double *P, double *V, double *n, double *T);
/*  Subroutine used for data collection, where:
 P = Absolute system pressure (Pa)
 V = System volume (m3)
 n = moles of component (mol)
 T = Absolute system temperature (K)
 */

#endif /* FluCompVar_h */

#ifndef FluCompCalc_h
#define FluCompCalc_h

double FluCompCalc(double P, double V, double n, double T);
/*  Subroutine used to calculate the fluid compressibility factor using the definition from the ideal gas law. Areas for developing this program are deriving the definition for compressibility factor from the ideal gas law. Where:
 top = numerator
 bot =  denominator
 frac = Inverse volume
 */

#endif /* FluCompCalc_h */

#ifndef FluCompWrite_h
#define FluCompWrite_h

void FluCompWrite(double P, double V, double n, double T, double c);
/*  Subroutine used to write the results of this program to a file. The results */

#endif /* FluCompWrite_h */
