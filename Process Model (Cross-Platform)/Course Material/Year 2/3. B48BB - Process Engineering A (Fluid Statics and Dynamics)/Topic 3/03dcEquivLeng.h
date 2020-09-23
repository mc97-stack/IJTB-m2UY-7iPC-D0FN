//
//  03dcEquivLeng.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef EquivLeng_h
#define EquivLeng_h

void EquivLeng(void);
/*  This subroutine is used to calculate head loss through the equivalent length method. Due to the length of this subroutine, an in-depth description is provided below:
 1) The double array containing the data is declared with additional columns for the user inputs and calculation variables.
 2) The data required for calculation is inputted into column 0
 3) The user is asked to input counts of each fitting into the program. Values are inputted into column 1.
 4) A for loop is run multiplying the counts by the equivalent length values. Values are outputted to column 2.
 5) Another for loop is run to determine the cumulative equivalent length.
 6) The user is asked whether they would like the data to be displayed in the console window. If affirmative, data is displayed
 This function currently does not return a value but future versions of this file may return the cumulative equivalent length to a general pressure loss function. 
 The option to declare the fitting description in a separate 2D character array can also be explored to further develop this function.
 */

#endif /* _3dcEquivLeng_h */
