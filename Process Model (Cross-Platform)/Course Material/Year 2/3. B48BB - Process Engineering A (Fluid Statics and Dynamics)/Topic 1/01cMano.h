//
//  01cMano.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef ManoMeasVar_h
#define ManoMeasVar_h

/// Subroutine used to collect the data required for completing manometer measurement calculations. The stated units state the units that the data is collected in prior to being converted for calculation.
/// @param P2 Atmospheric pressure (kPa)
/// @param rho1 Process fluid density (kg/ m3)
/// @param h1 Height of process fluid in the manometer arm (cm)
/// @param rho2 Density of the manometer fluid (kg/ m3)
/// @param h2 Height of the manometer fluid in the manometer arm (cm)
void ManoMeasVar(double *P2, double *rho1, double *h1, double *rho2, double *h2);

#endif /* ManoMeasVar_h */

#ifndef ManoEstiVar_h
#define ManoEstiVar_h

/// Subroutine used to collect the data required for completing calculations to estimate the rise of manometer fluid. The stated units state the units that the data is collected in prior to being converted for calculation.
/// @param P1 Pressure of the process fluid (kPa)
/// @param P2 Atmospheric pressure (kPa)
/// @param rho1 Density of the process fluid (kg/ m3)
/// @param rho2 Density of the manometer fluid (kg/ m3)
/// @param h1 Height of the process fluid in the manometer arm (cm)
void ManoEstiVar(double *P1, double *P2, double *rho1, double *rho2, double *h1);

#endif /* ManoEstiVar_h */

#ifndef ManoMeasCal_h
#define ManoMeasCal_h

/// Subroutine used for calculating the process fluid pressure given some atmospheric conditions. After calculation, the function returns the value of P1 or the fluid pressure.
/// @param P2 Atmospheric pressure (Pa)
/// @param rho1 Process fluid density (kg/ m3)
/// @param h1 Height of process fluid in the manometer arm (m)
/// @param rho2 Density of the manometer fluid (kg/ m3)
/// @param h2 Height of the manometer fluid in the manometer arm (m)
double ManoMeasCal(double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoMeasCal_h */

#ifndef ManoEstiCal_h
#define ManoEstiCal_h

///  Subroutine used for estimating the height of manometer fluid given some process fluid pressure in an attached pipe, density values and height of the process fluid in the manometer arm.  After calculation, the function returns h2 or the height of manometer fluid in the respective arm to the calling function.
/// @param P1 Pressure of the process fluid (kPa)
/// @param P2 Atmospheric pressure (kPa)
/// @param rho1 Density of the process fluid (kg/ m3)
/// @param rho2 Density of the manometer fluid (kg/ m3)
/// @param h1 Height of the process fluid in the manometer arm (cm)
double ManoEstiCal(double P1, double P2, double rho1, double h1, double rho2);

#endif /* ManoEstiCal_h */

#ifndef ManoMeasWrite_h
#define ManoMeasWrite_h

/// Subroutine used to write the results from manometer measurement calculations to a .txt file
/// @param P1 Process fluid pressure (Pa)
/// @param P2 Atmospheric pressure (Pa)
/// @param rho1 Process fluid density (kg/m3)
/// @param h1 Height of process fluid in manometer (m)
/// @param rho2 Manometer fluid density (kg/m3)
/// @param h2 Height of manometer fluid in manometer arm (m)
void ManoMeasWrite(double P1, double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoMeasWrite_h */

#ifndef ManoEstiWrite_h
#define ManoEstiWrite_h

/// Subroutine used to write the results from the manometer estimation calculations
/// @param P1 Process fluid pressure (Pa)
/// @param P2 Atmospheric pressure (Pa)
/// @param rho1 Process fluid density (kg/m3)
/// @param h1 Height of process fluid in manometer (m)
/// @param rho2 Manometer fluid density (kg/m3)
/// @param h2 Height of manometer fluid in manometer arm (m)
void ManoEstiWrite(double P1, double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoEstiWrite_h */
