/* July 2017 Guillem Rigaill <guillem.rigaill@inra.fr> 

   This file is part of the R package Robseg

   robseg is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License (LGPL) as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.
   
   robseg is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with opfp; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _CFunctPartH
#define _CFunctPartH
#include <math.h>
#include <float.h>
#include <stdlib.h>

class CFunctPart {
     public:
     // coefficients a2 x^2 + a1 x^1 + a0 x^0
     double a2, a1, a0;

     // borders [lBorder, rBorder], roots etc...
     double lBorder, rBorder;
     double rac1, rac2;
     int racStatus;
     // others
     int origine;
    

     /* status of the polynome 0 = roots not computed, 1 = computed*/ 
     CFunctPart()
     : a0(0.), a1(0.), a2(0.),
       lBorder(0.), rBorder(0.),
       rac1(0.), rac2(0.), racStatus(0),
       origine(0) {}

     ~CFunctPart() {}

     CFunctPart(double a0_, double a1_, double a2_, double lBorder_, double rBorder_, int origine_)
     : a0(a0_), a1(a1_), a2(a2_),
       lBorder(lBorder_), rBorder(rBorder_),
       rac1(0.), rac2(0.), racStatus(0),
       origine(origine_) {}

     CFunctPart(double lBorder_, double rBorder_)
     : a0(0.), a1(0.), a2(0.),
       lBorder(lBorder_), rBorder(rBorder_),
       rac1(0.), rac2(0.), racStatus(0),
       origine(-1) {}

     CFunctPart(double a0_, double a1_, double a2_, double lBorder_, double rBorder_, 
	double rac1_, double rac2_, int origine_)
     : a0(a0_), a1(a1_), a2(a2_),
       lBorder(lBorder_), rBorder(rBorder_),
       rac1(rac1_), rac2(rac2_), racStatus(0),
       origine(origine_) {}
     double min();
     double mean();
     void reset(double cost_, int origine_);
     /* add */
     bool addLeft(double lBorder_, double a0_, double a1_);
     bool addCenter(double rBorder, double a0_, double a1_, double a2_);
     //bool addCenter(double X_, double thrs_);
     void addRight(double a0_, double a1_);
     void updateRoots(double a0_);
     void compare(double a0_);

};

#endif //CFunctPartH

