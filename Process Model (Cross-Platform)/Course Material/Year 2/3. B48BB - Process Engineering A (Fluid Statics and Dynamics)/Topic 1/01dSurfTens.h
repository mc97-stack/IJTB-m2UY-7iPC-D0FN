//
//  01dSurfTens.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 13/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/*  
 sigma = Surface tension
 F = Force to break fluid surface (N)
 L = Circumference of ring used
 C_F = Correction factor
 cang = Contact angle in radians
 */

#ifndef wettfacts_h
#define wettfacts_h

void wettfacts(double cang);
/*  This subroutine is used to provide dialogue on fluid characteristics based upon the contact angle of a fluid (in degrees) with a solid, horizontal surface. The subroutine utilises the contact angle alone to provide these facts. This subroutine only returns dialogue to the active program window. This subroutine is used in "CappVar(...)" in "01fCapp.c".*/

#endif /* wettfacts_h */

#ifndef duNouyVar_h
#define duNouyVar_h

void duNouyVar(double *F, double *L, double *C_F, double *cang);
/*  This subroutine is used to for data collection for calculating the surface tension using the du Nouy ring method. Where:
 F = Force to break the fluid surface (N)
 r = Radius of ring (cm)
- This is a local variable that is not passed outside this subroutine 
- After collection, the value is converted to metres before being utilised to calculate the circumference of the ring (L).
 C_F = Correction factor for the correlation. 
 cang = Contact angle with the ring breaking the liquid-vapour interface. 
 This subroutine returns the values stated above in the declaration to the main function in this file ("SurfTens"). This subroutine has a codependency on the subroutine "wettfacts" to provide information on the fluid properties after the contact angle with the ring has been inputted. 
 */

#endif /* duNouyVar_h */

#ifndef duNouyCalc_h
#define duNouyCalc_h

double duNouyCalc(double F, double L, double C_F, double cang);
/*  This subroutine is used to calculate the surface tension (sigma) in N/m given the:
 - Force (F) (N) required to break the fluid surface
 - Ring circumference (L) (m)
 - Contact angle with the ring (rad)
 - Correction factor (C_F)
 The subroutine then returns the surface tension back to the main function ("SurfTens").
 */

#endif /* duNouyCalc_h */
