//
//  03fOrifice.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

// Global variables
/*  
 u = Fluid velocity
 Q = Volumetric flow rate
 m = mass flowrate
 C_d = Discharge coefficient
 d1 = Pipe diameter
 d2 = Vena contracta diameter
 rho = Fluid density
 P1 = Initial system pressure
 P2 = Final system pressure
 h_f = Frictional head loss
 */

#ifndef OrificeVar_h
#define OrificeVar_h

void OrificeVar(double *C_d, double *d1, double *d2, double *rho, double *P1, double *P2, double *h_f);
/*  This subroutine is used to collect the data required to predict the mass flowrate through an orifice plate. Aside from the above declared global variables, this subroutine uses an additional character array to receive character input from the user. This function returns the variables requested in the arguments back to the calling function and has no external dependencies.
 */

#endif /* OrificeVar_h */

#ifndef OrificeCalc_h
#define OrificeCalc_h

void OrificeCalc(double C_d, double d1, double d2, double rho, double P1, double P2, double h_f, double *u, double *Q, double *m);
/*  This subroutine is used to calculate the mass flowrate, volumetric flowrate and average fluid velocity as it flows through an orifice plate meter through Bernoulli's principle. This subroutine does not have any external dependencies.
 */

#endif /* OrificeCalc_h */
