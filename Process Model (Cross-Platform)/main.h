//
//  main.h
//  Process Model (Cross-Platform)
//  
//  Created by Matthew Cheung on 17/08/2020.
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

#ifndef main_h
#define main_h

int main(void);

/* This is the subroutine that provides access to all subroutines contained wit-
hin the program through a series of menus*/

#endif /* main_h */

#ifndef MinorUnitOps_h
#define MinorUnitOps_h

void MinorUnitOps(void);

/* This contains access to the subroutines involved with the design and control 
 of the following minor unit operations:
 - Pump
 - Compressor
 - Turbine
 - Heat Exchanger (Sensible heat)
 - Oil & Gas Processing equipment
 */

#endif /* MinorUnitOps_h */

#ifndef MajorUnitOps_h
#define MajorUnitOps_h

void MajorUnitOps(void);

/* This contains access to the subroutines involved with the design and control 
 of the following major unit operations:
 - Heat exchanger (Latent heat)
 - Reactor (w/ and w/o Catalyst present)
 - Bioreactor
 - Flash Drum
 - Distillation Column (w/ Trays)
 - Absorption column (+ apply to distillation)
 - Liquid-Liquid Extraction
 - Evaporator
 - Dryer
 - Crystalliser
 */

#endif /* MajorUnitOps_h */

#ifndef CourseSelection_h
#define CourseSelection_h

void CourseSelection(void);
/* This contains the menu that allows the user to select the university course to access in option '3' of the switch statement contained in "main.c"*/

#endif /* CourseSelection_h */

#ifndef ThermoProps_h
#define ThermoProps_h

void ThermoProps(void);
/* This contains access to all subroutines concerned with estimation the following thermophysical properties:
 - Critical Properties
 - Pure component acentric factor
 - Estimation of Boiling and Freezing Points
 - PVT relations of pure component fluids
 - Mixing rules
    - N.B. Gibbs-Duhem is not included 
 - Fluid heat capacities
 - Thermodynamic Properties of Ideal Gases
 - Vapor Pressures for pure fluids
 - Enthalpy of Vaporisation for pure fluids
 - Fluid Phase equilibria for multicomponent systems (VLE, LLE, Electrolytic solutions)
 - Viscosity
 - Thermal Conductivity
 - Binary liquid diffusivities (Incl. Multicomponent mixtures and electrolytic solutions
 - Surface tension
 */

#endif /* ThermoProps_h */

#ifndef DynProcessSim_h
#define DynProcessSim_h

void DynProcessSim(void);

/* This contains access to all subroutines made available in the Major and Minor unit operations in addition to pipe sizing to optimise fluid velocities
 */

#endif /* DynProcessSim_h */

#ifndef NiceThings_h
#define NiceThings_h

void NiceThings(void);

/* This will operate similar to an appendix in a report, whatever doesn't fit in the main body of the program will live here*/

#endif /* NiceThings_h */

#ifndef License_h
#define License_h

/// This subroutine is used to display the GNU General Public License on the user console.
void License(void);

#endif /* License_h */

#ifndef Year1_h
#define Year1_h

void Year1(void);

/* This function contains access to the following subroutines:
 - B17CA - Principles of Chemistry
 - B47AA - Process Industries A
 - B47AC - Foundation Engineering A (Physics)
 - F17XA - Mathematics for Engineers and Scientists 1
 - B17BC - Chemical Reactivity
 - B47AB - Process Industries B
 - B47AD - Foundation Engineering B (Biology)
 - F17XB - Mathematics for Engineers and Scientists 2
 */
#endif /* Year1_h */

#ifndef Year2_h
#define Year2_h

void Year2(void);

/* This function contains access to the following subroutines:
 - B18AP - Chemical Thermodynamics and Introductory Chemical Kinetics for Chemical Engineers
 - B48BA - Process Industries C
 - B48BB - Process Engineering A (Fluid Statics and Dynamics)
 - F18XC - Mathematics for Engineers and Scientists 3
 - B48BC - Process Engineering B (Introduction to Thermodynamics)
 - B48BD - Process Engineering C (Heat Transfer)
 - F18XD - Mathematics for Engineers and Scientists 4
 */

#endif /* Year2_h */

#ifndef Year3_h
#define Year3_h

void Year3(void);

/* This function contains access to the following subroutines:
- B18OA - Organic Structural Identification, Stereochemistry and Reaction Mechanisms
- B48CA - Separation Processes A
- B49CB - Business Awareness, Safety and Sustainability
- F49CC - Chemical Reaction Engineering A
- B18OB - Synthesis in Organic Chemistry
- B48CB - Separation Processes B
- B49CE - Multiphase Thermodynamics
- B49CF - Process Modelling and Control
*/

#endif /* Year3_h */

#ifndef Year4_h
#define Year4_h

void Year4(void);

/* This function contains access to the following subroutines:
- B40DB - Sustainability, Health and Safety
- B40EA - Unit Operations A
- B40DC - Energy Generation and Utilisation
- B41OA - Oil and Gas Processing
- B40DD - Reaction Engineering B
*/

#endif /* Year4_h */
