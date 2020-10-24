//
//  02g1LamVelPro.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 21/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef LamVelProVar_h
#define LamVelProVar_h

/// This subroutine is used to collect the data required for calculating the velocity profile of a fluid flowing with laminar flow characteristics.
/// @param dP Fluid pressure loss (Pa)
/// @param L Pipe length (m)
/// @param d Pipe diameter (mm)
/// @param mu Fluid viscosity (cP)
void LamVelProVar(double *dP, double *L, double *d, double *mu);

#endif /* LamVelProVar_h */

#ifndef LamVelCalc_h
#define LamVelCalc_h

/// This subroutine is used to calculate the point velocity at some radius in a cylindrical pipe segment from theory.
/// @param dP Fluid pressure loss (Pa)
/// @param L Pipe length (m)
/// @param d Pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param r Pipe point radius (m)
double LamVelCalc(double dP, double L, double d, double mu, double r);

#endif /* LamVelCalc_h */

#ifndef LamGenCalc_h
#define LamGenCalc_h

/// This subroutine is used to calculate the general velocity profile from the point radius and fixed pipe diameter. This subroutine returns the value of v/v_{max} to the calling function.
/// @param r Point radius (m)
/// @param d Fixed pipe diameter (m)
double LamGenCalc(double r, double d);

#endif /* LamGenCalc_h */

#ifndef LamVelProfCalc_h
#define LamVelProfCalc_h

typedef struct LamVelProfile{
    double r[5000]; //  Point radius
    double v_x[5000]; //  Point velocity
    double ratio[5000]; //  Velocity ratio
} LamVelProf;

/// This subroutine is used to calculate and display the fully developed velocity profile for a fluid flowing with laminar properties. This subroutine does not return the generated array to the calling function.
/// @param dP Fluid pressure loss (Pa).
/// @param L Pipe length (m).
/// @param d Pipe diameter (mm).
/// @param mu Fluid viscosity (Pa.s).
LamVelProf LamVelProfCalc(double dP, double L, double d, double mu, int *rowcount);

#endif /* LamVelProfCalc_h */

#ifndef LamVelProDisp_h
#define LamVelProDisp_h

/// This subroutine is used to write the collected data and generated velocity profile to the user console.
/// @param dP Fluid pressure loss (Pa).
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param mu Fluid dynamic viscosity (Pa.s).
/// @param rows Number of rows generated in "LamVelProfCalc".
/// @param profile Velocity profile struct.
void LamVelProDisp(double dP, double L, double d, double mu, int rows, LamVelProf profile);

#endif /* LamVelProDisp_h */

#ifndef LamVelProWrite_h
#define LamVelProWrite_h

/// This subroutine is used to write the collected data and generated velocity profile to a .txt file
/// @param dP Fluid pressure loss (Pa).
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param mu Fluid dynamic viscosity (Pa.s).
/// @param rows Number of rows generated in "LamVelProfCalc".
/// @param profile Velocity profile struct.
void LamVelProWrite(double dP, double L, double d, double mu, int rows, LamVelProf profile);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param dP Fluid pressure loss (Pa).
/// @param L Pipe length (m).
/// @param d Pipe diameter (m).
/// @param mu Fluid dynamic viscosity (Pa.s).
/// @param rows Number of rows generated in "LamVelProfCalc".
/// @param profile Velocity profile struct.
void LamVelProWrite(double dP, double L, double d, double mu, int rows, LamVelProf profile);

#endif /* LamVelProWrite_h */

#ifndef LamVelPro_h
#define LamVelPro_h

/// This is the main subroutine controlling the behaviour of the subroutines listed in the file.
void LamVelPro(void);

#endif /* LamVelPro_h */
