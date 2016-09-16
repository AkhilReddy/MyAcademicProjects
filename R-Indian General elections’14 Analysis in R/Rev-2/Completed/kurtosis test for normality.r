kurtosis.test <- function (x) {
  m4 <- sum((x-mean(x))^4)/length(x)
  s4 <- var(x)^2
  kurt <- (m4/s4) - 3
  sek <- sqrt(24/length(x))
  totest <- kurt/sek
  pvalue <- pt(totest,(length(x)-1))
  pvalue 
}

