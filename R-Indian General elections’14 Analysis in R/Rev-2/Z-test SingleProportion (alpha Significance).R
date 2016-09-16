alpha = .05 
z.testalpha = function(alpha){
 z.half.alpha = qnorm(1???alpha/2)
 return(c(???z.half.alpha, z.half.alpha))
}
