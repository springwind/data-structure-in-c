#include "llist.h"
#include <stdio.h>

int printData(ElemType e)
{
	printf("%4d", e);
	return OK;
}

void testInsertDelete()
{
	printf("test list insert and delete:-------------\n");
	LinkList L = NULL;
	InitList_L(&L);

	for(int i = 1; i<10; i++)
	{
		ListInsert_L(L, i, i);
	}

	printf("Get all element:-------------\n");
	for(int i = 1; i<10; i++)
	{
		ElemType e;
		GetElem_L(L, i, &e);
		printf("%d----%4d\n", i, e);
	}

	printf("List traverse:--------------\n");
	ListTraverse_L(L, printData);

	printf("\n");


	for(int i = 9; i>0; i-=2)
	{
		ElemType e;
		ListDelete_L(L, i, &e);
		printf("delete %dth --- %d \n", i, e);
	}
	
	ListTraverse_L(L, printData);
	printf("\n");

	int flag = 1;
	while(flag)
	{
		ElemType e;
		printf("\n");
		ListTraverse_L(L, printData);
		flag = ListDelete_L(L, 1, &e);
	}
			;
	DestroyList_L(L);
}


void testMerge()
{
	printf("test list merge:---------------\n");

	LinkList La = NULL, Lb = NULL;
	InitList_L(&La);
	InitList_L(&Lb);

	int increase1 = 1;
	int increase2 = 1;
	
	for(int i = 1, j = 1; i<50; i+= increase1, j++)
	{
		ListInsert_L(La, j, i);
		increase1 +=2;
	}
	

	for(int i = 1, j = 1; i<100; i+=increase2, j++)
	{
		ListInsert_L(Lb, j, i);
		increase2 += 3;
	}

	printf("La:-------------\n");
	ListTraverse_L(La, printData);
	printf("\n");

	printf("Lb:-------------\n");
	ListTraverse_L(Lb, printData);
	printf("\n");
	
	MergeList_L(La, Lb);
	printf("La after merged with Lb:----------\n");
	ListTraverse_L(La, printData);
	printf("\n");


	DestroyList_L(La);
}
int main()
{
	testMerge();
	testInsertDelete();
}
