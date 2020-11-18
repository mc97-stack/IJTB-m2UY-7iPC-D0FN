//
//  02AcentricFactor.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/11/2020.
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

#ifndef _2AcentricFactorVariable_h
#define _2AcentricFactorVariable_h

/// This subroutine is used to collect the data required to calculate the acentric factor through either the Antoine equation ~~or the Lee-Kesler vapour pressure relations~~.
/// @param mode This variable is used to control which variables are collected given the method. (1) = Collects parameters for the Antoine equation definition. (2) = Collects critical properties and normal boiling point. (3) = Collects critical properties and normal boiling point. (4) = Collects all variables.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param TBoil Normal boiling point (deg C).
/// @param ANTA Antoine equation constant A (mmHg).
/// @param ANTB Antoine equation constant B (K. mmHg).
/// @param ANTC Antoine equation constant C (K).
void AcFactorVariable(int mode, double *Pc, double *Tc, double *TBoil, double *ANTA, double *ANTB, double *ANTC);

#endif /* _2AcentricFactorVariable_h */

#ifndef _2AcentricFactorCalculation_h
#define _2AcentricFactorCalculation_h

/// This subroutine is used to calculate the vapour pressure with the Antoine equation in mmHg.
/// @param ANTA Antoine equation constant A (mmHg).
/// @param ANTB Antoine equation constant B (K. mmHg).
/// @param ANTC Antoine equation constant C (K).
/// @param T Temperature (K)
double AntoineEquation(double ANTA, double ANTB, double ANTC, double T);

/// This subroutine is used to calculate the acentric factor through the Antoine equation in mmHg.
/// @param ANTA Antoine equation constant A (mmHg).
/// @param ANTB Antoine equation constant B (K. mmHg).
/// @param ANTC Antoine equation constant C (K).
/// @param Tc Critical temperature (K).
/// @param Pc Critical pressure (bar).
double AcFactorPHatCalculation(double ANTA, double ANTB, double ANTC, double Tc, double Pc);

/// This subroutine is used to calculate the acentric factor using the critical pressure and temperature and the normal boiling point.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param TBoil Normal boiling point (K).
double AcFactorCritCalc(double Pc, double Tc, double TBoil);

/// This subroutine is used to calculate the acentric factor through the Lee-Kesler vapour pressure relations.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param TBoil Normal boiling point (K).
double AcFactorLKCalc(double Pc, double Tc, double TBoil);

#endif /* _2AcentricFactorCalculation_h */

#ifndef _2AcentricFactorDisplay_h
#define _2AcentricFactorDisplay_h

/// This subroutine is used to display the inputted parameters and calculated acentric factor on the user console.
/// @param mode This variable is used to control which variables get written to the .txt file. (1) = Collects parameters for the Antoine equation definition. (2) = Collects critical properties and normal boiling point. (3) = Collects critical properties and normal boiling point. (4) = Collects all variables.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param ANTA Antoine equation constant A (mmHg).
/// @param ANTB Antoine equation constant B (K. mmHg).
/// @param ANTC Antoine equation constant C (K).
/// @param omegaANT Acentric factor calculated with the Antoine equation ([ ]).
/// @param omegaCRI Acentric factor calculated with critical properties and the normal boiling point ([ ]).
/// @param omegaLK Acentric factor calculated with the Lee-Kesler vapour pressure relations ([ ])
void AcFactorDisplay(int mode, double Pc, double Tc, double TBoil, double ANTA, double ANTB, double ANTC, double omegaANT, double omegaCRI, double omegaLK);

#endif /* _2AcentricFactorDisplay_h */

#ifndef _2AcentricFactorWrite_h
#define _2AcentricFactorWrite_h

/// This subroutine is used to write the inputted parameters and calculated acentric factor to a .txt file.
/// @param mode This variable is used to control which variables get written to the .txt file. (1) = Collects parameters for the Antoine equation definition. (2) = Collects critical properties and normal boiling point. (3) = Collects critical properties and normal boiling point. (4) = Collects all variables.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param ANTA Antoine equation constant A (mmHg).
/// @param ANTB Antoine equation constant B (K. mmHg).
/// @param ANTC Antoine equation constant C (K).
/// @param omegaANT Acentric factor calculated with the Antoine equation ([ ]).
/// @param omegaCRI Acentric factor calculated with critical properties and the normal boiling point ([ ]).
/// @param omegaLK Acentric factor calculated with the Lee-Kesler vapour pressure relations ([ ])
void AcFactorWrite(int mode, double Pc, double Tc, double TBoil, double ANTA, double ANTB, double ANTC, double omegaANT, double omegaCRI, double omegaLK);

/// This subroutine is used to ask the user whether or not they would like to write the inputted parameters and calculated acentric factor to a .txt file.
/// @param mode1 This variable is used to control whether the display or write function is run.
/// @param mode2 This variable is used to control which variables get written to the .txt file. (1) = Collects parameters for the Antoine equation definition. (2) = Collects critical properties and normal boiling point. (3) = Collects critical properties and normal boiling point. (4) = Collects all variables.
/// @param Pc Critical pressure (bar).
/// @param Tc Critical temperature (K).
/// @param ANTA Antoine equation constant A (mmHg).
/// @param ANTB Antoine equation constant B (K. mmHg).
/// @param ANTC Antoine equation constant C (K).
/// @param omegaANT Acentric factor calculated with the Antoine equation ([ ]).
/// @param omegaCRI Acentric factor calculated with critical properties and the normal boiling point ([ ]).
/// @param omegaLK Acentric factor calculated with the Lee-Kesler vapour pressure relations ([ ])
void AcFactorSwitch(int mode1, int mode2, double Pc, double Tc, double TBoil, double ANTA, double ANTB, double ANTC, double omegaANT, double omegaCRI, double omegaLK);

#endif /* _2AcentricFactorWrite_h */
