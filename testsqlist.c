#include "sqlist.h"
#include <stdio.h>

void printList(SqList * L)
{
	for(int i =1; i<= L->length; i++)
		printf("%d: %d\n", i, L->elem[i-1]);

	printf("\n");
}

int main()
{
	SqList L;
	InitList_Sq(&L);
	ListInsert_Sq(&L, 1, 12);
	ListInsert_Sq(&L, 2, 13);
	ListInsert_Sq(&L, 3, 21);
	ListInsert_Sq(&L, 4, 24);
	ListInsert_Sq(&L, 5, 77);
	ListInsert_Sq(&L, 5, 42);
	ListInsert_Sq(&L, 5, 30);
	ListInsert_Sq(&L, 5, 28);

	printList(&L);

	ListInsert_Sq(&L, 5, 25);
	printList(&L);

	printf("delete the 4th ele:\n");

	ElemType e;
	ListDelete_Sq(&L, 4, &e);
	printf("the deleted elem is %d\n", e);
	printf("after delete 4th elem:\n");
	printList(&L);

	while(L.length > 0)
	{
		ListDelete_Sq(&L, 1, &e);
		printf("after delete %d\n", e);
		printList(&L);
	}

	DestroyList_Sq(&L);
}
