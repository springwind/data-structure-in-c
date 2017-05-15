#include "tsmatrix.h"
#include <stdlib.h>
#include <stdio.h>


int
printMatrix(TSMatrix * M)
{
	printf("%d X %d, %d\n", M->mu, M->nu, M->tu);

	int t = 1;
	for(int i=1; i<= M->mu; i++)
	{
		for(int j=1; j<= M->nu; j++)
		{
			if(t <= M->tu && i == M->data[t].i && j == M->data[t].j)
			{
				printf("%8d", M->data[t].e);
				t++;
			}
			else
			{	
				printf("%8d", 0);
			}
		}
		printf("\n");
	}
}

int
transposeMatrix(TSMatrix * M, TSMatrix * T)
{
	T->mu = M->nu; 
	T->nu = M->mu;
	T->tu = M->tu;

	int q = 0;
	for(int j=1; j<= M->nu; j++)
		for(int i=1; i<= M->mu; i++)
		{
			for(int t=1; t<= M->tu; t++)
			{
				if(j == M->data[t].j && i == M->data[t].i)
				{
					T->data[++q].i = M->data[t].j;
					T->data[q].j = M->data[t].i;
					T->data[q].e = M->data[t].e;
				}
			}	
		}
}

int
fastTransposeMatrix(TSMatrix *M, TSMatrix *T)
{
	if(0 == M->tu)
		return -1;

	T->mu = M->nu; 
	T->nu = M->mu;
	T->tu = M->tu;

	int *nums = malloc(sizeof(int) * M->nu);
	int *spots = malloc(sizeof(int) * M->nu);
	
	for(int i = 1; i<= M->nu; i++)
		nums[i] = 0;

	for(int t = 1; t<= M->tu; t++)
	{
		nums[M->data[t].j]++;	
	}
	
	spots[1] = 1;
	for(int col = 1; col <= M->nu; col++)
		spots[col] = spots[col-1] + nums[col-1];

	for(int t = 1; t<= M->tu; t++)
	{
		int i = M->data[t].i;
		int j = M->data[t].j;
		T->data[spots[j]].i = j;
		T->data[spots[j]].j = i;
		T->data[spots[j]].e = M->data[t].e;
		spots[j]++;
	}

	free(nums);
	free(spots);

}

static void
getRowPoses(TSMatrix * M, int * rposes)
{
	int r = 0;
	for(int t = 1; t<= M->tu; t++)
	{
		if(r < M->data[t].i)
		{
			while(++r < M->data[t].i)
				rposes[r] = t;
			rposes[r] = t;
		}
		//else //r == M->data[t].i do nothing
		
	}
	while(++r <= M->tu +1)
		rposes[r] = M->tu + 1;

}

int
matrixMultiply(TSMatrix *M, TSMatrix *N, TSMatrix *Q)
{
	if(0 == M->tu || 0 == N->tu || (M->nu != N->mu))
		return -1;

	Q->mu = M->mu;
	Q->nu = N->nu;
	Q->tu = 0;

	int * rposes1 = malloc(sizeof(int) * M->mu + 2);		
	int * rposes2 = malloc(sizeof(int) * N->mu + 2);

	getRowPoses(M, rposes1);
	getRowPoses(N, rposes2);

	int * ctemp = malloc(sizeof(int) *( N->nu + 1));

	for(int i = 1; i<= M->mu; i++)
	{
		for(int i=1; i<= N->nu; i++)
			ctemp[i] = 0;
		int p2 = rposes1[i+1];
	//	if(i < M->mu)
	//		p2 = rposes1[i+1];
	//	else
	//		p2 = M->tu + 1;

		for(int p= rposes1[i]; p<p2; p++)
		{
			int k = M->data[p].j;
			
			int q2 = rposes2[k+1];
		//	if( k < N->mu)
		//		q2 = rposes2[k+1];
		//	else
		//		q2 = N->tu + 1;

			for(int q = rposes2[k]; q<q2; q++)
			{
				int j = N->data[q].j;
				ctemp[j] += M->data[p].e * N->data[q].e;
			}
		}

		for(int col = 1; col<= N->nu; col++)
		{
			if(ctemp[col] != 0)
			{
				Q->tu++;
				Q->data[Q->tu].i = i;
				Q->data[Q->tu].j = col;
				Q->data[Q->tu].e = ctemp[col];
			}
		}

	}
	
	free(ctemp);
	free(rposes1);
	free(rposes2);
}
