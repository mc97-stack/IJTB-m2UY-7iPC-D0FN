//
//  B48BC_T1.h
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

#ifndef ThermoProfiler_h
#define ThermoProfiler_h

/// This struct is used to hold the generated dataset for a thermodynamic process.
typedef struct T1ThermodynamicProfile{
    // Remember to change the limits of the intervals and for loops in the function as well!
    double P[250];
    double V[250];
    double T[250];
    double W_V[250]; // Cumulative energy requirements are not calculated and stored in the struct
    double Q[250];
} T1ThermoProf;

#endif /* ThermoProfiler_h */

#ifndef Polytropic_h
#define Polytropic_h

/// This subroutine is used to guide the user through collecting the data required to estimate the volume work and plot the thermodynamic profile for a polytropic process.
void Polytropic(void);

#endif /* Polytropic_h */

#ifndef Isothermal_h
#define Isothermal_h

/// This subroutine is used to guide the user through collecting the data required to estimate the volume work and plot the thermodynamic profile for an Isothermal process.
void Isothermal(void);

#endif /* Isothermal_h */

#ifndef Isobaric_h
#define Isobaric_h

/// This subroutine is used to guide the user through collecting the data required to estimate the volume work and plot the thermodynamic profile for an Isobaric process.
void Isobaric(void);

#endif /* Isobaric_h */

#ifndef Isochoric_h
#define Isochoric_h

/// This subroutine is used to guide the user through collecting the data required to estimate the volume work and plot the thermodynamic profile for an Isochoric process.
void Isochoric(void);

#endif /* Isochoric_h */

#ifndef Adiabatic_h
#define Adiabatic_h

/// This subroutine is used to guide the user through collecting the data required to estimate the volume work and plot the thermodynamic profile for an Adiabatic process.
void Adiabatic(void);

#endif /* Adiabatic_h */
