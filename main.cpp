#include "CSCMatrix.h"

int main(void)
{
	CSCMatrix new_matrix(10000, 0.1);
	new_matrix.saveCSCMatrixAsCSCMatrix("csc_matrix.csv");
	return 0;
}