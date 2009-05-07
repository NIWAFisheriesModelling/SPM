"spm.pos.match"<-
function(vector, regexp)
{
  min((1:length(vector))[spm.regexpr(regexp, vector) > 0])
}
