Rob_seg.std <- structure(function
### main function to use fpop for L1, L2, Huber and biweight (outlier) losses
(
x,
### A vector of double : the signal to be segmented
loss="L1",
### loss function (L1, L2, Huber and outlier)
lambda,
### penalty value
lthreshold
### for L1 (none), for L2 (none), for Huber typically 1.345 if sd=1, for Outlier typically 3 if sd=1
){

if(loss=="L1"){
  Rob_seg(x, lambda=lambda, lthreshold=0, lslope=-1)-> res
}
if(loss=="L2"){
  Rob_seg(x, lambda=lambda, lthreshold=diff(range(x)))-> res
}

if("Huber" == loss){
  Rob_seg(x, lambda=lambda, lthreshold=lthreshold, lslope=-2*lthreshold) -> res
}

if("Outlier"== loss){
  Rob_seg(x, lambda=lambda, lthreshold=lthreshold) -> res
}

return(res)
}, ex=function(){
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

)
