//
//  03aFrictFactor.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 09/10/2020.
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

//  Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  Custom header files
#include "03aFrictFactor.h"
#include "02dReyNo.h"

double Laminar(double rho, double u, double d, double mu)
{
    double FrictFactor = 0.0;
    
    FrictFactor = ReyNoCalculation(rho, u, d, mu);
    FrictFactor = (8.0)/(FrictFactor);
    
    return FrictFactor;
}

double Turbulent1(double rho, double u, double d, double mu)
{
    double FrictFactor = 0.0;
    
    FrictFactor = ReyNoCalculation(rho, u, d, mu);
    FrictFactor = pow(FrictFactor, (-0.25));
    FrictFactor = 0.0396*(FrictFactor);
    
    return FrictFactor;
}

double Turbulent2(double rho, double u, double d, double mu)
{
    double FrictFactor = 0.0;
    double LHS = 0.0;
    double RHS = 0.0;
    
    double incr = 0.0; // Increment between iterations
    
    int i = 0; // Loop controller
    int i_max = 90000; // Max number of iterations
    
    double error[i_max]; // Error data
    
    //Setting initial guess
    FrictFactor = 0.001;
    incr = 0.0000001;
    
    for(i = 0; i < i_max; ++i){
        LHS = pow(FrictFactor, (-0.5));
        
        RHS = ReyNoCalculation(rho, u, d, mu);
        RHS = (RHS)*pow(FrictFactor, 0.5);
        RHS = log(RHS);
        RHS = 2.5*(RHS);
        RHS = (RHS)+0.3;
        
        error[i] = fabs(RHS - LHS);
        
        FrictFactor += incr;
    }
    
    //  Finding the location of the smallest value in the error data
    for(i = 1; i < i_max; ++i){
        if(error[i - 1] < error[i]){
            // Minimum value has been found
            break;
        }else{
            // Do nothing
        }
    }
    FrictFactor = 0.001 + (i-1)*(incr);
    
    return FrictFactor;
}

double Turbulent3(double rho, double u, double d, double mu, double vareps)
{
    double FrictFactor = 0.0;
    double LHS = 0.0;
    double RHS = 0.0;
    double term1 = 0.0;
    double term2 = 0.0;
    
    double incr = 0.0; // Increment between iterations
    
    int i = 0; // Loop controller
    int i_max = 90000; // Max number of iterations
    
    double error[i_max]; // Error data
    
    //Setting initial guess
    FrictFactor = 0.001;
    incr = 0.0000001;
    
    term1 = vareps/d;
    term1 = 0.27*(term1);
    
    for(i = 0; i < i_max; ++i){
        LHS = pow(FrictFactor, (-0.5));
        
        term2 = pow(FrictFactor, 0.5);
        RHS = ReyNoCalculation(rho, u, d, mu);
        term2 = RHS*term2;
        term2 = 0.885/(term2);
        
        RHS = term1 + term2;
        RHS = log(RHS);
        RHS = 2.5*(RHS);
        RHS = -1*(RHS);
        
        error[i] = fabs(RHS - LHS);
        
        FrictFactor += incr;
    }
    //  Finding the location of the smallest value in the error data
    for(i = 1; i < i_max; ++i){
        if(error[i - 1] < error[i]){
            // Minimum value has been found
            break;
        }else{
            // Do nothing
        }
    }
    FrictFactor = 0.001 + (i-1)*(incr);
    
    return FrictFactor;
}

double Turbulent4(double d, double vareps)
{
    double FrictFactor = 0.0;
    
    FrictFactor = vareps/d;
    FrictFactor = log(FrictFactor);
    FrictFactor = 2.5*(FrictFactor);
    FrictFactor = 3.2 - (FrictFactor);
    
    FrictFactor = 1/(FrictFactor);
    FrictFactor = pow(FrictFactor, 2);
    
    return FrictFactor;
}
