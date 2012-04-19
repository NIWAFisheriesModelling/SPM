"PF" <-
function(type="none",x,alpha,...,rescale=T) {
  valid<-c("constant","doublenormal","exponential","inverselogistic","logistic","normal","threshold")
  if(length(type)!=1) stop("Only 1 preference function can be specified")
  type<-valid[pmatch(type,valid)]
  if(type=="") stop(paste("type must be one of",paste(valid,collapse=", "),sep=" "))
  fun<-get(paste("PF",type,sep=""))
  res<-fun(x=x,alpha=alpha,rescale=rescale,...)
  return(res)
}

"PFconstant" <-
function(x,alpha,rescale=T) {
  res<-x^alpha
  if(rescale) res<-res/max(res)
  return(res)
}

"PFdoublenormal" <-
function(x,alpha,mu,sigmaL,sigmaR,rescale=T) {
  pow<-function(x,y) return(x^y)
  res1<-pow(2.0,-((x-mu)/sigmaL * (x-mu)/sigmaL))^alpha
  res2<-pow(2.0,-((x-mu)/sigmaR * (x-mu)/sigmaR))^alpha
  res<-ifelse(x < mu, res1, res2)
  if(rescale) res<-res/max(res)
  return(res)
}

"PFexponential" <-
function(x,alpha,lambda,rescale=T) {
  res<-exp(-lambda * x)^alpha
  if(rescale) res<-res/max(res)
  return(res)
}

"PFinverselogistic" <-
function(x,alpha,a50,ato95,rescale=T) {
  pow<-function(x,y) return(x^y)
  temp<-(a50-x)/ato95
  result<-ifelse(temp > 5.0,0,-1)
  result<-ifelse(temp < -5.0,1,result)
  result[result<0]<-1.0/(1.0+pow(19.0,temp[result<0]))
  result<-(1-result) ^ alpha
  if(rescale) result<-result/max(result)
  return(result)
}

"PFlogistic" <-
function(x,alpha,a50,ato95,rescale=T) {
  pow<-function(x,y) return(x^y)
  temp<-(a50-x)/ato95
  result<-ifelse(temp > 5.0,0,-1)
  result<-ifelse(temp < -5.0,1,result)
  result[result<0]<-1.0/(1.0+pow(19.0,temp[result<0]))
  result<-result ^ alpha
  if(rescale) result<-result/max(result)
  return(result)
}

"PFnormal" <-
function(x,alpha,mu,sigma,rescale=T) {
  pow<-function(x,y) return(x^y)
  res<-pow(2.0,-((x-mu)/sigma * (x-mu)/sigma))^alpha
  if(rescale) res<-res/max(res)
  return(res)
}

"PFthreshold" <-
function(x,alpha,N,lambda,rescale=T) {
  pow<-function(x,y) return(x^y)
  res<-1.0/(pow(x/N,lambda))
  res<-ifelse(x > N, res,1)^alpha
  if(rescale) res<-res/max(res)
  return(res)
}
