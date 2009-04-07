# $Id: First.lib.R,v 1.3 2007/11/12 21:01:38 adunn Exp $
".First.lib"<-
function(library, section)
{
  spm.version()
}
# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
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
  res<-1.0-(1.0/(1.0+pow(19.0,temp)))
  res<-res^alpha
  if(rescale) res<-res/max(res)
  return(res)
}

"PFlogistic" <-
function(x,alpha,a50,ato95,rescale=T) {
  pow<-function(x,y) return(x^y)
  temp<-(a50-x)/ato95
  res<-1.0/(1.0+pow(19.0,temp))
  res<-res ^alpha
  if(rescale) res<-res/max(res)
  return(res)
}

"PFnormal" <-
function(x,alpha,mu,sigma,rescale=T) {
  pow<-function(x,y) return(x^y)
  res<-pow(2.0,-((x-mu)/sigma * (x-mu)/sigma))^alpha
  if(rescale) res<-res/max(res)
  return(res)
}

"PFthreshold" <-
function(x,alpha,lambda,rescale=T) {
  pow<-function(x,y) return(x^y)
  res<-1.0/(pow(x/N,lambda))
  res<-ifelse(x > N, res,1)^alpha
  if(rescale) res<-res/max(res)
  return(res)
}
# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"calc.abundance" <-
function(data,categories=NULL,ages=NULL,total=T) {
  if(!is.null(categories)) data<-data[data$Category %in% categories,]
  index<-paste(data$Row,data$Col)
  data<-data[,regexpr("Age",names(data))>0]
  Ages<-substring(names(data),5)
  Ages<-as.numeric(substring(Ages,1,nchar(Ages)-1))
  if(!is.null(ages)) {
    data<-data[,Ages %in% ages]
    Ages<-Ages[Ages %in% ages]
  }
  data<-aggregate(data,by=list("index"=index),sum)
  index<-unpaste(data$index,sep=" ")
  Row<-as.numeric(index[[1]])
  Col<-as.numeric(index[[2]])
  if(length(Ages)==1) {
    data$Total<-data[,-1]
  }
  data$Total<-apply(data[,-1],1,sum)
  data$Row<-Row+1
  data$Col<-Col+1
  row.names(data)<-1:nrow(data)
  if(total) return(data[,names(data) %in% c("Row","Col","Total")])
  else return(data)
}
"extract" <-
function(file,path=""){
  if(missing(path)) path<-""
  filename<-spm.make.filename(path=path,file=file)
  line <- scan(filename, what = "", sep = "\n")
  # if a header exists, read it then delete
  res<-list()
  if(substring(line[1],1,3)=="SPM") {
    header<-list()
    header$call<-line[2]
    header$date<-line[3]
    header$version<-line[4]
    header$user.name<-line[5]
    header$machine.name<-line[6]
    res$header<-header
  }
  # which lines are labels of reports?
  index<-(1:length(line))[substring(line,1,1)=="["]
  # get the report label
  report.label<-substring(line[index],2,nchar(line[index])-1)
  # get the report type
  report.type<-substring(line[index+1],13)
  # error check
  if(length(report.label)!=length(report.type)) stop("Error")
  # add the last line of the file to index to assist in tracking reports
  index<-c(index,length(line))
  # create a counter to assist in labelling
  counter<-list("initialisation_phase"=0,"partition"=0,"process"=0,"derived_quantity"=0,"estimate_value"=0,"estimate_summary"=0,"objective_function"=0,"observation"=0,"layer"=0,"selectivity"=0,"random_number_seed"=0,"weight_at_size"=0)

  # iterate through report types and extract values
  for(i in 1:length(report.type)) {
    if(report.type[i]=="initialisation_phase") {
      if(!("initialisation_phase" %in% names(res))) {
        res$"initialisation_phase"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"initialisation_phase"<-counter$"initialisation_phase"+1
      # extract report
      temp<-extract.initialisationphase(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"initialisation_phase"[[counter$"initialisation_phase"]]<-temp
      names(res$"initialisation_phase")[counter$"initialisation_phase"]<-report.label[i]
    }
    if(report.type[i]=="partition") {
      if(!("partition" %in% names(res))) {
        res$"partition"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"partition"<-counter$"partition"+1
      # extract report
      temp<-extract.partition(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"partition"[[counter$"partition"]]<-temp
      names(res$"partition")[counter$"partition"]<-report.label[i]
    }
    if(report.type[i]=="process") {
      if(!("process" %in% names(res))) {
        res$"process"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"process"<-counter$"process"+1
      # extract report
      temp<-extract.process(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"process"[[counter$"process"]]<-temp
      names(res$"process")[counter$"process"]<-report.label[i]
    }
    if(report.type[i]=="derived_quantity") {
      if(!("derived_quantity" %in% names(res))) {
        res$"derived_quantity"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"derived_quantity"<-counter$"derived_quantity"+1
      # extract report
      temp<-extract.derivedquantity(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"derived_quantity"[[counter$"derived_quantity"]]<-temp
      names(res$"derived_quantity")[counter$"derived_quantity"]<-report.label[i]
    }
    if(report.type[i]=="estimate_summary") {
      if(!("estimate_summary" %in% names(res))) {
        res$"estimate_summary"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"estimate_summary"<-counter$"estimate_summary"+1
      # extract report
      temp<-extract.estimatesummary(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"estimate_summary"[[counter$"estimate_summary"]]<-temp
      names(res$"estimate_summary")[counter$"estimate_summary"]<-report.label[i]
    }
    if(report.type[i]=="objective_function") {
      if(!("objective_function" %in% names(res))) {
        res$"objective_function"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"objective_function"<-counter$"objective_function"+1
      # extract report
      temp<-extract.objectivefunction(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"objective_function"[[counter$"objective_function"]]<-temp
      names(res$"objective_function")[counter$"objective_function"]<-report.label[i]
    }
    if(report.type[i]=="observation") {
      if(!("observation" %in% names(res))) {
        res$"observation"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"observation"<-counter$"observation"+1
      # extract report
      temp<-extract.observation(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"observation"[[counter$"observation"]]<-temp
      names(res$"observation")[counter$"observation"]<-report.label[i]
    }
    if(report.type[i]=="layer") {
      if(!("layer" %in% names(res))) {
        res$"layer"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"layer"<-counter$"layer"+1
      # extract report
      temp<-extract.layer(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"layer"[[counter$"layer"]]<-temp
      names(res$"layer")[counter$"layer"]<-report.label[i]
    }
    if(report.type[i]=="selectivity") {
      if(!("selectivity" %in% names(res))) {
        res$"selectivity"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"selectivity"<-counter$"selectivity"+1
      # extract report
      temp<-extract.selectivity(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"selectivity"[[counter$"selectivity"]]<-temp
      names(res$"selectivity")[counter$"selectivity"]<-report.label[i]
    }
    if(report.type[i]=="random_number_seed") {
      if(!("random_number_seed" %in% names(res))) {
        res$"random_number_seed"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"random_number_seed"<-counter$"random_number_seed"+1
      # extract report
      temp<-extract.randomnumberseed(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"random_number_seed"[[counter$"random_number_seed"]]<-temp
      names(res$"random_number_seed")[counter$"random_number_seed"]<-report.label[i]
    }
    if(report.type[i]=="weight_at_size") {
      if(!("weight_at_size" %in% names(res))) {
        res$"weight_at_size"<-list() #create an entry if it doesn't already exist
      }
      # update counter
      counter$"weight_at_size"<-counter$"weight_at_size"+1
      # extract report
      temp<-extract.weightatsize(lines=line[index[i]:(index[i+1]-1)]) # lines from index to the start (-1) of the next report
      # add to results
      res$"weight_at_size"[[counter$"weight_at_size"]]<-temp
      names(res$"weight_at_size")[counter$"weight_at_size"]<-report.label[i]
    }
  }
  return(res)
}
# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.derivedquantity" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  res$data<-NA
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.estimatesummary" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  data<-spm.string.to.vector.of.words(lines[(index.start+2):(index.end-1)],sep=" ")
  data<-matrix(data,ncol=5,byrow=TRUE)
  data<-data[(nrow(data)/2+1):nrow(data),]
  data<-data.frame("parameter"=data[,1],"lower_bound"=as.numeric(data[,2]),"upper_bound"=as.numeric(data[,3]),
                   "prior"=data[,4],"value"=as.numeric(data[,5]))
  res$data<-data
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.initialisationphase" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  col.labs<-spm.string.to.vector.of.words(lines[2+index.start],sep=",")
  values<-spm.string.to.vector.of.words(lines[(3+index.start):(index.end-1)])
  values<-as.data.frame(matrix(values,ncol=length(col.labs),byrow=FALSE))
  names(values)<-col.labs
  values$category<-as.character(values$category)
  values$row<-as.numeric(values$row)
  values$column<-as.numeric(values$column)
  values[,4:ncol(values)]<-apply(values[,4:ncol(values)],2,as.numeric)
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  res$data<-values
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.objectivefunction" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  data<-spm.string.to.vector.of.words(lines[(index.start+2):(index.end-1)],sep=" ")
  data<-matrix(data,ncol=2,byrow=FALSE)
  data<-data.frame("type"=data[,1],"parameter"=data[,1],"value"=as.numeric(data[,2]))
  data$parameter<-as.character(data$parameter)
  tmp<-regexpr("->",data$parameter)
  data$type<-substring(data$parameter,1,tmp-1)
  data$parameter<-substring(data$parameter,tmp+2,nchar(data$parameter)-1)
  res$data<-data
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.observation" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  res$data<-NA
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.partition" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  col.labs<-spm.string.to.vector.of.words(lines[2+index.start],sep=",")
  values<-spm.string.to.vector.of.words(lines[(3+index.start):(index.end-1)])
  values<-as.data.frame(matrix(values,ncol=length(col.labs),byrow=FALSE))
  names(values)<-col.labs
  values$category<-as.character(values$category)
  values$row<-as.numeric(values$row)
  values$column<-as.numeric(values$column)
  values[,4:ncol(values)]<-apply(values[,4:ncol(values)],2,as.numeric)
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  res$data<-values
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.process" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  res$data<-NA
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.randomnumberseed" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  data<-spm.string.to.vector.of.words(lines[(index.start+2):(index.end-1)],sep=" ")
  res$data<-data[2]
  return(res)
}

# $Id: spm.make.filename.R,v 1.3 2007/12/02 21:32:26 adunn Exp $
"extract.selectivity" <-
function(file,path="",lines){
  if(missing(lines)) {
    if(missing(path)) path<-""
    filename<-spm.make.filename(path=path,file=file)
    res<-read.table(filename,skip=1,sep=",",header=T,na.strings="-1.#IND")
  }
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$type<-substring(lines[index.start+1],13)
  data<-spm.string.to.vector.of.words(lines[(index.start+2):(index.end-1)],sep=",")
  data<-matrix(data,ncol=2,byrow=TRUE)
  data<-data.frame("ages"=as.numeric(data[-1,1]),"values"=as.numeric(data[-1,2]))
  res$data<-data
  return(res)
}

# $Id: spm.area.R,v 1.1 2007/11/13 04:32:41 adunn Exp $
"spm.area"<-
function(corners)
{
# Ian Doonan
# Find the area of a polygon
# corners$x,$y corners of polygon
# Area(list(x=c(0,2,3,4,4),y=c(0,2,1,2,0))) -->5
#
  if(length(corners$x) < 3 | length(corners$y) < 3) {
    print("ERROR Area(): need 3 or more points ************")
    return(NULL)
  }
  if(length(corners$x) != length(corners$y)) {
    print("ERROR Area(): points in corners$y not equal to corners$x ************")
    return(NULL)
  }
  TotArea <- 0
  SubArea <- 0
  n <- length(corners$x)
  I0 <- 0
  for(j in c(1:(n))) {
    if(!is.na(corners$y[j]) & !is.na(corners$x[j]) & I0 == 0)
      I0 <- j
  }
  for(j in c(I0:(n))) {
    i <- j
    i1 <- j + 1
    if(i1 > n)
      i1 <- I0
    if(is.na(corners$y[i1]) | is.na(corners$x[i1])) i1 <- I0  # still problems if 2 NA's in a row
    if(!is.na(corners$y[i]) & !is.na(corners$x[i])) {
      SubArea <- SubArea + corners$x[i] * corners$y[i1] - corners$x[i1] * corners$y[i]
    }
    else {
      TotArea <- TotArea + abs(SubArea)
      SubArea <- 0
      I0 <- i1
    }
  }
  TotArea <- (TotArea + abs(SubArea))/2
  return(TotArea)
}
"spm.binary.version"<-
function() {
return("1.00-2009-04-07 (rev. 3098)")
}
# $Id: spm.convert.to.lines.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.convert.to.lines"<-
function(filename)
{
# note blank lines are not included - I would rather they were but am not sure how
  scan(filename, what = "", sep = "\n")
}
# $Id: spm.dplot.R,v 1.2 2007/11/13 04:23:59 adunn Exp $
"spm.dplot"<-
function(..., name=T, quantiles=c(0.5), plot.mean=F, main="", xlab="", ylab="", ylim, srtx=0, bw="nrd0", adjust=1/3, adj=0, fill=F, gap=0.2)
{
  dlines <- function(y, offset, Q, bw, adjust, gap)
  {
    y <- y[!is.na(y)]
    if(min(y) == max(y)) {
      ans <- list(x = min(y), y = 1)
      y1 <- ans$x
      x1 <- ans$y/max(ans$y) * (1-gap)
      q.y1 <- quantile(y, probs = c(0, Q, 1))
      q.x1 <- offset + x1
      q.x2 <- offset
      mean.y1 <- mean(y)
      mean.x1 <- offset + x1
      mean.x2 <- offset
    }
    else {
      ans <- density(y, n = 100, bw=bw, adjust=adjust, from = min(y), to = max(y))
      y1 <- ans$x
      x1 <- ans$y/max(ans$y) * (1-gap)
      q.y1 <- quantile(y, probs = c(0, Q, 1))
      q.x1 <- offset + approx(y1, x1, xout = q.y1)$y
      q.x2 <- offset
      mean.y1 <- mean(y)
      mean.x1 <- offset + approx(y1, x1, xout = mean.y1)$y
      mean.x2 <- offset
      x1<-c(offset,q.x1[1],offset+x1,rev(q.x1)[1],offset)
      y1<-c(q.y1[1],q.y1[1],y1,rev(q.y1)[1],rev(q.y1)[1])
    }
    return(list(x1 =  x1, y1 = y1, q.x1 = q.x1, q.y1 = q.y1, q.x2 = q.x2, mean.x1 = mean.x1, mean.x2 = mean.x2, mean.y1 = mean.y1)
      )
  }
  all.x <- list(...)
  nam <- character(0)
  if(is.list(all.x[[1]])) {
    all.x <- all.x[[1]]
    if(is.logical(name) && name)
      name <- names(...)
  }
  n <- length(all.x)
  centers <- seq(from = 0, by = 1.0, length = n) + 0.1
  ymax <- max(sapply(all.x, max, na.rm = T),na.rm=T)
  if(is.na(ymax)) stop("Error: list of empty vectors")
  ymin <- min(sapply(all.x, min, na.rm = T),na.rm=T)
  xmax <- max(centers) + 0.95
  xmin <- 0
  if(gap>1) gap<-0.2
  if(!missing(ylim)) plot(c(xmin, xmax), c(ymin, ymax), type = "n", main = main, xlab = xlab, ylab = ylab, xaxt = "n", ylim=ylim)
  else plot(c(xmin, xmax), c(ymin, ymax), type = "n", main = main, xlab = xlab, ylab = ylab, xaxt = "n")
  for(i in 1:n) {
    if(length(all.x[[i]][!is.na(all.x[[i]])]) > 0) {
      plot.values <- dlines(all.x[[i]], centers[i], quantiles, bw, adjust, gap)
      if(fill & length(plot.values$x1)>2) polygon(plot.values$x1, plot.values$y1, col=fill)
      lines(plot.values$x1, plot.values$y1)
      segments(centers[i], min(plot.values$y1), centers[i], max(plot.values$y1))
      segments(plot.values$q.x1, plot.values$q.y1, plot.values$q.x2, plot.values$q.y1)
      if(plot.mean)
        segments(plot.values$mean.x1, plot.values$mean.y1, plot.values$mean.x2, plot.values$mean.y1, lwd = 3)
      }
  }
  if(is.logical(name)) {
    if(name)
      axis(1, centers, sapply(substitute(list(...)), deparse)[2:(n + 1)], srt = srtx, adj = if(srtx == 0) adj else 1)
  }
  else axis(1, centers, name, srt = srtx, adj = if(srtx == 0) adj else 1)
  invisible(centers)
}

# $Id: spm.get.lines.R,v 1.3 2007/11/12 21:01:38 adunn Exp $
"spm.get.lines"<-
function(lines, from = -1, to = -1, contains = "", starts.with = "", clip.to = "", clip.from = "", clip.to.match = "", clip.from.match = "", ...)
{
  result <- lines
  if(from > 0) {
    result <- result[(1:length(result)) >= from]
  }
  if(to > 0) {
    result <- result[(1:length(result)) <= to]
  }
  if(clip.to != "") {
    result <- result[(spm.pos(result, clip.to) + 1):length(result)]
  }
  if(clip.from != "") {
    result <- result[1:(spm.pos(result, clip.from) - 1)]
  }
  if(clip.to.match != "") {
    if(spm.regexp.in(result, clip.to.match)) {
      result <- result[(spm.pos.match(result, clip.to.match) + 1):length(result)]
    }
  }
  if(clip.from.match != "") {
    if(spm.regexp.in(result, clip.from.match)) {
      result <- result[1:(spm.pos.match(result, clip.from.match) - 1)]
    }
  }
  if(contains != "") {
    result <- result[spm.regexpr(contains, result) > 0]
  }
  if(starts.with != "") {
    result <- result[spm.regexpr(paste("^", starts.with, sep = ""), result) > 0]
  }
  return(result)
}
# $Id: spm.inR.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.inR"<-
function()
{
  if(!exists("version")) return(F)
  else if(is.null(version$language)) return(F)
  else return(version$language == "R")
}
# $Id: spm.inS.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.inS"<-
function()
{
  !exists("version")
}
# $Id: spm.is.whole.number.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.is.whole.number"<-
function(string)
{
# this function is very dicey - works in its intended context but ...
  for(i in 1:nchar(string)) {
    digit <- substring(string, i, i)
    if(!spm.isin(digit, as.character(0:9))) {
      return(F)
    }
  }
  return(T)
}
# $Id: spm.isin.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.isin"<-
function(x, y)
{
  !is.na(match(x, y))
}
"spm.make.filename" <-
function(file,path="")
{
  if(path != "") {
    plc<-substring(path, nchar(path))
    if(!(plc== "\\" | plc=="/")) path <- paste(path, "/", sep = "")
  }
  filename<-paste(path, file, sep = "")
  return(filename)
}
# $Id: spm.make.list.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.make.list"<-
function(lines)
{
  result <- list()
  for(i in 1:length(lines)) {
    label <- spm.string.to.vector.of.words(lines[i])[1]
    contents <- spm.string.to.vector.of.numbers(spm.remove.first.words(lines[i],1))
    result[[label]] <- contents
  }
  result
}
# $Id: spm.make.table.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.make.table"<-
function(lines)
{
  columns <- spm.string.to.vector.of.words(lines[1])
  if(length(lines) < 2) return(NA)
  data <- matrix(0, length(lines) - 1, length(columns))
  for(i in 2:length(lines)) {
    data[i - 1,  ] <- spm.string.to.vector.of.numbers(lines[i])
  }
  data <- data.frame(data)
  names(data) <- columns
  data
}
# $Id: spm.pos.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.pos"<-
function(vector, x)
{
  min((1:length(vector))[vector == x])
}
# $Id: spm.pos.match.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.pos.match"<-
function(vector, regexp)
{
  min((1:length(vector))[spm.regexpr(regexp, vector) > 0])
}
# $Id: spm.recodevector.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.recodevector"<-
function(in.data, from.vals, to.vals)
{
  data <- in.data
  for(count in 1:length(from.vals)) {
    data[in.data == from.vals[count]] <- to.vals[count]
  }
  return(data)
}
# $Id: spm.remove.first.words.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.remove.first.words"<-
function(string, words = 1)
{
  paste(spm.unpaste(string, sep = " ")[ - (1:words)], collapse = " ")
}
# $Id: spm.remove.last.words.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.remove.last.words"<-
function(string, words = 1)
{
  temp <- spm.unpaste(string, sep = " ")
  to.drop <- length(temp) - (0:(words - 1))
  paste(unlist(temp[ - to.drop]), collapse = " ")
}
# $Id: spm.string.to.vector.of.numbers.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.string.to.vector.of.numbers"<-
function(string,sep=",")
{
  as.numeric(spm.string.to.vector.of.words(string,sep))
}
# $Id: spm.string.to.vector.of.words.R,v 1.3 2007/11/12 21:01:38 adunn Exp $
"spm.string.to.vector.of.words"<-
function(string,sep=",")
{
  temp <- spm.unpaste(string, sep = sep)
  return(temp[temp != ""])
}
# $Id: spm.unpaste.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.unpaste"<-
function(string, sep)
{
  if(spm.inR()) {
    return(unlist(strsplit(string, " ")))
  }
  if(spm.inS()) {
# this code written by Ralph Coburn
    write(string, "unpaste.temp.output")
    scan("unpaste.temp.output", w = "")
  }
  else {
# in S+
    unlist(unpaste(string, sep))
  }
}
# $Id: spm.version.R,v 1.6 2007/11/26 20:40:31 adunn Exp $
"spm.version"<-
function()
{
  cat(paste("spm R package for use with spm ",spm.binary.version(),"\n",sep=""))
}
spm.zeroFun<-function(x,delta=1e-10) {
  if (x>=delta) return(x)
  else return(delta/(2-(x/delta)))
}
