skew.test <- function (x) {
  m3 <- sum((x-mean(x))^3)/length(x)
  s3 <- sqrt(var(x))^3
  skew <- m3/s3
  ses <- sqrt(6/length(x))
  totest <- skew/ses
  pt(totest,(length(x)-1))
  pval <- pt(totest,(length(x)-1))
  pval
}