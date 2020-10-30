//
//  01eAdiabatic.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 07/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef AdiaVariable_h
#define AdiaVariable_h

/// This subroutine is used for collecting data for calculating the volume work for a adiabatic process.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Pressure-Temperature equation.
/// @param P1 Initial system pressure (kPa).
/// @param P2 Final system pressure (kPa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (deg C).
/// @param n Moles of component in system (kmol/s).
/// @param gamma Heat capacity ratio ([ ]).
void AdiaVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T1, double *n, double *gamma);

#endif /* AdiaVariable_h */

#ifndef AdiaVolume_h
#define AdiaVolume_h

/// This subroutine is used to calculate the adiabatic volume work from the system pressure and volume.
/// @param P1 Initial system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param gamma Heat capacity ratio ([ ]).
double AdiaVolume(double P1, double V1, double V2, double gamma);

#endif /* AdiaVolume_h */

#ifndef AdiaTemperature_h
#define AdiaTemperature_h

/// This subroutine is used to calculate the adiabatic volume work from the system pressure and temperature.
/// @param n Moles of component in system (mol/s).
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param gamma Heat capacity ratio ([ ]).
double AdiaTemperature(double n, double T1, double P1, double P2, double gamma);

#endif /* AdiaTemperature_h */

#ifndef AdiaFinalPress_h
#define AdiaFinalPress_h

/// This subroutine is used to calculate the final pressure using the Pressure-Volume relationship for an adiabat.
/// @param P1 Initial system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param gamma Heat capacity ratio ([ ]).
double AdiaFinalPress(double P1, double V1, double V2, double gamma);

#endif /* AdiaFinalPress_h */

#ifndef AdiaFinalVol_h
#define AdiaFinalVol_h

/// This subroutine is used to calculate the final volume using the Pressure-Temperature relationship for an adiabat.
/// @param V1 Initial system volume (m3).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param gamma Heat capacity ratio ([ ]).
double AdiaFinalVol(double V1, double P1, double P2, double gamma);

#endif /* AdiaFinalVol_h */

#ifndef AdiaFinalTemp_h
#define AdiaFinalTemp_h

/// This subroutine is used to calculate the final temperature using the Pressure-Temperature relationship for an adiabat.
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param gamma Heat capacity ratio ([ ]).
double AdiaFinalTemp(double T1, double P1, double P2, double gamma);

#endif /* AdiaFinalTemp_h */

#ifndef AdiaProfile_h
#define AdiaProfile_h

#include "B48BC_T1.h"

/// This subroutine is used to determine the process profile given the input parameters. This subroutine requires "IdealTemperature(...)" and "IdealVolume(...)" from "IdealGasLaw.h" to function as intended.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Pressure-Temperature equation.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
T1ThermoProf AdiaProfile(int method, double P1, double P2, double V1, double V2, double T1, double n, double gamma);
/* 
 Pressure|Volume|Temperature|Work|Work_Cum.
 */

#endif /* AdiaProfile_h */

#ifndef AdiaProcDisp_h
#define AdiaProcDisp_h

/// Subroutine used to output the collected data and generated dataset from AdiaProfile(...) to the user console.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param profile Process profile.
void AdiaProcDisplay(double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma, T1ThermoProf profile);

#endif /* AdiaProcDisp_h */

#ifndef AdiaProcWrite_h
#define AdiaProcWrite_h

/// Subroutine used to write the collected data and generated dataset from AdiaProfile(...) to a .txt file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param profile Process profile.
void AdiaProcWrite(double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma, T1ThermoProf profile);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param gamma Heat capacity ratio ([ ]).
/// @param profile Process profile.
void AdiaProcWriteSwitch(double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma, T1ThermoProf profile);

#endif /* AdiaProcWrite_h */
