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
	Position Next;
};

Position AllocationMem();
void PushS(Position);
void PushR(Position);
int Pop(Position);
void PrintList(Position);
void CleanExit(Position);
void CheckEnd(Position);
void PrintMenu();
void Menu(int, Position, Position);

int main()
{
	_cvor red, stog;
	red.Next = NULL;
	stog.Next = NULL;
	int x = 0;
	srand((unsigned)time(NULL));

	do
	{
		PrintMenu();
		printf("\n\t Vas izbor : ");
		scanf(" %d", &x);
		Menu(x,&red,&stog);
	} while (x != -1);

	return 0;
}

void Menu(int x,Position red, Position stog)
{
	system("cls");
	switch (x)
	{
		case 1:
		{
			Pop(stog);
			break;
		}
		case 2:
		{
			PushS(stog);
			break;
		}
		case 3:
		{
			Pop(red);
			break;
		}
		case 4:
		{
			PushR(red);
			break;
		}
		case 5:
		{
			PrintList(stog->Next);
			break;
		}
		case 6:
		{
			PrintList(red->Next);
			break;
		}
		case -1:
		{
			CheckEnd(red);
			printf("\nRed ociscen!\n");

			CheckEnd(stog);
			printf("\nStog ociscen!\n");
			break;
		}
		default:
			printf("Doslo je do greske pri izboru...\n");
	}
}

void PushS(Position p)
{
	Position q;
	q = AllocationMem();
	q->element = rand() % (100 + 1);;
	q->Next = p->Next;
	p->Next = q;
	if (p->Next->element != NULL)
		printf("\nUspjesno dodan random element!\n");
}

void PushR(Position p)
{
	while (p->Next != NULL)
		p = p->Next;
	PushS(p);
}

int Pop(Position p)
{
	int x=0;
	Position q;
	if (p->Next != NULL)
	{
		x = p->Next->element;
		q = p->Next;
		p->Next = q->Next;
		free(q);
		if (x != 0)
			printf("\nUspjesno skinut element!\n");
		return x;
	}
	else
	{
		printf("Lista je prazna!!");
		return -1;
	}
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