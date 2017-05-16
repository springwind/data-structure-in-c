#include "sqlist.h"
#include <stdlib.h>

Status InitList_Sq(SqList * L)
{
	L->elem = malloc(sizeof(ElemType) * LIST_INIT_SIZE);
	if(!L->elem)
		exit(OVERFLOW);

	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}

void DestroyList_Sq(SqList *L)
{
	if(L)
		free(L->elem);
}

/*
 *	1<=i<=ListLength_Sq(L) + 1
 * */
Status ListInsert_Sq(SqList * L, int i, ElemType e)
{
	if(i<1 || i > L->length + 1)
		return ERROR;

	if(L->length == L->listsize)
	{
		ElemType * newbase = realloc(L->elem, sizeof(ElemType) * (L->listsize + LISTINCREMENT));
		if(!newbase)
			exit(OVERFLOW);
		L->elem = newbase;
		L->listsize += LISTINCREMENT;		
	}

	ElemType * q = &(L->elem[i-1]);
	for(ElemType *p = L->elem + L->length -1; p>= q; p--)
		*(p+1) = *p;
	
	*q = e;
	L->length ++;

	return OK;
}

/*	1<= i <= ListLength_Sq(L)
 *	
 * */
Status ListDelete_Sq(SqList *L, int i, ElemType *e)
{
	if ( i<1 || i> L->length)
		return ERROR;

	ElemType *p = L->elem + (i-1);
	*e = *p;

	ElemType *q = L->elem + (L->length -1);
	for(++p; p<=q; ++p)
		*(p - 1) = *p;

	L->length --;

	return OK;
}


int LocateElement(SqList *L, ElemType e)
{
	int i = 1;
	ElemType * p = L->elem;
	while( i<= L->length && *p !=e)
		i++;
	if(i <= L->length)
		return i;
	return 0;
}

void MergeList(SqList *La, SqList * Lb, SqList * Lc)
{
	ElemType * pa = La->elem;
	ElemType * pb = Lb->elem;

	Lc->listsize = Lc->length = La->length + Lb->length;

	Lc->elem = malloc(sizeof(ElemType) * Lc->listsize);
	if(!Lc->elem)
		exit(OVERFLOW);

	ElemType * pc = Lc->elem;
	
	ElemType * pa_last = La->elem + La->length -1;
	ElemType * pb_last = Lb->elem + Lb->length -1;
	while(pa <= pa_last && pb <= pb_last)
	{
		if(*pa <= *pb)
		{
			*pc ++ = *pa ++;
		}
		else
		{
			*pc ++ = *pb ++;
		}
	}

	while( pa <= pa_last)
		*pc ++ = *pa ++;
	while( pb <= pb_last)
		*pc ++ = *pb ++;
}

