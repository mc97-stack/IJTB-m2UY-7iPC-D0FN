//
//  02g2TurVelPro.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 21/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef TurVelProVar_h
#define TurVelProVar_h

/// This subroutine is used for the data collection of the turbulent flow velocity profile using Prandtl's one-seventh law.
/// @param umax Maximum point fluid velocity (m/ s). This value is inferred from the average fluid velocity.
/// @param d Pipe diameter (mm)
void TurVelProVar(double *umax, double *d);

#endif /* TurVelProVar_h */

#ifndef TurVelProCalc_h
#define TurVelProCalc_h

/// This subroutine is used to determine the point velocity by utilising the relationship between the point velocity and maximum velocity given by Prandtl's one-seventh law.
/// @param vmax Maximum point fluid velocity (m/ s).
/// @param r Pipe point radius (m).
/// @param d Fixed pipe diameter (m).
/// @param gen v/v_{max}. N.B. This value is generated alongside the calculation
double TurVelProCalc(double vmax, double r, double d, double *gen);

#endif /* TurVelProCalc_h */

#ifndef TurVelProfCalc_h
#define TurVelProfCalc_h

typedef struct TurVelProfile{
    double r[5000]; //  Point radius
    double v_x[5000]; //  Point velocity
    double ratio[5000]; //  Velocity ratio
} TurVelProf;

/// This subroutine is used to generate the data for the velocity profile for a turbulent fluid that obeys Prandtl's one-seventh law. This subroutine does not return the generated array to the calling function.
/// @param vmax Maximum fluid velocity (m/ s).
/// @param d Fixed pipe diameter (m).
TurVelProf TurVelProfCalc(double vmax, double d, int *rows);

#endif /* TurVelProfCalc_h */

#ifndef TurVelPro_h
#define TurVelPro_h

/// This pseudomain subroutine is used to control the behaviour of the above listed functions.
void TurVelPro(void);

#endif /* TurVelPro_h */
