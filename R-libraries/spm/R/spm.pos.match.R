# $Id: spm.pos.match.R,v 1.2 2007/11/12 21:01:38 adunn Exp $
"spm.pos.match"<-
function(vector, regexp)
{
  min((1:length(vector))[spm.regexpr(regexp, vector) > 0])
}
