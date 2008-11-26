# $Id: spm.isin.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.isin"<-
function(x, y)
{
  !is.na(match(x, y))
}
