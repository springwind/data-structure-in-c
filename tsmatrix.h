#ifndef __TMATRIX
#define __TMATRIX

#define MAXSIZE 12500

typedef int ElemType;

typedef struct
{
	int		i, j;
	ElemType e;
}Triple;


typedef struct{
	Triple 	data[MAXSIZE+1]; //data[0] not used
	int			mu,nu,tu;
}TSMatrix;

int printMatrix(TSMatrix *M);
int transposeMatrix(TSMatrix *M, TSMatrix * T);
int fastTransposeMatrix(TSMatrix *M, TSMatrix *T);
int matrixMultiply(TSMatrix *M, TSMatrix *N, TSMatrix *Q);


#endif
