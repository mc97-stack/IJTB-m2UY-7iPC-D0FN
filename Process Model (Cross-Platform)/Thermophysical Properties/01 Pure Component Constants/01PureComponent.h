//
//  01PureComponent.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
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
