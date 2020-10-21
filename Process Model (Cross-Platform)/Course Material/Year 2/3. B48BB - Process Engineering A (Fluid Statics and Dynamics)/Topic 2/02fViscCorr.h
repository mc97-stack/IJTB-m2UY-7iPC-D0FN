//
//  02fViscCorr.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef ViscCorrVar_h
#define ViscCorrVar_h

/// This subroutine is used to collect the data required for standard fluid viscosity correlations.
/// @param a Parameter 1 for correlation
/// @param b Parameter 2 for correlation
/// @param T System temperature (Units dependent on correlation  being used)
/// @param rho Fluid density (kg/ m3)
void ViscCorrVar(double *a, double *b, double *T, double *rho);

#endif /* ViscCorrVar_h */

#ifndef LiqViscCalc_h
#define LiqViscCalc_h

/// This subroutine is used to calculate the liquid viscosity given the required arguments. After calculation, the subroutine displays the value of viscosity before returning the value to the calling function. 
/// @param a Parameter 1 for correlation
/// @param b Parameter 2 for correlation
/// @param T System temperature (Units dependent on correlation  being used)
double LiqViscCalc(double a, double b, double T);

#endif /* LiqViscCalc_h */

#ifndef VapViscCalc_h
#define VapViscCalc_h

/// This subroutine is used to calculate the vapour viscosity given the required arguments. After calculation, the subroutine displays the value of viscosity before returning the value to the calling function. 
/// @param a Parameter 1 for correlation
/// @param b Parameter 2 for correlation
/// @param T System temperature (Units dependent on correlation  being used)
double VapViscCalc(double a, double b, double T);

#endif /* VapViscCalc_h */

#ifndef KinVisc_h
#define KinVisc_h

/// This subroutine is used to calculate the kinematic viscosity given the declared arguments. This subroutine then returns the value of kinematic viscosity to the calling function prior to displaying the calculated value on the console..
/// @param mu Dynamic viscosity (Pa. s) 
/// @param rho Fluid density (kg/ m3)
double KinVisc(double mu, double rho);

#endif /* KinVisc_h */

#ifndef ViscWrite_h
#define ViscWrite_h

/// This subroutine is used to write the viscosity correlation results to a .txt file.
/// @param method Variable used to tell the subroutine whether the liquid or vapour correlation was used in the program. This subroutine then modifies behaviour accordingly.
/// @param a Correlation constant
/// @param b Correlation constant
/// @param T Temperature
/// @param rho Fluid density
/// @param mu Fluid dynamic viscosity
/// @param upsi Fluid kinematic viscosity
void ViscWrite(int method, double a, double b, double T, double rho, double mu, double upsi);

#endif /* ViscWrite_h */
