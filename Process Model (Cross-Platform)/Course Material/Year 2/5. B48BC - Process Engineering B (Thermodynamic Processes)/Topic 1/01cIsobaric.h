//
//  01cIsobaric.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IsobVariable_h
#define IsobVariable_h

void IsobVariable(int method, double *P, double *V1,double *V2, double *T1, double *T2, double *n);
/*  This subroutine is used for collecting data for calculating the volume work for a isobaric process. As stated in the pseudomain's description in "B48BC_T1.h", there are two methods for calculation. These are:
 int method == 1: Pressure-Volume equation. This equation requires: P, V1 and V2 to be declared.
 int method == 2: Temperature equation. This equation requires: n, T1 and T2 to be declared.
 To determine other system conditions, both methods will require the moles of substance to be declared.
 */

#endif /* IsobVariable_h */

#ifndef IsobVolume_h
#define IsobVolume_h

double IsobVolume(double P, double V1, double V2);
/*  This subroutine is used to calculate the volume work done associated with a change in volume for an isobaric process. 
 */

#endif /* IsobVolume_h */

#ifndef IsobTemperature_h
#define IsobTemperature_h

double IsobTemperature(double n, double T1, double T2);
/*  This subroutine is used to calculate the volume work done assocaited with a change in temperature for an isobaric process.
 */

#endif /* IsobTemperature_h */

#ifndef IsobProfile_h
#define IsobProfile_h

void IsobProfile(int method, double P, double V1, double V2, double T1, double T2, double n);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* IsobProfile_h */
