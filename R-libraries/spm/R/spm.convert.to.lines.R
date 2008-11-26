# $Id: spm.convert.to.lines.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.convert.to.lines"<-
function(filename)
{
# note blank lines are not included - I would rather they were but am not sure how
  scan(filename, what = "", sep = "\n")
}
