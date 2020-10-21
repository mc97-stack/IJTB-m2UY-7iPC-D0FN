//
//  02aCompressor.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 17/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//  

typedef struct CompProfile{
    double P[512]; // System pressure
    double V[512]; // System volume
    double T[512]; // System temperature
    double W_V[512]; // Volume work
    double W_S[512]; // Shaft work
} T2CompProfile;

#ifndef CompressorVar_h
#define CompressorVar_h

/// This subroutine is used to collect the data required to perform the calculations for a reciprocating compressor undergoing an isothermal or polytropic process. This subroutine also requires "IdealGasLaw.h" to function as it calls "IdealVolume(...)" and "SpecVolume(...)".
/// @param method Integer variable used to determine which equation should be used and hence the variables required. (1) = Isothermal equation. (2) = Polytropic equation (Pressure-Volume statement). 
/// @param P1 Initial system pressure. (kPa)
/// @param P2 Final system pressure. (kPa)
/// @param Vc Clearance volume (m3)
/// @param V1 Initial system volume. (m3)
/// @param T1 Initial system temperature. For the isothermal equation, this variable is the constant temperature. (deg C)
/// @param T2 Final system temperature. (deg C)
/// @param n Moles of component. (kmol/ s)
/// @param R Specific gas constant. (J/ mol. K)
/// @param alpha Polytropic index
void CompressorVar(int method, double *P1, double *P2, double *Vc, double *V1, double *T1, double *T2, double *n, double *R, double *alpha);

#endif /* _2aCompressor_h */

#ifndef CompressorProfile_h
#define CompressorProfile_h

/// This subroutine is used to generate the profile for one sweep of the compressor. For this subroutine to operate, it requires "IdealGasLaw.h" and "Isobaric.h". It also requires "Isothermal.h" or "Polytropic.h" to function dependent on the value of 'int method'.
/// @param method Integer variable used to determine which equation should be used and hence the variables required. (1) = Isothermal equation. (2) = Polytropic equation (Pressure-Volume statement). 
/// @param P1 Initial system pressure. (Pa)
/// @param P2 Final system pressure. (Pa)
/// @param Vc Clearance volume (m3)
/// @param V1 Initial system volume. (m3)
/// @param V2 System volume after compression. (m3)
/// @param T1 Initial system temperature. For the isothermal equation, this variable is the constant temperature. (K)
/// @param T2 Final system temperature. (K)
/// @param n Moles of component. (mol/ s)
/// @param R Specific gas constant. (J/ mol. K)
/// @param alpha Polytropic index
T2CompProfile CompressorProfile(int method, double P1, double P2, double Vc, double V1, double T1, double T2, double n, double R, double alpha, double *V2);

#endif /* CompressorProfile_h */

#ifndef CompresWrite_h
#define CompresWrite_h

/// This subroutine is used to write the collected data and generated process simulation to a .txt file.
/// @param P1 Initial system pressure. (Pa)
/// @param P2 Final system pressure. (Pa)
/// @param Vc Clearance volume (m3)
/// @param V1 Initial system volume. (m3)
/// @param V2 System volume after compression. (m3)
/// @param T1 Initial system temperature. For the isothermal equation, this variable is the constant temperature. (K)
/// @param T2 Final system temperature. (K)
/// @param n Moles of component. (mol/ s)
/// @param R Specific gas constant. (J/ mol. K)
/// @param alpha Polytropic index
//T2ThermoProffile Compressor Profile.
void CompresWrite(double P1, double P2, double Vc, double V1, double V2, double T1, double T2, double n, double R, double alpha, T2CompProfile profile);

#endif /* CompresWrite_h */