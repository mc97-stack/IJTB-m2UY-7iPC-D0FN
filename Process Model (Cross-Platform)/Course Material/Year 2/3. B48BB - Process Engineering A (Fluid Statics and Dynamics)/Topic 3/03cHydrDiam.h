//
//  03cHydrDiam.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Global variables
/* 
 A_F = Cross-sectional flow area (input)
 P_W = Wetted perimeter (input)
 d_H = Hydraulic diameter (output)
 */

#ifndef HydrDiamVar_h
#define HydrDiamVar_h

void HydrDiamVar(double *A_F, double *P_W);
/*  This subroutine is used for collecting the data required to calculate the hydraulic diameter of a non-cylindrical pipe. It uses the following variables in addition to the input variables stated above:
 input = A character array used to receive input from the user
 convfactor = A double variable used to hold the conversion factor between mm2 and m2.
 This subroutine converts the units used into SI units prior to returning to the calling function. This subroutine is not used elsewhere outside of this file. 
 */

#endif /* HydrDiamVar_h */

#ifndef HydrDiamCalc_h
#define HydrDiamCalc_h

double HydrDiamCalc(double A_F, double P_W);
/*  This subroutine is used to calculate the hydraulic diameter of a non-cylindrical pipe. It returns the hydraulic diameter back to the calling function and is not used outside of this file.
 */

#endif /* HydrDiamCalc_h */
