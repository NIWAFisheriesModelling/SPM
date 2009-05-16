is.odd<-function(x) ifelse((x/2) == (x %/% 2), F, T)

hexagon<-function(x,y,len=1) {
  # let the length of one side be lenC = len
  vC <- len
  vA <- 0.5*vC
  vB <- sin(pi/3) * vC
  xpts<-c(0,0,vB,2*vB,2*vB,vB,0)-vB + x
  ypts<-c(vA,vA+vC,vC+2*vA,vA+vC,vA,0,vA)-vC + y
  return(list("x"=x,"y"=y,"xpts"=xpts,"ypts"=ypts,"vA"=vA,"vB"=vB,"vC"=vC))
}

square<-function(x,y,len=1) {
  # let the length of one side be lenC = len
  vA <- len
  xpts<-c(0,0,vA,vA,0)-0.5*vA
  ypts<-c(0,vA,vA,0,0)-0.5*vA
  return(list(x,y,"xpts"=xpts,"ypts"=ypts,vA))
}

hexagon(0,0,1)
square(0,0,1)

par(pty="s")
a1<-hexagon(0,0,1)
a2<-square(0,0,2*a1$vB)
plot(a1$xpts,a1$ypts,type="l",xlim=c(-1.1,1.1),ylim=c(-1.1,1.1))
lines(a2$xpts,a2$ypts)

par(.par)
par(mfrow=c(2,1))
par(pty="s")

plot(0,0,xlim=c(1,14),ylim=c(1,14),type="n",xlab="",ylab="",axes=F)
a1<-hexagon(0,0,1)
for(j in 1:6) {
  for(i in 1:6) {
    if(is.odd(j)) {
      x<-1 + (i * 2 * a1$vB)
      y<-1 + (j * 1.5 * a1$vC)
      lines(a1$xpts + x, a1$ypts + y)
      text(x,y,paste("(",as.character(i),",",as.character(j),")",sep=""))
      #lines(a2$xpts + x, a2$ypts + y,lty=1,col=8)
    } else {
      x<-1 + a1$vB + (i * 2 * a1$vB)
      y<-1 + (j * 1.5 * a1$vC)
      lines(a1$xpts + x, a1$ypts + y)
      text(x,y,paste("(",as.character(i),",",as.character(j),")",sep=""))
      #lines(a2$xpts + x, a2$ypts + y,lty=1,col=8)
    }
  }
}
save("NShexagon.png",dir="",Path="c:\\Projects\\General\\SPM\\doc\\manual\\figures\\",ExportType="png")

