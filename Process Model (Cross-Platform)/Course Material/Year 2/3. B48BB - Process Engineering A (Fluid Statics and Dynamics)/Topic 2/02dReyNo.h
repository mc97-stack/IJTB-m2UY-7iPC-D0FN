//
//  02dReyNo.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 14/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 ReyNum = Variable used to hold the value of Reynolds number
 rho = Fluid density (kg/m3)
 u = Fluid velocity (m/s)
 d = Pipe diameter (m)
 mu = Fluid viscosity (Pa.s)
 */

#ifndef ReyNoVar_h
#define ReyNoVar_h

void ReyNoVar(double *rho, double *u, double *d, double *mu);
/*  Subroutine used to collect the data required to calculate Reynolds number. The local variables used in this function are:
 - rho = Fluid density (kg/m3)
 - u = Fluid velocity (m/s)
 - d = Pipe diameter (mm) (N.B. This value is converted to meters prior to returning to parent subroutine) 
 - mu = Fluid viscosity (cP) (N.B. This value is converted to Pa.s prior to returning to the parent subroutine)
 */

#endif /* ReyNoVar_h */

#ifndef ReyNoCalc_h
#define ReyNoCalc_h

double ReyNoCalc(double rho, double u, double d, double mu);
/*  This subroutine is used to calculate the Reynolds number of a moving fluid. It receives the following variable from the calling subroutine ("ReyNo(void)"):
 - rho = Fluid density (kg/m3)
 - u = Fluid velocity (m/s)
 - d = Pipe diameter (m)
 - mu = Fluid viscosity (Pa.s)
 After calculating the Reynolds number from the received variables, it then returns visual output informing the user of the flow regime in operation assuming a fully developed velocity profile.
 */

#endif /* ReyNoCalc_h */
