#include "hashquad.h"

#include <stdio.h>

#define NumItems 400 

int main()
{
	int CurrSize = 11;
	
	HashTable H;
	H = InitializeTable(CurrSize);

	for(int i= 0, j= 0; i< NumItems; i++, j+= 71)
	{
		Insert(j, H);
	}

	for(int i =0, j= 0; i< NumItems; i++, j+= 71)
	{
		Position p = Find(j, H);
		ElemType key = Retrieve(p, H);
		if(key != j)
		{
			printf("\n----%4d, %8d, %8d---\n", p, j, key);
		}
	}

	ShowTableValues(H);
	DestroyTable(H);
	printf("\n-----------------------end of program.-----------------------\n");
}
