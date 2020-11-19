//
//  B48BC_T2.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
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

typedef struct T2ThermodynamicProfile{
    // Maximum of 250 rows per 'column'
    double P[250];
    double V[250];
    double T[250];
    double W_V[250]; // Cumulative energy requirements are not calculated and stored in the struct
    double Q[250];
} T2ThermoProf;

#ifndef Compressor_h
#define Compressor_h

/// This subroutine is used to guide the user through the calculations to design a reciprocating processor using a polytropic or isothermal process.
void Compressor(void);

#endif /* Compressor_h */

#ifndef PolyShaftWork_h
#define PolyShaftWork_h

/// This subroutine guides the user through the calculations to find the shaft work for an a polytropic process
void PolyShaftWork(void);

#endif /* PolyShaftWork */

#ifndef OpenFirstLaw_h
#define OpenFirstLaw_h

/// This subroutine guides the user through the calculations to first the overall energy content for an open systems and notifies the user of whether the process is operating at steady- or unsteady-state.
void OpenFirstLaw(void);

#endif /* OpenFirstLaw_h */
