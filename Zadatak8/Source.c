#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<limits.h>

struct Cvor;
typedef struct Cvor* Position;
typedef struct Cvor _cvor;

struct Cvor
{
	double element;
	Position Next;
};

Position AllocationMem();
void PushS(Position,double);
double Pop(Position);
void ReadPostfix(Position);
void Operations(Position,char[]);
int IsOpera(char[]);
int IsNum(char[]);
void CheckEnd(Position);

int main()
{
	_cvor stog;
	stog.Next = NULL;
	ReadPostfix(&stog);
	printf("\nRjesenje Postfix izraza iz datoteke Post.txt: \t%.2f \n", Pop(&stog));
	CheckEnd(&stog);

	return 0;
}

void ReadPostfix(Position p)
{
	FILE* fp;
	char read[20];
	fp = fopen("Post.txt", "r");
	if (fp == NULL)
		exit(-1);

	while (!feof(fp))
	{
		fscanf(fp, "%s", read);
		if (IsNum(read) == 1)
			PushS(p, atoi(read));
		else if (IsOpera(read) == 1)
			Operations(p, read);
		else
		{
			printf("### GRESKA U POSTFIX IZRAZU ###");
			exit(-1);
		}
		printf("%s ", read);
		strcpy(read, "\0");
	}
	fclose(fp);
}

void Operations(Position p, char read[])
{
	double rez = 0;
	double op2 = 1;
	Position op1 = NULL;

	if ((op2 = Pop(p)) != LONG_MAX)
	{
		if (p->Next != NULL)
			op1 = p->Next;
		else
		{
			printf("\nGRESKA OPERATIONS op1- NE POSTOJI ELEMENT NA STOGU\n");
			exit(-1);
		}
	}
	else
	{
		printf("\nGRESKA OPERATIONS op2- NEUSPJESNO SKIDANJE SA STOGA\n");
		exit(-1);
	}

	if (read[0] == '+')
	{
		op1->element += op2;
	}
	else if (read[0] == '-')
	{
		op1->element -= op2;
	}
	else if (read[0] == '*')
	{
		op1->element *= op2;
	}
	else if (read[0] == '/')
	{
		op1->element /= op2;
	}
	else
	{
		printf("Greska pri citanju operacije postfix izraza!!!");
	}
}

void PushS(Position p, double x)
{
	Position q;
	q = AllocationMem();
	q->element = x;
	q->Next = p->Next;
	p->Next = q;
	//if (p->Next != NULL)
	//	printf("\nUspjesno dodan element %.2f na niz!\n",q->element);
}

double Pop(Position p)
{
	double x = 0;
	Position q;
	if (p->Next != NULL)
	{
		x = p->Next->element;
		q = p->Next;
		p->Next = q->Next;
		free(q);
		//if (x != 0)
		//	printf("\nUspjesno skinut element!\n");
		return x;
	}
	else
	{
		printf("Lista je prazna!!");
		return LONG_MAX;
	}
}

Position AllocationMem()
{
	Position el;
	el = (Position)malloc(sizeof(_cvor));
	if (el == NULL)
		printf("\nGRESKA U ALOKACIJI!!!\n");
	return el;
}

int IsOpera(char text[])
{
	if (strlen(text) != 1)
		return 0;
	else
	{
		switch (text[0]) {
		case '+':
		case '-':
		case '/':
		case '*':
			return 1;
		}
	}
	return 0;
}

int IsNum(char text[])
{
	for (size_t i = 0; i < strlen(text); i++)
	{
		if (isdigit(text[i]) == 0)
			if(i == 0 && text[i] != '-')
				return 0;
	}
	return 1;
}

void CheckEnd(Position p)
{
	if (p->Next != NULL)
	{
		printf("\n ERROR-\t VISE OD JEDNOG ELEMENTA JE NA STOGU \n");
		printf("Los Postfix izraz!");
	}
	else
		printf("\n OK - Stog prazan");
}