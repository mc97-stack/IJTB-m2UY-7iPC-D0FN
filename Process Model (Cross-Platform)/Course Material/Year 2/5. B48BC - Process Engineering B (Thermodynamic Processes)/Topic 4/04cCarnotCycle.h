//
//  04cCarnotCycle.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 31/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef _4cCarnotCycleStruct_h
#define _4cCarnotCycleStruct_h

typedef struct T4CarnotCycle{
    double P[1500];
    double V[1500];
    double T[1500];
    double work[1500];
    double heat[1500];
} T4CarnotProfile;

#endif /* _4cCarnotCycleStruct_h */

#ifndef _4cCarnotCycleVariable_h
#define _4cCarnotCycleVariable_h

/// This subroutine is used to collect the data required to construct a Carnot cycle.
/// @param P1 Fluid pressure prior to entry to pump (kPa).
/// @param P2 Fluid pressure prior to entry to boiler (kPa).
/// @param P3 Fluid pressure prior to entry to turbine (kPa).
/// @param P4 Fluid pressure prior to entry to condenser (kPa).
/// @param THot Hot reservoir temperature (deg C)
/// @param TCold Cold reservoir temperature (deg C)
/// @param n Molar flowrate (kmol/s)
/// @param gamma1 Heat capacity ratio in pump ([ ]).
/// @param gamma2 Heat capacity ratio in turbine ([ ]).
void CarnotVariable(double *P1, double *P2, double *P3, double *P4, double *THot, double *TCold, double *n, double *gamma1, double *gamma2);

#endif /* _4cCarnotCycleVariable_h */

#ifndef _4cCarnotCycleCalculation_h
#define _4cCarnotCycleCalculation_h

/// This subroutine is used to calculate the process path that a fluid undertakes when performing the Carnot cycle.
/// @param P1 Fluid pressure prior to entry to pump (Pa).
/// @param P2 Fluid pressure prior to entry to boiler (Pa).
/// @param P3 Fluid pressure prior to entry to turbine (Pa).
/// @param P4 Fluid pressure prior to entry to condenser (Pa).
/// @param THot Hot reservoir temperature (K)
/// @param TCold Cold reservoir temperature (K)
/// @param n Molar flowrate (mol/s)
/// @param gamma1 Heat capacity ratio in pump ([ ]).
/// @param gamma2 Heat capacity ratio in turbine ([ ]).
/// @param worknet Net work (kW).
/// @param qhot Heat supplied to the process (kW).
/// @param qcold Heat removed from the process (kW).
T4CarnotProfile CarnotProfileCalc(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, double *worknet, double *qhot, double *qcold);

#endif /* _4cCarnotCycleCalculation_h */

#ifndef _4cCarnotCycleDisplay_h
#define _4cCarnotCycleDisplay_h

/// This subroutine is used to display the inputted parameters, calculated variables and generated profile on the user console. It also calculates the thermal efficiency of from the process descriptors and the equivalent reversible process.
/// @param P1 Fluid pressure prior to entry to pump (Pa).
/// @param P2 Fluid pressure prior to entry to boiler (Pa).
/// @param P3 Fluid pressure prior to entry to turbine (Pa).
/// @param P4 Fluid pressure prior to entry to condenser (Pa).
/// @param THot Hot reservoir temperature (K)
/// @param TCold Cold reservoir temperature (K)
/// @param n Molar flowrate (mol/s)
/// @param gamma1 Heat capacity ratio in pump ([ ]).
/// @param gamma2 Heat capacity ratio in turbine ([ ]).
/// @param profile Carnot cycle process profile.
/// @param worknet Net work (kW).
/// @param qhot Heat supplied to the process (kW).
/// @param qcold Heat removed from the process (kW).
void CarnotDisplay(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, T4CarnotProfile profile, double worknet, double qhot, double qcold);

#endif /* _4cCarnotCycleDisplay_h */

#ifndef _4cCarnotCycleWrite_h
#define _4cCarnotCycleWrite_h

/// This subroutine is used to write the inputted parameters, calculated variables and generated profile to a .txt file. It also calculates the thermal efficiency of from the process descriptors and the equivalent reversible process.
/// @param P1 Fluid pressure prior to entry to pump (Pa).
/// @param P2 Fluid pressure prior to entry to boiler (Pa).
/// @param P3 Fluid pressure prior to entry to turbine (Pa).
/// @param P4 Fluid pressure prior to entry to condenser (Pa).
/// @param THot Hot reservoir temperature (K)
/// @param TCold Cold reservoir temperature (K)
/// @param n Molar flowrate (mol/s)
/// @param gamma1 Heat capacity ratio in pump ([ ]).
/// @param gamma2 Heat capacity ratio in turbine ([ ]).
/// @param profile Carnot cycle process profile.
/// @param worknet Net work (kW).
/// @param qhot Heat supplied to the process (kW).
/// @param qcold Heat removed from the process (kW).
void CarnotWrite(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, T4CarnotProfile profile, double worknet, double qhot, double qcold);

/// This subroutine is used to ask the user whether they would like to write the inputted parameters, calculated variables and generated profile to a .txt file.
/// @param P1 Fluid pressure prior to entry to pump (Pa).
/// @param P2 Fluid pressure prior to entry to boiler (Pa).
/// @param P3 Fluid pressure prior to entry to turbine (Pa).
/// @param P4 Fluid pressure prior to entry to condenser (Pa).
/// @param THot Hot reservoir temperature (K)
/// @param TCold Cold reservoir temperature (K)
/// @param n Molar flowrate (mol/s)
/// @param gamma1 Heat capacity ratio in pump ([ ]).
/// @param gamma2 Heat capacity ratio in turbine ([ ]).
/// @param profile Carnot cycle process profile.
/// @param worknet Net work (kW).
/// @param qhot Heat supplied to the process (kW).
/// @param qcold Heat removed from the process (kW).
void CarnotWriteSwitch(double P1, double P2, double P3, double P4, double THot, double TCold, double n, double gamma1, double gamma2, T4CarnotProfile profile, double worknet, double qhot, double qcold);

#endif /* _4cCarnotCycleWrite_h */
