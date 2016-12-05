fpop_intern <- structure(function
### internal function to call the robust fpop algorithm using
### some standard parametrization of the loss function
### for now this include the L2 loss (Normal), L1 loss (Laplace), Huber loss and outlier loss
### (Note that to be coherent with changepoint the loss corresponds to
### the test.stat parameter)
(
x,
### A vector of double : the signal to be segmented
test.stat="Normal",
### The assumed test statisticis or distribution. It can be either Normal, Laplace,
### Huber or Outlier
pen.value,
### penalty value
lthreshold=NA
### threshold parameters for the Huber and Outlier test.stat.
### By default for Huber we take 1.345
### By default for Outlier we take 3
){

################################################################################
## provide an lthreshold value if lthreshold value if it is not provided
################################################################################
if(is.na(lthreshold)){
  lthreshold <- switch(test.stat,
                       Laplace = NA,
                       Normal  = NA,
                       Huber   = 1.345,
                       Outlier = 3)
}

################################################################################
## call core fpop function
################################################################################
tmp.res <- switch(test.stat,
           ### Laplace
           Laplace = Rob_seg(x, lambda=pen.value, lthreshold=0, lslope=-1),

           ### Normal
           Normal  = Rob_seg(x, lambda=pen.value, lthreshold=diff(range(x))),

           ### Huber
           Huber   = Rob_seg(x, lambda=pen.value, lthreshold=lthreshold,
                             lslope=-2*lthreshold),

           ### Outlier
           Outlier = Rob_seg(x, lambda=pen.value, lthreshold=lthreshold)
         )

################################################################################
## add some missing argument for changepoints
################################################################################

tmp.res$method <- "rob.fpop"
tmp.res$test.stat <- test.stat
tmp.res$minseglen <- 1
## (Note for the outlier loss the min length depends on the penalty and threshold)

################################################################################
## format the object for changepoint
################################################################################

##
link.param <- matrix(nc=3, byrow=T,
data=c("signal",     "data",         "keep",
  "n",          "n",            "discard",
  "lambda",     "pen.value",    "keep",
  "lthreshold", "lthreshold",   "keep",
  "rthreshold", "rthreshold",   "keep",
  "lslope",     "lslope",       "keep",
  "rslope",     "rslope",       "keep",
  "min",        "min",          "discard",
  "max",        "max",          "discard",
  "path",       "path",         "discard",
  "cost",       "cost",         "keep",
  "mean",       "mean.path",    "discard",
  "t.est",      "cpts",         "keep",
  "smt",        "smt.signal",   "keep",
  "out",        "out.position", "keep",
  "K",          "nb.bkp",       "keep",
  "method",     "method",       "keep",
  "test.stat",  "test.stat",    "keep",
  "minseglen",  "minseglen",    "keep"
  ))

toKeep <- which(link.param[, 3] == "keep")

names(tmp.res)[match(link.param[, 1], names(tmp.res))] <- link.param[, 2]

return(tmp.res)
}, ex=function(){
  x <- c(rnorm(100), rnorm(100)+2)
  std.dev <- mad(diff(x)/sqrt(2))
  x_ <- x/std.dev
  lambda = log(length(x))
  res.l1 <- fpop_intern(x_,  "Laplace", pen.value=lambda)
  res.l2 <- fpop_intern(x_,  "Normal", pen.value=2*lambda)
  res.Hu <- fpop_intern(x_,  "Huber", pen.value=1.4*lambda, lthreshold=1.345)
  res.Ou <- fpop_intern(x_,  "Outlier", pen.value=2*lambda, lthreshold=3)
  plot(x_, pch=20)
  matlines(data.frame(res.l1$smt.signal, res.l2$smt.signal,
                      res.Hu$smt.signal, res.Ou$smt.signal), lty=2, lwd=2)
}
)

