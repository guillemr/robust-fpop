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
#ifndef LISTEH
#define LISTEH
#include "CFunctPart.h"



class Liste {
public:
  CFunctPart *cFunc;
  Liste *next;
  /* constructors and destructors */
  Liste()
  : next(NULL), cFunc(NULL) {}
  Liste(Liste *next_, CFunctPart* cFunc_)
  : next(next_), cFunc(cFunc_) {}
  Liste(CFunctPart* cFunc_)
  : next(NULL), cFunc(cFunc_) {}
  ~Liste(){
    if(next != NULL) delete next;
    delete cFunc;
  }

  // Compute Min taking into account boundaries
  void getMin(double *min_, int *origine_, double *mean_);
  //void getMean(double *min_, int *origine_, double *mean_);
  // add a new data point (leads to potential new elements...)
  void add(double X_, double lthrs_, double rthres_, double lslope, double rslope);
  // compare to a new candidate (leads to potential new elements ...)
  void compare(double cost_, int origine_);
  // 
  void mergeSimilarElements();
};
#endif //INLINED

