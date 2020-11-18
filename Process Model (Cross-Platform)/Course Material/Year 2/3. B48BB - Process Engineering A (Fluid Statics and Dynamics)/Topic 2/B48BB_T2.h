//
//  B48BB_T2.h
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

#ifndef MassCon_h
#define MassCon_h

/// This subroutine guides the user through gathering the data and calculation of volumetric and mass flowrates at a process endstate.
void MassConservation(void);

#endif /* MassCon_h */

#ifndef EnerCon_h
#define EnerCon_h

/// This subroutine guides the user through gathering the data and determining whether the first law for an open system at steady-state is being violated or not.
void EnergyConservation(void);

#endif /* EnerCon_h */

#ifndef BernEqn_h
#define BernEqn_h

/// This subroutine guides the user through gathering the data and calculation of the fluid pressure at a process endstate through Bernoulli's equation.
void BernoulliEquation(void);

#endif /* BernEqn_h */

#ifndef ReyNo_h
#define ReyNo_h

/// This subroutine guides the user through gathering the data and calculation of Reynold's number for a fluid
void ReynoldsNumber(void);

#endif /* ReyNo_h */

#ifndef NewVisc_h
#define NewVisc_h

void NewVisc(void);
/*  Subroutine that details Newton's Law of Viscosity
 */

#endif /* NewVisc_h */

#ifndef ViscCorr_h
#define ViscCorr_h

/// This subroutine guides the user through gathering the data and calculation of dynamic and kinematic viscosity from standard correlations.
void ViscosityCorrelation(void);

#endif /* ViscCorr_h */

#ifndef VelProfile_h
#define VelProfile_h

/// This subroutine guides the user through gathering the data and estimation of the velocity profile for a flowing fluid with either fully developed laminar or turbulent properties.
void VelocityProfileMenu(void);

#endif /* VelProfile_h */

#ifndef HagPois_h
#define HagPois_h

/// This subroutine guides the user through gathering the data and calculation of the pressure losses incurred by a fluid flowing with fully developed laminar flow properties.
void HagenPoiseuille(void);

#endif /* HagPois_h */
