//
//  VdWEOS.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 27/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef VdWConstants_h
#define VdWConstants_h

/// This subroutine is used to calculate the repulsive term in the Van der Waals Equation of State.
/// @param Tc Critical temperature (K)
/// @param Pc Critical pressure (Pa)
double VdWcalculateA(double Tc, double Pc);

/// This subroutine is used to calculate the term representing the actual volume of the molecule in the Van der Waals Equation of State.
/// @param Tc Critical temperature (K)
/// @param Pc Critical pressure (Pa)
double VdWcalculateB(double Tc, double Pc);

#endif /* VdWEOS_h */
