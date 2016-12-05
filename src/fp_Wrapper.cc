
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
