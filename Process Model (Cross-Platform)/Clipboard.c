//
//  Clipboard.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 02/11/2020.
//  Copyright © 2020 Matthew Cheung. All rights reserved.
//

#include <math.h>
#include <stdio.h>
#include <time.h>

    //  Variables for timing function
struct timespec start, end;
double elapsed = 0.0;

clock_getres(CLOCK_MONOTONIC, &start);
clock_gettime(CLOCK_MONOTONIC, &start);

//  Calculations

clock_getres(CLOCK_MONOTONIC, &end);
clock_gettime(CLOCK_MONOTONIC, &end);

elapsed = timer(start, end);

printf("Calculations completed in %.6f seconds.\n", elapsed);
