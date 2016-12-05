/* February 2015 Guillem Rigaill <rigaill@evry.inra.fr> 

   This file is part of the R package Robseg

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


#include "fp_CFunctPart.h"
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

//#include<iostream>
//using namespace std;

void CFunctPart::reset(double cost_, int origine_)
{
		this->origine = origine_;
		this->a2 = 0.;
		this->a1 = 0.;
		this->a0 = cost_;
		this->rac1 = 0.;
		this->rac2 = 0.;
		this->racStatus = 0;
}

bool CFunctPart::addLeft(double lBorder_, double a0_, double a1_){
	if( this->rBorder <= lBorder_){
		a0 = a0 + a0_;
		a1 = a1 + a1_;
		return(true);	
	} 
	else return(false);
}

bool CFunctPart::addCenter(double rBorder_, double a0_, double a1_, double a2_){
	if( this->rBorder <= rBorder_){
		a0 = a0 + a0_;
		a1 = a1 + a1_;
		a2 = a2 + a2_;
		return(true);	
	} 
	else return(false);
}

void CFunctPart::addRight(double a0_, double a1_){
	a0 = a0 + a0_;
	a1 = a1 + a1_;
}

double CFunctPart::min(){
	if((a2 == 0)){
		if(a1 == 0) return(a0);
		else 
		{
			return( ( MIN(lBorder*a1, rBorder*a1) ) + a0); // should not occur
		}
	}
	else 
	{
	   double xMin = - a1/ (2*a2);
	   if( (lBorder <= xMin) & (xMin <= rBorder))
	   {
		return(xMin*(a2*xMin + a1) + a0);
	   }
	   else 
	   {
	   	return( (MIN(lBorder*(a2*lBorder + a1), rBorder*(a2*rBorder + a1))) + a0);
	   }
	}
	
}
double CFunctPart::mean(){

	/*if(a2 == 0) return(lBorder);
	else 
	{
		double xMin = - a1/ (2*a2);
		xMin = MIN( MAX(lBorder, xMin), rBorder) ;
		return(xMin);
	}*/
	
	if(a2 != 0) 
	{
		double xMin = - a1/ (2*a2);
		xMin = MIN( MAX(lBorder, xMin), rBorder) ;
		return(xMin);
	}
	else
	{
		if(a1 >= 0) return(lBorder);
		else return(rBorder);
			
	}
	
}
// either full replace, nothing to do, split left, split right
void CFunctPart::updateRoots(double a0_){
	
		if(a1 == 0) 	
		{	
			if( a0 > a0_)
			{
				rac1 = rBorder;
				rac2 = lBorder;
			}
			else 
			{
				rac1 =lBorder;
				rac2 =rBorder;				
			}
		}
		else 
		{
			// should not occur as adding either a 2nd degree or zer0 degree pol
		}
	
	if(a2 !=0)
	{
		double delta = a1*a1 - 4*a2*(a0-a0_);
		if(delta < 0)	
		{
			rac1 = rBorder;
			rac2 = lBorder;
		} 
		else 
		{
			rac1 = (-a1 - sqrt(delta))/(2*a2);
			rac2 = (-a1 + sqrt(delta))/(2*a2);	
		}
	}
        else 
	{
		if(a1 != 0) 	
		{	
			double intersect = (a0_-a0)/a1;
			if(a1 > 0) 
			{
				rac1 = lBorder;
				rac2 = intersect;	
			}
			else
			{
				rac1 = intersect;
				rac2 = rBorder;	
			}
		}
		else 
		{
			if( a0 > a0_)
			{
				rac1 = rBorder;
				rac2 = lBorder;
			}
			else 
			{
				rac1 =lBorder;
				rac2 =rBorder;				
			}
		}
	}
	
	rac1 = MAX(rac1, lBorder);
	rac2 = MIN(rac2, rBorder);

	if( (rac1 >= rBorder) | (rac2 <= lBorder)  )  racStatus = -1;	// full replace		
	else 
	{
		if( (rac1 == lBorder) & (rac2 == rBorder))  // nothing to do
		{
			rac1 =0.;
			rac2 =0.;
			racStatus = 0; 
		}
		else 	 // split
		{
			racStatus = 1;
		}			
	}			
		
	//cout << "Ori : " << this->origine << ", stat: " << this->racStatus << ", rac1: " << this->rac1 << ", rac2: " << this->rac2 << "poly : " << a2 << "x^2 + " << a1 << "x + " << a0 << "- " << a0_ << "[" << lBorder << "," << rBorder << "]" <<"\n";
}
