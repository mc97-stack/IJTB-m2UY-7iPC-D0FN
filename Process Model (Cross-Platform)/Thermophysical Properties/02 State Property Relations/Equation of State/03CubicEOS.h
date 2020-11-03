//
//  03CubicEOS.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef _3CubicEOSVariable_h
#define _3CubicEOSVariable_h

/// This subroutine is used to collect the required component specific data to determine an isotherm for a P-V-T surface.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param omega Acentric factor.
void CubicEOSVariable(double *Pc, double *Tc, double *omega);

#endif /* _3CubicEOSVariable_h */

#ifndef _3CubicEOSCalculation_h
#define _3CubicEOSCalculation_h

/// This subroutine is used to calculate the repulsive term in the Van der Waals Equation of State.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
double VdWcalculateA(double Tc, double Pc);

/// This subroutine is used to calculate the term actual molecular volume term in the Van der Waals Equation of State.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
double VdWcalculateB(double Tc, double Pc);

/// This subroutine is used to calculate the repulsive term in the Redlich-Kwong Equation of State.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
/// @param T Isotherm temperature (K).
double RKcalculateA(double Tc, double Pc, double T);

/// This subroutine is used to calculate the actual molecular volume term in the Redlich-Kwong Equation of State.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
double RKcalculateB(double Tc, double Pc);

/// This subroutine is used to calculate the acentric factor function for the Soave-Redlich-Kwong Equation of State.
/// @param omega Acentric factor ([ ]).
double SRKcalculateAcFunc(double omega);

/// This subroutine is used to calculate the repulsive term in the Redlich-Kwong Equation of State (Soave modification).
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
/// @param T Isotherm temperature (K).
/// @param omega Acentric factor ([ ]).
double SRKcalculateA(double Tc, double Pc, double T, double omega);

/// This subroutine is used to calculate the acentric factor function for the Peng-Robinson Equation of State.
/// @param omega Acentric factor ([ ]).
double PRcalculateAcFunc(double omega);

/// This subroutine is used to calculate the repulsive term in the Peng-Robinson Equation of State.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
/// @param T Isotherm temperature (K).
/// @param omega Acentric Factor ([ ]).
double PRcalculateA(double Tc, double Pc, double T, double omega);

/// This subroutine is used to calculate the actual molecular volume term in the Peng-Robinson Equation of State.
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
double PRcalculateB(double Tc, double Pc);

#include "EquationofState.h"

/// This subroutine is used to generate the isotherm according to the general cubic equation of state.
/// @param T Isotherm temperature.
/// @param a Repulsive term ((bar.cm6)/(mol2))
/// @param b Actual molecular volume (cm3/mol)
/// @param u Equation-specific constant.
/// @param w Equation-specific constant.
EOSIsotherm CubicEOSIsotherm(double T, double a, double b, double u, double w);

#endif /* _3CubicEOSCalculation_h */

#ifndef _3CubicEOSDisplay_h
#define _3CubicEOSDisplay_h

/// This subroutine is used to display the inputted parameters and generated isotherm on the user console.
/// @param eqn This variable is used to control some of the text output within this subroutine. N.B. '5' is not a permitted argument since this will say that all equations are being called when this subroutine can only output one equation at a time.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param omega Acentric factor ([ ]).
/// @param T Isotherm temperature (K)
/// @param a Repulsive term in the general cubic equation of state ((bar.cm6)/(mol2))
/// @param b Actual molecular volume constant for the general cubic equation of state (cm3/mol).
/// @param Isotherm Struct where the isotherm data is stored.
void CubicEOSDisplay(int eqn, double Pc, double Tc, double omega, double T, double a, double b, EOSIsotherm Isotherm);

#endif /* _3CubicEOSDisplay_h */

#ifndef _3CubicEOSWrite_h
#define _3CubicEOSWrite_h

/// This subroutine is used to write the inputted parameters and generated isotherm to a .txt file.
/// @param eqn This variable is used to control some of the text output within this subroutine. N.B. '5' is not a permitted argument since this will say that all equations are being called when this subroutine can only output one equation at a time.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param omega Acentric factor ([ ]).
/// @param T Isotherm temperature (K)
/// @param a Repulsive term in the general cubic equation of state ((bar.cm6)/(mol2))
/// @param b Actual molecular volume constant for the general cubic equation of state (cm3/mol).
/// @param Isotherm Struct where the isotherm data is stored.
void CubicEOSWrite(int eqn, double Pc, double Tc, double omega, double T, double a, double b, EOSIsotherm Isotherm);

/// This subroutine is used to ask whether the user would like to display or write the calculated subroutine results either to the user console or a .txt file.
/// @param mode This variable is used to control whether the display or write functions are performed. (1) = Display. (2) = Write.
/// @param eqn This variable is used to control some of the text output within this subroutine. 
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param omega Acentric factor ([ ]).
/// @param T Isotherm temperature (K)
/// @param VdWa Repulsive term in the van der Waals equation of state ((bar.cm6)/(mol2))
/// @param VdWb Actual molecular volume constant for the van der Waals equation of state (cm3/mol).
/// @param RKa Repulsive term in the Redlich-Kwong equation of state ((bar.cm6)/(mol2))
/// @param RKb Actual molecular volume constant for the Redlich-Kwong equation of state (cm3/mol).
/// @param SRKa Repulsive term in the Soave-Redlich-Kwong cubic equation of state ((bar.cm6)/(mol2))
/// @param SRKb Actual molecular volume constant for the Soave-Redlich-Kwong equation of state (cm3/mol).
/// @param PRa Repulsive term in the Peng-Robinson equation of state ((bar.cm6)/(mol2))
/// @param PRb Actual molecular volume constant for the Peng-Robinson equation of state (cm3/mol).
/// @param VdWIsotherm Struct where the isotherm data for the van der Waals Equation of State is stored.
/// @param RKIsotherm Struct where the isotherm data for the Redlich-Kwong Equation of State is stored.
/// @param SRKIsotherm Struct where the isotherm data for the Soave-Redlich-Kwong Equation of State is stored.
/// @param PRIsotherm Struct where the isotherm data for the Peng-Robinson Equation of State is stored.
void CubicEOSSwitch(int mode, int eqn, double Pc, double Tc, double omega, double T, double VdWa, double VdWb, double RKa, double RKb, double SRKa, double SRKb, double PRa, double PRb, EOSIsotherm VdWIsotherm, EOSIsotherm RKIsotherm, EOSIsotherm SRKIsotherm, EOSIsotherm PRIsotherm);

#endif /* _3CubicEOSWrite_h */
