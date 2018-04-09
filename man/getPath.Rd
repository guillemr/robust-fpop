\name{getPath}
\alias{getPath}
\title{getPath}
\description{This function is used by the Rob_seg function to recover the best segmentation from 1:n from the C output}
\usage{getPath(path, i)}
\arguments{
  \item{path}{the path vector of the "Rob_seg" function}
  \item{i}{the last position to consider in the path vector}
}

\value{return a vector with the best change-points w.r.t. to L2 to go from point 1 to i}

\author{Guillem Rigaill}





