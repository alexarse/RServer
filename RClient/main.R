source("r_source/SimpleExample.R")

# value = 89
# vec = matrix(data = c(1, 2, 3, 4, 5, 6), nrow = 2, ncol = 3, byrow = TRUE)
vec = runif(500000, 5.0, 7.5);

ptm <- proc.time()
answer = AverageVector(vec)
tt = proc.time() - ptm

print(answer)
print(tt)

ptm <- proc.time()
answer = mean(vec)
tt = proc.time() - ptm

print(answer)
print(tt)