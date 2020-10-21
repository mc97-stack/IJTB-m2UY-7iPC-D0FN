//
//  01fCapp.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef CappVar_h
#define CappVar_h

/// Subroutine used to collect the data required to determine the capillary rise and pressure.
/// @param sigma Surface tension (N/m)
/// @param cang Contact angle (deg)
/// @param rho Fluid density (kg/m3)
/// @param d Cappillary tube diameter (mm)
void CappVar(double *sigma, double *cang, double *rho, double *d);

#endif /* _1fCapp_h */

#ifndef CappCalch_h
#define CappCalch_h

/// Subroutine used to calculate the capillary rise given the arguments required. This subroutine, after calculation, returns the capillary rise (m) to the calling function.
/// @param sigma Surface tension (N/m)
/// @param cang Contact angle (rad)
/// @param rho Fluid density (kg/m3)
/// @param d Capillary tube diameter (m)
double CappCalch(double sigma, double cang, double rho, double d);

#endif /* CappCalch_h */

#ifndef CappCalcP_h
#define CappCalcP_h

/// Subroutine used to calculate the capillary pressure given the required arguments. This subroutine, after calculation, returns the capillary pressure (Pa) to the calling function.
/// @param sigma Surface tension (N/m)
/// @param cang Contact angle (rad)
/// @param d Capillary tube diameter (m)
double CappCalcP(double sigma, double cang, double d);

#endif /* CappCalcP_h */

#ifndef CappWrite_h
#define CappWrite_h

/// Subroutine used to output the results of capillary rise and pressure from capillarity calculations to a .txt file.
/// @param sigma Surface Tension (N/m)
/// @param cang Contact angle (rad)
/// @param d Capillary tube diameter
/// @param h Capillary rise (m)
/// @param Pc Capillary pressure (Pa) 
void CappWrite(double sigma, double cang, double d, double h, double Pc);

#endif /* CappWrite_h */
