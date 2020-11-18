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
/// @param allowZero Integer value used to control whether a zero value is permitted in the data entry. A value of 0 will force a non-zero value to be entered.
/// @param allowNeg Integer value used to control whether a negative value is permitted in the data entry. A value of 0 will force a positive value to be entered.
/// @param VariableName Variable descriptor.
/// @param Units Units of the variable.
double inputDouble(int allowZero, int allowNeg, char VariableName[], char Units[]);

#endif /* Input_h */

#ifndef Timer_h
#define Timer_h

/// This subroutine takes and returns the difference between two time states of the internal CPU.
/// @param start Starting time state of process.
/// @param end Ending time state of process.
double timer(struct timespec start, struct timespec end);

#endif /* Timer_h */

#ifndef pcterr_h
#define pcterr_h

/// This subroutine is used calculate the percentage error in a calculated value 
/// @param input Calculated value.
/// @param data Empirical value.
double pcterror(double input, double data);

#endif /* pcterr_h */

#ifndef Continue_h
#define Continue_h

/// This subroutine is used to control whether the user would like to continue with another round of calculations or go to the above menu.
/// @param ControlVariable Variable controlling the main loop in the subroutine it is called from.
int Continue(int ControlVariable);

#endif /* System_h */
