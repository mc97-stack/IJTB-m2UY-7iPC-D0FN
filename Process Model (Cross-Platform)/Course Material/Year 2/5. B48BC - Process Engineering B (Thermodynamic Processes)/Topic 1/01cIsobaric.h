//
//  01cIsobaric.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IsobVariable_h
#define IsobVariable_h

/// This subroutine is used for collecting data for calculating the volume work for a isobaric process.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P System pressure (kPa)
/// @param V1 Initial system volume (m3)
/// @param V2 Final system volume (m3)
/// @param T1 Initial system temperature (deg C)
/// @param T2 Final system temperature (deg C)
/// @param n Moles of component in system (kmol/s)
void IsobVariable(int method, double *P, double *V1,double *V2, double *T1, double *T2, double *n);

#endif /* IsobVariable_h */

#ifndef IsobVolume_h
#define IsobVolume_h

/// This subroutine is used to calculate the volume work done associated with a change in volume for an isobaric process. 
/// @param P  System pressure (Pa)
/// @param V1 Initial system volume (m3)
/// @param V2 Final system volume (m3)
double IsobVolume(double P, double V1, double V2);

#endif /* IsobVolume_h */

#ifndef IsobTemperature_h
#define IsobTemperature_h

/// This subroutine is used to calculate the volume work done assocaited with a change in temperature for an isobaric process.
/// @param n Moles of component in system (mol/s)
/// @param T1 Initial system temperature (K)
/// @param T2 Final system temperature (K)
double IsobTemperature(double n, double T1, double T2);

#endif /* IsobTemperature_h */

#ifndef IsobProfile_h
#define IsobProfile_h

/// This subroutine is used to calculate the process profile associated with an isobaric process. This subroutine requires "IdealTemperature(...)" and "IdealGasLaw.h" to function as intended.
/// @param method Integer variable used to determine what equation should be used. (1) = Pressure-Volume equation. (2) = Temperature equation.
/// @param P System pressure (Pa)
/// @param V1 Initial system volume (m3)
/// @param V2 Final system volume (m3)
/// @param T1 Initial system temperature (K)
/// @param T2 Final system temperature (K)
/// @param n Moles of component in system (mol/s)
T1ThermoProf IsobProfile(int method, double P, double V1, double V2, double T1, double T2, double n);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* IsobProfile_h */
