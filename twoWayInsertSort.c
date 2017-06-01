#include <stdlib.h>
#include <stdio.h>

//sort arr[m,n]
void twoWayInsertSort(int a[], int m, int n)
{
	int N = n - m + 1;

	//auxiliary array
	int *b = malloc(sizeof(int ) * N);

	//put a[m] in b at [0]
	b[0] = a[m];
	int first = 0;
	int final = 0;

	//insert a[m+1, n] into b one by one
	for(int i = m+1; i<=n; i++)
	{
		if(a[i] < b[0])
		{
			if(0 == first)
			{
				b[N - 1] = a[i];
				first = N - 1;
			}
			else
			{
				int low = first;
				int high = N - 1;
				while(low <= high)
				{
					int mid = (low + high)/2;
					if(b[mid] < a[i])
						low = mid + 1;
					else //b[mid] >= a[i]
						high = mid - 1;
				}//after while, b[first, high] < a[i], b[low, N - 1] >= a[i]

				//shift b[first, high] left by one position
				for(int j = first; j<= high; j++)
					b[j - 1] = b[j];

				//put a[i] at [high]
				b[high] = a[i];
				first --;
			}
		}
		else
		{
			int low = 0;
			int high = final;
			while(low <= high)
			{
				int mid = (low + high)/2;
				if(b[mid] <= a[i])
					low = mid + 1;
				else
					high = mid -1;
			}//after while, b[0, high] <= a[i], b[low, final] > a[i]
			
			//shift b[low, final] right by one position
			for(int j = final; j>= low; j--)
				b[j + 1] = b[j];
			b[low] = a[i];
			final ++;
		}
	}

	//copy b to a
	int j = m;
	if(0 == first)
	{
		for(int i = 0; i < N; i++)
			a[j++] = b[i];
	}
	else
	{
		for(int i = first; i<N; i++)
			a[j++] = b[i];
		for(int i = 0; i<= final; i++)
			a[j++] = b[i];
	}

	//free auxiliary array
	free(b);
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

	twoWayInsertSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	twoWayInsertSort(arr, m, n);
	printf("\nafter sort:\n");
	showArr(arr, m, n);
	if(isNonDecreasing(arr, m, n))
		printf("sorted.\n");
	else
		printf("NOT sorted!!!\n");
	
	reverseArr(arr, m, n);
	printf("\nafter reverse array:\n");
	showArr(arr, m, n);

	twoWayInsertSort(arr, m, n);
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

//	testSort(arr, 0, N/4);
//	testSort(arr, N/4, N-1);
	testSort(arr, 0, N - 1);
}
