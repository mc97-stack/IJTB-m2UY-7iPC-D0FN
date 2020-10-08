//
//  01dIsochoric Process.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IsocVariable_h
#define IsocVariable_h

void IsocVariable(int method, double *P1, double *P2, double *V, double *T1, double *T2, double *n, double *cv);
/*  This subroutine is used for collecting data for calculating the heat for a isochoric process. As stated in the pseudomain's description in "B48BC_T1.h", there are two methods for calculation. These are:
 int method == 1: Pressure-Volume equation. This equation requires: P1, P2 and V.
 int method == 2: Temperature equation. This equation requires: T1 and T2 to be declared.
 Additionally, both methods will require n and cv to be stated.
 */

#endif /* IsocVariable_h */

#ifndef IsocPressure_h
#define IsocPressure_h

double IsocPressure(double P1, double P2, double V, double n, double cv);
/*  This subroutine is used to calculate the heat associated with a pressure change for an isochoric process.
 */

#endif /* IsocPressure_h */

#ifndef IsocTemperature_h
#define IsocTemperature_h

double IsocTemperature(double T1, double T2, double n, double cv);
/*  This subroutine is used to calculate the heat associated with a temperature change for an isochoric process.
 */

#endif /* IsocTemperature_h */

#ifndef IsocProfile_h
#define IsocProfile_h

void IsocProfile(int method, double P1, double P2, double V, double T1, double T2, double n, double cv);
/*  Pressure|Volume|Temperature|Work|Q|Q_cum.|
 */

#endif /* IsocProfile_h */
