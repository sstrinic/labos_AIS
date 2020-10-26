#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Osoba;
typedef struct Osoba* Element;
typedef struct Osoba _osoba;

struct Osoba
{
	char ime[15];
	char prezime[15];
	int godina;
	Element next;
};

void Ispis(Element);
void UnosPocetak(Element);
void UnosKraj(Element);
Element Trazi(char[], Element);
void Brisi(Element,char[]);
void Meni(Element,int*);

int main()
{
	_osoba head;
	head.next = NULL;

	/*while(x != -1)
	{
		Meni(&head,x);
	}*/

	return 0;
}

void Ispis(Element p)
{
	do
	{
		p=p->next;
		printf("Ime:	%s",p->ime);
		printf("Prezime:	%s",p->prezime);
		printf("Godina:		%d",p->godina);
		
	}while(p->next != NULL);
}

void UnosPocetak(Element p)
{
	Element q;
	q = (Element)malloc(sizeof(struct Osoba));

	printf("Upisi ime:	");
	scanf("%s", q->ime);
	printf("\nUpisi prezime:	");
	scanf("%s", q->prezime);
	printf("\nUpisi godinu rodjenja:	");
	scanf("%d", q->godina);

	q->next = p->next;
	p->next = q;

}

void UnosKraj(Element p)
{
	while(p->next != NULL)
		p=p->next;

	UnosPocetak(p);
}

Element Trazi(char prezime[], Element p)
{
	do
	{
		p=p->next;
		if(strcmp(prezime,p->prezime)!=0)
		{
			printf("\nIme:	%s",p->ime);
			printf("\nPrezime:	%s",p->prezime);
			printf("\nGodina:	%d",p->godina);
			break; 
		}
	}while(p->next != NULL);

}

void Brisi(Element p,char prezime[])
{

}

void Meni(Element Head,int* x)
{
	FILE* f;
	char str[1023];
	char prezime[15];
	f = fopen("Meni.txt", "r");
	while (!feof(f))
	{
		fscanf(f,"%s\n",str);
		printf("%s\n", str);
	}
	scanf(" %d", &x);
	switch(*x)
	{
		case 1:
		{
			UnosPocetak(Head); 
			break;
		}
		case 2:
		{
			Ispis(Head); 
			break;
		}
		case 3:
		{
			UnosKraj(Head); 
			break;
		}
		case 4:
		{
			Trazi(prezime,Head);
			break;
		}
		case 5:
		{
			Brisi(Head,prezime); 
			break;
		}
		case -1:
			exit(1);
		default:
			printf("Doslo je do greske pri izboru...\n");
	}
	system("cls");
	fclose(f);
}