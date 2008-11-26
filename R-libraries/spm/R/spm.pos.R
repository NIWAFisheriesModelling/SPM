# $Id: spm.pos.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.pos"<-
function(vector, x)
{
  min((1:length(vector))[vector == x])
}
