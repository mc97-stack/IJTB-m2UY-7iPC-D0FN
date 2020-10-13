//
//  03dbthreeK.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef threeKcalc_h
#define threeKcalc_h

/// This subroutine is used calculate the K-value used to calculate the head loss in the main function
/// @param K1 K_1 ([ ])
/// @param Kinf K_{infty} ([ ])
/// @param Kd K_d (inches OR mm)
/// @param Re Reynold's number ([ ])
/// @param NPS Nominal Pipe Schedule
double threeKcalc(double K1, double Kinf, double Kd, double Re, double NPS);

#endif /* _3dbthreeK_h */

#ifndef threeK_h
#define threeK_h

/// This subroutine is used to calculate the overall head loss incurred by a fluid travelling through large diameter pipes. 
/// 
///1) The array to contain the 3K database, input values and calculation steps is declared with 34 rows and 9 columns.\n
///
///2) Data is entered into the array.
///   Column 0 = k_1 values
///   Column 1 = k_inf values
///   Column 2 = k_d values (inches)
///   Column 3 = k_d values (mm)
///
///3) The program asks for user input and inputs the collected integer values into Column 4.
///
///4) The program collects the Reynolds number, Nominal Pipe Size and average fluid velocity.
///
///5) The program begins calculating the head loss for each fitting before multiplying by the count.
///   Column 5 = K-value by fitting
///   Column 6 = Fitting head loss
///   Column 7 = Total group head loss
///   Column 8 = Cumulative head loss
///
///6) The program then asks if the user would like to see the final calculation sheet. If affirmative, a for loop is run to display the collected data on the console
void threeK(void);

#endif /* threeK_h */
