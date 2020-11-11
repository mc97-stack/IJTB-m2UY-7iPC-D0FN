//
//  04dClausiusInequality.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 31/10/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#ifndef _4dClausiusInequalityStruct_h
#define _4dClausiusInequalityStruct_h

typedef struct ClausiusInequality{
    double q[500];
    double T[500];
    double s[500];
    double sum[500];
} T4EntropyDef;

#endif /* _4dClausiusInequalityStruct_h */

#ifndef _4dClausiusInequalityVariable_h
#define _4dClausiusInequalityVariable_h

/// This subroutine is used to get the variables for the entropy at a given time state.
/// @param i Time state.
/// @param data Struct where data is being collected into.
T4EntropyDef EntropyVariable(int i, T4EntropyDef data);

#endif /* _4dClausiusInequalityVariable_h */

#ifndef _4dClausiusInequalityCalculation_h
#define _4dClausiusInequalityCalculation_h

/// This subroutine is used to calculate the entropy at a given time state from the data contained within the struct 'data'.
/// @param i Time state.
/// @param data Struct where data is both being held and where the calculation is returned to.
T4EntropyDef EntropyCalculation(int i, T4EntropyDef data);

/// This subroutine is used to calculate the entropy using the clausius inequality definition. This subroutine is not used within this file and is meant for use when the entropy is needed for calculation elsewhere in the program.
/// @param q Process heat (kJ).
/// @param T Temperature of process (K).
double EntropyCalc(double q, double T);

#endif /* _4dClausiusInequalityCalculation_h */

#ifndef _4dClausiusInequalityDisplay_h
#define _4dClausiusInequalityDisplay_h

/// This subroutine is used to display the collected and calculated data on the user console.
/// @param imax Number of entries inputted for calculation.
/// @param data Struct where the required data is stored.
void EntropyDisplay(int imax, T4EntropyDef data);

#endif /* _4dClausiusInequalityDisplay_h */

#ifndef _4dClausiusInequalityWrite_h
#define _4dClausiusInequalityWrite_h

/// This subroutine is used to write the collected and calculated data to a .txt file.
/// @param imax Number of entries inputted for calculation.
/// @param data Struct where the required data is stored.
void EntropyWrite(int imax, T4EntropyDef data);

/// This subroutine is used to ask the user if they would like to output the inputted parameters and calculated data to a .txt file.
/// @param imax Number of entries inputted for calculation.
/// @param data Struct where the required data is stored.
void EntropyWriteSwitch(int imax, T4EntropyDef data);

#endif /* _4dClausiusInequalityWrite_h */
