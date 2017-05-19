#include "llist.h"
#include <stdlib.h>

struct LNode{
	ElemType data;
	struct LNode * next;
};


typedef struct LNode * Position;

Status InitList_L(LinkList *pL)
{
	LinkList L = *pL;
	if(L)
		DestroyList_L(L);

	L = malloc(sizeof(struct LNode));

	if(!L)
		return OVERFLOW;

	L->next = NULL;
	
	*pL = L;
	return OK;
}

void DestroyList_L(LinkList L)
{
	while(L)
	{
		Position next = L->next;
		
		free(L);
		L = next;
	}
}

Status ListInsert_L(LinkList L, int i, ElemType e)
{
	Position p = L;
	int j = 0;
	
	//find prev node of the ith node
	while(p && j<i-1)
	{
		p= p->next;
		j++;
	}

	if(!p || j>i-1) //when i > L's length + 1 or i <1
	{
		return ERROR;
	}

	Position q = malloc(sizeof(struct LNode));
	if(!q)
		return OVERFLOW;

	q->data = e;

	//insert q after p
	q->next = p->next;
	p->next = q;

	return OK;
}

// delete the ith node
// i <= L's length and i>=1
Status ListDelete_L(LinkList L, int i, ElemType *pe)
{
	Position p ;
	int j;

	//find  the prev node of the ith node
	p = L;
	j = 0;

	while(p->next && j < i-1)
	{
		p = p->next;
		j ++;
	}

	if(!p->next || j > i-1) //when i > L's length or i<1
		return ERROR;

	*pe = p->next->data;

	Position pfound = p->next;
	p->next = p->next->next;
	free(pfound);

	return OK;
}

//get data of ith node
Status GetElem_L(LinkList L, int i, ElemType * pe)
{
	Position p = L->next;
	int j = 1;

	while(p && j<i)
	{
		p = p->next;
		j ++;
	}

	*pe = p->data;
	return OK;
}


//merge nondecreasing ordered  list La and Lb, the new list is La, and Lb is freed
void MergeList_L(LinkList La, LinkList Lb)
{
	Position p = La;
	Position pa = La->next;
	Position pb = Lb->next;

	while(pa && pb)
	{
		if(pa->data <= pb->data)
		{
			p->next = pa;
			p = p->next;
			pa = pa->next;
		}
		else
		{
			p->next = pb;
			p = p->next;
			pb = pb->next;
		}
	}

	p->next = pa? pa : pb;

	free(Lb);
}


void ListReverse_L(LinkList L)
{
	Position p1 = L;
	Position p2 = L->next;

	while(p2)
	{
		Position p3 = p2->next;
		p2->next= p1;
		p2 = p3;
	}

	if( L->next && L->next->next == L) //only one node except head node
	{
		L->next->next  = NULL;
	}

	L = p1;
}

Status  ListTraverse_L(LinkList L, int (*visit)(ElemType ))
{
	Position p = L->next;
	
	while(p)
	{
		if(!visit(p->data))
			return ERROR;
		p  = p->next;
	}
}


