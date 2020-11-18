//
//  B48BB_T1.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 19/08/2020.
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

#ifndef FluComp_h
#define FluComp_h

/// This subroutine guides the user through gathering the data and calculation of the fluid coefficient of compressibility derived from the ideal gas law..
void CoefficientofCompressibility(void);

#endif /* FluComp_h */

#ifndef FluidVHyd_h
#define FluidVHyd_h

/// This subroutine guides the user through gathering the data and calculation of the hydrostatic pressure gradient for a stationary fluid.
void FluidVerticalHydrostaticPressure(void);

#endif /* FluidVHyd_h */

#ifndef Mano_h
#define Mano_h

/// This subroutine guides the user through gathering the data and calculation of the pressure that a fluid exerts of a system wall through either a vertical or inclined manometer.
void Manometer(void);

#endif /* Mano_h */

#ifndef SurfTens_h
#define SurfTens_h

/// This subroutine guides the user through gathering the data and calculation of  the force required to break a fluid's surface through the Du Nouy ring method. This function calls "BubPresCalc" from "01eBubPres.c" to calculate the internal pressure of some bubble containing the fluid under analysis and "CappCalch" and "CappCalcP" located in "01fCapp.c" to calculate the cappillary rise and pressure respectively.
void SurfaceTension(void);

#endif /* SurfTens_h */

#ifndef BubPres_h
#define BubPres_h

/// This subroutine guides the user through gathering the data and calculation of  the pressure of a bubble using the fluid surface tension.
void BubblePressure(void);

#endif /* BubPres_h */

#ifndef Capp_h
#define Capp_h

/// This subroutine guides the user through gathering the data and calculation of  capillarity effects from surface tension data.
void Cappilarity(void);

#endif /* Capp_h */
