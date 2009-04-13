spm.zeroFun<-function(x,delta=1e-11) {
  if (x>=delta) return(x)
  else return(delta/(2-(x/delta)))
}
