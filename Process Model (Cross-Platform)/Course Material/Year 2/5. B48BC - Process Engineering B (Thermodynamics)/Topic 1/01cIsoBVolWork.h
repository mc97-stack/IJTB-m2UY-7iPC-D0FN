//
//  01cIsoBVolWork.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

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
 This function returns the user inputted values of the variables given to the function for assignment. 
 */

#endif /* IsoBVolWorkVar_h */

#ifndef IsoBVolWorkCalcV_h
#define IsoBVolWorkCalcV_h

double IsoBVolWorkCalcV(double P, double V1, double V2);
/* Subroutine for estimating the isobaric volume work from the change in volume. Function returns the isobaric volume work. This subroutine is later used in "IsoTVolWorkPlot(...)" to calculate the process line
 */
#endif /* IsoBVolWorkCalcV_h */

#ifndef IsoBVolWorkCalcT_h
#define IsoBVolWorkCalcT_h

double IsoBVolWorkCalcT(double n, double T1, double T2);
/* Subroutine for estimating the isobaric volume work from the change in temperature. Function returns the isobaric volume work. 
*/

#endif /* IsoBVolWorkCalcT_h */

#ifndef IsoTVolWorkPlot_h
#define IsoTVolWorkPlot_h

void IsoTVolWorkPlot(double n, double T, double P1, double P2);
/* Subroutine for plotting the process line using the function "IsoBVolWorkCalcV". The process line is simulated through modelling the system as a consecutive series quasi-static variable changes using "IsoBVolWorkCalcV(...)". The variables used in this subroutine are:
 reso = resolution/ number of iterations being used for calculation
 incr1 = Temperature increment between iterations across the set resolution
 incr2 = Volume increment between iterations across the set resolution
 profile[i][j] = Matrix being used to store the generated 
 - Column 1 = System pressure (displayed in kPa)
 - Column 2 = System volume (m3)
 - Column 3 = System temperature (deg C)
 - Column 4 = Section volume work (kW)
 - Column 5 = Cumulative volume work (kW)
 The function does not currently return a value back to the parent routine, future developments may change this however.
 */

#endif /* IsoTVolWorkPlot_h */
