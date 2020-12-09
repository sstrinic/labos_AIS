#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct Cvor;
typedef struct Cvor* Position;
typedef struct Cvor _cvor;

struct Cvor
{
	int element;
	Position Next;
};

Position AllocationMem();
void ReadList(Position);
void PrintList(Position);
void CleanExit(Position);
void CheckEnd(Position);
void ListUnion(Position, Position, Position);
void ListIntersec(Position, Position, Position);
void SortListByElement(Position);

int main()
{
	_cvor L1, L2, L3, L4;
	L1.Next = NULL;
	L2.Next = NULL;
	L3.Next = NULL;
	L4.Next = NULL;

	ReadList(&L1);
	ReadList(&L2);

	PrintList(L1.Next);
	PrintList(L2.Next);

	ListUnion(L1.Next, L2.Next, &L3);
	printf("\nListe ujedinjene...");
	ListIntersec(L1.Next, L2.Next, &L4);
	printf("\nListe iskrizane...");

	SortListByElement(&L3);
	printf("\nLista unije sortirana...");
	SortListByElement(&L4);
	printf("\nLista krizanja sortirana...");

	PrintList(L3.Next);
	PrintList(L4.Next);

	CheckEnd(&L1);
	printf("\nL1 ociscen!\n");

	CheckEnd(&L2);
	printf("\nL2 ociscen!\n");

	CheckEnd(&L3);
	printf("\nL3 ociscen!\n");

	CheckEnd(&L4);
	printf("\nL4 ociscen!\n");

	return 0;
}

void CheckEnd(Position p)
{
	if (p->Next != NULL)
		CleanExit(p->Next);
}

void CleanExit(Position p)
{
	if (p->Next == NULL)
	{
		free(p);
	}
	else
	{
		p = p->Next;
		CleanExit(p);
	}
}

Position AllocationMem()
{
	Position el;
	el = (Position)malloc(sizeof(_cvor));
	return el;
}

void ReadList(Position P)
{
	FILE* f;
	Position q, k;
	k = P;
	char ime_dat[30] = "Lista1.txt";
	printf("Upisite naziv datoteke sa zeljenom listom : ");
	scanf("%s", ime_dat);
	f = fopen(ime_dat, "r");
	if (f == NULL)
	{
		printf("Greska datoteke %s!!", ime_dat);
		exit(1);
	}
	else
	{
		while (!feof(f))
		{
			q = AllocationMem();
			fscanf_s(f, "%d ", &q->element);
			if (q->element == 0)
				free(q);
			else
			{
				while (P->Next != NULL && P->Next->element < q->element)
					P = P->Next;

				q->Next = P->Next;
				P->Next = q;
			}
			P = k;
		}
		fclose(f);
	}
}

void PrintList(Position P)
{
	if (P == NULL)
		printf("\nLista je prazna!!!");
	else
	{
		printf("\nSortirana lista: ");
		while (P != NULL)
		{
			printf("%d , ", P->element);
			P = P->Next;
		}
	}
}

void ListUnion(Position P, Position Q, Position N)
{
	Position q,z;
	z = NULL;
	while (P != NULL && Q != NULL) {
		if (P->element < Q->element) {
			q = AllocationMem();

			q->element = P->element;
			q->Next = N->Next;
			N->Next = q;
			P = P->Next;
		}
		else if (P->element > Q->element) {
			q = AllocationMem();

			q->element = Q->element;
			q->Next = N->Next;
			N->Next = q;
			Q = Q->Next;
		}
		else {
			q = AllocationMem();

			q->element = P->element;
			q->Next = N->Next;
			N->Next = q;
			P = P->Next;
			Q = Q->Next;
		}
		N = N->Next;
	}
	if (P != NULL)
		z = P;
	else if (Q != NULL)
		z = Q;

	while (z != NULL)
	{
		q = AllocationMem();

		q->element = z->element;
		q->Next = N->Next;
		N->Next = q;
		z = z->Next;
	}
}

void ListIntersec(Position P, Position Q, Position N)
{
	Position q;
	while (P != NULL && Q != NULL) 
	{
		if (P->element < Q->element) 
		{
			P = P->Next;
		}
		else if (P->element > Q->element) 
		{
			Q = Q->Next;
		}
		else 
		{
			q = AllocationMem();

			q->element = P->element;
			q->Next = N->Next;
			N->Next = q;

			P = P->Next;
			Q = Q->Next;
			N = N->Next;
		}
	}
}

void SortListByElement(Position p)
{
	Position q, prev_q, temp, end;
	end = NULL;
	while (p->Next != end)
	{
		prev_q = p;
		q = p->Next;
		while (q->Next != end)
		{
			if (q->element > q->Next->element)
			{
				temp = q->Next;
				prev_q->Next = temp;
				q->Next = temp->Next;
				temp->Next = q;
				q = temp;
			}
			prev_q = q;
			q = q->Next;
		}
		end = q;
	}
}