//
//  IdealGasLaw.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
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

#ifndef IdealPressure_h
#define IdealPressure_h

/// This subroutine is used to calculate the pure component pressure from rearrangement of the ideal gas law. This function returns the pure component pressure.
/// @param n Moles of substance
/// @param T System Temperature
/// @param V Volume of Component
double IdealPressure(double n, double T, double V);

#endif /* IdealPressure_h */

#ifndef SpecPressure_h
#define SpecPressure_h

/// This subroutine is used to calculate the pure component pressure from rearrangement of the ideal gas law applied to a real gas. This function returns the pure component pressure.
/// @param n Moles of substance
/// @param T System Temperature
/// @param V Volume of Component
/// @param R Specific gas constant
double SpecPressure(double n, double T, double V, double R);

#endif /* SpecPressure_h */

#ifndef IdealTemperature_h
#define IdealTemperature_h

/// This subroutine is used to calculate the system temperature from rearrangement of the ideal gas law. This function returns the system temperature.
/// @param n Moles of substance
/// @param P Component partial pressure
/// @param V Volume of Component
double IdealTemperature(double n, double P, double V);

#endif /* IdealTemperature_h */

#ifndef SpecTemperature_h
#define SpecTemperature_h

/// This subroutine is used to calculate the system temperature from rearrangement of the ideal gas law. This function returns the system temperature.
/// @param n Moles of substance
/// @param P Component partial pressure
/// @param V Volume of Component
/// @param R Specific gas constant
double SpecTemperature(double n, double P, double V, double R);

#endif /* SpecTemperature_h */

#ifndef IdealVolume_h
#define IdealVolume_h

/// This subroutine is used to calculate the system volume from rearrangement of the ideal gas law. This function returns the pure component volume.
/// @param n Moles of substance
/// @param P Component partial pressure
/// @param T System Temperature
double IdealVolume(double n, double P, double T);

#endif /* IdealVolume_h */

#ifndef SpecVolume_h
#define SpecVolume_h

/// This subroutine is used to calculate the system volume from rearrangement of the ideal gas law. This function returns the pure component volume.
/// @param n Moles of substance
/// @param P Component partial pressure
/// @param T System Temperature
/// @param R Specific gas constant
double SpecVolume(double n, double P, double T, double R);

#endif /* SpecVolume_h */
