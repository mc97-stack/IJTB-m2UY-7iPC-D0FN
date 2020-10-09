//
//  03bGenPressureLoss.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef PressLossVariable_h
#define PressLossVariable_h

void PressLossVariable(double *rho, double *u, double *d, double *mu, double *L, double *vareps);

#endif /* PressLossVariable_h */

#ifndef phi_h
#define phi_h

double phicalc(double rho, double u, double d, double mu, double vareps);

#endif /* phi_h */

#ifndef LossCalculation_h
#define LossCalculation_h

double LossCalculation(double phi, double L, double d, double rho, double u);

#endif /* LossCalculation_h */
