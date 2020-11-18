//
//  B48BB_T3.h
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

#ifndef GenPressLoss_h
#define GenPressLoss_h

/// This subroutine guides the user through gathering the data and calculation of pressure losses for a moving fluid between Reynold's number of 0 < Re <= 10,000,000.
void GeneralPressureLoss(void);

#endif /* GenPressLoss_h */

#ifndef HydrDiam_h
#define HydrDiam_h

/// This subroutine guides the user through gathering the data and calculation of hydraulic diameter for a non-circular pipe.
void HydraulicDiameter(void);

#endif /* HydrDiam_h */

#ifndef Fittings_h
#define Fittings_h

/// This subroutine guides the user through gathering the data and calculation of pressure losses through pipe fittings with the 1K, 3K and equivalent length methods.
void Fittings(void);

#endif /* Fittings_h */

#ifndef Pitot_h
#define Pitot_h

/// This subroutine guides the user through gathering the data and calculation of pressure of a flowing fluid using a pitot static tube.
void PitotStaticTube(void);

#endif /* Pitot_h */

#ifndef Orifice_h
#define Orifice_h

/// This subroutine guides the user through gathering the data and calculation of the mass flowrate of a flowing fluid through an orifice plate meter.
void OrificePlateMeter(void);

#endif /* Orifice_h */

#ifndef Rotameter_h
#define Rotameter_h

/// This subroutine guides the user through gathering the data and calculation of the mass flowrate of a flowing fluid through a rotameter.
void Rotameter(void);

#endif /* Rotameter_h */
