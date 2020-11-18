//
//  01bFluidVHyd.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
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

#ifndef FluidVHydVar_h
#define FluidVHydVar_h

/// Subroutine used for collecting the data required for calculating the fluid hydrostatic pressure.
/// @param rho Fluid density (kg/m3).
/// @param h Height of fluid (m).
void FluidVHydVariable(double *rho, double *h);

#endif /* FluidVHydVar_h */

#ifndef FluidVHydCalc_h
#define FluidVHydCalc_h

/// Subroutine used to calculate the fluid hydrostatic pressure. The value of fluid hydrostatic pressure is returned to the calling function.
/// @param rho Fluid density (kg/m3).
/// @param h Height of fluid (m).
double FluidVHydCalculation(double rho, double h);

#endif /* FluidVHydCalc_h */

#ifndef FluidVHydDisp_h
#define FluidVHydDisp_h

/// This subroutine is used to write the results of this program to the user console.
/// @param rho Fluid density (kg/ m3).
/// @param h Fluid depth from the free fluid surface (m).
/// @param P Hydrostatic pressure (Pa).
void FluidVHydDisplay(double rho, double h, double P);

#endif /* FluidVHydDisp_h */

#ifndef FluidVHydWrite_h
#define FluidVHydWrite_h

/// This subroutine is used to write the results of this program to a .txt file.
/// @param rho Fluid density (kg/ m3).
/// @param h Fluid depth from the free fluid surface (m).
/// @param P Hydrostatic pressure (Pa).
void FluidVHydWrite(double rho, double h, double P);
/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param rho Fluid density (kg/ m3).
/// @param h Fluid depth from the free fluid surface (m).
/// @param P Hydrostatic pressure (Pa).
void FluidVHydWriteSwitch(double rho, double h, double P);

#endif /* FluidVHydWrite_h */
