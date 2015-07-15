### Run these two functions before we can run the Dijkstra algorithm
######################### Takes the base layer and a distance matrix with a cell and looks at adjacent cells
## This sets up the next candidate moves
## Aim of this algorithm is to get reliable distance from a source cell to a target cell taking into account going around land
## This assumes that Fish know where land is and actively avoid it. 

## Question is it better(Computationally faster) to calculate the distance from a source cell to every other cell
## or should I just get the algorithm to terminate after a specific target cell has been reached.

Look_around<- function(Graph,distance_mat,long_mat,lat_mat, i, j) 		## This assuming there exists a lat and a long mat and a distance mat
		{
			Daughter_nodes<- vector()
			index = 1
				iHeight <- nrow(Graph)										## Calculate dimensions
				iWidth <- ncol(Graph)
				## If this is a true origin node then look around at adjacent nodes
			
				if((!((i - 1) <=0)) & !((i-1) > iHeight) )	## Look up
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i-1),j],lat_mat[(i-1),j])) < distance_mat[i-1,j] & !(Graph[(i-1),j] ==0) )
					{
						distance_mat[(i-1),j]  <- (distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i-1),j],lat_mat[(i-1),j]))
						Daughter_nodes[index]<- paste((i-1),j,sep=",")
						index<- index+1
					}
				}
				if(!((i + 1) <=0) & !((i+1) > iHeight))	## Look down
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i+1),j],lat_mat[(i+1),j])) < distance_mat[(i+1),j] & !(Graph[(i+1),j] ==0))
					{
						distance_mat[(i+1),j]  <- (distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i+1),j],lat_mat[(i+1),j]))
						Daughter_nodes[index]<- paste((i+1),j,sep=",")
						index<- index+1
					}
				}
				if(!((j + 1) <=0) & !((j +1 ) > iWidth))	## Look right
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[i,(j+1)],lat_mat[i,(j+1)])) < distance_mat[i,(j+1)] & !(Graph[i,(j+1)] ==0))
					{
						distance_mat[i,(j+1)]  <- (distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[i,(j+1)],lat_mat[i,(j+1)]))
						Daughter_nodes[index]<- paste(i,(j+1),sep=",")
						index<- index+1
					}
				}
				if((!((j - 1) <=0) & !((j - 1) > iWidth)))	## Look left
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[i,(j-1)],lat_mat[i,(j-1)])) < distance_mat[i,(j-1)] &  !(Graph[i,(j - 1)] ==0))
					{
						distance_mat[i,(j-1)]  <- (distance_mat[i,j] +gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[i,(j-1)],lat_mat[i,(j-1)]))	
						Daughter_nodes[index]<- paste(i,(j-1),sep=",")
						index<- index+1								

					}
				}
				## Now for the diagonal moves

				if(!((j - 1) <=0) & !((i - 1) <=0) & !((j - 1) > iWidth) & !((i - 1) > iHeight))				## Look up and to the left
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i-1),(j-1)],lat_mat[(i-1),(j-1)])) < distance_mat[(i-1),(j-1)] &  !(Graph[(i-1),(j - 1)] ==0))
					{
						distance_mat[(i-1),(j-1)]  <- (distance_mat[i,j] +gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i-1),(j-1)],lat_mat[(i-1),(j-1)]))
						Daughter_nodes[index]<- paste((i-1),(j-1),sep=",")
						index<- index+1								

					}
				}



				if(!((j + 1) <=0) & !((i - 1) <=0) & !((j + 1) > iWidth) & !((i - 1) > iHeight))				## Look down and to left
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i-1),(j+1)],lat_mat[(i-1),(j+1)])) < distance_mat[(i-1),(j+1)] &  !(Graph[(i-1),(j + 1)] ==0))
					{
						distance_mat[(i-1),(j+1)]  <- (distance_mat[i,j] +gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i-1),(j+1)],lat_mat[(i-1),(j+1)]))	
						Daughter_nodes[index]<- paste((i-1),(j+1),sep=",")
						index<- index+1									

					}
				}

				if(!((j + 1) <=0) & !((i + 1) <=0) & !((j + 1) > iWidth) & !((i + 1) > iHeight))				## Look down and to right
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i+1),(j+1)],lat_mat[(i+1),(j+1)])) < distance_mat[(i+1),(j+1)] &  !(Graph[(i+1),(j + 1)] ==0))
					{
						distance_mat[(i+1),(j+1)]  <- (distance_mat[i,j] +gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i+1),(j+1)],lat_mat[(i+1),(j+1)]))
						Daughter_nodes[index]<- paste((i+1),(j+1),sep=",")
						index<- index+1										

					}
				}

				if(!((j - 1) <=0) & !((i + 1) <=0) & !((j - 1) > iWidth) & !((i + 1) > iHeight))				## Look up and to right
				{
				## Valid node calculate distance store it, save whether it has been visited.
					if((distance_mat[i,j] + gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i+1),(j-1)],lat_mat[(i+1),(j-1)])) < distance_mat[(i+1),(j-1)] &  !(Graph[(i+1),(j - 1)] ==0))
					{
						distance_mat[(i+1),(j-1)]  <- (distance_mat[i,j] +gcd.hf(long_mat[i,j],lat_mat[i,j],long_mat[(i+1),(j-1)],lat_mat[(i+1),(j-1)]))	
						Daughter_nodes[index]<- paste((i+1),(j-1),sep=",")
						index<- index+1									

					}
				}
		list(Daughter_nodes,distance_mat)
		}




