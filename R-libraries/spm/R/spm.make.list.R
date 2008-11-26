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
