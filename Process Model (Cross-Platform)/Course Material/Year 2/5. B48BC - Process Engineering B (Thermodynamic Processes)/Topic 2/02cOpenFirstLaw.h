//
//  02cOpenFirstLaw.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
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

#ifndef OpFirstLawStruct
#define OpFirstLawStruct

typedef struct T2StateEnergy{
    double enthalpy;
    double kinenergy;
    double potenergy;
} T2StateEnergy;

#endif /* OpFirstLawStruct */

#ifndef OpenFirstLawVarProc_h
#define OpenFirstLawVarProc_h

/// This subroutine collects values associated with the unit operation under examination.
/// @param q Specific process heat (kJ/ kmol).
/// @param w_s Specific shaft work (kJ/ kmol).
void OpenFirstLawProcessVariable(double *q, double *w_s);

#endif /* OpenFirstLawVarProc_h */

#ifndef OpenFirstLawVar_h
#define OpenFirstLawVar_h

/// This subroutine collects values associated with the fluid streams at a particular time state.
/// @param ins Timestate indicator.
T2StateEnergy OpenFirstLawFluidVariable(int ins);

#endif /* OpenFirstLawVar_h */

#ifndef OpenFirstLawCalc_h
#define OpenFirstLawCalc_h

/// This subroutine is used to calculate the state of the open system.
/// @param q Specific process heat (J/kmol).
/// @param w_s Specific shaft work (J/kmol).
/// @param state1 Fluid energy content at state 1 (J/kmol).
/// @param state2 Fluid energy content at state 2 (J/kmol).
double OpenFirstLawCalculation(double q, double w_s, T2StateEnergy state1, T2StateEnergy state2);

#endif /* OpenFirstLawCalc_h */

#ifndef OpenInitialValue_h
#define OpenInitialValue_h

/// Subroutine used to calculate the values of velocity and height from the first law applied to an open system.
/// @param state State energy contribution.
/// @param u Fluid velocity.
/// @param z Fluid height.
void OpenInitialValue(T2StateEnergy state, double *u, double *z);

#endif /* OpenInitialValue_h */

#ifndef OpenFirstLawDisp_h
#define OpenFirstLawDisp_h

/// Subroutine used to output the input variables and evaluated system state to the user console.
/// @param state1 State 1 energy contribution (J/kmol).
/// @param state2 State 2 energy contribution (J/kmol).
/// @param q Process Heat (J/kmol).
/// @param w_s Process shaft work (J/kmol).
/// @param sysstate Inequality between process energy and fluid energy contributions (J/kmol).
void OpenFirstLawDisplay(T2StateEnergy state1,T2StateEnergy state2, double q, double w_s, double sysstate);

#endif /* OpenFirstLawDisp_h */

#ifndef OpenFirstLawWrite_h
#define OpenFirstLawWrite_h

/// Subroutine used to write the input variables and evaluated system state to a .txt file
/// @param state1 State 1 energy contribution (J/kmol).
/// @param state2 State 2 energy contribution (J/kmol).
/// @param q Process Heat (J/kmol).
/// @param w_s Process shaft work (J/kmol).
/// @param sysstate Inequality between process energy and fluid energy contributions (J/kmol).
void OpenFirstLawWrite(T2StateEnergy state1,T2StateEnergy state2, double q, double w_s, double sysstate);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param state1 State 1 energy contribution (J/kmol).
/// @param state2 State 2 energy contribution (J/kmol).
/// @param q Process Heat (J/kmol).
/// @param w_s Process shaft work (J/kmol).
/// @param sysstate Inequality between process energy and fluid energy contributions (J/kmol). 
void OpenFirstLawWriteSwitch(T2StateEnergy state1,T2StateEnergy state2, double q, double w_s, double sysstate);

#endif /* OpenFirstLawWrite_h */
