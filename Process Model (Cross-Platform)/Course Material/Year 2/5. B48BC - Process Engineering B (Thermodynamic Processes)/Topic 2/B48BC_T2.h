//
//  B48BC_T2.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
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

/// This subroutine is used to guide the user through the calculations to design a reciprocating processor using a polytropic process.
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

#ifndef AppFirstLaw_h
#define AppFirstLaw_h

/// This subroutine guides the user through checking unit operations for whether they are in violation of the first law of thermodynamics. For this course, only the following are discussed: Heat exchanger, Non-adiabatic compression, Pump/compressor in adiabatic operation, Isothermal compression of an ideal gas and Polytropic compression.
void AppFirstLaw(void);

#endif /* AppFirstLaw_h */
