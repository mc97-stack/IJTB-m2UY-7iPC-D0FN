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
