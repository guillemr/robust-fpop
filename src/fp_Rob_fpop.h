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

#ifndef ROB_FPOPH
#define ROB_FPOPH

#include "fp_liste.h"

void rob_fpop(const double *profil, const int *nbi, const double *lambda_, 
		const double *lthreshold_, const double *rthreshold_,
		const double *lslope_, const double *rslope_,
		const double *mini, const double *maxi, int *origine, double *cout_n,
	      double *mean_n, int *intervals);
#endif
