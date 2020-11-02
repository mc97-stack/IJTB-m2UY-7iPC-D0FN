//
//  VdWEOS.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 27/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

//  Standard header files
#include <math.h>

//  Custom header files
#include "VdWEOS.h"

#define R 8.3145

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
