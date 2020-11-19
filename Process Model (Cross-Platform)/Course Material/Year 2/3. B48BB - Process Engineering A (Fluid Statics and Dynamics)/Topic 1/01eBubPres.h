//
//  01eBubPres.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef BubPresVar_h
#define BubPresVar_h

/// This subroutine is used for collecting the data required for calculating the pressure required to form a bubble of set radius.
/// @param sigma Surface tension (N/m).
/// @param r Bubble radius (mm).
void BubPresVariable(double *sigma, double *r);

#endif /* BubPresVar_h */

#ifndef BubPresCalc_h
#define BubPresCalc_h

/// This subroutine is used to calculate the bubble pressure. After calculation, this subroutine returns the pressure required to form the given bubble.
/// @param sigma Surface tension (N/m).
/// @param r bubble radius (m).
double BubPresCalculation(double sigma, double r);

#endif /* BubPresCalc_h */

#ifndef BubPresDisp_h
#define BubPresDisp_h

/// This subroutine is used to output the results from bubble pressure calculation to the user console.
/// @param sigma Surface tension (N/m).
/// @param r bubble radius (m).
/// @param P Bubble Pressure (Pa).
void BubPresDisplay(double sigma, double r, double P);

#endif /* BubPresDisp_h */

#ifndef BubPresWrite_h
#define BubPresWrite_h

/// This subroutine is used to write the results from bubble pressure calculation to a .txt file.
/// @param sigma Surface tension (N/m).
/// @param r bubble radius (m).
/// @param P Bubble Pressure (Pa).
void BubPresWrite(double sigma, double r, double P);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param sigma Surface tension (N/m).
/// @param r bubble radius (m).
/// @param P Bubble Pressure (Pa).
void BubPresWriteSwitch(double sigma, double r, double P);

#endif /* BubPresWrite_h */
