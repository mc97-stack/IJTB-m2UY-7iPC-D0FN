//
//  01aPolytropic.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef PolyVariable_h
#define PolyVariable_h

/// This subroutine is used for collecting data for calculating the volume work for a polytropic process. Logic has also been implemented to collect the temperatures first in case an isothermal process is specified although the user specifies an isothermal process when asked in the pseudomain function.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa)
/// @param V1 Initial system volume (m3)
/// @param T1 Initial system temperature (deg C)
/// @param T2 Final system temperature (deg C)
/// @param n Moles of component in system (kmol/s)
/// @param R Specific gas constant (kJ/ kmol.K)
/// @param alpha Polytropic index ([ ]).
void PolyVariable(int method, double *P1, double *P2, double *V1, double *T1,double *T2, double *n, double *R, double *alpha);

#endif /* _1aPolytropic_h */

#ifndef PolyVolume_h
#define PolyVolume_h

/// Subroutine used to calculate the volume work for a polytropic process utilising the system pressure and volume.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param alpha Polytropic index ([ ]).
double PolyVolume(double P1, double P2, double V1, double alpha);

#endif /* PolyVolume_h */

#ifndef PolyTemperature_h
#define PolyTemperature_h

/// Subroutine used to calculate the volume work for a polytropic process utilising the changes to system temperature.
/// @param n Moles of component in system (kmol/s)
/// @param R Specific gas constant (kJ/ kmol.K)
/// @param T1 Initial system temperature (K)
/// @param T2 Final system temperature (K)
/// @param alpha Polytropic index ([ ]).
double PolyTemperature(double n, double R, double T1, double T2, double alpha);

#endif /* PolyTemperature_h */

#ifndef PolyFinalVolume_h
#define PolyFinalVolume_h

/// Subroutine used to determine the final volume from the pressure-volume relationship for a polytropic process.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param alpha Polytropic index ([ ]).
double PolyFinalVolume(double P1, double P2, double V1, double alpha);

#endif /* PolyFinalVolume_h */

#ifndef PolyFinalPressure_h
#define PolyFinalPressure_h

/// Subroutine used to determine the final pressure from the pressure-temperature relationship for a polytropic process.
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param alpha Polytropic index ([ ]).
double PolyFinalPressure(double T1, double T2, double P1, double alpha);

#endif /* PolyFinalPressure_h */

#ifndef PolyFinalTemperature_h
#define PolyFinalTemperature_h

/// Subroutine used to determine the final temperature from the pressure-temperature relationship for a polytropic process.
/// @param T1 Initial system temperature (K).
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param alpha Polytropic index ([ ]).
double PolyFinalTemperature(double T1, double P1, double P2, double alpha);

#endif /* PolyFinalTemperature_h */

#ifndef PolyProfile_h
#define PolyProfile_h

/// This subroutine is used to determine the process profile given the input parameters.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P1 Initial system pressure (Pa)
/// @param P2 Final system pressure (Pa)
/// @param V1 Initial system volume (m3)
/// @param T1 Initial system temperature (K)
/// @param T2 Final system temperature (K)
/// @param n Moles of component in system (mol/s)
/// @param R Specific gas constant (J/ mol.K)
/// @param alpha Polytropic index ([ ]).
T1ThermoProf PolyProfile(int method, double P1, double P2, double V1, double T1, double T2, double n, double R, double alpha);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* PolyProfile_h */
