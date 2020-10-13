//
//  01eBubPres.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef BubPresVar_h
#define BubPresVar_h

/// Subroutine used for collecting the data required for calculating the pressure required to form a bubble of set radius.
/// @param sigma Surface tension (N/m)
/// @param r Bubble radius (mm)
void BubPresVar(double *sigma, double *r);

#endif /* BubPresVar_h */

#ifndef BubPresCalc_h
#define BubPresCalc_h

/// Subroutine is used to calculate the bubble pressure given the surface tension and bubble radius. After calculation, this subroutine returns the pressure required to form the given bubble.
/// @param sigma Surface tension (N/m)
/// @param r bubble radius (r)(m)
double BubPresCalc(double sigma, double r);

#endif /* BubPresCalc_h */
