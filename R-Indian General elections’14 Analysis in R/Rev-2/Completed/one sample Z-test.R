a = c(65, 78, 88, 55, 48, 95, 66, 57, 79, 81)

z.test = function(a, mu, var){
  zeta = (mean(a) - mu) / (sqrt(var / length(a)))
  return(zeta)
}

