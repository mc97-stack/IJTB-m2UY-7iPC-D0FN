//
//  01cIsobaric.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
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

#ifndef IsobVariable_h
#define IsobVariable_h

/// This subroutine is used for collecting data for calculating the volume work for a isobaric process.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P System pressure (kPa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (deg C).
/// @param T2 Final system temperature (deg C).
/// @param n Moles of component in system (kmol/s).
void IsobVariable(int method, double *P, double *V1,double *V2, double *T1, double *T2, double *n);

#endif /* IsobVariable_h */

#ifndef IsobVolume_h
#define IsobVolume_h

/// This subroutine is used to calculate the volume work done associated with a change in volume for an isobaric process.
/// @param P  System pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
double IsobVolume(double P, double V1, double V2);

#endif /* IsobVolume_h */

#ifndef IsobTemperature_h
#define IsobTemperature_h

/// This subroutine is used to calculate the volume work done associated with a change in temperature for an isobaric process.
/// @param n Moles of component in system (mol/s).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
double IsobTemperature(double n, double T1, double T2);

#endif /* IsobTemperature_h */

#ifndef IsobFinalTemperature_h
#define IsobFinalTemperature_h

/// This subroutine calculates the final system temperature from the combined gas law modified for an isobaric process.
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
double IsobFinalTemperature(double V1, double V2, double T1);

#endif /* IsobFinalTemperature_h */

#ifndef IsobProfile_h
#define IsobProfile_h

#include "B48BC_T1.h"

/// This subroutine is used to calculate the process profile associated with an isobaric process. This subroutine requires "IdealTemperature(...)" and "IdealGasLaw.h" to function as intended.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P System pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
T1ThermoProf IsobProfile(int method, double P, double V1, double V2, double T1, double T2, double n);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* IsobProfile_h */

#ifndef IsobProcDisp_h
#define IsobProcDisp_h

/// This subroutine is used to output the collected data and generated profile from "IsobProfile(...)" to the user console.
/// @param P System pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param profile Isobaric process profile.
void IsobProcDisplay(double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile);

#endif /* IsobProcDisp_h */

#ifndef IsobProcWrite_h
#define IsobProcWrite_h

/// This subroutine is used to write the collected data and generated profile from "IsobProfile(...)" to a .txt file.
/// @param P System pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param profile Isobaric process profile.
void IsobProcWrite(double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile);

/// This subroutine is used to ask the user if they would like to either display the results on the console or save the results of this program to a file.
/// @param mode Integer used to control whether this function will access the display (1) or write (2) function.
/// @param P System pressure (Pa).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 Initial system temperature (K).
/// @param T2 Final system temperature (K).
/// @param n Moles of component in system (mol/s).
/// @param profile Isobaric process profile.
void IsobProcSwitch(int mode, double P, double V1, double V2, double T1, double T2, double n, T1ThermoProf profile);

#endif /* IsobProcWrite_h */
