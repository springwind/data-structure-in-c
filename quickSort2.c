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


//use the first element as pivot
//partition array a into two disjoint groups a[m, pivotPos-1], a[piovtPos + 1, n]
//where a[m, pivotPos]<= pivot, a[pivotPos] = pivot, a[pivotPos + 1, n] >= pivot
int partition(int a[], int m, int n)
{
	int low = m;
	int high = n;

	int pivot = a[low]; //use the first element as pivot

	//partition
	while(low < high)
	{
		while(low<high && a[high] >= pivot)//find the last small element
			high --;
		a[low] = a[high];//put the small element in lower part

		while(low < high && a[low] <= pivot) //find the first big element
			low ++;
		a[high] = a[low]; //put the big element in higher part
	}

	//put the pivot at correct place
	a[low] = pivot;

	//return pivot position
	return low;
}



//sort arr[m,n]
void quickSort(int arr[], int m, int n)
{
	if(m < n)
	{
		//divide
		int pivotPos = partition(arr, m, n);

		//conquer
		quickSort(arr, m, pivotPos -1);
		//arr[pivotPos] is in the correct position
		//conquer
		quickSort(arr, pivotPos + 1, n);

	}
	//else there is only one element, done.

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

int find(int arr[], int m, int n, int x)
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
		if(!find(arrSorted, m, n, arr2[i]))
			return 0;
	}
	return 1;
}

void testSort(int arr[], int m, int n)
{
	printf("\noriginal array:----------------------------------------\n:");
	showArr(arr, m, n);

	quickSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	quickSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	reverseArr(arr, m, n);
	printf("\nafter reverse array:\n");
	showArr(arr, m, n);

	quickSort(arr, m, n);
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
		printf("\nsort err.\n");

	testSort(arr, 0, 1);
	if(!checkExist(arr, arrNotSort, 0, 1))
		printf("\nsort err.\n");

	testSort(arr, 0, 11);
	if(!checkExist(arr, arrNotSort, 0, 11))
		printf("\nsort err.\n");


	testSort(arr, N/4, N-1);
	if(!checkExist(arr, arrNotSort, N/4, N-1))
		printf("\nsort err.\n");


	testSort(arr, 0, N - 1);
	if(!checkExist(arr, arrNotSort, 0, N-1))
		printf("\nsort err.\n");


	return 0;
}
