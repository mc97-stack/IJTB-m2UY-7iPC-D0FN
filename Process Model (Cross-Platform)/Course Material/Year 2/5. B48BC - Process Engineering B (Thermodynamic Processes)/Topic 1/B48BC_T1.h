//
//  B48BC_T1.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef ThermoProfiler_h
#define ThermoProfiler_h

/// This struct is used to hold the generated dataset for a thermodynamic process.
typedef struct ThermodynamicProfile{
    // Maximum of 1000 rows per 'column'
    double P[250];
    double V[250];
    double T[250];
    double W_V[250]; // Cumulative energy requirements are not calculated and stored in the struct
    double Q[250];
} ThermoProf;

#endif /* ThermoProfiler_h */

#ifndef Polytropic_h
#define Polytropic_h

void Polytropic(void);
/* This subroutine is the pseudomain subroutine guiding the user through the calculations to determine the volume work for an polytropic process. The variables used in this subroutine are:
 P = System pressure at the start and end of the process
 V = System volume at the start and end of the process
 T = System temperature at the start and end of the process
 n = moles of gas in the system
 alpha = = Polytropic index.
 Since there are 2 approaches to calculate the volume work, either method is offered to the user prior to data being collected as the required variables differ depending on the method being used.
 */

#endif /* Polytropic_h */

#ifndef Isothermal_h
#define Isothermal_h

void Isothermal(void);
/* This subroutine is the pseudomain subroutine guiding the user through the calculations to determine the volume work for an isothermal process. The variables used in this subroutine are:
 P = System pressure at the start and end of the process
 V = System volume at the start and end of the process
 T = System temperature throughout the process
 n = moles of ideal gas in the system
 Since there are 2 approaches to calculate the volume work, either method is offered to the user prior to data being collected as the required variables differ depending on the method being used.
 */

#endif /* Isothermal_h */

#ifndef Isobaric_h
#define Isobaric_h

void Isobaric(void);
/*  This subroutine is the pseudomain subroutine guiding the user through the calculations to determine the volume work for an isobaric process. The variables used in this subroutine are:
 P = System pressure throughout the process
 V = System volume at the start and end of the process
 T = System temperature at the start and end the process
 n = moles of ideal gas in the system
 Since there are 2 approaches to calculate the volume work, either method is offered to the user prior to data being collected as the required variables differ depending on the method being used.
 */

#endif /* Isobaric_h */

#ifndef Isochoric_h
#define Isochoric_h

void Isochoric(void);
/*  This subroutine is the pseudomain subroutine guiding the user through the calculations to determine the volume work for an isochoric process. The variables used in this subroutine are:
 P = System pressure start and end the process
 V = System volume throughout the process
 T = System temperature at the start and end the process
 n = moles of ideal gas in the system
 Since there are 2 approaches to calculate the volume work, either method is offered to the user prior to data being collected as the required variables differ depending on the method being used.
 */

#endif /* Isochoric_h */

#ifndef Adiabatic_h
#define Adiabatic_h

void Adiabatic(void);
/* This subroutine is the pseudomain subroutine guiding the user through the calculations to determine the volume work for an adiabatic process. The variables used in this subroutine are:
 P = System pressure at the start and end of the process
 V = System volume at the start and end of the process
 T = System temperature at the start and end of the process
 n = moles of ideal gas in the system
 gamma = = heat capacity ratio.
 
 Since there is a Pressure-Volume and Pressure Temperature explicit methods of calculating, either method should be used offered to the user for calculation. Since this must be known before collecting data, this must be stated prior to collecting any data.
 */

#endif /* Adiabatic_h */
