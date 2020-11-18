//
//  04bCoefficientofPerformance.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 31/10/2020.
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

#ifndef _4bCoefficientofPerformanceVariable_h
#define _4bCoefficientofPerformanceVariable_h

/// This subroutine is used to collect the data required to calculate the Coefficient of Performance for either a refrigerator or a heat pump.
/// @param method This variable is used to control what variables this subroutine collects. Although there are alot of shared variables between the two methods, this variable can take the value of either '1' or '2'. This is representative of the fridge or heat pump respectively.
/// @param wnet Specific net work done on/by the process (kJ/kg).
/// @param qhot Specific heat supplied to the hot reservoir (kJ/kg).
/// @param qcold Specific heat received from the cold reservoir (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
void CoPVariable(int method, double *wnet, double *qhot, double *qcold, double *THot, double *TCold);

#endif /* _4bCoefficientofPerformanceVariable_h */

#ifndef _4bCoefficientofPerformanceCalculation_h
#define _4bCoefficientofPerformanceCalculation_h

/// This subroutine is used to calculate the coefficient of performance for a refrigerator.
/// @param qcold Specific heat received from the cold reservoir (kJ/kg).
/// @param wnet Specific net work done on/by the process (kJ/kg).
double CoPFridge(double qcold, double wnet);

/// This subroutine is used to calculate the coefficient of performance for a heat pump.
/// @param qhot Specific heat supplied to the hot reservoir (kJ/kg).
/// @param wnet Specific net work done on/by the process (kJ/kg).
double CoPHeatPump(double qhot, double wnet);

/// This subroutine is used to calculate the reversible coefficient of performance for a refrigerator.
/// @param TCold Cold reservoir temperature (K).
/// @param THot Hot reservoir temperature (K).
double CoPRevFridge(double TCold, double THot);

/// This subroutine is used to calculate the reversible coefficient of performance for a heat pump.
/// @param TCold Cold reservoir temperature (K).
/// @param THot Hot reservoir temperature (K).
double CoPRevHeatPump(double TCold, double THot);

/// This subroutine is used to calculate the thermal efficiency of a refrigerator.
/// @param CoP Coefficient of Performance for a refrigerator.
double etaFridge(double CoP);

/// This subroutine is used to calculate the thermal efficiency of a heat pump.
/// @param CoP Coefficient of Performance for a heat pump.
double etaHeatPump(double CoP);

#endif /* _4bCoefficientofPerformanceCalculation_h */

#ifndef _4bCoefficientofPerformanceDisplay_h
#define _4bCoefficientofPerformanceDisplay_h

/// This subroutine is used to display the inputted parameters and calculated values on the user console.
/// @param method This variable is used to control the display ouput behaviour. This variable can take the value of either '1' or '2', which is 'representative of the fridge or heat pump respectively.
/// @param wnet Specific net work done on/by the process (kJ/kg).
/// @param qhot Specific heat supplied to the hot reservoir (kJ/kg).
/// @param qcold Specific heat received from the cold reservoir (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
/// @param CoP Coefficient of Performance for either a refrigerator or a heat pump.
/// @param CoPRev Reversible Coefficient of Performance for either a refrigerator or a heat pump.
/// @param eta Thermal efficiency of either a refrigerator or a heat pump.
/// @param etac Reversible thermal efficiency of either a refrigerator or a heat pump.
void CoPDisplay(int method, double wnet, double qhot, double qcold, double THot, double TCold, double CoP, double CoPRev, double eta, double etac);

#endif /* _4bCoefficientofPerformanceDisplay_h */

#ifndef _4bCoefficientofPerformanceWrite_h
#define _4bCoefficientofPerformanceWrite_h

/// This subroutine is used to write the inputted parameters and calculated values to a .txt file.
/// @param method This variable is used to control the write ouput behaviour. This variable can take the value of either '1' or '2', which is 'representative of the fridge or heat pump respectively.
/// @param wnet Specific net work done on/by the process (kJ/kg).
/// @param qhot Specific heat supplied to the hot reservoir (kJ/kg).
/// @param qcold Specific heat received from the cold reservoir (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
/// @param CoP Coefficient of Performance for either a refrigerator or a heat pump.
/// @param CoPRev Reversible Coefficient of Performance for either a refrigerator or a heat pump.
/// @param eta Thermal efficiency of either a refrigerator or a heat pump.
/// @param etac Reversible thermal efficiency of either a refrigerator or a heat pump.
void CoPWrite(int method, double wnet, double qhot, double qcold, double THot, double TCold, double CoP, double CoPRev, double eta, double etac);

/// This subroutine is used to ask the user whether they would like to write the subroutine data to a .txt file.
/// @param method This variable is used to control the write ouput behaviour. This variable can take the value of either '1' or '2', which is 'representative of the fridge or heat pump respectively.
/// @param wnet Specific net work done on/by the process (kJ/kg).
/// @param qhot Specific heat supplied to the hot reservoir (kJ/kg).
/// @param qcold Specific heat received from the cold reservoir (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
/// @param CoP Coefficient of Performance for either a refrigerator or a heat pump.
/// @param CoPRev Reversible Coefficient of Performance for either a refrigerator or a heat pump.
/// @param eta Thermal efficiency of either a refrigerator or a heat pump.
/// @param etac Reversible thermal efficiency of either a refrigerator or a heat pump.
void CoPWriteSwitch(int method, double wnet, double qhot, double qcold, double THot, double TCold, double CoP, double CoPRev, double eta, double etac);

#endif /* _4bCoefficientofPerformanceWrite_h */
