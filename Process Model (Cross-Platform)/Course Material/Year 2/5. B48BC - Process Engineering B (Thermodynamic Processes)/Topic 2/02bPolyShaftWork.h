//
//  02bPolyShaftWork.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef PolyShaftVar_h
#define PolyShaftVar_h

/// This subroutine is used to collect the data required to calculate shaft work associated with a polytropic process.
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa)
/// @param T1 Initial system temperature (deg C)
/// @param n Moles of component in system (kmol/s)
/// @param R Specific gas constant (J/mol.K)
/// @param alpha Polytropic index
int PolyShaftVar(double *P1, double *P2, double *T1, double *n, double *R, double *alpha);

#endif /* _2bPolyShaftWork_h */

#ifndef IdealShaftCalc_h
#define IdealShaftCalc_h

/// This subroutine is used to calculate the shaft work associated with an isothermal process. This subroutine returns the shaft work in Watts (W).
/// @param n Moles of component in system (mol/s)
/// @param R Specific gas constant (J/mol.K)
/// @param T1 Initial system temperature (deg C)
/// @param P1 Initial system pressure (Pa)
/// @param P2 Final system pressure (Pa)
double IdealShaftCalc(double n, double R, double T1, double P1, double P2);

#endif /* IdealShaftCalc_h */

#ifndef PolyShaftCalc_h
#define PolyShaftCalc_h

/// This subroutine is used to calculate the shaft work associated with a polytropic process. This subroutine returns the shaft work in Watts (W).
/// @param n Moles of component in system (mol/s)
/// @param R Specific gas constant (J/mol.K)
/// @param T1 Initial system temperature (K)
/// @param P1 Initial system pressure (Pa)
/// @param P2 Final system pressure (Pa)
/// @param alpha Polytropic index
double PolyShaftCalc(double n, double R, double T1, double P1, double P2, double alpha);

#endif /* PolyShaftCalc_h */
