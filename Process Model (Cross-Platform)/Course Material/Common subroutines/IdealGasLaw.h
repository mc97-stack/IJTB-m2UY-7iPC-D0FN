//
//  IdealGasLaw.h
//  Process Model (Cross)
//
//  Created by Matthew Cheung on 18/08/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef IdealPressure_h
#define IdealPressure_h

double IdealPressure(double n, double T, double V);
/*  Subroutine to calculate the pure component pressure from rearrangement of the ideal gas law. Function returns the pure component pressure.
 */

#endif /* IdealPressure_h */

#ifndef IdealTemperature_h
#define IdealTemperature_h

double IdealTemperature(double n, double P, double V);
/*  Subroutine to calculate the system temperature from rearrangement of the ideal gas law. Funtion returns the system temperature
*/

#endif /* IdealPressure_h */

#ifndef IdealVolume_h
#define IdealVolume_h

double IdealVolume(double n, double P, double T);
/*  Subroutine to calculate the system volume from rearrangement of the ideal gas law. Function returns the pure component volume
*/

#endif /* IdealPressure_h */
