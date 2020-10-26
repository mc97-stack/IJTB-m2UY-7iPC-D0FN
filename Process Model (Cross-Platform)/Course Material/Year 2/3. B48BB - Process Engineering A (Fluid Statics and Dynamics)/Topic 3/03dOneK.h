//
//  03daoneK.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef OneKStruct
#define OneKStruct

typedef struct OneKFittings{
    double data[15];
    int count[15];
    double headloss[15];
} OneKFittings;

#endif /* OneKStruct */

#ifndef OneKData_h
#define OneKData_h

/// This subroutine is used to input K-values into the table being used by the "OneK(void)"
/// @param input Table where data values should be inputted.
OneKFittings OneKData(OneKFittings input);

#endif /* OneKData_h */

#ifndef OneKVar_h
#define OneKVar_h

/// This subroutine is used to collect the fluid veloicty and counts for each fitting available.
/// @param table Table where fitting counts should be inputted.
/// @param u Fluid velocity (m/s)
OneKFittings OneKVariable(OneKFittings table, double *u);

#endif /* OneKVar */

#ifndef OneKCalc_h
#define OneKCalc_h

/// This subroutine is used to calculate the head loss associated with one fitting. The following variables are required by this subroutine. The subroutine returns the total head loss for the singular fitting, multiplied by the count.
/// @param count Number of occurences of the fitting being calculated.
/// @param data Fitting k-value. This is numbered from 0 - 14 in the order that the counts were asked for in "OneK(void)".
/// @param u Fluid Velocity (m/ s).
double OneKCalculate(int count, double data, double u);

/// This subroutine is used to perform the calculations required for the excess head/ 1K method of pressure losses through pipe fittings
/// @param data Table containing counts and k-values
/// @param u Fluid velocity (m/s)
OneKFittings OneKFinalTable(OneKFittings data, double u);

#endif /* OneKCalc_h */

#ifndef OneKFinalTable_h
#define OneKFinalTable_h

/// This subroutine is used to perform the calculations required for the excess head/ 1K method of pressure losses through pipe fittings
/// @param data Table containing counts and k-values
/// @param u Fluid velocity (m/s)
OneKFittings OneKFinalTable(OneKFittings data, double u);

#endif /* OneKFinalTable_h */

#ifndef OneKDisplay_h
#define OneKDisplay_h

/// This subroutine is used to display the collected data and calculated table on the console.
/// @param table Table containing counts, k-values and calculated head losses
/// @param u Fluid velocity (m/s).
/// @param total Total head losses presented in the table (m).
void OneKDisplay(OneKFittings table, double u, double total);

#endif /* OneKDisplay_h */

#ifndef OneKWrite_h
#define OneKWrite_h

/// This subroutine is used to write the collected data and calculated table to a .txt file.
/// @param table Table containing counts, k-values and calculated head losses
/// @param u Fluid velocity (m/s).
/// @param total Total head losses presented in the table (m).
void OneKWrite(OneKFittings table, double u, double total);

/// This subroutine is used to check whether the user would like to write the generated results to a .txt file..
/// @param table Table containing counts, k-values and calculated head losses
/// @param u Fluid velocity (m/s).
/// @param total Total head losses presented in the table (m).
void OneKWriteSwitch(OneKFittings table, double u, double total);

#endif /* OneKWrite_h */

#ifndef OneK_h
#define OneK_h

/// This subroutine is the pseudomain subroutine used to calculate the head loss associated with standard pipe fittings with the 1K method (Also known as the Excess head method).
void OneK(void);

#endif /* _OneK_h */
