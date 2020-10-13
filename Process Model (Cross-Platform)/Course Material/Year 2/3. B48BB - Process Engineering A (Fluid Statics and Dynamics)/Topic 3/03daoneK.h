//
//  03daoneK.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef OneKCalc_h
#define OneKCalc_h

/// This subroutine is used to calculate the head loss associated with one fitting. The following variables are required by this subroutine. The subroutine returns the total head loss for the singular fitting, multiplied by the count.
/// @param count Number of occurences of the fitting being calculated.
/// @param i Fitting identifier. This is numbered from 0 - 14 in the order that the counts were asked for in "OneK(void)".
/// @param u Fluid Velocity (m/ s).
double OneKCalc(int count, int i, double u);

#endif /* OneKCalc_h */

#ifndef OneK_h
#define OneK_h

/// This subroutine is the pseudomain subroutine used to calculate the head loss associated with standard pipe fittings with the 1K method (Also known as the Excess head method).
double OneK(void);

#endif /* _OneK_h */
