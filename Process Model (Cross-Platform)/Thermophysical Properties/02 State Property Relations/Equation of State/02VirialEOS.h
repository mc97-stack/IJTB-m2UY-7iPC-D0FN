//
//  02VirialEOS.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 01/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef _2_Virial_Equation_of_StateVariable_h
#define _2_Virial_Equation_of_StateVariable_h

/// This subroutine is used to collect the data required to calculate an isotherm for the Virial equation of state.
/// @param polar This variable is used to control whether or not the variables required for the second virial coefficient is collected based on the molecule that the isotherm is being generated for.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol).
/// @param accFactor Acentric factor.
/// @param a Constant required for calculating B^(2) for a polar molecule.
/// @param b Constant required for calculating B^(2) for a polar molecule.
void VirialEOSVariable(int polar, double *Pc, double *Tc, double *Vc, double *accFactor, double *a, double *b);

#endif /* _1_Virial_Equation_of_StateVariable_h */

#ifndef _2_Virial_Equation_of_StateGeneralCalculation_h
#define _2_Virial_Equation_of_StateGeneralCalculation_h

/// This subroutine is used to calculate the reduced state variable.
/// @param critical Critical parameter.
/// @param process Respective parameter respective to the above criticla parameter.
double reducedProperty(double critical, double process);

#endif /* _2_Virial_Equation_of_StateGeneralCalculation_h */

#ifndef _2_Virial_Equation_of_StatePolarCalculation_h
#define _2_Virial_Equation_of_StatePolarCalculation_h
/*  These functions have currently been commented out but they are functional.
/// This subroutine is used to calculate the dimensionless dipole moment.
/// @param mu Dipole moment (Debye)
/// @param Pc Critical pressure (bar)
/// @param Tc Critical temperature (K)
double reducedDipoleMoment(double mu, double Pc, double Tc);

/// This subroutine is used to calculate a and b for a Ketone, aldehyde or nitrile compound.
/// @param mu_r Dimensionless dipole moment.
/// @param a Constant a for calculating B^(2)
/// @param b Constant b for calculating B^(2)
void group1(double mu_r, double *a, double *b);

/// This subroutine is used to calculate a and b for a ether, ammonia, hydrogen sulfide, hydrogen cyanide or an ester.
/// @param mu_r Dimensionless dipole moment.
/// @param a Constant a for calculating B^(2)
/// @param b Constant b for calculating B^(2)
void group2(double mu_r, double *a, double *b);

/// This subroutine is used to calculate a and b for a mercaptan.
/// @param mu_r Dimensionless dipole moment.
/// @param a Constant a for calculating B^(2)
/// @param b Constant b for calculating B^(2)
void group3(double mu_r, double *a, double *b);

/// This subroutine is used to calculate a and b for a monoalkylhalide.
/// @param mu_r Dimensionless dipole moment.
/// @param a Constant a for calculating B^(2)
/// @param b Constant b for calculating B^(2)
void group4(double mu_r, double *a, double *b);

/// This subroutine is used to calculate a and b for an alcohol.
/// @param mu_r Dimensionless dipole moment.
/// @param a Constant a for calculating B^(2)
/// @param b Constant b for calculating B^(2)
void group5(double mu_r, double *a, double *b);

/// This subroutine is used to calculate a and b for a phenol.
/// @param mu_r Dimensionless dipole moment ([ ]).
/// @param a Constant a for calculating B^(2)
/// @param b Constant b for calculating B^(2)
void group6(double mu_r, double *a, double *b);
*/
#endif /* _2_Virial_Equation_of_StatePolarCalculation_h */

#ifndef _2_Virial_Equation_of_StateSecondCalculation_h
#define _2_Virial_Equation_of_StateSecondCalculation_h

/// This subroutine is used to calculate B^(0) required for calculating the second virial coefficient.
/// @param Tr Reduced temperature ([ ]).
double VirialEOSB0Calc(double Tr);

/// This subroutine is used to calculate B^(1) required for calculating the second virial coefficient.
/// @param Tr Reduced temperature ([ ]).
double VirialEOSB1Calc(double Tr);

/// This subroutine is used to calculate B^(2) required for calculating the second virial coefficient for a polar molecule.
/// @param a Required constant.
/// @param b Required constant.
/// @param Tr Reduced temperature ([ ]).
double VirialEOSB2Calc(double a, double b, double Tr);

/// This subroutine is used to calculate \hat{B} required for calculating the second virial coefficient.
/// @param B0 B^(0) constant.
/// @param B1 B^(1) constant.
/// @param B2 B^(2) constant.
/// @param accFactor Accentric factor.
double VirialEOSBHat(double B0, double B1, double B2,  double accFactor);

