\name{fpop_intern}
\alias{fpop_intern}
\title{fpop_intern}
\description{Internal function to call the robust fpop algorithm using
some standard parametrization of the loss function
for now this include the L2 loss (Normal), L1 loss (Laplace), Huber loss and outlier loss
(Note that to be coherent with changepoint the loss corresponds to
the test.stat parameter)
}
\usage{fpop_intern(x, test.stat="Normal", pen.value, lthreshold=NA)}
\arguments{
  \item{x}{A vector of double : the signal to be segmented}
  \item{test.stat}{The assumed test statisticis or distribution. It can be either Normal, Laplace, Huber or Outlier}
  \item{pen.value}{Value of the penalty}
  \item{lthreshold}{threshold parameters for the Huber and Outlier test.stat. By default for Huber we take 1.345
By default for Outlier we take 3}
}

\value{return an object}

\author{Guillem Rigaill}

