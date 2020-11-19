//
//  03dbthreeK.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef ThreeKStruct
#define ThreeKStruct

typedef struct ThreeKFittings{
    int k1[34];
    double kinf[34];
    double Impkd[34];
    double Metkd[34];
    int count[34];
    double headloss[34];
    double dP_f[34];
}ThreeKFittings;

#endif /* ThreeKStruct */

#ifndef ThreeKData_h
#define ThreeKData_h

/// This subroutine is used to load the 3K database into the struct stated above.
/// @param input Struct where constants should be entered.
ThreeKFittings ThreeKData(ThreeKFittings input);

/// This subroutine is used to collect the variables required to run the calculations.
/// @param table Struct where model constants and counts should be entered.
/// @param DN Diameter Nominal (mm)
/// @param rho Fluid density (kg/ m3) - For Reynolds number.
/// @param u Fluid velocity (m/ s) - For Reynolds number and 3K.
/// @param d Internal pipe diameter (mm) - For Reynolds number.
/// @param mu Fluid viscosity (cP) - For Reynolds number.
ThreeKFittings ThreeKVariable(ThreeKFittings table, double *DN, double *rho, double *u, double *d, double *mu);

#endif /* ThreeKData_h */

#ifndef ThreeKCalc_h
#define ThreeKCalc_h

/// This subroutine is used to calculate the Resistant Coefficient.
/// @param Re Reynolds number
/// @param DN Diameter nominal (mm)
/// @param k1 k_1 value from database
/// @param kinf k_inf value from database
/// @param kd k_d value from database (mm^0.3)
double ThreeKCalculateK(double Re, double DN, int k1, double kinf, double kd);

/// This subroutine is used to calculate the head loss associated with a singular fitting. This calculated value is then multiplied by the count.
/// @param count Number of fittings
/// @param K Resistant Coefficient from "ThreeKCalcK(...)"
/// @param u Fluid velocity (m/ s)
double ThreeKCalculateHead(double count, double K, double u);

/// This subroutine is used to calculate the pressure loss associated with the head loss attributed to a single fitting.
/// @param h Head loss calculated from "ThreeKCalculateHead(...)".
/// @param rho Fluid density (kg/m3)
double ThreeKCalculatePLoss(double h, double rho);

/// This subroutine is used to amalgamate the data into a single variable.
/// @param data Struct where data was previously entered.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa. s)
/// @param DN Diameter Nominal
/// @param Re Reynolds number ([ ])
ThreeKFittings ThreeKFinalTable(ThreeKFittings data, double rho, double u, double d, double mu, double DN, double *Re);

#endif /* ThreeKCalc_h */

#ifndef ThreeKDisplay_h
#define ThreeKDisplay_h

/// This subroutine is used to display the contents of the generated data table in addition to all inputted variables.
/// @param data Generated data table.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Re Reynold's number
/// @param DN Diameter Nominal (mm)
/// @param TotalH Total head loss (m)
/// @param TotalP Total pressure loss (Pa)
void ThreeKDisplay(ThreeKFittings data, double rho, double u, double d, double mu, double Re, double DN, double TotalH, double TotalP);

#endif /* ThreeKDisplay_h */

#ifndef ThreeKWrite_h
#define ThreeKWrite_h

/// This subroutine is used to write the collected data and generated dataset to a .txt file.
/// @param data Generated data table.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Re Reynold's number
/// @param DN Diameter Nominal (mm)
/// @param TotalH Total head loss (m)
/// @param TotalP Total pressure loss (Pa)
void ThreeKWrite(ThreeKFittings data, double rho, double u, double d, double mu, double Re, double DN, double TotalH, double TotalP);

/// This subroutine is used to check if the user would like to write the generated dataset and collected parameters to a file.
/// @param data Generated data table.
/// @param rho Fluid density (kg/m3)
/// @param u Fluid velocity (m/s)
/// @param d Internal pipe diameter (m)
/// @param mu Fluid viscosity (Pa.s)
/// @param Re Reynold's number
/// @param DN Diameter Nominal (mm)
/// @param TotalH Total head loss (m)
/// @param TotalP Total pressure loss (Pa)
void ThreeKWriteSwitch(ThreeKFittings data, double rho, double u, double d, double mu, double Re, double DN, double TotalH, double TotalP);

#endif /* ThreeKWrite_h */

#ifndef ThreeK_h
#define ThreeK_h

/// This subroutine is used to guide the user through collecting the necessary data and calculating and displaying head losses associated with the 3K method.
void ThreeK(void);

#endif /* ThreeK_h */
