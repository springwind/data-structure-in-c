#include <stdlib.h>
#include <stdio.h>

//sort arr[m,n]
void binInsertSort(int arr[], int m, int n)
{
	//arr[m, i-1] sorted, arr[i, n] unsorted, insert arr[i] in the proper position
	for(int i = m + 1; i<=n; i++)
	{
		int tmp = arr[i];

		//find the position in [m, i-1] to put arr[i]
		int low = m;
		int high = i - 1;
		while(low <= high)
		{
			int mid = (low + high)/2;
			if(arr[mid] <= tmp)
				low = mid + 1;
			else
				high = mid - 1;
		}
		//after while, arr[m, high] <= tmp, arr[high + 1, i-1] >tmp

		//shift arr[high+1, i-1] right by one position
		for(int j = i-1; j > high; j--)
			arr[j+1] = arr[j];

		//put tmp in position high + 1;
		arr[high + 1] = tmp;
	}
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

void testSort(int arr[], int m, int n)
{
	printf("\noriginal array:----------\n:");
	showArr(arr, m, n);

	binInsertSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	binInsertSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	reverseArr(arr, m, n);
	printf("\nafter reverse array:\n");
	showArr(arr, m, n);

	binInsertSort(arr, m, n);
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
	for(int i = 0, j = 0; i<N; i++, j+= 71)
		arr[i] = j %N;

	testSort(arr, 0, N/4);
	testSort(arr, N/4, N-1);
	testSort(arr, 0, N - 1);
}
