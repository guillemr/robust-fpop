#ifndef ROB_FPOPH
#define ROB_FPOPH

#include "liste.h"

void rob_fpop(const double *profil, const int *nbi, const double *lambda_, 
		const double *lthreshold_, const double *rthreshold_,
		const double *lslope_, const double *rslope_,
		const double *mini, const double *maxi, int *origine, double *cout_n, double *mean_n);
#endif
