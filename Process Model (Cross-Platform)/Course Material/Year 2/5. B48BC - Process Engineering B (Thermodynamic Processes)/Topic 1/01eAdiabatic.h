//
//  01eAdiabatic.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 07/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef AdiaVariable_h
#define AdiaVariable_h

void AdiaVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T1, double *T2, double *n, double *gamma);
/* As detailed in "Adiabatic(void)", there are two methods that can be used to calculate the volume work for an adiabatic process involving an ideal gas. As such, the variable "method" was defined to dictate the behaviour of the data collection function. To review:
 - If method == 1, then the Pressure-Volume definition of volume work is used. The equation requires, the initial pressure and starting and end volume states to be known.
 - If method == 2, then the Pressure-Temperature method is used. The equation requires, the moles present in the system, starting temperature and starting and end pressures to be known.
 Across both methods, only the heat capacity ratio is required.
 */
#endif /* AdiaVariable_h */

#ifndef AdiaVolume_h
#define AdiaVolume_h

double AdiaVolume(double P1, double V1, double V2, double gamma);
/*  This subroutine is used to calculate the adiabatic volume work from the system pressure and volume. This subroutine has a dependency on the "math.h" header being available for the "pow(double ..., double ...)" function. In addition to requiring the stated variables, the subroutine makes the following local calculation variables:
 frac1num && frac1den = Fraction at start of the volume work equation concerning  pressure and volume.
 frac2 = Volume ratio
 "power" and "brack" are variables used to hold values before "work" is calculated.
 After calculation, this subroutine then returns the volume work associated with the volume change V1 -> V2.
 */

#endif /* AdiaVolume_h */

#ifndef AdiaTemperature_h
#define AdiaTemperature_h

double AdiaTemperature(double T1, double P1, double P2, double n, double gamma);
/*  This subroutine is used to calculate the adiabatic volume work from the system pressure and temperature. This subroutine has a dependency on the "math.h" header being available for the "pow(double ..., double ...)" function. In addition to requiring the stated variables, the subroutine makes the following local calculation variables:
 frac1num && frac1den = Fraction at start of the volume work equation concerning  pressure and volume.
 frac2 = Pressure ratio
 "power" and "brack" are variables used to hold values before "work" is calculated.
 After calculation, this subroutine then returns the volume work associated with the volume change P1 -> P2.
 */

#endif /* AdiaTemperature_h */

#ifndef AdiaFinalPress_h
#define AdiaFinalPress_h

double AdiaFinalPress(double P1, double V1, double V2, double gamma);

#endif /* AdiaFinalPress_h */

#ifndef AdiaFinalTemp_h
#define AdiaFinalTemp_h

double AdiaFinalTemp(double T1, double P1, double P2, double gamma);

#endif /* AdiaFinalTemp_h */


#ifndef AdiaProfile_h
#define AdiaProfile_h

void AdiaProfile(int method, double P1, double P2, double V1, double V2, double T1, double T2, double n, double gamma);
/* 
 Pressure|Volume|Temperature|Work|Work_Cum.
 */

#endif /* AdiaProfile_h */


