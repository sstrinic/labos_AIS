#define _CRT_SECURE_NO_WARNINGS
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
void CheckEnd(Position);

int main()
{
	_cvor P, Q, M, N;
	P.Next = NULL;
	Q.Next = NULL;
	M.Next = NULL;
	N.Next = NULL;

	ReadPoly(&P);
	ReadPoly(&Q);
	printf("\nP(x) = ");
	PrintPoly(P.Next);
	printf("\nQ(x) = ");
	PrintPoly(Q.Next);

	SumPoly(P.Next, Q.Next, &M);
	printf("\n\nM(x) = ");
	PrintPoly(M.Next);

	MulPoly(P.Next, Q.Next, &N);
	printf("\nN(x) = ");
	PrintPoly(N.Next);

	CheckEnd(&P);
	printf("\nP ociscen!\n");

	CheckEnd(&Q);
	printf("\nQ ociscen!\n");
	
	CheckEnd(&N);
	printf("\nN ociscen!\n");

	CheckEnd(&M);
	printf("\nM ociscen!\n");

	return 0;
}

void CheckEnd(Position p)
{
	if (p->Next != NULL)
		CleanExit(p->Next);
}
Position AllocationMem()
{
	Position el;
	el = (Position)malloc(sizeof(_cvor));
	return el;
}

void ReadPoly(Position P)
{
	FILE* f;
	Position q, k;
	k = P;
	char ime_dat[30] = "pol1.txt";
	printf("Upisite naziv datoteke s polinomom: ");
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
			fscanf_s(f, "%d %d\n", &q->Koef, &q->Exp);
			if (q->Koef == 0)
				free(q);
			else
			{
				while (P->Next != NULL && P->Next->Exp > q->Exp)
					P = P->Next;
				if (P->Next != NULL && P->Next->Exp == q->Exp)
				{
					P->Next->Koef += q->Koef;
					free(q);
					if (P->Next->Koef == 0)
					{
						q = P->Next;
						P->Next = q->Next;
						free(q);
					}
				}
				else
				{
						q->Next = P->Next;
						P->Next = q;
				}
				
			}
			P = k;
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
	Position z,q;
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
			z->Exp = Q->Exp;
			z->Koef = P->Koef + Q->Koef;
			P = P->Next;
			Q = Q->Next;
		}
		M->Next = z;
		M = M->Next;
		M->Next = NULL;
	}
	
	while (P != NULL)
	{
		z = AllocationMem();
		z->Exp = P->Exp;
		z->Koef = P->Koef;
		P = P->Next;

		z->Next = M->Next;
		M->Next = z;
		M = M->Next;
		
	}
	while (Q != NULL)
	{
		q = AllocationMem();
		q->Exp = Q->Exp;
		q->Koef = Q->Koef;
		Q = Q->Next;

		q->Next = M->Next;
		M->Next = q;
		M = M->Next;
	}
}

void MulPoly(Position P,Position Q,Position N)
{
	Position q,o,tp;
	tp = N;
	while (P != NULL)
	{
		o = Q;
		while (o!= NULL)
		{
			q = AllocationMem();

			q->Exp = P->Exp + o->Exp;
			q->Koef = P->Koef * o->Koef;

			while (N->Next != NULL && N->Next->Exp > q->Exp)
				N = N->Next;

			if (N->Next != NULL && N->Next->Exp == q->Exp)
			{
				N->Next->Koef += q->Koef;
				free(q);
			}
			else
			{
					q->Next = N->Next;
					N->Next = q;
			}
			o = o->Next;
			N = tp;
		}
		P = P->Next;
	}
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