//
//  01dIsoChHeat.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IsoChHeatVar_h
#define IsoChHeatVar_h

void IsoChHeatVar(double *n, double *c_v, double *V, double *P1, double *P2, double *T1, double *T2, int method);
/* Subroutine for data collection, where:
 n = moles of substance (mol/ s)
 c_v = Heat capacity at constant volume (J/ (mol. K))
 V = System volume (m3)
 P1 = Initial system pressure (Pa)
 P2 = Final system pressure (Pa)
 T1 = Initial system temperature (K)
 T2 = Final system temperature (K)
 method = choice variable of heat calculation (Pressure -> method = 1 || Temperature -> method = 0)
 This subroutine returns the user inputted values of the variables passed to it from the parent subroutine for assignment.
*/

#endif /* IsoChHeatVar_h */

#ifndef IsoChHeatCalcT_h
#define IsoChHeatCalcT_h

double IsoChHeatCalcT(double n, double c_v, double T1, double T2);
/* Subroutine for calculating the heat required for an isochoric process from the temperature difference. Where:
 brack = Temperature differential (K)
 This subroutine returns the heat required to perform the isochoric process from the Temperature difference between the two end states.
 */

#endif /* IsoChHeatCalcT_h */

#ifndef IsoChHeatCalcP_h
#define IsoChHeatCalcP_h

double IsoChHeatCalcP(double n, double c_v, double V, double P1, double P2);
/* Subroutine for calculating the heat required for an isochoric process from the pressure difference. The variables used for this subroutine are:
 frac = Volume to perfect gas constant
 brack = Pressure differential
 This subroutine returns the heat required to perform the isochoric process from the Temperature difference between the two end states. Function returns Q and is used later in the function "IsoChHeatPlot".
*/

#endif /* IsoChHeatCalcP_h */

#ifndef IsoChHeatPlot_h
#define IsoChHeatPlot_h

void IsoChHeatPlot(double n, double c_v, double V, double P1, double P2);
/* Subroutine for plotting the process line using the function "IsoChHeatCalcP". The process line is simulated through modelling the system as a consecutive series of quasi-static variable changes. Variables used:
 incr = pressure increment
 reso = resolution/ number of iterations - 1 being used for calculation
 profile[i][j] = Matrix being used to store the generated
 - Column 1 = System pressure (kPa)
 - Column 2 = System volume (m3)
 - Column 3 = System temperature (deg C)
 - Column 4 = Section heat load (kW)
 - Column 5 = Cumulative heat load (kW)
 The function does not currently return a value back to the parent routine, future developments may change this however.
 */

#endif
