#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Osoba;
typedef struct Osoba* Pozicija;
typedef struct Osoba _osoba;

struct Osoba
{
	char ime[15];
	char prezime[15];
	int godina;
	Pozicija next;
};

void Ispis(Pozicija);
void UnosPocetak(Pozicija);
void UnosKraj(Pozicija);
Pozicija Trazi(char[], Pozicija);
Pozicija TraziPrethodni(char[], Pozicija);
void Brisi(Pozicija, char[]);
void Meni(Pozicija, int);
void CleanExit(Pozicija);
void IspisMeni();
void AddNewAfterElement(char[], Pozicija);
void AddNewBeforeElement(char[], Pozicija);
void ListToFile(Pozicija);
void ReadFile();
void SortListBySName(Pozicija);

int main()
{
	int x=0;
	_osoba head;
	head.next = NULL;

	do
	{
		IspisMeni();
		scanf(" %d", &x);
		Meni(&head, x);
	} while (x != -1);
	CleanExit(&head);
	return 0;
}

void Ispis(Pozicija p)
{
	if (p == NULL)
		printf("\nLista je prazna!!!");
	do
	{
		p = p->next;
		printf("\nIme:	%s", p->ime);
		printf("\nPrezime:	%s", p->prezime);
		printf("\nGodina:		%d", p->godina);

	} while (p->next != NULL);
}

void UnosPocetak(Pozicija p)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(_osoba));

	printf("Upisi ime:	");
	scanf("%s", q->ime);
	printf("\nUpisi prezime:	");
	scanf("%s", q->prezime);
	printf("\nUpisi godinu rodjenja:	");
	scanf("%d", &q->godina);

	q->next = p->next;
	p->next = q;
}

void UnosKraj(Pozicija p)
{
	while (p->next != NULL)
		p = p->next;

	UnosPocetak(p);
}

Pozicija Trazi(char prezime[], Pozicija p)
{
	p = p->next;
	while (p != NULL && (strcmp(prezime, p->prezime) != 0))
		p = p->next;
	if (p == NULL)
	{
		printf("\nElement ne postoji u listi!!!");
		return NULL;
	}
	else
	{
		return p;
	}
}

Pozicija TraziPrethodni(char prezime[], Pozicija p)
{
	while (p->next != NULL && (strcmp(prezime, p->next->prezime) != 0))
		p = p->next;
	if (p->next == NULL)
	{
		printf("\nElement ne postoji u listi!!!");
		return NULL;
	}
	else
	{
		return p;
	}
}

void Brisi(Pozicija p, char prezime[])
{
	Pozicija q = NULL;
	p = TraziPrethodni(prezime, p);
	if (p == NULL)
	{
		printf("Greska pri brisanju!!\n");
	}
	else
	{
		q = p->next;
		p->next = q->next;
		free(q);
	}
}

void IspisMeni()
{
	FILE* f;
	char str[1023];
	f = fopen("Meni.txt", "r");
	while (!feof(f))
	{
		fgets(str,1023, f);
		printf("%s", str);
	}
	fclose(f);
}

void Meni(Pozicija p, int x)
{
	
	char prezime[15];
	system("cls");
	switch (x)
	{
	case 1:
	{
		UnosPocetak(p);
		break;
	}
	case 2:
	{
		Ispis(p);
		break;
	}
	case 3:
	{
		UnosKraj(p);
		break;
	}
	case 4:
	{
		printf("\nUpisite prezime za pronaci: ");
		scanf("%s", prezime);
		p=Trazi(prezime, p);
		printf("\nIme:	%s", p->ime);
		printf("\nPrezime:	%s", p->prezime);
		printf("\nGodina:	%d", p->godina);
		break;
	}
	case 5:
	{
		printf("\nUpisite prezime za obrisat: ");
		scanf("%s", prezime);
		Brisi(p, prezime);
		break;
	}
	case 6:
	{
		AddNewAfterElement(prezime, p);
		break;
	}
	case 7:
	{
		AddNewBeforeElement(prezime, p);
		break;
	}
	case 8:
	{
		SortListBySName(p);
		break;
	}
	case 9:
	{
		ListToFile(p);
		break;
	}
	case 10:
	{
		ReadFile();
		break;
	}
	case -1:
		exit(1);
	default:
		printf("Doslo je do greske pri izboru...\n");
	}
}

void CleanExit(Pozicija p)
{
	Pozicija temp = p->next;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	free(p);
}

void SortListBySName(Pozicija p)
{
	Pozicija q,prev_q,temp,end;
	end = NULL;
	while (p->next != end)
	{
		prev_q = p;
		q = p->next;
		while (q->next != end)
		{
			if (strcmp(q->prezime, q->next->prezime) > 0)
			{
				temp = q->next;
				prev_q->next = temp;
				q->next = temp->next;
				temp->next = q;
				q = temp;
			}
			prev_q = q;
			q = q->next;
		}
		end = q;
	}
}

void AddNewAfterElement(char prezime[],Pozicija p)
{
	p = Trazi(prezime, p);
	UnosPocetak(p);
}

void AddNewBeforeElement(char prezime[], Pozicija p)
{
	p = TraziPrethodni(prezime, p);
	UnosPocetak(p);
}

void ListToFile(Pozicija p)
{
	FILE* f;
	f = fopen("Lista.txt", "w");
	if (f == NULL)
		exit(1);
	fprintf(f, "%s %s %d\n", p->ime, p->prezime, p->godina);
	fclose(f);
}

void ReadFile()
{
	FILE* f;
	char ime[15];
	char prezime[15];
	int godina;
	f = fopen("Lista.txt", "r");
	while (!feof(f))
	{
		fscanf(f, "%s %s %d\n", ime, prezime, &godina);
		printf("\n%s	%s	%d", ime, prezime, godina);
	}
	fclose(f);
}