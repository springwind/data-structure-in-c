#include <stdlib.h>
#include <stdio.h>

void shellInsert(int a[], int m, int n, int dk)
{
	for(int i = m + dk; i<=n; i++)
	{
		int tmp = a[i];
		int j;
		for(j = i - dk; j>=m && a[j] > tmp; j-= dk)
			a[j + dk] = a[j];
		a[j + dk] = tmp;
	}
}

//sort arr[m,n]
void shellSort(int a[], int m, int n, int dlta[], int t)
{
	for(int k = 0; k<t; k++)
		shellInsert(a, m, n, dlta[k]);
}

void showArr(int arr[], int m, int n)
{
	int cnt = 0;
	for(int i = m; i<=n; i++)
	{
		if(cnt ++ %10 == 0)
			printf("\n");
		printf("%d\t", arr[i]);
	}
}

void swap(int * a, int * b)
{
	int tmp= *a;
	*a = *b;
	*b = tmp;
}

void reverseArr(int arr[], int m, int n)
{
	int half = (n-m+1)/2;
	for(int i = 0; i<half; i++)
		swap(arr + m + i, arr + n - i);
}

int isNonDecreasing(int arr[], int m, int n)
{
	for(int i = m+1; i<=n; i++)
		if(arr[i] < arr[i-1])
			return 0;
	return 1;
}

void testSort(int arr[], int m, int n, int dlta[], int t)
{
	printf("\noriginal array:----------\n:");
	showArr(arr, m, n);

	shellSort(arr, m, n, dlta, t);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	shellSort(arr, m, n, dlta, t);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	reverseArr(arr, m, n);
	printf("\nafter reverse array:\n");
	showArr(arr, m, n);

	shellSort(arr, m, n, dlta, t);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
}

void main()
{
	int N = 100;
	int arr[100];
	for(int i = 0, j = 0; i<N/2; i++, j+= 71)
		arr[i] = j %N;
	for(int i = N/2, j = 0; i<N; i++, j++)
		arr[i] = arr[j];

	int dlta[5] = {9, 5, 3, 2, 1};
	int dlta2[4] = {40, 13, 4, 1};


	testSort(arr, 0, N/4, dlta, 5);
	testSort(arr, N/4, N-1, dlta, 5);
	testSort(arr, 0, N - 1, dlta2, 4);
}
