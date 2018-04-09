\name{Rob_seg.std}
\alias{Rob_seg.std}
\title{Rob seg std}
\description{main function to use fpop for L1, L2, Huber and biweight (outlier) losses}
\usage{Rob_seg.std(x, loss = "L1", lambda, lthreshold)}
\arguments{
  \item{x}{A vector of double : the signal to be segmented}
  \item{loss}{loss function (L1, L2, Huber and outlier)}
  \item{lambda}{penalty value}
  \item{lthreshold}{for L1 (none), for L2 (none), for Huber typically 1.345 if sd=1, for Outlier typically 3 if sd=1}
}



\author{Guillem Rigaill}




\examples{
x <- c(rnorm(100), rnorm(100)+2)
std.dev <- mad(diff(x)/sqrt(2))
x_ <- x/std.dev
lambda = log(length(x))
res.l1 <- Rob_seg.std(x_,  "L1", lambda=lambda)
res.l2 <- Rob_seg.std(x_,  "L2", lambda=2*lambda)
res.Hu <- Rob_seg.std(x_,  "Huber", lambda=1.4*lambda, lthreshold=1.345)
res.Ou <- Rob_seg.std(x_,  "Outlier", lambda=2*lambda, lthreshold=3)
plot(x_, pch=20)
matlines(data.frame(res.l1$smt, res.l2$smt, res.Hu$smt, res.Ou$smt), lty=2, lwd=2)
}
