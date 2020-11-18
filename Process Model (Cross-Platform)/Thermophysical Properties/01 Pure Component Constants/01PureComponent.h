//
//  01PureComponent.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
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

#ifndef _1PureComponent_h
#define _1PureComponent_h

/// This subroutine is a menu function which informs the user of the available enclosed subroutines.
void pureComponentConstants(void);

#endif /* _1PureComponent_h */

#ifndef CriticalProperty_h
#define CriticalProperty_h

/// This subroutine is used to guide the user through estimating the critical properties of an organic molecule
void CriticalProperty(void);

#endif /* CriticalProperty_h */

#ifndef AcentricFactor_h
#define AcentricFactor_h

/// This subroutine is used to guide the user through estimating the acentric factor of a pure component through either the Antoine equation, critical parameters or Lee-Kesler vapour pressure relations. It then return the value of the 
double AcentricFactor(void);

#endif /* AcentricFactor_h */

#ifndef BoilingFreezingPoint_h
#define BoilingFreezingPoint_h

/// This subroutine is a menu function which informs the user of the available enclosed subroutines.
void BoilingFreezingPoint(void);

#endif /* BoilingFreezingPoint_h */
