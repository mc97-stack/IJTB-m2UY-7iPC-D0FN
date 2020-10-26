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
/// @param A_F Flow area (mm2).
/// @param P_W Wetted perimeter (cm).
void HydrDiamVariable(double *A_F, double *P_W);

#endif /* HydrDiamVar_h */

#ifndef HydrDiamCalc_h
#define HydrDiamCalc_h

/// This subroutine is used to calculate the hydraulic diameter of a non-cylindrical pipe.
/// @param A_F Flow area (m2).
/// @param P_W Wetted perimeter (m).
double HydrDiamCalculation(double A_F, double P_W);

#endif /* HydrDiamCalc_h */

#ifndef HydrDiamDisp_h
#define HydrDiamDisp_h

/// This subroutine is used to display the collected data and the calculated hydraulic diameter to the user console.
/// @param A_F Cross-sectional flow area (m2).
/// @param P_W Wetted perimeter (m).
/// @param d_H Hydraulic diameter (m).
void HydrDiamDisplay(double A_F, double P_W, double d_H);

#endif /* HydrDiamDisp_h */

#ifndef HydrDiamWrite_h
#define HydrDiamWrite_h

/// This subroutine is used to write the collected data and the calculated hydraulic diameter to a .txt file
/// @param A_F Cross-sectional flow area (m2).
/// @param P_W Wetted perimeter (m).
/// @param d_H Hydraulic diameter (m).
void HydrDiamWrite(double A_F, double P_W, double d_H);

/// Subroutine to ask the user if they would like to save the results of this program to a file.
/// @param A_F Cross-sectional flow area (m2).
/// @param P_W Wetted perimeter (m).
/// @param d_H Hydraulic diameter (m).
void HydrDiamWriteCheck(double A_F, double P_W, double d_H);

#endif /* HydrDiamWrite_h */
