//
//  01cMano.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef ManoMeasVar_h
#define ManoMeasVar_h

/// This subroutine is used to collect the data required for completing manometer measurement calculations. The stated units state the units that the data is collected in prior to being converted for calculation.
/// @param P2 Atmospheric pressure (kPa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param h1 Height of process fluid in the manometer arm (cm).
/// @param rho2 Density of the manometer fluid (kg/ m3).
/// @param h2 Height of the manometer fluid in the manometer arm (cm).
void ManoMeasVariable(double *P2, double *rho1, double *h1, double *rho2, double *h2);

#endif /* ManoMeasVar_h */

#ifndef ManoEstiVar_h
#define ManoEstiVar_h

/// This subroutine is used to collect the data required for completing calculations to estimate the rise of manometer fluid. The stated units state the units that the data is collected in prior to being converted for calculation.
/// @param P1 Pressure of the process fluid (kPa).
/// @param P2 Atmospheric pressure (kPa).
/// @param rho1 Density of the process fluid (kg/ m3).
/// @param rho2 Density of the manometer fluid (kg/ m3).
/// @param h1 Height of the process fluid in the manometer arm (cm).
void ManoEstiVariable(double *P1, double *P2, double *rho1, double *rho2, double *h1);

#endif /* ManoEstiVar_h */

#ifndef ManoMeasCal_h
#define ManoMeasCal_h

/// This subroutine is used for calculating the process fluid pressure given some atmospheric conditions. After calculation, the function returns the value of P1 or the fluid pressure.
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/ m3).
/// @param h1 Height of process fluid in the manometer arm (m).
/// @param rho2 Density of the manometer fluid (kg/ m3).
/// @param h2 Height of the manometer fluid in the manometer arm (m)
double ManoMeasCalculation(double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoMeasCal_h */

#ifndef ManoEstiCal_h
#define ManoEstiCal_h

/// This subroutine is used for estimating the height of manometer fluid given some process fluid pressure. After calculation, the function returns h2 or the height of manometer fluid in the respective arm to the calling function.
/// @param P1 Pressure of the process fluid (kPa).
/// @param P2 Atmospheric pressure (kPa).
/// @param rho1 Density of the process fluid (kg/ m3).
/// @param rho2 Density of the manometer fluid (kg/ m3).
/// @param h1 Height of the process fluid in the manometer arm (cm).
double ManoEstiCalculation(double P1, double P2, double rho1, double h1, double rho2);

#endif /* ManoEstiCal_h */

#ifndef ManoDisp_h
#define ManoDisp_h

/// This subroutine is used to write the results from manometer measurement calculations to the user console.
/// @param P1 Process fluid pressure (Pa).
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/m3).
/// @param h1 Height of process fluid in manometer (m).
/// @param rho2 Manometer fluid density (kg/m3).
/// @param h2 Height of manometer fluid in manometer arm (m).
void ManoMeasDisplay(double P1, double P2, double rho1, double h1, double rho2, double h2);

/// This subroutine is used to output the results from the manometer estimation calculations to the user console.
/// @param P1 Process fluid pressure (Pa).
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/m3).
/// @param h1 Height of process fluid in manometer (m).
/// @param rho2 Manometer fluid density (kg/m3).
/// @param h2 Height of manometer fluid in manometer arm (m).
void ManoEstiDisplay(double P1, double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoDisp_h */

#ifndef ManoMeasWrite_h
#define ManoMeasWrite_h

/// This subroutine is used to write the results from manometer measurement calculations to a .txt file.
/// @param P1 Process fluid pressure (Pa).
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/m3).
/// @param h1 Height of process fluid in manometer (m).
/// @param rho2 Manometer fluid density (kg/m3).
/// @param h2 Height of manometer fluid in manometer arm (m).
void ManoMeasWrite(double P1, double P2, double rho1, double h1, double rho2, double h2);

/// This subroutine is used to ask the user if they would like to save the results of this measurement program to a file.
/// @param P1 Process fluid pressure (Pa).
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/m3).
/// @param h1 Height of process fluid in manometer (m).
/// @param rho2 Manometer fluid density (kg/m3).
/// @param h2 Height of manometer fluid in manometer arm (m).
void ManoMeasWriteSwitch(double P1, double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoMeasWrite_h */

#ifndef ManoEstiWrite_h
#define ManoEstiWrite_h

/// This subroutine is used to write the results from the manometer estimation calculations to a .txt file.
/// @param P1 Process fluid pressure (Pa).
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/m3).
/// @param h1 Height of process fluid in manometer (m).
/// @param rho2 Manometer fluid density (kg/m3).
/// @param h2 Height of manometer fluid in manometer arm (m).
void ManoEstiWrite(double P1, double P2, double rho1, double h1, double rho2, double h2);

/// This subroutine is used to ask the user if they would like to save the results of the estimation program to a file.
/// @param P1 Process fluid pressure (Pa).
/// @param P2 Atmospheric pressure (Pa).
/// @param rho1 Process fluid density (kg/m3).
/// @param h1 Height of process fluid in manometer (m).
/// @param rho2 Manometer fluid density (kg/m3).
/// @param h2 Height of manometer fluid in manometer arm (m).
void ManoEstiWriteSwitch(double P1, double P2, double rho1, double h1, double rho2, double h2);

#endif /* ManoEstiWrite_h */
