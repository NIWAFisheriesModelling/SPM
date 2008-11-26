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
