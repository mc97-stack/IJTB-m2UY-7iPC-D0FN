//
//  01dSurfTens.h
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

#ifndef wettfacts_h
#define wettfacts_h

/// Subroutine used to provide dialogue on fluid characteristics based on the contact angle of the fluid with a solid, horizontrol surface.
/// @param cang Contact angle (degrees).
void wettabilityfacts(double cang);

#endif /* wettfacts_h */

#ifndef duNouyVar_h
#define duNouyVar_h

/// Subroutine used for collecting the data required for calculating the surface tension using the du Nouy ring method. This functions calls "wettfacts(void)" to provide facts about the fluid during data entry.
/// @param F Force to break the fluid surface (N).
/// @param L Circumference of ring. This value is inferred from the ring radius (m).
/// @param C_F Correction factor ([ ]).
/// @param cang Contact angle (degrees).
void duNouyVariable(double *F, double *L, double *C_F, double *cang);

#endif /* duNouyVar_h */

#ifndef duNouyCalc_h
#define duNouyCalc_h

/// Subroutine used to calculate the surface tension given the following variables. The function, after calculation steps, returns the value of sigma or surface tension in N/m.
/// @param F Force required to break the fluid surface (N).
/// @param L Ring circumference (m).
/// @param C_F Correction factor (C_F) ([ ]).
/// @param cang Fluid contact angle with the ring (rad). 
double duNouyCalculation(double F, double L, double C_F, double cang);

#endif /* duNouyCalc_h */

#ifndef duNouyDisp_h
#define duNouyDisp_h

/// Subroutine used to output the results of calculating the surface tension through the du Nouy Ring method to the user console.
/// @param F Force required to break the fluid surface (N).
/// @param L Ring circumference (m).
/// @param C_F Correction factor (C_F) ([ ]).
/// @param cang Fluid contact angle with the ring (rad). 
/// @param sigma Surface tension (N/m).
void duNouyDisplay(double F, double L, double C_F, double cang, double sigma);

#endif /* duNouyDisp_h */

#ifndef duNouyWrite_h
#define duNouyWrite_h

/// Subroutine used to write the results of calculating the surface tension through the du Nouy Ring method to a .txt file.
/// @param F Force required to break the fluid surface (N).
/// @param L Ring circumference (m).
/// @param C_F Correction factor (C_F) ([ ]).
/// @param cang Fluid contact angle with the ring (rad). 
/// @param sigma Surface tension (N/m).
void duNouyWrite(double F, double L, double C_F, double cang, double sigma);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param F Force required to break the fluid surface (N).
/// @param L Ring circumference (m).
/// @param C_F Correction factor (C_F) ([ ]).
/// @param cang Fluid contact angle with the ring (rad). 
/// @param sigma Surface tension (N/m).
void duNouyWriteSwitch(double F, double L, double C_F, double cang, double sigma);

#endif /* duNouyWrite_h */
