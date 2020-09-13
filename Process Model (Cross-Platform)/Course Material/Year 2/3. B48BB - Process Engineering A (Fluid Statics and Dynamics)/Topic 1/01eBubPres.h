//
//  01eBubPres.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef BubPresVar_h
#define BubPresVar_h

void BubPresVar(double *sigma, double *r);
/*  This subroutine is used to collect data for calculating the pressure required to hold a bubble. The variables being collected are:
 sigma = Surface tension (N/m)
 r = Bubble radius (mm)
- The collected value is then converted to m prior to being returned.
 This subroutine returns both of the collected values in the appropriate units to the main function ("BubPres").
 */

#endif /* BubPresVar_h */

#ifndef BubPresCalc_h
#define BubPresCalc_h

double BubPresCalc(double sigma, double r);
/*  This subroutine is used to calculate the bubble pressure given the surface tension (sigma)(N/m) and bubble radius (r)(m). The function then returns the bubble pressure in Pa prior to returning the calculated value to the main function ("BubPres").  
 */

#endif /* BubPresCalc_h */
