#include "hashquad.h"
#include "err.h"

#include <stdio.h>
#include <stdlib.h>

#define MinTableSize 10

enum KindOfEntry {Legitimate, Empty, Deleted};

struct HashEntry
{
	ElemType 	Elem;
	enum KindOfEntry Info;
};

struct HashTbl
{
	int		TableSize;
	int 	Count;
	struct HashEntry * Cells;
};

int NextPrimeSize(int N)
{
	int j = (N-3)/4 ;
	int M  = 4 * j + 3;
	N = N>M? M + 4 : M;

	while(1)
	{
		int i = 3;
		while( i * i< N)
		{
			if(N %i == 0)
			{
				N += 4;
				i = 3;
			}
			else
			{
				i += 2;
			}
		}
		return N;
	}
}

static Position Hash(ElemType Key, int TableSize)
{
	return Key %TableSize;
}


static void MakeEmpty(HashTable H)
{
	H->Count = 0;

	for(int i = 0; i<H->TableSize; i++)
		H->Cells[i].Info = Empty;
}

HashTable InitializeTable( int TableSize)
{
	//check size first
	if(TableSize < MinTableSize)
		Error("Table size is too small");

	HashTable H = malloc(sizeof(struct HashTbl));
	if(!H)
		FatalError("Out of space!!!");

	H->TableSize = NextPrimeSize(TableSize);
	H->Cells = malloc(sizeof(struct HashEntry)* H->TableSize);
	if(!H->Cells)
		FatalError("Out of space!!!");

	MakeEmpty(H);

	return H;
}

void DestroyTable(HashTable H)
{
	free(H->Cells);
	free(H);
}

Position Find(ElemType Key, HashTable H)
{
	Position p = Hash(Key, H->TableSize);

	int offset = 1;

	while(H->Cells[p].Info != Empty && H->Cells[p].Elem != Key)
	{
		p += offset;
		offset += 2;

		if(p >= H->TableSize)
			p -= H->TableSize;
	}

	return p;
}

void Insert(ElemType Key, HashTable H)
{
	//check to see if need to rehash
	if(H->Count > H->TableSize / 2)
	{
		Rehash(H);
	}

	Position p = Find(Key, H);
	if(H->Cells[p].Info != Legitimate)
	{
		H->Cells[p].Info = Legitimate;
		H->Cells[p].Elem = Key;
		H->Count ++;
	}

}

ElemType Retrieve(Position P, HashTable H)
{
	return H->Cells[P].Elem;
}

void Rehash(HashTable H)
{
	int oldSize = H->TableSize;
	struct HashEntry * oldCells = H->Cells;

	//malloc new
	int N = NextPrimeSize(oldSize * 2);
	struct HashEntry * newCells = malloc(sizeof(struct HashEntry) *N);
	if(!newCells)
		FatalError("Out of space!!!");

	H->Cells = newCells;
	H->TableSize = N;
	MakeEmpty(H);

	//insert old into new
	for(int i = 0; i<oldSize; i++)
	{
		if(Legitimate == oldCells[i].Info)
		{
			Insert(oldCells[i].Elem, H);
		}
	}

	//free old
	free(oldCells);
}


void ShowTableValues(HashTable H)
{
	printf("\n%4d, %4d:\t", H->TableSize, H->Count);
	int cnt = 0;
	for(int i = 0; i<H->TableSize; i++)
	{
		if(Legitimate == H->Cells[i].Info)
		{
			if(0 == (cnt %10))
				printf("\n\t" );
			printf("%8d", H->Cells[i].Elem);
			cnt ++;
		}
	}
}