/// This subroutine is used to calculate the second virial coefficient.
/// @param BHat \hat{B}.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
double VirialEOSBCalc(double BHat, double Pc, double Tc);

#endif /* _2_Virial_Equation_of_StateSecondCalculation_h */

#ifndef _2_Virial_Equation_of_StateThirdCalculation_h
#define _2_Virial_Equation_of_StateThirdCalculation_h

/// This subroutine is used to calculate C^(0) required for calculating the third virial coefficient.
/// @param Tr Reduced temperature ([ ]).
double VirialEOSC0Calc(double Tr);

/// This subroutine is used to calculate C^(1) required for calculating the third virial coefficient.
/// @param Tr Reduced temperature ([ ]).
double VirialEOSC1Calc(double Tr);

/// This subroutine is used to calculate \hat{C} required for calculating the third virial coefficient.
/// @param C0 C^(0).
/// @param C1 C^(1).
/// @param accFactor Accentric factor ([ ]).
double VirialEOSCHat(double C0, double C1, double accFactor);

/// This subroutine is used to calculate the third virial coefficient.
/// @param CHat \hat{C}.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (bar).
double VirialEOSCCalc(double CHat, double Pc, double Tc);

#endif /* _2_Virial_Equation_of_StateThirdCalculation_h */

#ifndef _2_Virial_Equation_of_StateEOSProfileCalculation_h
#define _2_Virial_Equation_of_StateEOSProfileCalculation_h

/// This subroutine is used to calculate the Pressure from the virial equation of state.
/// @param T System temperature (K).
/// @param V Molar volume of compound (cm3/mol).
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm6/mol2).
double VirialEOSCalc(double T, double V, double B, double C);

/// This subroutine is used to generate the isotherm related to the virial equation for a non-polar molecule.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol).
/// @param T Temperature where the isotherm is to be calculated at (K).
/// @param omega Accentric factor ([ ]).
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm6/mol2).
EOSIsotherm VirialEOSIsotherm(double Pc, double Tc, double Vc, double T, double omega, double *B, double *C);

/// This subroutine is used to generate the isotherm related to the virial equation for a polar molecule.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol).
/// @param T Temperature where the isotherm is to be calculated at (K)
/// @param omega Accentric factor ([ ]).
/// @param a Constant required for calculating B^(2).
/// @param b Constant required for calculating B^(2).
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm6/mol2).
EOSIsotherm VirialEOSIsothermPolar(double Pc, double Tc, double Vc, double T, double omega, double a, double b, double *B, double *C);

#endif /* _2_Virial_Equation_of_StateEOSProfileCalculation_h */

#ifndef _2_Virial_Equation_of_StateDisplay_h
#define _2_Virial_Equation_of_StateDisplay_h

/// This subroutine is used to display the calculated isotherm related to the virial equation for any molecule on the user console.
/// @param polar This variable is used to control what variables 
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol)
/// @param T Temperature at which the isotherm was calculated at (K).
/// @param omega Accentric factor.
/// @param a Constant used for calculating B^(2).
/// @param b Constant used for calculating B^(2).
/// @param data Struct where the isotherm is stored.
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm3/mol).
void VirialEOSDisplay(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, EOSIsotherm data, double B, double C);

#endif /* _2_Virial_Equation_of_StateDisplay_h */

#ifndef _2_Virial_Equation_of_StateWrite_h
#define _2_Virial_Equation_of_StateWrite_h

/// This subroutine is used to write the generated isotherm to a .txt file.
/// @param polar This variable is used to control what variables 
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol)
/// @param T Temperature at which the isotherm was calculated at (K).
/// @param omega Accentric factor.
/// @param a Constant used for calculating B^(2).
/// @param b Constant used for calculating B^(2).
/// @param data Struct where the isotherm is stored.
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm3/mol).
void VirialEOSWrite(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, EOSIsotherm data, double B, double C);

/// This subroutine is used to ask the user whether they would like to write the generated isotherm to a .txt file.
/// @param polar This variable is used to control what variables 
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param Vc Critical molar volume (cm3/mol)
/// @param T Temperature at which the isotherm was calculated at (K).
/// @param omega Accentric factor.
/// @param a Constant used for calculating B^(2).
/// @param b Constant used for calculating B^(2).
/// @param data Struct where the isotherm is stored.
/// @param B Second virial coefficient (cm3/mol).
/// @param C Third virial coefficient (cm3/mol).
void VirialEOSWriteSwitch(int polar, double Pc, double Tc, double Vc, double T, double omega, double a, double b, EOSIsotherm data, double B, double C);

#endif /* _2_Virial_Equation_of_StateWrite_h */
