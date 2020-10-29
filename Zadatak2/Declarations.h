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