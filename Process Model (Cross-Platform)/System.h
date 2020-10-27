//
//  System.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 24/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef Input_h
#define Input_h

/// This subroutine is used to force the entry of a non-zero value that will be assigned to a variable. 
/// @param VariableName Variable descriptor.
/// @param Units Units of the variable.
double inputDouble(char VariableName[], char Units[]);

#endif /* Input_h */

#ifndef Continue_h
#define Continue_h

/// This subroutine is used to control whether the user would like to continue with another round of calculations or go to the above menu.
/// @param ControlVariable Variable controlling the main loop in the subroutine it is called from.
int Continue(int ControlVariable);

#endif /* System_h */
