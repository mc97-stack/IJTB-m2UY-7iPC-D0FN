//
//  01bIsothermal.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 08/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IsotVariable_h
#define IsotVariable_h

void IsotVariable(int method, double *P1, double *P2, double *V1, double *V2, double *T, double *n);
/*  This subroutine is used to collect the data to required to calculate the volume work for an isothermal process. As stated in the pseudomain's description in "B48BC_T1.h", there are two methods for calculation. These are:
 int method == 1: Volume definition
 int method == 2: Pressure definition
 Both methods require similar variables (n and T) but the dependent variable is dependent on the equation being used.
 */

#endif /* IsotVariable_h */

#ifndef IsotVolume_h
#define IsotVolume_h

double IsotVolume(double n, double T, double V1, double V2);
/*  This subroutine used to calculate the volume work associated with an isothermal process from a volume change. This subroutine then returns the volume work associated with the volume change.
 */

#endif /* IsotVolume_h */

#ifndef IsotPressure_h
#define IsotPressure_h

double IsotPressure(double n, double T, double P1, double P2);
/*  This subroutine used to calculate the volume work associated with an isothermal process from a pressure change. This subroutine then returns the volume work associated with the pressure change.
 */

#endif /* IsotPressure_h */

#ifndef IsotProfile_h
#define IsotProfile_h

void IsotProfile(int method, double n, double T, double P1, double P2, double V1, double V2);
/*  Pressure|Volume|Temperature|Work|Work_cum.|
 */

#endif /* IsotProfile_h */
