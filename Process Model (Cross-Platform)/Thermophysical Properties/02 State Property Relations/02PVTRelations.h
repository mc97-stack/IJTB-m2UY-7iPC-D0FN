//
//  02PVTRelations.h
//  Process Model (Cross-Platform)
//
//  Created by Matthew Cheung on 01/11/2020.
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

#ifndef _2PVTRelations_h
#define _2PVTRelations_h

/// This subroutine is a menu function giving the user a choice of which enclosed subroutine they would like to run.
void statePropertyRelations(void);

#endif /* _2PVTRelations_h */

#ifndef IdealEOS_h
#define IdealEOS_h

/// This subroutine is used to generate the P-V-T surface according to the Ideal Gas EOS.
void IdealEOS(void);

#endif /* IdealEOS_h */

#ifndef VirialEOS_h
#define VirialEOS_h

/// This subroutine can be used to generate the P-V-T surface according to the Virial EOS.
void VirialEOS(void);

#endif /* VirialEOS_h */

#ifndef CubicEOS_h
#define CubicEOS_h

/// This subroutine can be used to generate the P-V-T surface according to the van der Waals, Redlich-Kwong, Soave-Redlich-Kwong or Peng-Robinson Equations of State or the corresponding compressibility factor charts.
void CubicEOS(void);

#endif /* CubicEOS_h */

#ifndef GenBWREOS_h
#define GenBWREOS_h

/// This subroutine is used to generate the P-V-T surface according to the generalised Benedict-Webb-Rubin EOS.
void GenBWREOS(void);

#endif /* GenBWREOS_h */

#ifndef saturatedMolarVolume_h
#define saturatedMolarVolume_h

/// This subroutine is used to generate the P-V-T surface according to the generalised Benedict-Webb-Rubin EOS.
void saturatedMolarVolume(void);

#endif /* saturatedMolarVolumeEOS_h */
