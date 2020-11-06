#include<stdio.h>
#include<stdlib.h>

struct Cvor;
typedef struct Cvor* Position;
typedef struct Cvor _cvor;

struct Cvor
{
	int Koef;
	int Exp;
	Position Next;
};

Position AllocationMem();
void ReadPoly(Position);
void PrintPoly(Position);
void CleanExit(Position);
void SumPoly(Position, Position, Position);
void MulPoly(Position, Position, Position);

int main()
{
	_cvor P, Q, M, N;
	P.Next = NULL;
	Q.Next = NULL;
	M.Next = NULL;
	N.Next = NULL;

	ReadPoly(&P);
	ReadPoly(&Q);
	SumPoly(P.Next, Q.Next, &M);
	MulPoly(P.Next, Q.Next, &N);

	printf("\nP(x) = ");
	PrintPoly(P.Next);
	printf("\nQ(x) = ");
	PrintPoly(Q.Next);
	printf("\nM(x) = ");
	PrintPoly(M.Next);
	printf("\nN(x) = ");
	PrintPoly(N.Next);

	CleanExit(&P);
	CleanExit(&Q);
	CleanExit(&M);
	CleanExit(&N);
	return 0;
}

Position AllocationMem()
{
	Position el;
	el = (Position)malloc(sizeof(_cvor));
	return el;
}

void ReadPoly(Position p)
{
	FILE* f;
	Position q;
	char ime_dat[30]="Polinom1.txt";
	printf("Upisite naziv datoteke s polinomom: ");
	scanf("%s", ime_dat);
	f = fopen(ime_dat, "r");
	if(f==NULL)
	{
		printf("Greska datoteke %s!!", ime_dat);
	}
	else
	{
		while (!feof(f))
		{
			q = AllocationMem();
			fscanf_s(f, "%d %d\n", &q->Koef, &q->Exp);
			if (q->Koef == 0)
				free(q);
			else
			{
				while (p->Next != NULL && p->Next->Exp > q->Exp)
					p = p->Next;
				if (p->Next != NULL && p->Next->Exp == q->Exp)
				{
					p->Next->Koef += q->Koef;
					free(q);
					if (p->Koef == 0)
					{
						q = p->Next;
						p->Next = q->Next;
						free(q);
					}
				}
				else
				{
					q->Next = p->Next;
					p->Next = q;
				}
			}
		}
		fclose(f);
	}
}

void PrintPoly(Position p)
{
		if (p == NULL)
			printf("\nLista je prazna!!!");
		else
		{
			printf("%dX^%d ", p->Koef, p->Exp);
			p = p->Next;
			while (p != NULL)
			{
				if (p->Koef > 0)
					printf("+ ");
				printf(" %d X ^(%d) ", p->Koef, p->Exp);
				p = p->Next;
			} 
		}	
}

void SumPoly(Position P, Position Q, Position M)
{
	Position z;
	while (P != NULL && Q != NULL)
	{
		z = AllocationMem();
		if (P->Exp > Q->Exp)
		{
			z->Exp = P->Exp;
			z->Koef = P->Koef;
			P = P->Next;
		}
		else if (P->Exp < Q->Exp)
		{
			z->Exp = Q->Exp;
			z->Koef = Q->Koef;
			Q = Q->Next;
		}
		else
		{
			z->Exp = P->Exp;
			z->Koef = P->Koef + Q->Koef;
		}
		M->Next = z;
		M = M->Next;
		M->Next = NULL;
	}
	while (P != NULL)
	{
		z = AllocationMem();
		z = P;
		M->Next = z;
		M = M->Next;
		M->Next = NULL;
		P = P->Next;
	}
	while (Q != NULL)
	{
		z = AllocationMem();
		z = Q;
		M->Next = z;
		M = M->Next;
		M->Next = NULL;
		Q = Q->Next;
	}
}

void MulPoly(Position P,Position Q,Position N)
{
	while (P->Next != NULL)
	{
		while (Q->Next != NULL)
		{

		}
	}
}

void CleanExit(Position P)
{
	if (P->Next == NULL)
	{
		free(P);
	}
	else
	{
		P = P->Next;
		CleanExit(P);
	}
}