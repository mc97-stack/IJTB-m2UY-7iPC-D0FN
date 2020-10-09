//
//  B48BB_T3.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 19/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef GenPressLoss_h
#define GenPressLoss_h

void GenPressureLoss(void);
/*  Subroutine used to calculate the pressure losses incurred by any moving fluid. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* GenPressLoss_h */

#ifndef HydrDiam_h
#define HydrDiam_h

void HydrDiam(void);
/*  Subroutine used to calculate the hydraulic diameter of a non-circular pipe. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* HydrDiam_h */

#ifndef Fittings_h
#define Fittings_h

void Fittings(void);
/*  Subroutine menu to select which correlation should be used for pressure losses through pipe fittings. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* Fittings_h */

#ifndef Pitot_h
#define Pitot_h

void Pitot(void);
/*  Subroutine used to calculate the pressure of a flowing fluid. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* Pitot_h */

#ifndef Orifice_h
#define Orifice_h

void Orifice(void);
/*  Subroutine used to calculate the mass flowrate of a flowing fluid through an orifice plate meter. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* Orifice_h */

#ifndef Rotameter_h
#define Rotameter_h

void Rotameter(void);
/*  Subroutine used to calculate the mass flowrate of a flowing fluid through a rotameter. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* Rotameter_h */
