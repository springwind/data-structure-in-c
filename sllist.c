#include "sllist.h"

#include <stdlib.h>

/*
 * Static Linked List implementations
 *	space[0] : free list head node
 *	list also use a head node
 *
 * */


static Position Malloc_SL(SLinkList space)
{
	Position i = space[0].cur;
	if(i)
		space[0].cur = space[i].cur;
	return i;
}


static void Free_SL(SLinkList space, Position k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

void InitList_SL(SLinkList space)
{
	for(int i = 0; i< MAXSIZE; i++)
		space[i].cur = i+1;
	space[MAXSIZE-1].cur = 0;
}

//make the list empty
void ClearList_SL(SLinkList space, Position  *pHead) 
{
	if(*pHead)
	{
		InitList_SL(space);
	}

	Position L =  Malloc_SL(space);
	space[L].cur = 0;
	*pHead = L;
}

int	ListEmpty_SL(SLinkList space, Position head) 
{
	return 0 == space[head].cur;
}


int ListLength_SL(SLinkList space, Position head) 
{
	int cnt = 0;
	Position p = space[head].cur;

	while(p)
	{
		cnt++;
		p = space[p].cur;
	}

	return cnt;
}

Status GetElem(SLinkList space, Position head, Position i, ElemType *pe)  //Get the ith node value
{
	int j = 1;
	Position p = space[head].cur;
	while(p != 0 && j< i)
	{
		p = space[head].cur;
		j ++;
	}

	if(0 == p || j > i)
		return ERROR;

	*pe = space[p].data;
}

Position LocateElem_SL(SLinkList space, Position head,  ElemType e, int (*compare)(ElemType, ElemType )) 
{
	Position p = space[head].cur;
	while(p && !compare(space[p].data, e))
	{	
		p = space[p].cur;
	}

	return p;
}

/* not implemented yet
Status PriorElem_SL(SLinkList space, ElemType e, ElemType *pe) 
{
	
}

Status NextElem_SL(SLinkList space, ElemType e, ElemType *pe) 
{

}
*/

//insert after legal position p
//p must be legal before calling this fun
Status ListInsertAfter_SL(SLinkList space, Position head, Position p, ElemType e) 
{
	Position q = Malloc_SL(space);
	if(!q)
		return OVERFLOW;

	space[q].data = e;
	space[q].cur = space[p].cur;
	space[p].cur = q;

	return OK;
}

//delete from the list
//
void ListDelete_SL(SLinkList space, Position head, ElemType e, int (*compare)(ElemType, ElemType )) 
{
	Position p = FindPrevious_SL(space, head, e, compare);
	if(space[p].cur) //found e
	{
		Position q = space[p].cur;
		space[p].cur = space[q].cur;
		Free_SL(space, q);
	}
}


Status ListTraverse_SL(SLinkList space, Position head, int (*visit)(ElemType)) 
{
	Position p = space[head].cur;
	while(p)
	{
		visit(space[p].data);
		p = space[p].cur;
	}
}

Position FindPrevious_SL(SLinkList space, Position head, ElemType e, int (*compare)(ElemType, ElemType))
{
	Position p = head;
	Position q = space[p].cur;
	while(q && !compare(space[q].data, e))
	{
		p = q;
		q = space[q].cur;
	}

	return p;
}




