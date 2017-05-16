#ifndef __SQLIST_
#define __SQLIST_

#include "head.h"

#define	LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct{
	ElemType *elem;
	int 	length;
	int 	listsize;
}SqList;

Status InitList_Sq(SqList * L);
void DestroyList_Sq(SqList *L);
Status ListInsert_Sq(SqList * L, int i, ElemType e);
Status ListDelete_Sq(SqList * L, int i, ElemType * e);
void MergeList(SqList * La, SqList * Lb, SqList * Lc);
int LocateElem_Sq(SqList * L, ElemType e);

#endif