############ Geodetic function ################### This calculates the distance between two co-ordinates in latitude 
##and longitude calculating distance in kilometers
# Convert degrees to radians
deg2rad <- function(deg) return(deg*pi/180)


# Calculates the geodesic distance between two points specified by radian latitude/longitude using the
# Haversine formula (hf)
gcd.hf <- function(long1, lat1, long2, lat2) {
  long1 <- deg2rad(long1)
  lat1 <- deg2rad(lat1)
  long2 <- deg2rad(long2)
  lat2 <- deg2rad(lat2)
  R <- 6371 # Earth mean radius [km]
  delta.long <- (long2 - long1)
  delta.lat <- (lat2 - lat1)
  a <- sin(delta.lat/2)^2 + cos(lat1) * cos(lat2) * sin(delta.long/2)^2
  c <- 2 * asin(min(1,sqrt(a)))
  d = R * c
  return(d) # Distance in km
}





############## Dijstra's Algorithm #########################
## My example has a base layer 5*5	########################
############################################################


DJ<- function(base_layer,lat.mat,long.mat,source_row,source_col)
{
	iHeight <- nrow(base_layer)										## Calculate dimensions
	iWidth <- ncol(base_layer)
	INF<- 9999999											## Define infinity
	## Find candidate nodes
	## Create an empty strucutre that can handle two integers
	nodes_unvisited<- vector()	
	index= 1
	for(i in 1:iHeight)
	{
		for ( j in 1: iWidth)
		{
			if(base_layer[i,j]==1)
			{
				nodes_unvisited[index]<- paste(i,j,sep=",")
				
				index<- index+1
			}
		}
	}


	i=source_row
	j=source_col
	Distance_mat<- matrix(INF, iHeight, iWidth)						## Create a distance matrix where all nodes are unvisited
	if(!(base_layer[i,j] == 1))
	{stop("Your source node is not a true node check base layer")}						## Finding starting node
	Distance_mat[i,j] = 0							## Initialise starting node to have cumulative distance = zero


	## Ths is the actual Algorithm, Which pretty much says that starting at one cell look around assign the shortest distance to adjacent cells
	## Now that the shortest path has been reached to those adjacent cells. Make them become the source cells and assign the shortest path 
	## To its adjacent cells. Each time removing the source cell from a character vector that lists unvisited nodes. keep iterating
	## Unill all nodes have been reached. This will create the shortest path from a source cell to all other cells due to the accumulation of
	## Distamce functions along the algorithm

	src_cell<- paste(i,j,sep=",")				## Give it the source node
	while(length(nodes_unvisited) > 0)
	{
		daughter_nodes<- vector()		## Create an empty vector to store daughter nodes
		for ( k in 1:length(src_cell))	## For all source cells 
		{
		## Once we have identified our source cells move out of our unvisited nodes vector
		nodes_unvisited<- nodes_unvisited[!(nodes_unvisited==src_cell[k])]	## remove current cell from nodes_unvisited
		## now inspect this element calculate distances and output daughter nodes
		check<- Look_around(base_layer,distance_mat=Distance_mat,lat_mat=lat.mat,long_mat=long.mat,as.numeric(unlist(strsplit(src_cell[k],split=","))[1]),as.numeric(unlist(strsplit(src_cell[k],split=","))[2]))	## Look around source cell output surounding nodes
		daughter_nodes1<- check[[1]]
		Distance_mat<- check[[2]]
		## This will output a vector of daughter cells for each i in src cell so I need to concatenate all these daughtet nodes for potentially 
		## Multiple src cells at that move
		daughter_nodes<- c(daughter_nodes,daughter_nodes1)
		} 
		src_cell<- daughter_nodes		## Make the daughter cells of that iteration the source cells of the next iteration.

	}
	return(Distance_mat)
}
 



############# An example


### With an Island

base4<- matrix(rep(1,26*31), 26,31)
## Turn off cells to create an island
base4[9:20,7:10] <- 0
base4
## Note that this is a square matrix SPM will only accept rectangle 
## Base layers but I am assuming this will work for all dimensions
long_mid<- 160.5:190.5
lat_mid <- -54.5:-29.5
lat_mat3 <-  matrix(sort(rep(lat_mid,31),decreasing = TRUE),26,31,byrow=T)
## I think the Haversine function that I have stolen only works for the longitudes -180 - 180 so convert our long matrix
long_mat3 <- matrix(sort(rep(long_mid,26)),26,31)


## Run it for this example
round(DJ(base_layer= base4, lat.mat=lat_mat3, long.mat= long_mat3, source_row=1,source_col=1),1)


