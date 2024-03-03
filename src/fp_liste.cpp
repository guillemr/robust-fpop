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

#include "fp_liste.h"
//#include<iostream>
//using namespace std;
void Liste::getMin(double *min_, int *origine_, double *mean_, int *intervals_){
	
	Liste* Current = this;	
	min_[0] = Current->cFunc->min();
	origine_[0] = Current->cFunc->origine;
	mean_[0] = Current->cFunc->mean();
	intervals_[0] = 1;
	double tmp=0.;
	while(Current-> next != NULL){
		Current = Current->next;
		tmp = Current->cFunc->min();
		if(min_[0] > tmp){
			min_[0] = tmp;
			origine_[0] = Current->cFunc->origine;	
			mean_[0] = Current->cFunc->mean();	
		}
		intervals_[0] += 1;
	}
}
void Liste::add(double X_, double lthrs_, double rthrs_, double lslope, double rslope){
	double lBorder = X_- lthrs_;
	double rBorder = X_ + rthrs_;

	double a0 = X_ * X_;
	double a1 = -2*X_;
	double a2 = 1;

	double la1 = lslope;
	double la0 = lthrs_ * lthrs_ - la1*lBorder;

	double ra1 = rslope;
        double ra0 = rthrs_ * rthrs_ - ra1*rBorder;

	
	Liste* Current = this;
	
	// add left //
	bool aL = true;
	aL = (Current->cFunc)->addLeft(lBorder, la0, la1);
	while(aL & (Current-> next != NULL) )
	{
		Current = Current->next;
		aL = (Current->cFunc)->addLeft(lBorder, la0, la1);	
	}
	
	// split if necessary //
	//if(Current->cFunc->origine == 7){
	//cout << "Border : " << lBorder << "," << rBorder << "then" << Current->cFunc->lBorder << "," << Current->cFunc->rBorder << "\n";
	//}

        if(Current->cFunc->rBorder != lBorder & Current->cFunc->lBorder < lBorder){
		//cout << "Here1\n";
		CFunctPart * newCFuncLeft = new CFunctPart(
			Current->cFunc->a0, Current->cFunc->a1, Current->cFunc->a2,
			lBorder, Current->cFunc->rBorder,
			Current->cFunc->origine);

		Liste *newListeLeft = new Liste(Current->next, newCFuncLeft);	
		Current->next = newListeLeft;
		Current->cFunc->a0 = Current->cFunc->a0 + la0;
		Current->cFunc->a1 = Current->cFunc->a1 + la1;
		Current->cFunc->rBorder = lBorder;
		Current = newListeLeft;
	}
	
	
	//cout << "Border : " << lBorder << "," << rBorder << "then" << Current->cFunc->lBorder << "," << Current->cFunc->rBorder << "\n";
	
	// add polynomial part (center part) //
	bool aC = true;
	aC = (Current->cFunc)->addCenter(rBorder, a0, a1, a2);
	while(aC & (Current-> next != NULL) )
	{
		Current = Current->next;
		aC = (Current->cFunc)->addCenter(rBorder, a0, a1, a2);	
	}

	// splitRight if necessary //
	if(Current->cFunc->rBorder > rBorder){
		//cout << "Here2\n";
		CFunctPart * newCFuncRight = new CFunctPart(
			Current->cFunc->a0, Current->cFunc->a1, Current->cFunc->a2,
			rBorder, Current->cFunc->rBorder,
			Current->cFunc->origine);

		Liste * newListeRight = new Liste(Current->next, newCFuncRight);
	
		Current->next = newListeRight;
		Current->cFunc->a0 = Current->cFunc->a0 + a0;
		Current->cFunc->a1 = Current->cFunc->a1 + a1;
		Current->cFunc->a2 = Current->cFunc->a2 + a2;
		Current->cFunc->rBorder = rBorder;
	}
	// add right //
	while(Current->next != NULL)
	{
		Current = Current->next;
		(Current->cFunc)->addRight(ra0, ra1);
	}
	
}


void Liste::compare(double cost_, int origine_)
{
    Liste* Current = this;	
    // >> Start loop over all
    while(Current != NULL){

	Current->cFunc->updateRoots(cost_);
	/*cout << "Coef :" << Current->cFunc->a0 << "," << Current->cFunc->a1 << "," << Current->cFunc->a2 << "\n"; 
	cout << "Racine :" << Current->cFunc->racStatus << "," 
	<< Current->cFunc->rac1 << ","  <<
	Current->cFunc->rac2 << "\n";*/
	// >> Full replace
	if(Current->cFunc->racStatus == -1){ 
		Current->cFunc->reset(cost_, origine_);	
	}
	// << end Full replace

	// >> Split in 2 or 3	
	if(Current->cFunc->racStatus == 1){ 
		// if necessary take into account rac1 => 
		// [lBorder, rBorder] => [lBorder, rac1] + [rac1, rBorder]
		//  poly	      =>  const + poly
		if( Current->cFunc->rac1 > Current->cFunc->lBorder) { 
			// create next
			
			CFunctPart * newCFuncRight = new CFunctPart(
				Current->cFunc->a0, Current->cFunc->a1, Current->cFunc->a2,
				Current->cFunc->rac1, Current->cFunc->rBorder,
				Current->cFunc->rac1, Current->cFunc->rac2,
				Current->cFunc->origine);
			
			Liste * newListeRight = new Liste(Current->next, newCFuncRight);
			Current->next = newListeRight;
			// replace
			Current->cFunc->reset(cost_, origine_);
			Current->cFunc->rBorder = Current->next->cFunc->lBorder;
			// move to next
			Current = Current->next;
			
		}
	
		// if necessary take into account rac1 => 
		// [lBorder, rBorder] => [lBorder, rac2] + [rac2, rBorder]
		//  poly	      =>  poly + const
		if(Current->cFunc->rac2 < Current->cFunc->rBorder) {
			// create new element
			CFunctPart * newCFuncRight = new CFunctPart(
				cost_, 0, 0,
				Current->cFunc->rac2, Current->cFunc->rBorder,
				origine_);
		
			Liste * newListeRight = new Liste(Current->next, newCFuncRight);
			// update current
			Current->cFunc->rBorder = Current->cFunc->rac2;
			Current->next = newListeRight;
			Current->cFunc->rac1 = 0.;
			Current->cFunc->rac2 = 0.;
			Current->cFunc->racStatus = 0;
			
			// move to next
			Current = Current->next;	
		}
	}
	// << end split in 2 or 3

   	Current = Current->next;
   } 
   // << End loop over List
}

void Liste::mergeSimilarElements(){
	Liste* Current = this;	
	// >> Start loop over all
	while(Current != NULL){
		// if two successive element have the same origin fuse them
    		if( (Current->next !=NULL) 
			&& (Current->next->cFunc->origine == Current->cFunc->origine) 
			&& (Current->next->cFunc->a2 == Current->cFunc->a2) 
			&& (Current->next->cFunc->a1 == Current->cFunc->a1)
			&& (Current->next->cFunc->a0 == Current->cFunc->a0)
			)
		{
			Current->cFunc->rBorder = Current->next->cFunc->rBorder;	
			Liste* toRemove = Current->next;
			Current->next = Current->next->next;
			
			toRemove->next= NULL;	
			delete toRemove;
		} 
		else 
		{
			Current = Current->next;
		}
	}

}
