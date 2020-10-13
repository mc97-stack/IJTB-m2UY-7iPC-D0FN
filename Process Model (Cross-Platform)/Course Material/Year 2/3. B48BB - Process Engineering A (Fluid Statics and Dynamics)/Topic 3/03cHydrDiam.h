//
//  03cHydrDiam.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef HydrDiamVar_h
#define HydrDiamVar_h

/// This subroutine is used for collecting the data required to calculate the hydraulic diameter of a non-cylindrical pipe.
/// @param A_F Flow area (mm2)
/// @param P_W Wetted perimeter (cm)
void HydrDiamVar(double *A_F, double *P_W);

#endif /* HydrDiamVar_h */

#ifndef HydrDiamCalc_h
#define HydrDiamCalc_h

/// This subroutine is used to calculate the hydraulic diameter of a non-cylindrical pipe.
/// @param A_F Flow area (m2)
/// @param P_W Wetted perimeter (m)
double HydrDiamCalc(double A_F, double P_W);

#endif /* HydrDiamCalc_h */
