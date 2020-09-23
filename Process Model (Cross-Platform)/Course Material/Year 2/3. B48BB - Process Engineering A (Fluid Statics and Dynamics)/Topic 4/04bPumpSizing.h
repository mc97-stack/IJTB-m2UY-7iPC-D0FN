//
//  04bPumpSizing.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 23/09/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Due to the number of variables being used, all variables being used in this file are declared local to the main function ("PumpSizing(void)") and controlled from there.

#ifndef PumpVar_h
#define PumpVar_h

void PumpVar(double *Q, double *rho, double *Psat, double *SucVesselP, double *hs1, double *hs2, double *dPsuction, double *DisVesselP, double *hd1, double *hd2, double *dPdischarge, double *eta);
/*  This subroutine is used for collecting data used to size a pump. Since alot of variables are being collected, this function can be simplified by asking the user to input the state variables and then allowing the computer to gather the required data and run the calculations. This subroutine has no external dependencies.
 */

#endif /* _4bPumpSizing_h */

#ifndef PumpInitialCalc_h
#define PumpInitialCalc_h

double PumpInitialCalc(double P, double rho, double h1, double h2, double fric);
/*  This subroutine is used to calculate the head produced either side of a pump. This subroutine returns the calculated head back to the calling function. This subroutine has no external dependencies outside of this file and is not used outside of this file.
 */

#endif /* PumpInitialCalc_h */

#ifndef PumpNPSHCalc_h
#define PumpNPSHCalc_h

double PumpNPSHCalc(double P, double Phat, double rho, double hs1, double hs2, double hfric);
/*  This subroutine is used to calculate the available NPSH on the suction side. This variable is used to determine if the pump is able to 
 */

#endif /* PumpNPSHCalc_h */

#ifndef PumpHeadCalc_h
#define PumpHeadCalc_h

double PumpHeadCalc(double hs, double hd);

#endif /* PumpHeadCalc_h */

#ifndef PumpPressureCalc_h
#define PumpPressureCalc_h

double PumpPressureCalc(double rho, double dHp);

#endif /* PumpPressureCalc_h */

#ifndef PumpPowerCalc_h
#define PumpPowerCalc_h

double PumpPowerCalc(double dPp, double Q, double eta);

#endif /* PumpPowerCalc_h */
