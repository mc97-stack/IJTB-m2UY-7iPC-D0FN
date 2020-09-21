//
//  B48BB_T2.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 19/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef MassCon_h
#define MassCon_h

void MassCon(void);
/*  Subroutine that calculates an endstates volumetric and mass flowrates. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations (See the function header file for more in depth description).
 */

#endif /* MassCon_h */

#ifndef EnerCon_h
#define EnerCon_h

void EnerCon(void);
/*  Subroutine that checks that the energy conservation statement of the first law is not being violated by comparing the beginning and end states of a process fluid against the steady-flow energy equation. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* EnerCon_h */

#ifndef BernEqn_h
#define BernEqn_h

void BernEqn(void);
/*  Subroutine that calculates the fluid pressure (along the x-direction) at the process fluid's end state. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* BernEqn_h */

#ifndef ReyNo_h
#define ReyNo_h

void ReyNo(void);
/*  Subroutine that calculates the Reynolds number for a moving fluid in a cylindrical pipe portion. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* ReyNo_h */

#ifndef NewVisc_h
#define NewVisc_h

void NewVisc(void);
/*  Subroutine that details Newton's Law of Viscosity
 */

#endif /* NewVisc_h */

#ifndef ViscCorr_h
#define ViscCorr_h

void ViscCorr(void);
/*  Subroutine that calculates the fluid viscosity with a standard correlation. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* ViscCorr_h */

#ifndef VelProfile_h
#define VelProfile_h

void VelProfile(void);
/*  Subroutine that estimates the velocity profile for a flowing fluid with either fully developed laminar or turbulent properties. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* VelProfile_h */

#ifndef HagPois_h
#define HagPois_h

void HagPois(void);
/*  Subroutine that estimates the pressure losses incurred by fluid flowing with fully developed laminar flow properties. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* HagPois_h */
