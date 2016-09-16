h -> 12  
t -> 20
p0 = .5                # hypothesized value 

z.test = function(h,t,p0){
  pbar = h/t           # sample proportion 
  n = t                # sample size  
  
  z = (pbar???p0)/sqrt(p0???(1???p0)/n) 
  
  return(z) 
}

