//
//  01cMano.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef ManoMeasVar_h
#define ManoMeasVar_h

void ManoMeasVar(double *P2, double *rho1, double *h1, double *rho2, double *h2);
/*  This subroutine is used for data collection for measuring the process fluid pressure where:
 P2 = Atmospheric/ Environmental pressure
 rho1 = Density of the process fluid
 h1 = Height of process fluid in the manometer arm
 rho2 = Density of the manometer fluid
 h2 = Height of the manometer fluid in the manometer arm
 
 // The following variables are used by the function but are not returned as a function output.
 L = Length of the inclined manometer arm
 incl = Degree of inclination of the manometer arm. The function should receive an input in degrees and then converts the value through to radians prior to using the sine trigonmetric identity to determine the absolute vertical rise of the manometer fluid.
 
 input = Character input variable
 abspres = Choice variable for setting P2 to 101.325 kPa
 inclcon = Choice variable for whether manometer is inclined
 
 PresCheck = Check integer variable for controlling the while loop dedicated to declaring whether standard atmospheric pressure should be used as the reference pressure
 InclCheck = Check integer variable for controlling the while loop dedicated to declaring whether the manometer in use is inclined or not
 */

#endif /* ManoMeasVar_h */

#ifndef ManoEstiVar_h
#define ManoEstiVar_h

void ManoEstiVar(double *P1, double *P2, double *rho1, double *rho2, double *h1);
/*  This subroutine is used for data collection for estimating the rise of manometer fluid where:
 P1 = Pressure of the process fluid
    Conversion through to Pascals after an input is made in kPa
 P2 = Environmental pressure
    A check is made if 0 kPa is inputted which will default the P2 value to 101.325 kPa. A conversion through to Pascals after an input is made in kPa. 
 rho1 = Density of the process fluid
 rho2 = Density of the manometer fluid
 h1 = Height of the process fluid in the manometer arm
    Conversion through to m is made after an input is made in cm.
 
 // The following variables are used by the function but are not returned as a function output.
 input = Character input variable
 abspres = Switch variable for setting P2 to 101.325 kPa or not
 PresCheck = Loop variable for controlling the input required (or not) for the variable 'P2'.
 */

#endif /* ManoEstiVar_h */

#ifndef ManoMeasCal_h
#define ManoMeasCal_h

double ManoMeasCal(double P2, double rho1, double h1, double rho2, double h2);
/* Subroutine used for calculating the process fluid pressure using the inputted values from "ManoMeasVar(...)". An additional calculation variable ("brack") is required to ensure that the correct order of operations is performed. The function returns the value of process fluid pressure (P1). This subroutine is not used elsewhere in this program */

#endif /* ManoMeasCal_h */

#ifndef ManoEstiCal_h
#define ManoEstiCal_h

double ManoEstiCal(double P1, double P2, double rho1, double h1, double rho2);
/* Subroutine used for estimating the height of some manometer fluid given some process fluid pressure in an attached pipe, density values and height of the process fluid in the manometer arm. Additional calculation variables are required to ensure that the correct order of operations is performed. These are:
 dP = Negative pressure difference between the environment and pressure at the appended pipe section
 top = Numerator (rho1*g*h1+(P1 - P2))
 bot = Denominator (rho2*g)
 
 h2 = Height of manometer fluid in the manometer arm (The value of this variable is returned by the function)
 
 InclCheck = Variable used to control the while loop that checks if the manometer is inclined prior to returning an onscreen value for the height of the manometer fluid.
 
 As stated in the variable declarations, the value of "h2" is returned to the parent subroutine. This subroutine is not used elsewhere in this program.
 */

#endif /* ManoEstiCal_h */
