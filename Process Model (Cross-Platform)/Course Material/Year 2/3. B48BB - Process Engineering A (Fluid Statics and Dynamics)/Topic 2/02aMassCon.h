//
//  02aMassCon.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//Global variables
/*
 rho = Fluid density at startpoint and endpoint (kg/m3).
 d = Pipe diameter at ... (m)
 u = Point fluid velocity at ... (m/s)
 m = mass flowrate at ... (kg/s)
 q = volumetric flowrate at ... (m3/s)
 */

#ifndef MasConVarCol_h
#define MasConVarCol_h

void MassConVar(double *rho1, double *rho2, double *d1, double *d2, double *u1);
/*  This subroutine is used to collect data for the subroutine "MassCon(...)". The pipe diameters are inputted in units mm and converted to m prior to being returned to the parent subroutine ("MassCon"). Definitions of the variables stated in the declaration have been specified above. This subroutine returns the inputted variables back to the parent subroutine.
 */

#endif /* MasConVarCol_h */

#ifndef VeloCalc_h
#define VeloCalc_h

double VelCalc(double u1, double d1, double d2);
/*  This subroutine calculates the final fluid velocity at some point past where the initial measure was taken. This subroutine receives:
 - u1 = Initial fluid velocity (m/s)
 - d1 = Pipe diameter at starting point (m)
 - d2 = Pipe diameter at endpoint (m)
 This subroutine utilises the following local variables:
 frac = Calculation variable representing the ratio between pipe diameters.
 
 This subroutine then returns the final fluid velocity back to the parent subroutine.
 */

#endif /* VeloCalc_h */

#ifndef VoluFloCalc_h
#define VoluFloCalc_h

double VolFloCalc(double u, double d);
/*  This subroutine calculates the volumetric flow rate utilising the following variables:
 - u = fluid velocity
 - d = pipe diameter
 This subroutine then utilises the following local variables to calculate the volumetric flowrate:
 - A = Pipe cross-sectional area
 - q = volumetric flow rate
 A separate variable is required for the volumetric flowrate since this calculation is independent of time placement. The volumetric flowrate is then returned to the parent subroutine ("MassCon(void)").
 */

#endif /* VoluFloCalc_h */

#ifndef MassFloCalc_h
#define MassFloCalc_h

double MassFloCalc(double rho, double d, double u);
/*  This subroutine calculates the mass flowrate utilising the following variables:
 - rho = fluid density (kg/m3)
 - d = pipe diameter (m)
 - u = fluid velocity (m/s)
 This subroutine utilises the following local variables to calculate the volumetric flowrate:
 - A = Pipe cross-sectional area (m2)
 - m = Mass flowrate (kg/s)
 A separate variable is required for the mass flowrate since this calculation is independent of time placement. The volumetric flowrate is then returned to the parent subroutine ("MassCon(void)").
 */

#endif /* MassFloCalc_h */
