Rob_seg <- function
### Function calling the fpop algorithm with a loss function of the form
### \gamma(X_i, \mu) = (X-i-\mu)^2 if \mu \in [X_i -lthrs, X_i+rthres]
### \gamma(X_i, \mu) = lslope \mu + la0 if \mu \in ]mini, X_i -lthrs]
### \gamma(X_i, \mu) = rslope \mu + ra0 if \mu \in [X_i +lthrs, maxi]
(x,
### A vector of double : the signal to be segmented
lambda,
### Value of the penalty
lthreshold,
### Value of the left threshold
rthreshold=lthreshold,
### Value of the left slope
lslope=0,
### Value of the left threshold
rslope=-lslope,
### Value of the left threshold
mini=min(x),
### Min value for the mean parameter of the segment
maxi=max(x)
### Max value for the mean parameter of the segment
){
  n <- length(x)
  A <- .C("rob_fpop_RtoC", signal=as.double(x), n=as.integer(n),
		lambda=as.double(lambda),
		lthreshold=as.double(lthreshold), rthreshold=as.double(rthreshold),
		lslope=as.double(lslope), rslope=as.double(rslope),
		min=as.double(mini), max=as.double(maxi),
		path=integer(n), cost=double(n) , mean=double(n), intervals=integer(n)
	, PACKAGE="robseg")
    A$t.est <- getPath(A$path, n)
    A$smt <- rep(A$mean[A$t.est], diff(c(0, A$t.est)))
    ## does not always make sense in particular if L1...
    A$out <- ( (x - A$smt) > A$rthreshold) | ( (x - A$smt) < -A$lthreshold )

    A$K <- length(A$t.est)
    #A$J.est <- getCostRob_Seg(A)
    return(A);
### return a list with a vector t.est containing the position of the change-points
}

getPath <- function
### This function is used by the Rob_seg function to recover the best segmentation from 1:n from the C output
(path,
 ### the path vector of the "Rob_seg" function
 i
 ### the last position to consider in the path vector
){
  chaine <- integer(1)
  chaine[1] <- length(path)
  j <- 2
  while(chaine[j-1] > 0){
    chaine[j] <- path[chaine[j-1]]
    j=j+1
  }
  return(rev(chaine)[-1])
  ### return a vector with the best change-points w.r.t. to L2 to go from point 1 to i
}

