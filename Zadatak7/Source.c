#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Cvor;
typedef struct Cvor* Position;
typedef struct Cvor _cvor;

struct Cvor
{
	int element;
	int prioritet;
	Position Next;
};

Position AllocationMem();
void PushS(Position,int);
void PushR(Position);
void Pop(Position);
void DropLast(Position);
void PrintList(Position);
void CleanExit(Position);
void CheckEnd(Position);
void PrintMenu();

int main()
{
	_cvor red, stog;
	int maxCapacity = 0;
	int currentCapacity = 0;
	int isStackFull = 0;

	red.Next = NULL;
	stog.Next = NULL;
	int x = 0;
	srand((unsigned)time(NULL));

	printf("Unesite kapacitet stoga: ");
	scanf("%d", &maxCapacity);
	do
	{
		PrintMenu();
		printf("\n\t Vas izbor : ");
		scanf(" %d", &x);
		system("cls");
		switch (x)
		{
		case 1:
		{
			if (currentCapacity > 0)
				--currentCapacity;
			Pop(&stog);
			break;
		}
		case 2:
		{
			if (currentCapacity == maxCapacity)
				isStackFull = 1;
			else
			{
				isStackFull = 0;
				++currentCapacity;
			}
			PushS(&stog, isStackFull);
			break;
		}
		case 3:
		{
			Pop(&red);
			break;
		}
		case 4:
		{
			PushR(&red);
			break;
		}
		case 5:
		{
			PrintList(stog.Next);
			break;
		}
		case 6:
		{
			PrintList(red.Next);
			break;
		}
		case -1:
		{
			CleanExit(&red);
			printf("\nRed ociscen!\n");

			CleanExit(&stog);
			printf("\nStog ociscen!\n");
			break;
		}
		default:
			printf("Doslo je do greske pri izboru...\n");
		}

	} while (x != -1);

	return 0;
}


void PushS(Position p,int isFull)
{
	Position q;
	q = AllocationMem();
	q->element = rand() % 90 + 10;
	q->prioritet = 0;
	if (q == NULL)
		printf("\nGRESKA U ALOKACIJI!!!\n");

	q->Next = p->Next;
	p->Next = q;
	if (isFull == 1)
		DropLast(p);

	if (p->Next != NULL)
		printf("\nUspjesno dodan random element na stog!\n");
}

void DropLast(Position p)
{
	Position tmp = NULL;
	while (p->Next->Next != NULL)
		p = p->Next;

	tmp = p->Next;
	p->Next = tmp->Next;
	free(tmp);
}

void PushR(Position p)
{
	Position q;
	q = AllocationMem();
	q->element = rand() % 90 + 10;
	q->prioritet = rand() % 5 + 1;

	if (q == NULL)
		printf("\nGRESKA U ALOKACIJI!!!\n");
	printf("\n####  %d s prioritetom %d  ####\n",q->element,q->prioritet);

	while (p->Next != NULL && p->Next->prioritet < q->prioritet)
		p = p->Next;

	q->Next = p->Next;
	p->Next = q;
	if (p->Next != NULL)
		printf("\nUspjesno dodan random element na red!\n");
}

void Pop(Position p)
{
	Position q;
	if (p->Next != NULL)
	{
		q = p->Next;
		p->Next = q->Next;
		printf("\nUspjesno skinut element!\n");
		free(q);
	}
	else
	{
		printf("Lista je prazna!!");
	}
}

void CleanExit(Position p)
{
	while (p->Next != NULL)
		Pop(p);
}

Position AllocationMem()
{
	Position el;
	el = (Position)malloc(sizeof(_cvor));
	return el;
}


void PrintList(Position P)
{
	int i = 1;
	if (P == NULL)
		printf("\nLista je prazna!!!");
	else
	{
		printf("\nSortirana lista: ");
		while (P != NULL)
		{
			if (P->prioritet == 0)
			{
				printf("\n%d \t %d ", i, P->element);
				i++;
			}
			else
				printf("\n%d \t %d ", P->element, P->prioritet);

			P = P->Next;
		}
	}
}

void PrintMenu()
{
	FILE* f;
	char str[1023];
	f = fopen("Menu.txt", "r");
	if (f == NULL)
		exit(-1);
	while (!feof(f))
	{
		fgets(str, 1023, f);
		printf("%s", str);
	}
	fclose(f);
}