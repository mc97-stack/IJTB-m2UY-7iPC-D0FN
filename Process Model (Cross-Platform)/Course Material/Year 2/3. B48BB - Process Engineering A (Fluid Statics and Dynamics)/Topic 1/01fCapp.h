//
//  01fCapp.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/* 
 h = Capillary rise (m)
 Pc = Capillary pressure (Pa)
 sigma = Surface tension (N/m)
 cang = Contact angle (rad)
 rho = Fluid density (kg/m3)
 d = Tube diameter (m)
 */

#ifndef CappVar_h
#define CappVar_h

void CappVar(double *sigma, double *cang, double *rho, double *d);
/*  This subroutine is used to collect data for the calculation of cappillary rise ("CappCalch") and pressure ("CappCalcP"). Where:
 sigma = Surface tension (N/m)
 cang = Contact angle (deg)
- This value is converted to radians prior to being returned to the main function ("Capp").
 rho = Fluid density (kg/m3)
 d = Cappillary tube diameter (mm)
- This value is converted to m before being returned to the main function ("Capp")
 This function returns back the value of all variables inputted to the main function. This function has a co-dependency on "01dSurfTen.c" to produce dialogue concerning fluid wetting properties.
 */

#endif /* _1fCapp_h */

#ifndef CappCalch_h
#define CappCalch_h

double CappCalch(double sigma, double cang, double rho, double d);
/*  This subroutine is used to calculate the capillary rise given:
 - Surface tension (sigma) (N/m)
 - Contact angle (cang) (rad)
 - Fluid density (rho) (kg/m3)
 - Capillary tube diameter (d) (m)
 This subroutine then returns the capillary rise (h)(m) back to the main function ("Capp(...)"). This function is used in "SurfTens(void)" in "01dSurfTens.c".
 */

#endif /* CappCalch_h */

#ifndef CappCalcP_h

double CappCalcP(double sigma, double cang, double d);
/*  This subroutine is used to calculate the capillary pressure given:
 - Surface tension (sigma) (N/m)
 - Contact angle (cang) (rad)
 - Capillary tube diameter (d) (m)
 This subroutine then returns the Capillary pressure (Pc)(Pa) back to the main function ("Capp(...)"). This function is used in "SurfTens(void)" in "01dSurfTens.c".
 */

#endif /* CappCalcP_h */
