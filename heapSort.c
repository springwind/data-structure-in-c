#include <stdlib.h>
#include <stdio.h>

void showArr(int arr[], int m, int n)
{
	printf("\n<--------------");
	
	int cnt = 0;
	for(int i = m; i<=n; i++)
	{
		if(cnt ++ %10 == 0)
			printf("\n");
		printf("%d\t", arr[i]);
	}
	printf("\n----------------->\n");
}
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

//arr[0,idx-1] is a max heap
//percolate up arr[idx] to the heap, keeping it a max heap
void percolateUp(int arr[], int idx)
{
	int val = arr[idx];//save the value in position idx

	int hole = idx; 
	int pa = (hole - 1)/2; //parent idx of hole

	while(hole > 0 && arr[pa] < val) //has a parent and bigger than parent. DO NOT use "pa >= 0" instead of "hole > 0, eitherwise  infinite loop
	{
		arr[hole] = arr[pa]; //move parent down to hole
		hole = pa;				//hole upward
		pa = (pa -1 ) /2;
	}

	//place value at hole
	arr[hole] = val;
}

//percolate arr[idx] downside, to make arr[0, lastIdx] a max heap
void percolateDown(int arr[], int lastIdx, int idx)
{
	int val = arr[idx]; //save the value 

	int hole = idx;
	int child = hole * 2 + 1; //left child of hole

	while(child <= lastIdx) //child is still in the reach of the max heap (to be fixed)
	{
		//find bigger child
		if(child + 1 <= lastIdx && arr[child + 1] > arr[child])
			child += 1;

		if(val < arr[child]) //child is bigger, should move child upword
		{
			arr[hole] = arr[child];
			hole = child; //move hole downward
			child = child * 2 + 1; //still left child
		}
		else
		{
			break;
		}
	}

	//place value at hole
	arr[hole] = val;
}

//makes arr[0, n] a max heap
void buildHeap(int arr[], int n)
{
	for(int i = 1; i<=n; i++)
		percolateUp(arr, i);
}

void heapSort(int arr[], int m, int n)
{
	int N = n - m + 1;
	int *p = arr + m;

	//makes arr[m,n] a max heap
	buildHeap(p, N - 1);

	for(int i = N-1; i>0; i--)
	{
		swap(p, p + i); //kick out max value in heap 
		percolateDown(p, i - 1, 0);
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
		{
			printf("error at %d\n", arr2[i]);
			return 0;
		}
	}
	return 1;
}

void testSort(int arr[], int m, int n)
{
	printf("\noriginal array:----------------------------------------\n:");
	showArr(arr, m, n);

	heapSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	heapSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	reverseArr(arr, m, n);
	printf("\nafter reverse array:\n");
	showArr(arr, m, n);

	heapSort(arr, m, n);
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
