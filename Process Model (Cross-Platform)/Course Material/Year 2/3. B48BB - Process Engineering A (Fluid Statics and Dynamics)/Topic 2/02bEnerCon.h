//
//  02bEnerCon.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef EnthalpyConv_h
#define EnthalpyConv_h

double EnthalpyConv(double u, double P, double rho);
/*  This subroutine is used to convert between internal energy and enthalpy. The subroutine receives values for the internal energy (u), pressure (P) and fluid density (rho) at a particular time state and performs a manipulation to determine the enthalpy at that time. This subroutine then returns the value of enthalpy to the function where this subroutine was called.*/

#endif /* EnthalpyConv_h */

#ifndef EnerConVar_h
#define EnerConVar_h

void EnerConVar(double *h1, double *h2, double *u1, double *u2, double *z1, double *z2, double *q, double *w);
/*  This subroutine is being used for collecting to verify a process against the steady flow energy equation. This equation has two forms for how a process can be validated, either the internal energy or enthalpy definition. To simplify calculations later in the program, the enthalpy definition is used for validation. This means that the internal energy must be converted to its enthalpy equivalent. Due to the two methods being used, there are additional local variables required in this function, these are:
 - inteng = Internal energy at the start and endpoints
 - pres = system pressure at the start and endpoints
 - rho = fluid density at the start and endpoints
 
 Additional local variables are:
 - input = character input variable
 - method = character input variable used to determine which method of calculation is to be used.
 - whilmeth = integer value to ensure that a valid input deision is made regarding the method variable.
 
 After data has been collected, it returns the values of all variables collected back to the main function ("EnerCon(void)")
 */

#endif /* EnerConVar_h */

#ifndef EnerConFluCalc_h
#define EnerConFluCalc_h

double EnerConFluCalc(double h, double u, double z);
/*  This subroutine is used to calculate the fluid intensive portion of the steady flow energy equation. By definition, this then receives the variables:
 - Enthalpy (h) (kJ/kg)
 - Fluid velocity (u) (m/s)
 - Relative height (Z) (m)
 
 This subroutine also utilises the following local variables to aid in calculation:
 - kin = kinetic energy
 - pot = potential energy
 - EnerCont = Total energy content
 
 This subroutine then returns the value of EnerCont back to the parent subroutine ("EnerCon(void)").
 */

#endif /* EnerConFluCalc_h */

#ifndef EnerConProCalc_h
#define EnerConProCalc_h

double EnerConProCalc(double q, double w);
/*  This subroutine is used to determine the total energy inputted into the system by the process. By definition, this can either be heat (q) or work (w). The subroutine then returns the value of "Energy" to the parent subroutine after adding the values of q and w together.*/

#endif /* EnerConProCalc_h */
