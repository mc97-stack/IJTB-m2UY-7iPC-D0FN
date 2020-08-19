//
//  01aGenVolWork.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef GenVolWorkVar_h
#define GenVolWorkVar_h

void GenVolWorkVar(double *n, double *T1, double *T2, double *V1, double *V2);
/* Subroutine for data collection, where:
 n = moles of substance (mol)
 T1 = Initial system temperature (K)
 T2 = Final system temperature (K)
 V1 = Initial system volume (m3)
 V2 = Final system volume (m3)
 */

#endif /* GenVolWorkVar_h */

#ifndef GenVolWorkCalc_h
#define GenVolWorkCalc_h

double GenVolWorkCalc(double n, double T1, double T2, double V1, double V2, double *VolWork);
/* Subroutine for calculating the volume work for a quasi-static process. This is used by "GenVolWorkPlot(...)" to plot the process line. 
 Variables used:
 term 1 && term 2 = calculation variables
 */

#endif /* GenVolWorkVar_h */

#ifndef GenVolWorkPlot_h
#define GenVolWorkPlot_h

void GenVolWorkPlot(double n, double T1, double T2, double V1, double V2);
/* Subroutine for drawing the process line through a series of quasi static changes through using "GenVolWorkCalc".
 Variables used:
 reso = resolution/ number of iterations being used for calculation
 incr1 = Temperature increment between iterations across the set resolution
 incr2 = Volume increment between iterations across the set resolution
 profile[i][j] = Matrix being used to store the generated 
 - Column 1 = System temperature
 - Column 2 = System volume
 - Column 3 = System pressure
 - Column 4 = Section volume work
 - Column 5 = Cumulative volume work
 */

#endif /* GenVolWorkPlot_h */
