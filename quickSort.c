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


void insertSort(int a[], int m, int n)
{
	for(int i = m + 1; i<=n; i++)
	{
		int tmp = a[i];
		int j;
		for(j = i -1; j >=m && a[j] > tmp; j--)
			a[j + 1] = a[j];
		a[j + 1] = tmp;
	}
}



int median3(int a[], int left, int right)
{
	//center pos
	int center = (left + right)/2;

	//sort a[left], a[center], a[right]
	if(a[center] < a[left])
		swap(a + center, a + left);
	if(a[right] < a[left])
		swap(a + right, a + left);
	if(a[right] < a[center])
		swap(a + right, a + center);

	//hide pivot
	swap(a + center,  a + right - 1);

	//return pivot
	return a[right - 1];
}


//sort array arr
//use the median of a[left], a[right], a[(left + right)/2] as  pivot
//will stop when elem equal to pivot
void quickSort(int arr[], int left, int right)
{
	static int CUTOFF = 10;

	if(left + CUTOFF < right)
	{
		//partition
		int pivot = median3(arr, left, right);
		int i = left;
		int j = right - 1;
		for(; ;)
		{
			while(arr[++i] < pivot)
				;
			while(arr[--j] > pivot)
				;
			if(i < j)
				swap(arr + i, arr + j);
			else // i>=j
				break;
		}//after for, i>=j, a[left,j]<= pivot, a[i,right] >= pivot

		swap(arr + right - 1, arr + i);//restore pivot

		//sort the smaller part
		quickSort(arr, left, i - 1);
		//sort the larger part
		quickSort(arr, i + 1, right);
	}
	else
	{
		insertSort(arr, left, right);
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
