# based on CASAL generate.MVU.R 2013-02-19 smormede
# original $Id: generate.MVU.R 1836 2007-12-04 23:29:28Z adunn $
# much simplified as outfile structure different

"generate.MVU"<-
function(file,path="",output.file,sample.size=1)
{
  run<-extract(file,path)
  parbnds<-run$"estimate_summary"[[1]]$data
  rand <- runif(n=sample.size*nrow(parbnds), min=parbnds$lower_bound, max=parbnds$upper_bound*1.0000000000001)
  rand <- matrix(rand,nrow=sample.size,byrow=T)
  colnames(rand)<-parbnds$parameter
  if(!missing(output.file)) {
    outfile <- spm.make.filename(file=output.file,path=path)
    write.table(x=signif(rand,6), file=outfile, append=FALSE,quote=FALSE, sep=" ",row.names=FALSE,col.names=TRUE)
  }
  invisible(list("header"=names(rand),"parameters"=parbnds$value,"bounds"=parbnds[,c("lower_bound","upper_bound")],"MVU"=rand))
}


