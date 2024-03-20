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
//#include<iostream>
//using namespace std;
void rob_fpop
(const double *profil, const int *nbi, const double *lambda_, 
 const double *lthreshold_, const double *rthreshold_,
 const double *lslope_, const double *rslope_,
 const double *mini, const double *maxi,
 int *origine, double *cout_n, double *mean_n,
 int *intervals
 ){
	int nb=*nbi;
	double lambda = *lambda_;
	double lthreshold = *lthreshold_;
	double rthreshold = *rthreshold_;
	double lslope = *lslope_;
	double rslope = *rslope_;

	double min=*mini;
	double max=*maxi;


	double minCurrent=-5;

	
	CFunctPart *iniFunc = new CFunctPart(min, max);
	Liste * candidates = new Liste(iniFunc); 
 
	cout_n[0] = minCurrent + lambda;
	for ( int t =0; t < nb; t++ ){
	  if(t>0){
	    candidates->compare(cout_n[t-1], t);
	    candidates->mergeSimilarElements();
	  }
	  candidates->add(profil[t], lthreshold, rthreshold, lslope, rslope);
	  if(t>0){
	    candidates->mergeSimilarElements();
	  }
	  candidates->getMin(&minCurrent, origine+t, mean_n+t, intervals+t);
	  cout_n[t] = minCurrent + lambda;
	}

	delete candidates;
	
}
