#ifndef __HASHQUAD_
#define __HASHQUAD_


typedef int ElemType;

typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl * HashTable;

HashTable InitializeTable(int TableSize);
void	DestroyTable(HashTable);
Position Find(ElemType Key, HashTable H);

void Insert(ElemType Key, HashTable H);
ElemType Retrieve(Position P, HashTable H);

void Rehash(HashTable H);
void ShowTableValues(HashTable H);

#endif
