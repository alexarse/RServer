

AverageVector <- function(vec)
{
	dyn.load("lib/RClient.so")
    
    average = 0.0;

	out <- .C("SendVector", 
			  data = vec, 
			  size = as.integer(length(vec)),
			  average = as.double(average))

	return(out$average)
}	
