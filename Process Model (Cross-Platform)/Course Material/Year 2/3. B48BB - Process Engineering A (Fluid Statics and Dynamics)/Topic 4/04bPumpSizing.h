//
//  04bPumpSizing.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef PumpStruct
#define PumpStruct

typedef struct head{
    double P;
    double h1;
    double h2;
    double hf;
} head;

#endif /* PumpStruct */

#ifndef PumpVar_h
#define PumpVar_h

/// This subroutine is used to collect the variables that do not belong to a struct.
/// @param Q Fluid volumetric flowrate (m3/s)
/// @param rho Fluid density (kg/m3)
/// @param Psat Saturated vapour pressure (kPa)
/// @param NPSHr Required NPSH
/// @param eta Pump efficiency (value between 0 and 100)
void PumpVar(double *Q, double *rho, double *Psat, double *NPSHr, double *eta);

/// This subroutine is used to collect the data required to calculate either the suction or discharge head.
/// @param type Integer value used to control the printf output. (1) = Suction descriptors. (2) = Discharge descriptors)
/// @param var Struct where data should be inputted to.
head PumpHeadVar(int type, head var);

#endif /* PumpVar_h */

#ifndef PumpCalc_h
#define PumpCalc_h

/// This subroutine is used to calculate the head on either side of the pump
/// @param var Struct containing variables specific to each side of the pump.
/// @param rho Fluid density (kg/m3).
double HeadCalc(head var, double rho);

/// This subroutine is used to calculate the NPSH available.
/// @param var Suction-side parameters.
/// @param Psat Saturated vapour pressure (Pa).
/// @param rho Fluid density (kg/m3).
double NPSHCalc(head var, double Psat, double rho);

/// This subroutine is used to calculate the pump head.
/// @param hs Suction head.
/// @param hd Discharge head.
double PumpHeadCalc(double hs, double hd);

/// This subroutine is used to calculate the pressure 'drop' across the pump.
/// @param rho Fluid density (kg/m3).
/// @param hp Pump head (m).
double PumpPressureCalc(double rho, double hp);

/// This subroutine is used to calculate the pump power requirement.
/// @param dP_p Pressure 'drop' across the pump (Pa).
/// @param Q Fluid volumetric flowrate (m3/s)
/// @param eta Pump efficiency.
double PumpPower(double dP_p, double Q, double eta);

#endif /* PumpCalc_h */

#ifndef PumpDisp_h
#define PumpDisp_h

/// This subroutine is used to display the collected data and calculated parameters on the user console.
/// @param suction Suction-side parameters
/// @param discharge Discharge-side parameters
/// @param Q Fluid volumetric flowrate (m3/s)
/// @param rho Fluid density (kg/m3)
/// @param Psat Saturated vapour pressure (Pa)
/// @param NPSHr Required Net Positive Suction Head (m)
/// @param NPSHa Available Net Positive Suction Head (m)
/// @param eta Pump efficiency (%)
/// @param phead Pump head (m)
/// @param ppressure Pump pressure 'drop' (Pa)
/// @param ppower Pump power requirement (kW)
void PumpDisplay(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower);

#endif /* PumpDisp_h */

#ifndef PumpWrite_h
#define PumpWrite_h

/// This subroutine is used to output the generated dataset and collected parameters to a .txt file.
/// @param suction Suction-side parameters
/// @param discharge Discharge-side parameters
/// @param Q Fluid volumetric flowrate (m3/s)
/// @param rho Fluid density (kg/m3)
/// @param Psat Saturated vapour pressure (Pa)
/// @param NPSHr Required Net Positive Suction Head (m)
/// @param NPSHa Available Net Positive Suction Head (m)
/// @param eta Pump efficiency (%)
/// @param phead Pump head (m)
/// @param ppressure Pump pressure 'drop' (Pa)
/// @param ppower Pump power requirement (kW)
void PumpWrite(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower);

/// This subroutine is used to ask the user if they would like to write the generated dataset and collected parameters to a .txt file.
/// @param suction Suction-side parameters
/// @param discharge Discharge-side parameters
/// @param Q Fluid volumetric flowrate (m3/s)
/// @param rho Fluid density (kg/m3)
/// @param Psat Saturated vapour pressure (Pa)
/// @param NPSHr Required Net Positive Suction Head (m)
/// @param NPSHa Available Net Positive Suction Head (m)
/// @param eta Pump efficiency (%)
/// @param phead Pump head (m)
/// @param ppressure Pump pressure 'drop' (Pa)
/// @param ppower Pump power requirement (kW)
void PumpWriteCheck(head suction, head discharge, double Q, double rho, double Psat, double NPSHr, double NPSHa, double eta, double phead, double ppressure, double ppower);

#endif /* PumpWrite_h */
