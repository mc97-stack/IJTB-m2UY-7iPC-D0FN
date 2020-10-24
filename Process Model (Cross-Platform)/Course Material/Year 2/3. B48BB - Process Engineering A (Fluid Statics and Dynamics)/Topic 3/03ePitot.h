//
//  03ePitot.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef PitotVar_h
#define PitotVar_h

/// This subroutine is used to collect the necessary data to predict the data associated with a pitot static tube.
/// @param P2 Static pressure on connection (kPa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param rho2 Manometer fluid density (kg/ m3).
/// @param h1 Process fluid height in manometer (cm).
/// @param h2 Manometer fluid height in manometer (cm).
/// @param d Pipe diameter (mm).
void PitotVar(double *P2, double *rho1, double *rho2, double *h1, double *h2, double *d);

#endif /* PitotVar_h */

#ifndef PitotCalc_h
#define PitotCalc_h

/// This subroutine is used to predict the volumetric flow rate of a fluid travelling with a pitot static tube. This function also returns the values of the initial fluid pressure and point velocity to the calling function.
/// @param P2 Static pressure on connection (kPa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param rho2 Manometer fluid density (kg/ m3).
/// @param h1 Process fluid height in manometer (m).
/// @param h2 Manometer fluid height in manometer (m).
/// @param d Pipe diameter (m).
/// @param P1 Fluid pressure (Pa).
/// @param v Fluid velocity (m/s).
/// @param Q Fluid volumetric flowrate (m3/ s).
void PitotCalc(double P2, double rho1, double rho2, double h1, double h2, double d, double *P1, double *v, double *Q);
/*  This subroutine is used to predict the volumetric flow rate of a fluid travelling with a pitot static tube. This function also returns the values of the initial fluid pressure and point velocity to the calling function. This function has an external dependency on the function "ManoMeasCal(...)" that can be found in "01cMano.c".
 */

#endif /* PitotCalc_h */

#ifndef PitotDisp_h
#define PitotDisp_h

/// This subroutine is used to output the collected data and calculated values to the user console.
/// @param P1 Fluid pressure (Pa).
/// @param P2 Static pressure on connection (Pa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param rho2 Manometer fluid density (kg/ m3).
/// @param h1 Process fluid height in manometer (m).
/// @param h2 Manometer fluid height in manometer (m).
/// @param d Pipe diameter (m).
/// @param v Fluid velocity (m/s).
/// @param Q Fluid volumetric flowrate (m3/ s).
void PitotDisp(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q);

#endif /* PitotDisp_h */

#ifndef PitotWrite_h
#define PitotWrite_h

/// This subroutine is used to output the collected data and calculated values to a .txt file.
/// @param P1 Fluid pressure (Pa).
/// @param P2 Static pressure on connection (Pa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param rho2 Manometer fluid density (kg/ m3).
/// @param h1 Process fluid height in manometer (m).
/// @param h2 Manometer fluid height in manometer (m).
/// @param d Pipe diameter (m).
/// @param v Fluid velocity (m/s).
/// @param Q Fluid volumetric flowrate (m3/ s).
void PitotWrite(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param P1 Fluid pressure (Pa).
/// @param P2 Static pressure on connection (Pa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param rho2 Manometer fluid density (kg/ m3).
/// @param h1 Process fluid height in manometer (m).
/// @param h2 Manometer fluid height in manometer (m).
/// @param d Pipe diameter (m).
/// @param v Fluid velocity (m/s).
/// @param Q Fluid volumetric flowrate (m3/ s).
void PitotWriteCheck(double P1, double P2, double rho1, double rho2, double h1, double h2, double d, double v, double Q);

#endif /* PitotWrite_h */
