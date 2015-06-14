#include <iostream>
#include <vector>
#include "RUtils.h"
#include "kmeans.h"

void CudaKMean(double* data, int* dim, int* nrow, int* ncol, int* nCluster, double* answer);