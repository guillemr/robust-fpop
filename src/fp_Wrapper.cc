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

#include "fp_Rob_fpop.h"
#include<R_ext/Arith.h>

// this function is visible by R
extern "C" {
void rob_fpop_RtoC (double *profil, int *nbi, double *lambda_, 
		double *lthreshold_, double *rthreshold_,
		double *lslope_, double *rslope_,
		double *mini, double *maxi, int *origine, double *cout_n, double *mean_n)
  {
    rob_fpop(profil, nbi, lambda_, 
		lthreshold_, rthreshold_, lslope_, rslope_, 
		mini, maxi, origine, cout_n, mean_n);
  }

}
