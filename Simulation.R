### variance estimation using MAD or HALL

varDiff <- function(x, method='MAD'){
  n = length(x)
  if(method == "MAD"){
    return(mad(diff(x)/sqrt(2)))
  }
  if(method == "HALL"){
    wei <- c(0.1942, 0.2809, 0.3832, -0.8582)
    mat <- wei %*% t(x)
    mat[2, -n] = mat[2, -1]
    mat[3, -c(n-1, n)] = mat[3, -c(1, 2)]
    mat[4, -c(n-2, n-1, n)] = mat[4, -c(1, 2, 3)]
    return(sqrt(sum(apply(mat[, -c(n-2, n-1, n)], 2, sum)^2) / (n-3)))
  }
}

Simu <- list()

########## SIMU 1
isimu <- 1
Simu[[isimu]] <- list()
Simu[[isimu]]$bkpPage29 <- c(0, c(205, 267, 308, 472, 512, 820, 902, 1332, 1557,
				1598, 1659) - 1, 2048)
Simu[[isimu]]$Lg <- diff(Simu[[isimu]]$bkpPage29)
Simu[[isimu]]$mu <- c(0, 14.64, -3.66, 7.32, -7.32, 10.98, -4.39,
			3.29, 19.03,7.68, 15.37, 0)
Simu[[isimu]]$sigma=10;
Simu[[isimu]]$signal <- rep(Simu[[isimu]]$mu, Simu[[isimu]]$Lg);
Simu[[isimu]]$Ktrue <- sum(diff(Simu[[isimu]]$signal)!=0)+1

########## SIMU 2
isimu <- 2
Simu[[isimu]] <- list()
Simu[[isimu]]$bkpPage29 <-c(0, c(139, 226, 243, 300, 309, 333)-1, 497)
Simu[[isimu]]$Lg <- diff(Simu[[isimu]]$bkpPage29)
Simu[[isimu]]$mu <- c(-0.18, 0.08, 1.07, -0.53, 0.16, -0.69,-0.16)
Simu[[isimu]]$sigma=0.3;
Simu[[isimu]]$signal <- rep(Simu[[isimu]]$mu, Simu[[isimu]]$Lg);
Simu[[isimu]]$Ktrue <- sum(diff(Simu[[isimu]]$signal)!=0)+1

########## SIMU 2'
isimu <- 3
Simu[[isimu]] <- list()
Simu[[isimu]]$bkpPage29 <-c(0, c(139, 226, 243, 300, 309, 333)-1, 497)
Simu[[isimu]]$Lg <- diff(Simu[[isimu]]$bkpPage29)
Simu[[isimu]]$mu <- c(-0.18, 0.08, 1.07, -0.53, 0.16, -0.69,-0.16)
Simu[[isimu]]$sigma= sqrt(0.04);
Simu[[isimu]]$signal <- rep(Simu[[isimu]]$mu, Simu[[isimu]]$Lg);
Simu[[isimu]]$Ktrue <- sum(diff(Simu[[isimu]]$signal)!=0)+1

########## SIMU 3
isimu <- 4
Simu[[isimu]] <- list()
Simu[[isimu]]$bkpPage29 <-c(0, c(11, 21, 41, 61, 91, 121, 161, 201, 251, 301, 361, 421, 491)-1, 560)
Simu[[isimu]]$Lg <- diff(Simu[[isimu]]$bkpPage29)
Simu[[isimu]]$mu <- c(7, -7, 6, -6, 5, -5, 4, -4, 3, -3, 2, -2, 1, -1)
Simu[[isimu]]$sigma=4;
Simu[[isimu]]$signal <- rep(Simu[[isimu]]$mu, Simu[[isimu]]$Lg);
Simu[[isimu]]$Ktrue <- sum(diff(Simu[[isimu]]$signal)!=0)+1


########## SIMU 4
isimu <- 5
Simu[[isimu]] <- list()
Simu[[isimu]]$bkpPage29 <- c(0, c(11, 21, 31, 41, 51, 61, 71, 81, 91, 101, 111, 121, 131)-1, 140)
Simu[[isimu]]$Lg <- diff(Simu[[isimu]]$bkpPage29)
Simu[[isimu]]$mu <- c(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1)
Simu[[isimu]]$sigma=0.4;
Simu[[isimu]]$signal <- rep(Simu[[isimu]]$mu, Simu[[isimu]]$Lg);
Simu[[isimu]]$Ktrue <- sum(diff(Simu[[isimu]]$signal)!=0)+1


########## SIMU 5
isimu <- 6
Simu[[isimu]] <- list()
Simu[[isimu]]$bkpPage29 <-c(0, c(11, 21, 31, 41, 51, 61, 71, 81, 91, 101, 111, 121, 131, 141)-1, 150)
Simu[[isimu]]$Lg <- diff(Simu[[isimu]]$bkpPage29)
Simu[[isimu]]$mu <- c(1:15)
Simu[[isimu]]$sigma=0.3;
Simu[[isimu]]$signal <- rep(Simu[[isimu]]$mu, Simu[[isimu]]$Lg);
Simu[[isimu]]$Ktrue <- sum(diff(Simu[[isimu]]$signal)!=0)+1
########################
