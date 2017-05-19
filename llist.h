#ifndef __LINKLIST_
#define	__LINKLIST_

#include "dsheader.h"

typedef int ElemType;
struct LNode;

typedef struct LNode * LinkList;

Status InitList_L(LinkList *pL);
void DestroyList_L(LinkList L);

Status ListInsert_L(LinkList L, int i, ElemType e);
Status ListDelete_L(LinkList L, int i, ElemType *e);

Status GetElem_L(LinkList L, int i, ElemType *e);

Status ListTraverse_L(LinkList L, int (*visit)(ElemType ));

void MergeList_L(LinkList La, LinkList Lb);

void ListReverse(LinkList L);


#endif
