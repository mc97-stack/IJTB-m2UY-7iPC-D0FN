//
//  01PureComponent.c
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 03/11/2020.
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

//  Custom header files
#include "01PureComponent.h"

#define maxstrlen 128

void pureComponentConstants()
{
    char input[maxstrlen];
    int control = 0;
    
    control = 1;
    while(control == 1)
    {
        printf("Subroutines available:\n");
        printf("1. Critical property estimation.\n");
        printf("2. Acentric factor calculation.\n");
        printf("3. Boiling and freezing point estimation.\n");
        printf("Q. Exit menu.\n\n");
        
        printf("Selection [2]: ");
        fgets(input, sizeof(input), stdin);
        switch(input[0])
        {
            case '1':
                //CriticalProperty();
                printf("Bear with me, this is still being written...\n");
                break;
            case '2':
                if(AcentricFactor() != 0.0)
                {
                    printf("AcentricFactor() success\n");
                }else{
                    printf("WARNING: AcentricFactor() == 0\n");
                }
                break;
            case '3':
                //BoilingFreezingPoint();
                printf("Bear with me, this is still being written...\n");
                break;
            case '0':
            case 'Q':
            case 'q':
                control = 0;
                break;
            default:
                printf("Input not recognised. Please enter an integer value between 1 and 2");
                break;
        }
    }
}
