#ifndef __SLINKLIST_
#define __SLINKLIST_

#include "dsheader.h"

/*
 *	Static Linked List
 *	Use a header
 * */


#define MAXSIZE 12 //only for test

typedef char ElemType;
typedef int Position;

typedef struct
{
	ElemType 	data;
	Position	cur;
}component, SLinkList[MAXSIZE];

void InitList_SL(SLinkList space);
void ClearList_SL(SLinkList space, Position  *pHead);
int	ListEmpty_SL(SLinkList space, Position head);
int ListLength_SL(SLinkList space, Position head);

Status  GetElem(SLinkList space, Position head, Position i, ElemType *pe); //Get the ith node value
Position LocateElem_SL(SLinkList space, Position head,  ElemType e, int (*compare)(ElemType, ElemType e));

Status PriorElem_SL(SLinkList space, ElemType e, ElemType *pe);
Status NextElem_SL(SLinkList space, ElemType e, ElemType *pe);

Status ListInsertAfter_SL(SLinkList space, Position head, Position p, ElemType e);
void ListDelete_SL(SLinkList space, Position head, ElemType e, int (*compare)(ElemType, ElemType ));

Status ListTraverse_SL(SLinkList space, Position head, int (*visit)(ElemType));

Position FindPrevious_SL(SLinkList space, Position head, ElemType e, int (*cmp)(ElemType, ElemType));


#endif
