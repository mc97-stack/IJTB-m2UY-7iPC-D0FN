//
//  02hHagPois.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 21/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 L = Pipe length (m)
 d = pipe diameter (m)
 u = Average fluid velocity (m/s)
 mu = Fluid viscosity (Pa.s)
 dP = Frictional pressure loss (Pa)
 */

#ifndef HagPoisVar_h
#define HagPoisVar_h

void HagPoisVar(double *u, double *mu, double *L, double *d);
/*  This subroutine is used to collect the variables required to calculate the frictional pressure loss of a fluid with a laminar flow regime. This subroutine uses the additional character input variable, "input", in addition to the global variables stated earlier:
 L = Pipe length (m)
 d = pipe diameter (mm)
    -> This value is converted after input to metres.
 u = Average fluid velocity (m/s)
 mu = Fluid viscosity (Pa.s)
    -> This value is converted to Pa.s after input.
 This subroutine returns the values of all inputted variables to the calling function. This subroutine has no external dependencies.
 */

#endif /* HagPoisVar_h */

#ifndef HagPoisCalc_h
#define HagPoisCalc_h

double HagPoisCalc(double u, double mu, double L, double d);
/*  This subroutine is used to calculate the frictional pressure losses for a fluid with a laminar flow regime with the Hagen-Poiseulle equation. This subroutine returns the frictional pressure loss calculated from the inputted values and displays the calculation result in the command window 
 */
#endif /* HagPoisCalc_h */
