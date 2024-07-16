#include "CSCMatrix.h"

int main(void)
{
	CSCMatrix new_matrix(4, 20);
	new_matrix.saveCSCMatrixAsCSCMatrix("csc_matrix.csv");
	new_matrix.saveCSCMatrixAsStandartMatrix("StandartMatrix.csv");
	return 0;
}