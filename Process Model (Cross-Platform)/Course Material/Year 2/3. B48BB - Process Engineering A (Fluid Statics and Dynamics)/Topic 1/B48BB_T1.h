//
//  B48BB_T1.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 19/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef FluComp_h
#define FluComp_h

void FluComp(void);
/*  Subroutine that calculates the fluid compressibility using the ideal gas law. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* FluComp_h */

#ifndef FluidVHyd_h
#define FluidVHyd_h

void FluidVHyd(void);
/*  Subroutine that calculates the hydrostatic pressure gradient for a stationary fluid. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* FluidVHyd_h */

#ifndef Mano_h
#define Mano_h

void Mano(void);
/*  Subroutine that calculates the pressure that a fluid exerts of a system wall through either a vertical or inclined manometer. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* Mano_h */

#ifndef SurfTens_h
#define SurfTens_h

void SurfTens(void);
/*  Subroutine that calculates the force required to break a fluid's surface through the Du Nouy ring method. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* SurfTens_h */

#ifndef BubPres_h
#define BubPres_h

void BubPres(void);
/*  Subroutine that calculates the force required to form a bubble utilising . This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* BubPres_h */

#ifndef SurfTens_h
#define SurfTens_h

void SurfTens(void);
/*  Subroutine that calculates the force required to break a fluid's surface through the Du Nouy ring method. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* SurfTens_h */

#ifndef Capp_h
#define Capp_h

void Capp(void);
/*  Subroutine that calculates capillarity effects from surface tension data. This parent subroutine does not return a value as child subroutines are used to collect data and perform manipulations.
 */

#endif /* Capp_h */
