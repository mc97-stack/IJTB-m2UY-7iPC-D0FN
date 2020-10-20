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
