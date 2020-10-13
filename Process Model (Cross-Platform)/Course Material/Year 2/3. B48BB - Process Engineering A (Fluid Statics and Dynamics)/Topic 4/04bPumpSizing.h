//
//  04bPumpSizing.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

#ifndef PumpVar_h
#define PumpVar_h

/// This subroutine is used for collecting data used to size a pump. Since alot of variables are being collected, this function can be simplified by asking the user to input the state variables and then allowing the computer to gather the required data and run the calculations.
/// @param Q Volumetric flowrate (m3/s)
/// @param rho Fluid density (kg/m3)
/// @param Psat Fluid vapour pressure (kPa)
/// @param SucVesselP Suction-side vessel pressure (kPa)
/// @param hs1 Liquid level in suction-side vessel (m)
/// @param hs2 Liquid elevation above pump inlet (m)
/// @param dPsuction Suction side frictional head loss (m)
/// @param DisVesselP Discharge-side vessel pressure (kPa)
/// @param hd1 Liquid level in Discharge-side vessel (m)
/// @param hd2 Liquid elevation above pump outlet (m)
/// @param dPdischarge Discharge side frictional head loss (m)
/// @param eta Pump efficiency (0% - 100%)
void PumpVar(double *Q, double *rho, double *Psat, double *SucVesselP, double *hs1, double *hs2, double *dPsuction, double *DisVesselP, double *hd1, double *hd2, double *dPdischarge, double *eta);

#endif /* _4bPumpSizing_h */

#ifndef PumpInitialCalc_h
#define PumpInitialCalc_h

/// This subroutine is used to calculate the head produced either side of a pump. This subroutine returns the calculated head back to the calling function.
/// @param P Vessel pressure.
/// @param rho Fluid density.
/// @param h1 Fluid level in receiving tank.
/// @param h2 Fluid elevation above pump port.
/// @param fric Headloss due to friction.
double PumpInitialCalc(double P, double rho, double h1, double h2, double fric);

#endif /* PumpInitialCalc_h */

#ifndef PumpNPSHCalc_h
#define PumpNPSHCalc_h

/// This subroutine is used to calculate the available NPSH for the pump.
/// @param P Suction-side vessel pressure (Pa)
/// @param Phat Vapour pressure of fluid in suction-side vessel (Pa)
/// @param rho Fluid density (kg/ m3)
/// @param hs1 Liquid level in suction-side vessel (m)
/// @param hs2 Liquid elevation above pump inlet (m)
/// @param hfric Frictional head loss (m)
double PumpNPSHCalc(double P, double Phat, double rho, double hs1, double hs2, double hfric);

#endif /* PumpNPSHCalc_h */

#ifndef PumpHeadCalc_h
#define PumpHeadCalc_h

/// This subroutine is used to calculate the pump head.
/// @param hs Suction head.
/// @param hd Discharge head.
double PumpHeadCalc(double hs, double hd);

#endif /* PumpHeadCalc_h */

#ifndef PumpPressureCalc_h
#define PumpPressureCalc_h

/// This subroutine is used to find the pressure change across the pump.
/// @param rho Fluid density (kg/ m3)
/// @param dHp Pump head (m)
double PumpPressureCalc(double rho, double dHp);

#endif /* PumpPressureCalc_h */

#ifndef PumpPowerCalc_h
#define PumpPowerCalc_h

/// This subroutine is used to find the pump power requirement.
/// @param dPp Pump pressure change (Pa)
/// @param Q Volumetric flowrate (m3/s)
/// @param eta Pump efficiency
double PumpPowerCalc(double dPp, double Q, double eta);

#endif /* PumpPowerCalc_h */
