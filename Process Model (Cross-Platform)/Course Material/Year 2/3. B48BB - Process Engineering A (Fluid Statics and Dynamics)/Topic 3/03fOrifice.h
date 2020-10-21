//
//  03fOrifice.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef OrificeVar_h
#define OrificeVar_h

/// This subroutine is used to collect the data required to predict the mass flowrate through an orifice plate.
/// @param C_d Discharge coefficient
/// @param d1 Pipe diameter (mm)
/// @param d2 Vena contracta diameter (mm)
/// @param rho Fluid density (kg/ m3)
/// @param P1 Initial system pressure (kPa)
/// @param P2 Final system pressure (kPa)
/// @param h_f Frictional head loss (m)
void OrificeVar(double *C_d, double *d1, double *d2, double *rho, double *P1, double *P2, double *h_f);

#endif /* OrificeVar_h */

#ifndef OrificeCalc_h
#define OrificeCalc_h

/// This subroutine is used to calculate the mass flowrate, volumetric flowrate and average fluid velocity as it flows through an orifice plate meter through Bernoulli's principle.
/// @param C_d Discharge coefficient
/// @param d1 Pipe diameter (m)
/// @param d2 Vena contracta diameter (m)
/// @param rho Fluid density (kg/ m3)
/// @param P1 Initial system pressure (Pa)
/// @param P2 Final system pressure (Pa)
/// @param h_f Frictional head loss (m)
/// @param u Fluid velocity (m/s)
/// @param Q Fluid volumetric flowrate (m3/ s)
/// @param m Fluid mass flowrate (kg/ s)
void OrificeCalc(double C_d, double d1, double d2, double rho, double P1, double P2, double h_f, double *u, double *Q, double *m);

#endif /* OrificeCalc_h */

#ifndef OrificeWrite_h
#define OrificeWrite_h

/// This subroutine is used to write the collected data and the calculated values to a .txt file.
/// @param P1 Initial system pressure (Pa)
/// @param P2 Final system pressure (Pa)
/// @param rho Fluid density (kg/ m3)
/// @param d1 Pipe diameter (m)
/// @param d2 Vena contracta diameter (m)
/// @param C_d Discharge coefficient
/// @param h_f Frictional head loss (m)
/// @param u Fluid velocity (m/s)
/// @param Q Fluid volumetric flowrate (m3/ s)
/// @param m Fluid mass flowrate (kg/ s)
void OrificeWrite(double P1, double P2, double rho, double d1, double d2, double C_d, double h_f, double u, double Q, double m);

#endif /* OrificeWrite_h */
