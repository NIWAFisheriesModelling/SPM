# Dijkstra's algorithm

base<-matrix(c(1,1,1,1,1,0,1,0,1),ncol=3)
base<-matrix(c(1,1,1,1,1,1,1,1,1),ncol=3)

res<-c()
dNoGo = 10;
dNotAdjacent = 1e10;
dDistanceToSelf = 0;
for(i in 1:nrow(base)) {
  for(j in 1:ncol(base)) {
    iRow = (i * nrow(base)) + j
    for(k in 1:nrow(base)) {
      for(l in 1:ncol(base)) {
        iCol = (k * nrow(base)) + l;
        if(base[i,j]!=0) {
          if(base[k,l]!=0) {
            if(k==(i-1) & l==(j-1)) res<-c(res,sqrt(2))
            else if(k==(i+0) & l==(j-1)) res<-c(res,1)
            else if(k==(i+1) & l==(j-1)) res<-c(res,sqrt(2))
            else if(k==(i-1) & l==(j+0)) res<-c(res,1)
            else if(k==(i+0) & l==(j+0)) res<-c(res,dDistanceToSelf)
            else if(k==(i+1) & l==(j+0)) res<-c(res,1)
            else if(k==(i-1) & l==(j+1)) res<-c(res,sqrt(2))
            else if(k==(i+0) & l==(j+1)) res<-c(res,1)
            else if(k==(i+1) & l==(j+1)) res<-c(res,sqrt(2))
            else res<-c(res,dNotAdjacent)
          } else res<-c(res,dNoGo)
        } else res<-c(res,dNoGo)
      }
    }
  }
}

res<-matrix(res,nrow=length(base),ncol=length(base))

minDistance<-function(vDist, vSptSet) {
   #Initialize min value
   min = 1e100
   minIndex = 0;
   V<-length(vDist)

   for (v in 1:V) {
     if (vSptSet[v] == FALSE && vDist[v] <= min) {
       min = vDist[v]
       minIndex = v
     }
   }
cat(paste(minIndex,"\n"))
   return(minIndex)
}

dijkstra<-function(graph, src) {
  V <- ncol(graph)
  dist<-rep(1e100,ncol(graph)) # The output array.  dist[i] will hold the shortest distance from src to i
  sptSet<-rep(FALSE,ncol(graph)) # sptSet[i] will true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

  # Distance of source vertex from itself is always 0
  dist[src] = 0;

  # Find shortest path for all vertices
  for (i in 1:(V-1)) {
    # Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in first iteration.
    u = minDistance(dist, sptSet);

    # Mark the picked vertex as processed
    sptSet[u] = TRUE;

    # Update dist value of the adjacent vertices of the picked vertex.
    for (v in 1:V) {
      #Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to  v through u is smaller than current value of dist[v]
      if (!sptSet[v] && graph[u,v] && dist[u] != 1e50 && (dist[u]+graph[u,v]) < dist[v]) {
        dist[v] = dist[u] + graph[u,v]
      }
    }
  }
  # print the constructed distance array
  return(list(dist, V))
}

dijkstra(res,1)
matrix(dijkstra(res,1)[[1]],ncol=3,byrow=T)

