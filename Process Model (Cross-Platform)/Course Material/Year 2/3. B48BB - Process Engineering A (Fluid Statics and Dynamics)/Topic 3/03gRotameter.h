//
//  03gRotameter.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 dP = Pressure differential across the float (Pa)
 m = Mass flowrate (kg/s)
 Q = Volumetric flowrate (m3/s)
 u = Fluid point velocity (m/s)
 C_d = Discharge coefficient
 V_f = Float volume (m3)
 rho_f = Float density (kg/m3)
 rho = Fluid density (kg/m3)
 A_f = Maximum cross-sectional area of the float
 are1 = Cross-sectional area of tube at point of float (m2)
 are2 = Annular area between float and tube at the point (m2)
 */
#ifndef RotameterVar_h
#define RotameterVar_h

void RotameterVar(double *C_d, double *V_f, double *rho_f, double *rho, double *A_f, double *are1, double *are2);
/*  This subroutine is used to collect data such that the mass flowrate can be predicted from a theoretical rotameter. In addition to the global variables being collected in the arguments, an additional character array is used to receive data input from the user. This subroutine then returns values back to the calling function and has no external dependencies.
 */

#endif /* RotameterVar_h */

#ifndef RotameterCalc_h
#define RotameterCalc_h

void RotameterCalc(double C_d, double V_f, double rho_f, double rho, double A_f, double are1, double are2, double *dP, double *m, double *Q, double *u);
/*  This subroutine is used to calculate the pressure drop, mass flowrate, volumetric flowrate and fluid velocity through a rotameter. This subroutine has no external dependencies and is not used outside of this file.
 */

#endif /* RotameterCalc_h */
