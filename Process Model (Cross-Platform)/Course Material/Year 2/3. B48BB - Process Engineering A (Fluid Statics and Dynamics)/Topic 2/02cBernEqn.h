//
//  02cBernEqn.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 P = Fluid pressure at start and endpoints
 rho = Fluid density (Bernoulli's equation assumes fluid is travelling isothermally. Since density is a temperature dependent function, this will remain constant)
 u = Fluid velocity 
 Z = Relative process height
 hf = head loss due to friction
 */

#ifndef BernEqnVar_h
#define BernEqnVar_h

void BernEqnVar(double *P1, double *rho, double *u1, double *u2, double *Z1, double *Z2, double *hf);
/*  This subroutine is used for data collection to calculate the end pressure through Bernoulli's equation. The water hammer effect is observed is u2 is set to 0. The variables that are being collected have been described within the description of global variables and returned to the parent subroutine ("BernEqn(void)"). 
 */
#endif /* BernEqnVar_h */

#ifndef StatHeadCalc_h
#define StatHeadCalc_h

double StatHeadCalc(double P, double rho);
/*  This subroutine is used to calculate the static head of a fluid that arises from the feeding/receiving vessel. This subroutine receives values for pressure (P) and density (rho) from the calling subroutine. It then returns the value of "stathead" to the calling subroutine. 
 */

#endif /* StatHeadCalc_h */

#ifndef DynHeadCalc_h
#define DynHeadCalc_h

double DynHeadCalc(double u);
/*  This subroutine is used to calculate the dynamic head of a fluid that arises from a moving fluid. This subroutine receives a value of fluid velocity (u) and returns the value of "dynhead" to the calling subroutine.
 */

#endif /* DynHeadCalc_h */

#ifndef BernEqnCalc_h
#define BernEqnCalc_h

double BernEqnCalc(double stathead, double dynhead, double Z);
/*  This subroutine calculates the total head contribution as specified through Bernoulli's equation. This utilises the local variable "calc" to hold a running sum through the calculation which is returned to the parent subroutine.
 */

#endif /* BernEqnCalc_h */
