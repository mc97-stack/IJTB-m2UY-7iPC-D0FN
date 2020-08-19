//
//  01cIsoBVolWork.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IdealVolCalcB_h
#define IdealVolCalcB_h

double IdealVolCalcB(double n, double P, double T);
/* Subroutine to calculate the system volume from rearrangement of the ideal gas law
 */

#endif /* IdealVolCalcB_h */

#ifndef IdealTempCalcB_h
#define IdealTempCalcB_h

double IdealTempCalcB(double n, double P, double V);
/* Subroutine to calculate the system temperature from rearrangement of the ideal gas law.
 Variables used:
 top = numerator
 bot = denominator
 */

#endif /* IdealTempCalcB_h */

#ifndef IsoBVolWorkVar_h
#define IsoBVolWorkVar_h

void IsoBVolWorkVar(double *n, double *P, double *V1, double *V2, double *T1, double *T2, int method);
/* Subroutine for data collection, where:
 n = moles of substance (mol/ s)
 P = System pressure
 V1 = Initial system volume (m3)
 V2 = Final system volume (m3)
 T1 = Initial system temperature (K)
 T2 = Final system temperature (K)
 method = choice variable of volume work calculation (Volume -> method = 1 || Temperature -> method = 0)
 */

#endif /* IsoBVolWorkVar_h */

#ifndef IsoBVolWorkCalcV_h
#define IsoBVolWorkCalcV_h

double IsoBVolWorkCalcV(double P, double V1, double V2);
/* Subroutine for estimating the isobaric volume work from the change in volume. Function returns the value volume work.
 */
#endif /* IsoBVolWorkCalcV_h */

#ifndef IsoBVolWorkCalcT_h
#define IsoBVolWorkCalcT_h

double IsoBVolWorkCalcT(double n, double T1, double T2);
/* Subroutine for estimating the isobaric volume work from the change in temperature. Function returns the value volume work 
*/

#endif /* IsoBVolWorkCalcT_h */

#ifndef IsoTVolWorkPlot_h
#define IsoTVolWorkPlot_h

void IsoTVolWorkPlot(double n, double T, double P1, double P2);
/* Subroutine for plotting the process line using the function "IsoBVolWorkCalcV". The process line is simulated through modelling the system as a consecutive series quasi-static variable changes.
 */

#endif /* IsoTVolWorkPlot_h */
