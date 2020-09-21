//
//  02g2TurVelPro.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 21/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef TurVelProVar_h
#define TurVelProVar_h

void TurVelProVar(double *umax, double *d);
/*  This subroutine is used for the data collection of the turbulent flow velocity profile using Prandtl's one-seventh law. this subroutine utilises the following variables:
 - umax = maximum point fluid velocity
 - u = Average fluid velocity.
 - d = Pipe diameter (mm)
    -> This value is converted to metres before being returned to the main function ("TurVelPro(void)")
 This subroutine then retuns the values of umax (derived from the average fluid velocity) and the pipe diameter to the main function.
 */

#endif /* TurVelProVar_h */

#ifndef TurVelProCalc_h
#define TurVelProCalc_h

double TurVelProCalc(double vmax, double r, double d, double *gen);
/*  This subroutine is used to determine the point velocity by utilising the relationship between the point velocity and maximum velocity given by Prandtl's one-seventh law. In addition to required inputs, this subroutine utilises several additional variables:
 - bot = absolute fixed pipe radius.
 - y = distance from the pipe wall (Typically determined from the pipe centreline).
 - gen = v/v_max ratio.
 - v_x = point velocity.
 This function returns the value of v_x to the calling function (within this file, "TurVelProfCalc(...)"). This function has no other external dependencies.
 */

#endif /* TurVelProCalc_h */

#ifndef TurVelProfCalc_h
#define TurVelProfCalc_h

void TurVelProfCalc(double vmax, double d);
/*  This subroutine is used to generate the data for the velocity profile for a turbulent fluid that obeys Prandtl's one-seventh law. In addition to the required inputs, this subroutine utilises the following local variables:
 - display = A character array containing the input for whether the user would like to display the generated on screen.
 - interval = A variable used to set the resolution of the generated velocity profile.
 - prad = Fixed pipe radius.
 - whildisp = An integer variable used to control the while loop controlling whether the generated data is displayed within the console.
 - rows = An integer variable calculated prior to declaring the 2D array that will contain the generated data set.
 - profile = A 2D doubles array containing the generated turbulent flow velocity profile according to Pradntl's one-seventh law.
 - r = The point radius where the point velocity is being calculated for.
 This function does not return the generated array back outside the function. This is possible but the there would be limited to a set size since variables are not dynamic within C. This subroutine has no external dependencies.
 */

#endif /* TurVelProfCalc_h */

#ifndef TurVelPro_h
#define TurVelPro_h

void TurVelPro(void);


#endif /* TurVelPro_h */
