//
//  02Compressibility.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef _2CompressibilityCalculation_h
#define _2CompressibilityCalculation_h

typedef struct ZFactor{
    double Z[1000];
    double P[1000];
    double T[1000];
} ZFactor;

/// This subroutine is used to calculate the isotherm for a Compressibility-factor graph for a non-polar molecule.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param T Isotherm temperature
/// @param omega Acentric factor.
/// @param B Second virial coefficient (cm3/mol)
/// @param C Third virial coefficient (cm6/mol2)
ZFactor VirialEOSCompIsotherm(double Pc, double Tc, double T, double omega, double *B, double *C);

/// This subroutine is used to calculate the isotherm for a Compressibiltiy-factor graph for a polar molecule.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param T Isotherm temperature
/// @param omega Acentric factor.
/// @param a Constant required for calculating B^(2).
/// @param b Constant required for calculating B^(2).
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm6/mol2).
ZFactor VirialEOSCompIsothermPolar(double Pc, double Tc, double T, double omega, double a, double b, double *B, double *C);

#endif /* _2CompressibilityCalculation_h */

#ifndef _2CompressibilityDisplay_h
#define _2CompressibilityDisplay_h

/// This subroutine is used to display the generated Compressibiltiy factor isotherm.
/// @param polar This variable is used to control whether the a and b constants required for calculating B^(2) are required or not.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol)
/// @param T Isotherm temperature
/// @param omega Acentric factor.
/// @param a Constant required for calculating B^(2).
/// @param b Constant required for calculating B^(2).
/// @param data Compressibility factor isotherm.
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm6/mol2).
void VirialEOSCompDisplay(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, ZFactor data, double B, double C);

#endif /* _2CompressibilityDisplay_h */

#ifndef _2CompressibilityWrite_h
#define _2CompressibilityWrite_h

/// This subroutine is used to write the compressibility factor isotherm to a .txt file.
/// @param polar This variable is used to control whether the a and b constants required for calculating B^(2) are required or not.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol)
/// @param T Isotherm temperature
/// @param omega Acentric factor.
/// @param a Constant required for calculating B^(2).
/// @param b Constant required for calculating B^(2).
/// @param data Compressibility factor isotherm.
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm6/mol2).
void VirialEOSCompWrite(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, ZFactor data, double B, double C);

#endif /* _2CompressibilityWrite_h */
