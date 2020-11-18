//
//  04aThermalEfficiency.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/10/2020.
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

#ifndef _4aThermalEfficiencyVariable_h
#define _4aThermalEfficiencyVariable_h

/// This subroutine is used to collect the data required for calculating the thermal efficiency of a thermodynamic cycle and comparing it to its equivalent Carnot cycle.
/// @param method This variable is used to control what variables are collected to calculate the thermal efficiency of the intended real process. (1) = Calculates the thermal efficiency from the net work and supplied heat. (2) = Calculates the thermal efficiency from the heat supplied to and sent to the cold reservoir from the cycle.
/// @param wnet Specific net work (kJ/kg).
/// @param qhot Specific heat supplied to the cycle from the hot reservoir (kJ/kg).
/// @param qcold Specific heat sent to the cold reservoir from the cycle (kJ/kg).
/// @param Thot Hot reservoir temperature (K).
/// @param Tcold Cold reservoir temperature (K).
void ThermEffVariable(int method, double *wnet, double *qhot, double *qcold, double *Thot, double *Tcold);

#endif /* _4aThermalEfficiencyVariable_h */

#ifndef _4aThermalEfficiencyCalculation_h
#define _4aThermalEfficiencyCalculation_h

/// This subroutine is used to calculate the thermal efficiency of a process from the net work and heat supplied to the cycle.
/// @param wnet Specific net work (kJ/kg).
/// @param qhot Specific heat supplied (kJ/kg)
double ThermEffCalc1(double wnet, double qhot);

/// This subroutine is used to calculate the thermal efficiency of a process from the heat supplied and dumped to/from the cycle.
/// @param qhot Specific heat supplied to the cycle (kJ/kg)
/// @param qcold Specific heat dumped to the cold reservoir (kJ/kg)
double ThermEffCalc2(double qhot, double qcold);

/// This subroutine is used to calculate the thermal efficiency of a process using the thermal reservoir temperatures. In practice, this equation assumes reversibilities in the process and so can only be applied to the process' equivalent Carnot cycle.
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K)
double ThermEffCarnotCalculation(double THot, double TCold);

#endif /* _4aThermalEfficiencyCalculation_h */

#ifndef _4aThermalEfficiencyDisplay_h
#define _4aThermalEfficiencyDisplay_h

/// This subroutine is used to display the inputted parameters and the calculated values on the user console.
/// @param method This variable is used to control what variables are displayed on the subroutine output. (1) = Displays the variable related to the thermal efficiency from the net work and supplied heat. (2) = Displays the variable related to the thermal efficiency from the heat supplied to and sent to the cold reservoir from the cycle.
/// @param wnet Specific net work (kJ/kg).
/// @param qhot Specific heat supplied to the cycle from the hot reservoir (kJ/kg).
/// @param qcold Specific heat sent to the cold reservoir from the cycle (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
/// @param eta Thermal efficiency (%).
/// @param etac Thermal efficiency of equivalent Carnot cycle (%).
void ThermEffDisplay(int method, double wnet, double qhot, double qcold, double THot, double TCold, double eta, double etac);

#endif /* _4aThermalEfficiencyDisplay_h */

#ifndef _4aThermalEfficiencyWrite_h
#define _4aThermalEfficiencyWrite_h

/// This subroutine is used to write the inputted parameters and the calculated values to a .txt file.
/// @param method This variable is used to control what variables are displayed on the subroutine output. (1) = Displays the variable related to the thermal efficiency from the net work and supplied heat. (2) = Displays the variable related to the thermal efficiency from the heat supplied to and sent to the cold reservoir from the cycle.
/// @param wnet Specific net work (kJ/kg).
/// @param qhot Specific heat supplied to the cycle from the hot reservoir (kJ/kg).
/// @param qcold Specific heat sent to the cold reservoir from the cycle (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
/// @param eta Thermal efficiency (%).
/// @param etac Thermal efficiency of equivalent Carnot cycle (%).
void ThermEffWrite(int method, double wnet, double qhot, double qcold, double THot, double TCold, double eta, double etac);

/// This subroutine is used to ask the user whether they would like to output the inputted parameters and the calculated values to a .txt file.
/// @param method This variable is used to control what variables are displayed on the subroutine output. (1) = Displays the variable related to the thermal efficiency from the net work and supplied heat. (2) = Displays the variable related to the thermal efficiency from the heat supplied to and sent to the cold reservoir from the cycle.
/// @param wnet Specific net work (kJ/kg).
/// @param qhot Specific heat supplied to the cycle from the hot reservoir (kJ/kg).
/// @param qcold Specific heat sent to the cold reservoir from the cycle (kJ/kg).
/// @param THot Hot reservoir temperature (K).
/// @param TCold Cold reservoir temperature (K).
/// @param eta Thermal efficiency (%).
/// @param etac Thermal efficiency of equivalent Carnot cycle (%).
void ThermEffWriteSwitch(int method, double wnet, double qhot, double qcold, double THot, double TCold, double eta, double etac);

#endif /* _4aThermalEfficiencyWrite_h */
