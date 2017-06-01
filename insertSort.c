#include <stdlib.h>
#include <stdio.h>

//print arr[m,n]
void showarr(int arr[], int m, int n)
{
	int cnt = 0;
	for(int i = m; i<=n; i++)
	{
		if(cnt++ %10 == 0)
			printf("\n");
		printf("%d\t", arr[i]);

	}
	printf("\n");
}

void swap(int * a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void reverseArray(int arr[], int m, int n)
{
	int half = (n-m+1)/2;
	for(int i = 0; i<half; i++)
		swap(arr + m + i, arr + n - i);
}


int checkNonDecreasing(int arr[], int m, int n)
{
	for(int i = m; i<n; i++)
		if(arr[i] > arr[i + 1])
			return 0;

	return 1;
}

//sort arr[m, n]
void insertSort(int a[], int m, int n)
{
	for(int i = m + 1; i<= n; i++)
	{
		int tmp = a[i];
		int j;
		for(j = i - 1; j >=m && a[j] > tmp; j--)
			a[j + 1] = a[j];
		//after for, a[j] <=tmp or j < m

		a[j + 1] = tmp;
	}
}

void testInsertSort(int arr[], int m, int n)
{

	insertSort(arr, m, n);

	printf("\nafter insert sort:\n");
	showarr(arr, m, n);
	if(!checkNonDecreasing(arr, m, n))
		printf("\n not nondecreasing .\n");

	insertSort(arr, m, n);

	printf("\nafter insert sort 2nd:\n");
	showarr(arr, m, n);
	if(!checkNonDecreasing(arr, m, n))
		printf("\n not nondecreasing .\n");


	reverseArray(arr, m, n);

	printf("\nafter reverse array:\n");
	showarr(arr, m, n);

	insertSort(arr, m, n);
	
	printf("\nafter insert sort:\n");
	showarr(arr, m, n);
	if(!checkNonDecreasing(arr, m, n))
		printf("\n not nondecreasing .\n");


}

void main()
{
	int N = 100;
	int arr[100];
	for(int i = 0, j = 0; i<N; i++, j+=71)
		arr[i] = j %N;

	printf("\noriginal array:-------------\n");
	showarr(arr, 0, N-1);

	testInsertSort(arr, 0, N/2);
	testInsertSort(arr, N/2+1, N-1);
	testInsertSort(arr, 0, N-1);
}
