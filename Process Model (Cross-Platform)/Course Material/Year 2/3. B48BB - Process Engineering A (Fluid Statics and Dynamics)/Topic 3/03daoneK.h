//
//  03daoneK.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef OneKCalc_h
#define OneKCalc_h

double OneKCalc(int count, int i, double u);
/*  This subroutine is used to calculate the head loss associated with one fitting. The following variables are required by this subroutine:
 - count = Occurence of the fitting being calculated
 - i = The fitting being calculated. This is in the same order that the counts were asked for in "OneK(void"
 - u = The fluid velocity.
 This subroutine then returns the total head loss associated with the multiple of fittings inputted to the subroutine.
 */

#endif /* OneKCalc_h */

#ifndef OneK_h
#define OneK_h

double OneK(void);
/*  This subroutine is the pseudomain subroutine used to calculate the head loss associated with standard pipe fittings with the 1K method (Also known as the Excess head method). Since the data cannot be collected and transferred from a separate data collection subroutine, this subroutine collects the required data and performs the manipulations. The continue function has been removed from this pseudomain subroutine.
 */

#endif /* _OneK_h */
