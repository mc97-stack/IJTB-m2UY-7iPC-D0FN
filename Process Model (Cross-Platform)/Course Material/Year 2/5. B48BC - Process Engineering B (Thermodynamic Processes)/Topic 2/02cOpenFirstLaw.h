//
//  02cOpenFirstLaw.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

typedef struct T2StateEnergy{
    double enthalpy;
    double kinenergy;
    double potenergy;
} T2StateEnergy;

#ifndef OpenFirstLawVarProc_h
#define OpenFirstLawVarProc_h

/// This subroutine collects values associated with the unit operation under examination.
/// @param q Specific process heat (kJ/ kmol)
/// @param w_s Specific shaft work (kJ/ kmol)
void OpenFirstLawVarProc(double *q, double *w_s);

#endif /* OpenFirstLawVarProc_h */

#ifndef OpenFirstLawVar_h
#define OpenFirstLawVar_h

/// This subroutine collects values associated with the fluid streams at a particular time state.
/// @param ins Timestate indicator
T2StateEnergy OpenFirstLawVar(int ins);

#endif /* OpenFirstLawVar_h */

#ifndef OpenFirstLawCalc_h
#define OpenFirstLawCalc_h

/// This subroutine is used to calculate the state of the open system.
/// @param q Specific process heat
/// @param w_s Specific shaft work
/// @param state1 Fluid energy content at state 1
/// @param state2 Fluid energy content at state 2
double OpenFirstLawCalc(double q, double w_s, T2StateEnergy state1, T2StateEnergy state2);

#endif /* OpenFirstLawCalc_h */


/// Subroutine used to extract the fluid velocity from the kinetic energy.
/// @param kinenergy Kinetic energy (kJ/kmol)
double VelCalc(double kinenergy);
/// Subroutine used to extract the fluid height from the potential energy
/// @param potenergy Potential energy (kJ/kmol)
double HeiCalc(double potenergy);
/// Subroutine used to write the input variables and evaluated system state to a .txt file
/// @param state1 State 1 energy contribution
/// @param state2 State 2 energy contribution
/// @param q Process Heat
/// @param w_s Process shaft work
/// @param sysstate Inequality between process energy and fluid energy contributions
void OpenFirstLawWrite(T2StateEnergy state1,T2StateEnergy state2, double q, double w_s, double sysstate);
