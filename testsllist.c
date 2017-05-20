#include "sllist.h"

#include <stdio.h>

/*
 *	Test static linked list
 *
 * */

int printData(ElemType e)
{
	printf("%2c", e);

}


int cmp(ElemType e1, ElemType e2)
{
	return e1 == e2;

}


/*
 *	(A-B) U (B - A)
 * */
void difference(SLinkList space, Position * pHead)
{
	InitList_SL(space);
	ClearList_SL(space, pHead);

	Position S = *pHead;

	int m = 0, n = 0;
	printf("enter number of set A:\n");
	scanf("%d", &m);

	printf("enter number of set B:\n");
	scanf("%d", &n);
	
	printf("m = %2d, n = %2d\n", m, n);

	printf("enter elements of set A:\n");
	for(int j = 1; j<=m; j++)
	{
		ElemType e;
		scanf("%c", &e);
		while(e < 'a' || e > 'z')
			scanf("%c", &e);
		
		ListInsertAfter_SL(space, S, S, e);
	}

	printf("now the list is like:\n");
	ListTraverse_SL(space, S, printData);
	printf("\n");

	printf("enter elements of set B:\n");
	for(int j = 1; j<= n; j++)
	{
		ElemType e;
		scanf("%c", &e);
		while(e < 'a' || e > 'z')
		{
			scanf("%c", &e);
		}
		
		if(LocateElem_SL(space, S, e, cmp))
			ListDelete_SL(space, S, e, cmp);
		else
			ListInsertAfter_SL(space, S, S, e);
	}

	printf("now the list is like:\n");
	ListTraverse_SL(space, S, printData);

	printf("\n");
}


int main()
{
	SLinkList space;
	Position S;
	difference(space, &S);
}
