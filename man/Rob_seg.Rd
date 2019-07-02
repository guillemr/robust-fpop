\name{Rob_seg}
\alias{Rob_seg}
\title{Rob seg}
\description{Function calling the fpop algorithm with a loss function of the form
\eqn{\gamma(X_i, \mu) = (X-i-\mu)^2} if \eqn{\mu \in [X_i -lthrs, X_i+rthres]}
\eqn{\gamma(X_i, \mu) = lslope \mu + la0} if \eqn{\mu \in ]mini, X_i -lthrs]}
\eqn{\gamma(X_i, \mu) = rslope \mu + ra0} if \eqn{\mu \in [X_i +lthrs, maxi]}}
\usage{Rob_seg(x, lambda, lthreshold, rthreshold = lthreshold, lslope = 0, 
    rslope = -lslope, mini = min(x), maxi = max(x))}
\arguments{
  \item{x}{A vector of double : the signal to be segmented}
  \item{lambda}{Value of the penalty}
  \item{lthreshold}{Value of the left threshold}
  \item{rthreshold}{Value of the left slope}
  \item{lslope}{Value of the left threshold}
  \item{rslope}{Value of the left threshold}
  \item{mini}{Min value for the mean parameter of the segment}
  \item{maxi}{Max value for the mean parameter of the segment}
}

\value{return a list with a vector t.est containing the position of the change-points}

\author{Guillem Rigaill}





