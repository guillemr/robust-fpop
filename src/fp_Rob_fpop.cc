/* February 2015 Guillem Rigaill <rigaill@evry.inra.fr> 

   This file is part of the R package robseg

   opfp is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License (LGPL) as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.
   
   opfp is distributed in the hope that it will be useful,
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
void rob_fpop(const double *profil, const int *nbi, const double *lambda_, 
		const double *lthreshold_, const double *rthreshold_,
		const double *lslope_, const double *rslope_,
		const double *mini, const double *maxi, int *origine, double *cout_n, double *mean_n){


	int nb=*nbi;
	double lambda = *lambda_;
	double lthreshold = *lthreshold_;
	double rthreshold = *rthreshold_;
	double lslope = *lslope_;
	double rslope = *rslope_;

	double min=*mini;
	double max=*maxi;


	int minPosition=-10;
	double minCurrent=100, meanCurrent=0.;

	
	CFunctPart *iniFunc = new CFunctPart(min, max);
	Liste * candidates = new Liste(iniFunc); 
 
	candidates->add(profil[0], lthreshold, rthreshold, lslope, rslope);

	// Initialize for -10, -1, -10 origine
	//Liste * Current = candidates;
	//while(Current != NULL){
	//	if(Current->cFunc->a2 == 0){
	//		Current->cFunc->origine=-10;		
	//	}	
	//	Current = Current->next;
	//}
	
	//
	candidates->getMin(&minCurrent, &minPosition, &meanCurrent);
	cout_n[0] = minCurrent + lambda;
	origine[0] = minPosition;
	mean_n[0] = meanCurrent;
	
	for ( int t =1; t < nb; t++ ){
		//cout << "Tour : " << t << "\n";
		candidates->compare(cout_n[t-1], t);
		candidates->mergeSimilarElements();	
		candidates->add(profil[t], lthreshold, rthreshold, lslope, rslope);
		candidates->mergeSimilarElements();
		candidates->getMin(&minCurrent, &minPosition, &meanCurrent);
		cout_n[t] = minCurrent + lambda;
		origine[t] = minPosition;
		mean_n[t] = meanCurrent;
	}

	delete candidates;
	
}
