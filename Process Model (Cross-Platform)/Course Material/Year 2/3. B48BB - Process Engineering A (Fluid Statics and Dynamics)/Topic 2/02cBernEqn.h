//
//  02cBernEqn.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef BernEqnVar_h
#define BernEqnVar_h

/// This subroutine is used for data collection to calculate the end pressure through Bernoulli's equation. The water hammer effect is observed is u2 is set to 0.
/// @param P1 Initial fluid pressure (kPa).
/// @param rho Fluid density (kg/ m3).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s). This value is inferred using velcalc(...).
/// @param Z1 Initial fluid height (m).
/// @param Z2 Final fluid height (m).
/// @param hf Frictional head loss between points '1' and '2' (m).
void BernEqnVar(double *P1, double *rho, double *u1, double *u2, double *Z1, double *Z2, double *hf);
 
#endif /* BernEqnVar_h */

#ifndef StatHeadCalc_h
#define StatHeadCalc_h

/// This subroutine is used to calculate the static head of a fluid (m).
/// @param P Vessel pressure (Pa)
/// @param rho Fluid density (kg/ m3)
double StatHeadCalc(double P, double rho);

#endif /* StatHeadCalc_h */

#ifndef DynHeadCalc_h
#define DynHeadCalc_h

/// This subroutine is used to calculate the dynamic head of a fluid (m)
/// @param u Fluid velocity (m/ s)
double DynHeadCalc(double u);

#endif /* DynHeadCalc_h */

#ifndef BernEqnCalc_h
#define BernEqnCalc_h

/// Subroutine that calculates the total head contribution of a fluid at a process endstate (m).
/// @param stathead Static head (m)
/// @param dynhead Dynamic head (m)
/// @param Z Potential head (m)
double BernEqnCalc(double stathead, double dynhead, double Z);

#endif /* BernEqnCalc_h */

#ifndef BernEqnWrite_h
#define BernEqnWrite_h


/// This subroutine is used to output the collected data and final result to a .txt file.
/// @param P1 Initial fluid pressure (Pa).
/// @param P2 Final fluid pressure (Pa).
/// @param rho Fluid density (kg/ m3).
/// @param u1 Initial fluid velocity (m/ s).
/// @param u2 Final fluid velocity (m/ s). This value is inferred using velcalc(...).
/// @param z1 Initial fluid height (m).
/// @param z2 Final fluid height (m).
/// @param hf Frictional head loss between points '1' and '2' (m).
void BernEqnWrite(double P1, double P2, double rho, double u1, double u2, double z1, double z2, double hf);

#endif /* BernEqnWrite_h */
