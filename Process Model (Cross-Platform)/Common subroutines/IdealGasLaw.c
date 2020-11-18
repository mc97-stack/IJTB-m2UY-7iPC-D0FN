//
//  IdealGasLaw.c
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
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

//  File contains the subroutines required to estimate the fundamental functions through rearrangement of the ideal gas law. Note, no variables are required to be inputted as the subroutines in this file are meant to be utilised during calculation

//  Standard header files
#include <stdio.h>

//  Custom header files
#include "IdealGasLaw.h"

double IdealPressure(double n, double T, double V)
{
    double P = 0.0;
    double R = 0.0;
    
    R = 8.31455;
    
    P = n*R;
    P = (P)*T;
    P = (P)/V;
    
    return P;
}

double SpecPressure(double n, double T, double V, double R)
{
    double P = 0.0;
    
    P = n*R;
    P = (P)*T;
    P = (P)/V;
    
    return P;
}

double IdealTemperature(double n, double P, double V)
{
    double T = 0.0;
    double R = 0.0;
    
    R = 8.31455;
    
    double top = 0.0;
    double bot = 0.0;
    
    top = P*V;
    bot = n*R;
    
    T = (top)/(bot);
    
    return T;
}

double SpecTemperature(double n, double P, double V, double R)
{
    double T = 0.0;
    
    double top = 0.0;
    double bot = 0.0;
    
    top = P*V;
    bot = n*R;
    
    T = (top)/(bot);
    
    return T;
}

double IdealVolume(double n, double P, double T)
{
    double V = 0.0;
    double R = 0.0;
    
    R = 8.31455;
    
    V = n*R;
    V = (V)*T;
    V = (V)/P;
    
    return V;
}

double SpecVolume(double n, double P, double T, double R)
{
    double V = 0.0;
    
    V = n*R;
    V = (V)*T;
    V = (V)/P;
    
    return V;
}
