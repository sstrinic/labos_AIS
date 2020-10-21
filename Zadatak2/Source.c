#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Osoba* Element;
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
void Brisi(Element);
void Meni();

int main()
{
	struct Osoba Head;
	Head.next = NULL;

	return 0;
}

void Ispis(Element p)
{

}

void UnosPocetak(Element p)
{
	Element q;
	q = (Element)malloc(sizeof(struct Osoba));
	printf("Upisi ime: ");
	scanf("%s", q->ime);
	printf("Upisi prezime: ");
	scanf("%s", q->prezime);
	printf("Upisi godinu rodjenja: ");
	scanf("%d", q->godina);

	q->next = p->next;
	p->next = q;

}

void UnosKraj(Element p)
{

}

Element Trazi(char prezime[], Element p)
{

}

void Brisi(Element p)
{

}

void Meni()
{
	FILE* f;
	char str[1024];
	f = fopen("Meni.txt", "r");
	while (!feof(f))
	{
		gets(str, 1024, f);
		printf("%s\n", str);
	}
	fclose(f);
}