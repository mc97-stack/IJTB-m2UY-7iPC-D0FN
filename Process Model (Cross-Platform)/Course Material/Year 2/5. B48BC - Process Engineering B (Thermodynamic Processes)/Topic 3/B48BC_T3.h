//
//  B48BC_T3.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 27/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef JouleThomsonEffect_h
#define JouleThomsonEffect_h

/// This subroutine is used to calculate the Joule-Thomson coefficient which provides a prediction of gas behaviour when being throttled isenthalpically. This subroutine also calculates the inversion temperature. Currently, only the Van der Waals Equation of State is supported.
void JouleThomsonEffect(void);

#endif /* JouleThomsonEffect_h */

#ifndef MultistageCompressor_h
#define MultistageCompressor_h

/// This subroutine is used to calculate the work input for a multistage gas compressor using the pressure-temperature statement of an adiabatic process assuming complete intercooling between stages.
void MultistageCompressor(void);

#endif /* MultistageCompressor_h */

#ifndef MultistageShaftWork_h
#define MultistageShaftWork_h

/// This subroutine is used to estimate the total shaft work for a multistage gas compressor using the pressure-temperature statement of an adiabatic process assuming complete intercooling between stages.
void MultistageShaftWork(void);

#endif /* MultistageShaftWork_h */
