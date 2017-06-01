#include <stdlib.h>
#include <stdio.h>

void showArr2(int arr[], int m, int part, int n)
{
	printf("\n");

	for(int i = m; i<part; i++)
		printf("%d\t", arr[i]);
	printf("[%d]\t", arr[part]);
	for(int i = part + 1; i<= n; i++)
		printf("%d\t", arr[i]);

	printf("\n");

}


void swap(int * a, int * b)
{
	int tmp= *a;
	*a = *b;
	*b = tmp;
}

void merge(int arr[], int tmpArr[], int left, int right, int rightEnd)
{
	//merge arr[left, right] and arr[right + 1, rightEnd] to tmpArr[left, rightEnd];
	int i = left;
	int j = right + 1;
	int k = left;
	while(i <= right && j <= rightEnd)
	{
		if(arr[i] <= arr[j])
			tmpArr[k++] = arr[i++];
		else
			tmpArr[k++] = arr[j++];
	}
	while(i <= right)
		tmpArr[k++] = arr[i++];
	while(j <= rightEnd)
		tmpArr[k++] = arr[j++];

	//copy tmpArr[left, rightEnd] back to arr[left, rightEnd]
	for(k = left; k<= rightEnd; k++)
		arr[k] = tmpArr[k];
}

void MSort(int arr[], int tmpArr[], int m, int n)
{
	if(m < n)
	{
		int mid= (m + n)/2;
		MSort(arr, tmpArr, m, mid);
		MSort(arr, tmpArr, mid + 1, n);
		merge(arr, tmpArr, m, mid, n);
	}
}

void mergeSort(int arr[], int m, int n)
{
	if(m < n)
	{
		int N = n - m + 1;
		int * b= malloc(sizeof(int) * N);

		MSort(arr + m, b, 0, N-1);

		free(b);
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

int binSearch(int arr[], int m, int n, int x)
{
	int low = m;
	int high = n;
	while(low <= high)
	{
		int mid = (low + high)/2;
		if(arr[mid] < x)
			low = mid + 1;
		else if (arr[mid] > x)
			high = mid - 1;
		else
			return 1;
	}
	return 0;
}

int checkExist(int arrSorted[], int arr2[], int m, int n)
{
	for(int i = m; i<=n; i++)
	{
		if(!binSearch(arrSorted, m, n, arr2[i]))
			return 0;
	}
	return 1;
}

void testSort(int arr[], int m, int n)
{
	printf("\noriginal array:----------------------------------------\n:");
	showArr(arr, m, n);

	mergeSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	mergeSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	reverseArr(arr, m, n);
	printf("\nafter reverse array:\n");
	showArr(arr, m, n);

	mergeSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
}

int main()
{
	int N = 100;
	int arr[100];
	for(int i = 0, j = 0; i<N/2; i++, j+= 71)
		arr[i] = j %N;
	for(int i = N/2, j = 0; i<N; i++, j++)
		arr[i] = arr[j];
	int arrNotSort [100];
	for(int i = 0; i<N; i++)
		arrNotSort[i] = arr[i];

	testSort(arr, 0, 0);
	if(!checkExist(arr, arrNotSort, 0, 0))
		printf("\nsort error: lost data.\n");

	testSort(arr, 0, 1);
	if(!checkExist(arr, arrNotSort, 0, 1))
		printf("\nsort error: lost data.\n");

	testSort(arr, 0, 11);
	if(!checkExist(arr, arrNotSort, 0, 11))
		printf("\nsort error: lost data.\n");


	testSort(arr, N/4, N-1);
	if(!checkExist(arr, arrNotSort, N/4, N-1))
		printf("\nsort error: lost data.\n");


	testSort(arr, 0, N - 1);
	if(!checkExist(arr, arrNotSort, 0, N-1))
		printf("\nsort error: lost data.\n");


	return 0;
}
