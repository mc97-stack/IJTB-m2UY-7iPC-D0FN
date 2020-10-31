//
//  B48BC_T4.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 30/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef ThermalEfficiency_h
#define ThermalEfficiency_h

/// This subroutine is used to calculate the thermal efficiency of a heat engine extracting heat from a hot thermal reservoir and dumping heat into a cold thermal reservoir. It also contains the calculations comparing the given process to its equivalent carnot cycle to determine whether or not the proposed is in violation of the quality argument of the second law of thermodynamics.
void ThermalEfficiency(void);

#endif /* ThermalEfficiency_h */

#ifndef CoefficientofPerformance_h
#define CoefficientofPerformance_h

/// This subroutine is used to calculate the coefficient of performance for a refrigerator or a heat pump. This, like with "ThermalEfficiency(void)" calculates the equivalent reversible process and checks whether or not the proposed process is in violation of the quality argument of the second law of thermodynamics.
void CoefficientofPerformance(void);

#endif /* CoefficientofPerformance_h */

#ifndef CarnotCycle_h
#define CarnotCycle_h

/// This subroutine is used to run a simulation of a carnot cycle and evaluates and quantifies the irreversibility of the process by using the functions given with "ThermalEfficiency(void)" and evaluating the Clausius inequality.
void CarnotCycle(void);

#endif /* CarnotCycle_h */

#ifndef ClausiusInequality_h
#define ClausiusInequality_h

/// This subroutine is used to guide the user through evaluating the thermodynamic feasibility of a process by analysis through conserved heat-temperature property (entropic contributions) throughout a process. After all heat contributions have been inputted into the subroutine, it then notifies the user of whether the given process is in violation of the second law of thermodynamics.
void ClausiusInequality(void);

#endif /* ClausiusInequality_h */
