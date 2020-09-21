//
//  02fViscCorr.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 mu = Fluid viscosity
 upsi = Fluid kinematic viscosity
 a = First constant
 b = Second constant
 T = Temperature
 rho = Fluid density
 */

#ifndef ViscCorrVar_h
#define ViscCorrVar_h

void ViscCorrVar(double *a, double *b, double *T, double *rho);
/*  This subroutine used to collect the data required for a standard fluid viscosity correlation. The main variables utilised in this subroutine have been previously declared as global variables. Other local variables utilised are:
 - input = character input used for data entry
 - tempconv = character array used for choice selection for conversion into degrees Kelvin.
 - TempCheck = Integer value used to control the while loop for temperature conversion choice.
 The subroutine then returns the entered data back to the parent subroutine ("ViscCorr(void)").
 */

#endif /* ViscCorrVar_h */

#ifndef LiqViscCalc_h
#define LiqViscCalc_h

double LiqViscCalc(double a, double b, double T);
/*  This subroutine is used to calculate the liquid viscosity given the required variables in the function. This subroutine, after calculation, returns the value of "mu" back to the parent subroutine ("ViscCorr(void)").
 */

#endif /* LiqViscCalc_h */

#ifndef VapViscCalc_h
#define VapViscCalc_h

double VapViscCalc(double a, double b, double T);
/*  This subroutine is used to calculate the vapour viscosity given the required variables in the function. This subroutine, after calculation, returns the value of "mu" back to the parent subroutine ("ViscCorr(void)").
*/

#endif /* VapViscCalc_h */

#ifndef KinVisc_h
#define KinVisc_h

double KinVisc(double mu, double rho);
/*  This subroutine is used to calculate the fluid dynamic viscosity given the required variables in the function. This subroutine, after calculation, returns the value of "upsi" back to the parent subroutine ("ViscCorr(void)").
*/

#endif /* KinVisc_h */
