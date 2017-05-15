#include "tsmatrix.h"
#include <stdio.h>


static void 
testMatrixMultiply()
{
	TSMatrix M = {{{}, {1, 1, 3}, {1, 4, 5}, {2, 2, -1}, {3, 1, 2}}, 3, 4, 4};
	TSMatrix N = { {{}, {1, 2, 2}, {2, 1, 1}, {3, 1, -2}, {3, 2, 4}}, 4, 2, 4};
	printf("M:\n");
	printMatrix(&M);

	printf("N:\n");
	printMatrix(&N);

	printf("M X N is:\n");
	TSMatrix Q;
	matrixMultiply(&M, &N, &Q);
	printMatrix(&Q);

}
static void
setMatrixData(TSMatrix * M, int t, int i, int j, int e)
{
	M->data[t].i = i;
	M->data[t].j = j;
	M->data[t].e = e;

}

int
testTranspose()
{
	TSMatrix M ={{{}, {1, 2, 12}, {1, 3, 9}, {3, 1, -3}, {3, 6, 14}, {4, 3, 24}, {5, 2, 18}, {6, 1, 15}, {6, 4, -7}}, 6, 7, 8};
	M.mu = 6;
	M.nu = 7;
	int i = 0;
	

	printf("matrix M is:\n");
	printMatrix(&M);

	TSMatrix T;
	transposeMatrix(&M, &T);
	printf("transposed matrix of M is:\n");
	printMatrix(&T);

	TSMatrix T2;
	transposeMatrix(&M, &T2);
	printf("transposed matrix of M is:\n");
	printMatrix(&T2);

}

int
main()
{
	testMatrixMultiply();

	testTranspose();
}
