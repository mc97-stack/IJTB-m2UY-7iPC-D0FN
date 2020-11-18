//
//  03CubicEOSConstants.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
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

/// MARK: HEADER DECLARATIONS
//  Standard header files
#include <math.h>

//  Custom header files
#include "03CubicEOS.h"

#define R 83.145        // (bar.cm3)/(mol.K)

/// MARK: VAN DER WAALS CONSTANTS
double VdWcalculateA(double Tc, double Pc)
{
    double a = 0.0;
    
    double frac1 = 0.0;
    double frac2 = 0.0;
    
    frac1 = (27.0)/(64.0);
    
    frac2 = pow(R,2);
    frac2 = (frac2)*pow(Tc, 2);
    frac2 = (frac2)/Pc;
    
    a = frac1*frac2;
    
    return a;
}

double VdWcalculateB(double Tc, double Pc)
{
    double b = 0.0;
    
    double top = 0.0;
    double bot = 0.0;
    
    top = R*Tc;
    bot = 8*Pc;
    
    b = top/bot;
    
    return b;
}

/// MARK: REDLICH-KWONG CONSTANTS
double RKcalculateA(double Tc, double Pc, double T)
{
    double a = 0.0;
    
    double top = 0.0;
    double bot = 0.0;
    double sto = 0.0;
    
    top = pow(Tc, 2.5);
    sto = pow(R, 2);
    top = (sto)*(top);
    top = 0.42748*(top);
    
    bot = pow(T, 0.5);
    bot = Pc*(bot);
    
    a = (top)/(bot);
    
    return a;
}

double RKcalculateB(double Tc, double Pc)
{
    double b = 0.0;
    
    double top = 0.0;
    
    top = R*Tc;
    top = 0.08664*(top);
    
    b = top/Pc;
    
    return b;
}

/// MARK: SOAVE-REDLICH-KWONG CONSTANTS
double SRKcalculateAcFunc(double omega)
{
    double func = 0.0;
    double sto = 0.0;
    
    sto = 1.574*omega;
    func = 0.48 + (sto);
    
    sto = pow(omega, 2);
    sto = 0.176*(sto);
    func = (func) - (sto);
    
    return func;
}

double SRKcalculateA(double Tc, double Pc, double T, double omega)
{
    double a = 0.0;
    
    double top = 0.0;
    double brack = 0.0;
    double sto = 0.0;
    
    top = pow(Tc, 2);
    sto = pow(R, 2);
    top = (sto)*(top);
    top = 0.42748*(top);
    
    a = (top)/Pc;
    
    brack = SRKcalculateAcFunc(omega);
    sto = T/Tc;                 // Calculating reduced temperature.
    sto = pow(sto, 0.5);
    sto = 1 - (sto);            // Inner brack calculated.
    brack = (brack)*(sto);
    brack = 1 + (brack);        // Square bracket calculated.
    brack = pow(brack, 2);
    
    a = (a)*(brack);
    
    return a;
}

/// MARK: PENG-ROBINSON CONSTANTS
double PRcalculateAcFunc(double omega)
{
    double func = 0.0;
    double sto = 0.0;
    
    sto = 1.54226*omega;
    func = 0.37464 + (sto);
    
    sto = pow(omega, 2);
    sto = 0.26992*(sto);
    func = (func) - (sto);
    
    return func;
}

double PRcalculateA(double Tc, double Pc, double T, double omega)
{
    double a = 0.0;
    
    double top = 0.0;
    double brack = 0.0;
    double sto = 0.0;
    
    top = pow(Tc, 2);
    sto = pow(R, 2);
    top = (sto)*(top);
    top = 0.45724*(top);
    
    a = (top)/Pc;
    
    brack = PRcalculateAcFunc(omega);
    sto = T/Tc;                 // Calculating reduced temperature.
    sto = pow(sto, 0.5);
    sto = 1 - (sto);            // Inner brack calculated.
    brack = (brack)*(sto);
    brack = 1 + (brack);        // Square bracket calculated.
    brack = pow(brack, 2);
    
    a = (a)*(brack);
    
    return a;
}

double PRcalculateB(double Tc, double Pc)
{
    double b = 0.0;
    
    double top = 0.0;
    
    top = R*Tc;
    top = 0.07780*(top);
    
    b = top/Pc;
    
    return b;
}
