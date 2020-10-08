//
//  01aPolytropic.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef PolyVariable_h
#define PolyVariable_h

void PolyVariable(int method, double *P1, double *P2, double *V1, double *T1,double *T2, double *n, double *R, double *alpha);
/*  This subroutine is used for collecting data for calculating the volume work for a polytropic process. As stated in the pseudomain's description in "B48BC_T1.h", there are two methods for calculation. These are:
 int method == 1: Pressure-Volume equation. This equation requires: P1, P2, V1 and alpha to be declared.
 int method == 2: Temperature equation. This equation requires: n, T1 and T2 to be declared.
 Additionally, both methods will require the moles present to be stated to determine the values for system pressure and volume at intermediate system states. Logic has also been implemented to collect the temperatures first in case an isothermal process is specified although the user specifies an isothermal process when asked in the pseudomain function.
 */

#endif /* _1aPolytropic_h */

#ifndef PolyVolume_h
#define PolyVolume_h

double PolyVolume(double P1, double P2, double V1, double alpha);
/*  Subroutine used to calculate the volume work for a polytropic process utilising the system pressure and volume. The subroutine creates an additional 4 calculation variables used for storing values between calculations.
 */

#endif /* PolyVolume_h */

#ifndef PolyTemperature_h
#define PolyTemperature_h

double PolyTemperature(double n, double R, double T1, double T2, double alpha);
/*  Subroutine used to calculate the volume work for a polytropic process utilising the changes to system temperature. The subroutine creates an additional 3 calculation variables used for stored values between calculations.
 */

#endif /* PolyTemperature_h */

#ifndef PolyFinalVolume_h
#define PolyFinalVolume_h

double PolyFinalVolume(double P1, double P2, double V1, double alpha);
/*  Subroutine used to determine the final volume from the pressure-volume relationship for a polytropic process.
 */

#endif /* PolyFinalVolume_h */

#ifndef PolyFinalPressure_h
#define PolyFinalPressure_h

double PolyFinalPressure(double T1, double T2, double P1, double alpha);
/*  Subroutine used to determine the final pressure from the pressure-temperature relationship for a polytropic process.
 */

#endif /* PolyFinalPressure_h */

#ifndef PolyProfile_h
#define PolyProfile_h

void PolyProfile(int method, double P1, double P2, double V1, double T1, double T2, double n, double R, double alpha);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* PolyProfile_h */
