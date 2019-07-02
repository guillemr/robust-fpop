\name{multiBinSeg}
\alias{multiBinSeg}
\title{multiBinSeg}
\description{Binary segmentation of p profiles using the L2 loss
}
\usage{multiBinSeg(geno, Kmax)}
\arguments{
  \item{geno}{A matrix with p columns and n lines, each column is one of the profile}
  \item{Kmax}{Maximum number of change-points}
}

\value{return a vector of changepoints t.est}

\author{Guillem Rigaill}

