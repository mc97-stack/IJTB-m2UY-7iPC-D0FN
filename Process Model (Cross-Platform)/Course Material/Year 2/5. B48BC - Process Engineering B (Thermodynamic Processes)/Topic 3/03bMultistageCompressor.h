//
//  03bMultistageCompressor.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 28/10/2020.
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

#ifndef _3bMultistageCompressorVariable_h
#define _3bMultistageCompressorVariable_h

/// This subroutine is used to collect the required data to calculate a multistage gas compression profile accounting for clearance volume.
/// @param P1 Initial system pressure (kPa).
/// @param P2 Final system pressure (kPa).
/// @param Vc Clearance volume (m3).
/// @param T1 System temperature before compression (deg C).
/// @param n Molar flowrate through the compressor (kmol/s).
/// @param N Number of compression stages (up to and including 6 stages).
/// @param gamma Heat capacity ratio ([ ]).
void MSCompVariable(double *P1, double *P2, double *Vc, double *T1, double *n, int *N, double *gamma);

#endif /* _3bMultistageCompressorVariable_h */

#ifndef _3bMultistageCompressorCalculation_h
#define _3bMultistageCompressorCalculation_h

typedef struct T3MultiStageCompressor{
    double P[1500];     // System pressure
    double V[1500];     // System volume
    double T[1500];     // System temperature
    double W_V[1500];   // Volume work
    double W_S[1500];   // Shaft work
} T3CompProfile;

/// This subroutine is used to calculate the pressure ratio between the starting pressure and desired final pressure.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
double calculatePressureRatio(double P1, double P2);

/// This subroutine is used to calculate the location of the start of the compressor intake stroke within the declared struct at a specified stage.
/// @param elements Total number of rows within each matrix within the struct.
/// @param stage Stage identifier - 1.
/// @param stages Total number of stages.
int stageIntake(int elements, int stage, int stages);

/// This subroutine is used to calculate the location of the start of the adiabatic portion of the compression process within the declared struct at a specified stage.
/// @param elements Total number of rows within each matrix within the struct.
/// @param stage Stage identifier - 1.
/// @param stages Total number of stages.
int stageProcess(int elements, int stage, int stages);

/// This subroutine is used to calculate the number of rows required for the adiabatic portion of the compression process. 
/// @param elements Total number of rows within each matrix within the struct.
/// @param stages Total number of stages.
int ProcessStages(int elements, int stages);

/// This subroutine is used to calculate the location of the start of the discharge stroke of the compression process as the gas is expelled from one compressor at a specified stage. 
/// @param elements Total number of rows within each matrix within the struct.
/// @param stage Stage identifier - 1.
/// @param stages Total number of stages.
int stageDischarge(int elements, int stage, int stages);

/// This subroutine is used to calculate the profile for a multistage gas compression process.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param Vc Clearance volume (m3).
/// @param T1 System temperature before compression (K).
/// @param n Molar flowrate through the compressor (mol/s).
/// @param N Number of compression stages (up to and including 6 stages).
/// @param gamma Heat capacity ratio ([ ]).
T3CompProfile MSCompProfile(double P1, double P2, double Vc, double T1, double n, int N, double gamma);

#endif /* _3bMultistageCompressorCalculation_h */

#ifndef _3bMultistageCompressorDisplay_h
#define _3bMultistageCompressorDisplay_h

/// This subroutine is used to display the generated data table for a multistage gas compression process.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param Vc Clearance volume (m3).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 System temperature before compression (K).
/// @param T2 System temperature after compression (K).
/// @param n Molar flowrate through the compressor (mol/s).
/// @param N Number of compression stages (up to and including 6 stages).
/// @param gamma Heat capacity ratio ([ ]).
/// @param profile Table generated from "MSCompProfile(...)".
void MSCompDisplay(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double N, double gamma, T3CompProfile profile);

#endif /* _3bMultistageCompressorDisplay_h */

#ifndef _3bMultistageCompressorWrite_h
#define _3bMultistageCompressorWrite_h

/// This subroutine is used to write the generated data to a .txt file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param Vc Clearance volume (m3).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 System temperature before compression (K).
/// @param T2 System temperature after compression (K).
/// @param n Molar flowrate through the compressor (mol/s).
/// @param N Number of compression stages (up to and including 6 stages).
/// @param gamma Heat capacity ratio ([ ]).
/// @param profile Table generated from "MSCompProfile(...)".
void MSCompWrite(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double N, double gamma, T3CompProfile profile);

/// This subroutine is used to ask the user whether they would like to write the results of this entire subroutine to a .txt file.
/// @param P1 Initial system pressure (Pa).
/// @param P2 Final system pressure (Pa).
/// @param Vc Clearance volume (m3).
/// @param V1 Initial system volume (m3).
/// @param V2 Final system volume (m3).
/// @param T1 System temperature before compression (K).
/// @param T2 System temperature after compression (K).
/// @param n Molar flowrate through the compressor (mol/s).
/// @param N Number of compression stages (up to and including 6 stages).
/// @param gamma Heat capacity ratio ([ ]).
/// @param profile Table generated from "MSCompProfile(...)".
void MSCompWriteSwitch(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double N, double gamma, T3CompProfile profile);

#endif /* _3bMultistageCompressorWrite_h */
