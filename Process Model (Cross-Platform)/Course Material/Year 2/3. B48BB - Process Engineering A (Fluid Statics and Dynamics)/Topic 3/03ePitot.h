//
//  03ePitot.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 P1 = Fluid pressure (Pa)
 v = Fluid velocity (m/s)
 Q = Fluid volumetric flowrate (m3/s)
     //Calculation Variables
 P2 = Static pressure on connection (Pa)
 rho1 = Process Fluid density (kg/m3)
 rho2 = Manometer fluid density (kg/m3)
 h1 = Process fluid height in manometer (kg/m3)
 h2 = Manometer fluid height in manometer (kg/m3)
 d = Pipe diameter (m)
 */

#ifndef PitotVar_h
#define PitotVar_h

/// This subroutine is used to collect the necessary data to predict the data associated with a pitot static tube.
/// @param P2 Static pressure on connection (kPa).
/// @param rho1 Process fluid density (kg/ m3)
/// @param rho2 Manometer fluid density (kg/ m3)
/// @param h1 Process fluid height in manometer (cm)
/// @param h2 Manometer fluid height in manometer (cm)
/// @param d Pipe diameter (mm)
void PitotVar(double *P2, double *rho1, double *rho2, double *h1, double *h2, double *d);

#endif /* PitotVar_h */

#ifndef PitotCalc_h
#define PitotCalc_h

/// This subroutine is used to predict the volumetric flow rate of a fluid travelling with a pitot static tube. This function also returns the values of the initial fluid pressure and point velocity to the calling function.
/// @param P2 Static pressure on connection (kPa).
/// @param rho1 Process fluid density (kg/ m3)
/// @param rho2 Manometer fluid density (kg/ m3)
/// @param h1 Process fluid height in manometer (m)
/// @param h2 Manometer fluid height in manometer (m)
/// @param d Pipe diameter (m)
/// @param P1 Fluid pressure (Pa)
/// @param v Fluid velocity (m/s)
/// @param Q Fluid volumetric flowrate (m3/ s)
void PitotCalc(double P2, double rho1, double rho2, double h1, double h2, double d, double *P1, double *v, double *Q);
/*  This subroutine is used to predict the volumetric flow rate of a fluid travelling with a pitot static tube. This function also returns the values of the initial fluid pressure and point velocity to the calling function. This function has an external dependency on the function "ManoMeasCal(...)" that can be found in "01cMano.c".
 */

#endif /* PitotCalc_h */
