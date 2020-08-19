//
//  01bIsoTVolWork.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IsoTVolWorkVar_h
#define IsoTVolWorkVar_h

void IsoTVolWorkVar(double *n, double *T, double *P1, double *P2, double *V1, double *V2, int method);
/* Subroutine for data collection, where:
 n = moles of substance (mol/s)
 T = System temperature (K)
 P1 = Initial system pressure (Pa)
 P2 = Final system pressure (Pa)
 V1 = Initial system volume (m3)
 V2 = Final system volume (m3)
 method = choice variable of volume work calculation (Volume -> method = 1 || Pressure -> method = 0)
 */

#endif /* IsoTVolWorkVar_h */

#ifndef IsoTVolWorkV_h
#define IsoTVolWorkV_h

double IsoTVolWorkV(double n, double T, double V1, double V2);
/* Subroutine for calculating the volume work for a quasi-static process from volumetric changes. 
 Variables used:
 frac = Volume ratio
 work = Volume work calculated through volume ratio
 */

#endif /* IsoTVolWorkV_h */

#ifndef IsoTVolWorkP_h
#define IsoTVolWorkP_h

double IsoTVolWorkP(double n, double T, double P1, double P2);
/* Subroutine for calculating the volume work for a quasi-static process from barometric changes. This function is later used to estimate the volume work 
 Variables used:
 frac = Pressure ratio
 work = Volume work calculated through pressure ratio
 */

#endif /* IsoTVolWorkP_h */

#ifndef IdealVolCalc_h
#define IdealVolCalc_h

double IdealVolCalc(double n, double T, double P);
/*  Subroutine to calculate the volume from rearrangment of the ideal gas law*/

#endif /* IdealVolCalc_h */

#ifndef IdealPreCalc_h
#define IdealPreCalc_h

double IdealPreCalc(double n, double T, double V);
/*  Subroutine to calculate the pressure from rearrangment of the ideal gas law*/

#endif /* IdealPreCalc_h */

#ifndef IsoTVolWorkPlot_h
#define IsoTVolWorkPlot_h

void IsoTVolWorkPlot(double n, double T, double P1, double P2);
/* Subroutine to plot the process line as Isothermal volume work is being performed using the function "IsoTVolWorkP" through modelling as quasi-static variable changes
 Variables used:
 reso = resolution/ number of iterations being used for calculation
 incr1 = Temperature increment between iterations across the set resolution
 incr2 = Volume increment between iterations across the set resolution
 profile[i][j] = Matrix being used to store the generated 
 - Column 1 = System pressure (displayed in kPa)
 - Column 2 = System volume (m3)
 - Column 3 = Section volume work (kW)
 - Column 4 = Cumulative volume work (kW)
 */

#endif /* IsoTVolWorkPlot_h */
