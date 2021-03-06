#' Utility extract function
#'
#' @author Alistair Dunn
#'
"extract.derivedquantitybycell" <-
function(lines){
  if(missing(lines)) stop("ERROR: Missing argument lines")
  index.start<-(1:length(lines))[substring(lines,1,1)=="["][1]
  index.end<-(1:length(lines))[substring(lines,1,4)=="*end"][1]
  if(index.start >= index.end) stop("Error")
  res<-list()
  res$label<-substring(lines[index.start],2,nchar(lines[index.start])-1)
  res$report.type<-substring(lines[index.start+1],14)
  res$derived_quantity_by_cell.label<-substring(lines[index.start+2],33)
  res$data<-lines[4:length(lines)]
  return(res)
}
