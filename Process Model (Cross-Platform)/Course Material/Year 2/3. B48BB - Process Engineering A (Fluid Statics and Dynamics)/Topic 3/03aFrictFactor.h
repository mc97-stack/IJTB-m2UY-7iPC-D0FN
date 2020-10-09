//
//  03aFrictFactor.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef Laminar_h
#define Laminar_h

double Laminar(double rho, double u, double d, double mu);
/*  This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with laminar flow profile. This subroutine requires the following header files to function:
 - 02dReyNo.h
 */

#endif /* Laminar_h */

#ifndef Turbulent1_h
#define Turbulent1_h

double Turbulent1(double rho, double u, double d, double mu);
/*  This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile. This equation is valid between 2500 < Re < 100,000. This subroutine requires the following header files to function:
 - 02dReyNo.h
 - math.h
 */

#endif /* Turbulent1_h */

#ifndef Turbulent2_h
#define Turbulent2_h

double Turbulent2(double rho, double u, double d, double mu);
/*  This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile through a brute force iteration scheme. This equation is valid when Re > 2500. This subroutine requires the following header files to function:
 - 02dReyNo.h
 - math.h
 This subroutine then returns the friction factor with 2 additional error digits to the calling function.
 */

#endif /* Turbulent2_h */

#ifndef Turbulent3_h
#define Turbulent3_h

double Turbulent3(double rho, double u, double d, double mu, double vareps);
/*  This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile through a brute force iteration scheme. This equation is valid when Re > 3000 and the friction factor is dependent on relative roughness. This subroutine requires the following header files to function:
 - 02dReyNo.h
 - math.h
 This subroutine then returns the friction factor with 2 additional error digits to the calling function.
 */

#endif /* Turbulent3_h */

#ifndef Turbulent4_h
#define Turbulent4_h

double Turbulent4(double d, double vareps);
/*  This subroutine is used to calculate the friction factor associated with the pressure loss of a fluid with a turbulent flow profile. This equation is valid when Re > 3000 and the Friction Factor is independent of surface roughness. This subroutine requires the following header files to function:
 - math.h
 */

#endif /* Turbulent4_h */
