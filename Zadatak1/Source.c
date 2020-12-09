#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Student
{
	char ime[15];
	char prezime[15];
	int bodovi;
}student;

int LineCounter();
int FileToStruct(student*, int);
int PrintFromStruct(student*, int);

int main()
{
	int br;
	br = LineCounter();

	student* studenti;
	studenti = (student*)malloc(br * sizeof(student));

	FileToStruct(studenti,br);
	PrintFromStruct(studenti,br);

	free(studenti);
	return 0;
}

int LineCounter()
{
	FILE* f;
	int x = 1;

	f = fopen("studenti.txt", "r");

	if (f == NULL)
	{
			printf("Greska prilikom citanja datoteke!!!\n");
			exit(1);
	}

	while (!feof(f))
	{

		if (getc(f) == '\n')
			x++;
	}

	fclose(f);
	return x;
}

int FileToStruct(student* studenti, int br)
{
	FILE* fp;
	fp = fopen("studenti.txt", "r");

	for (int i = 0; i < br; i++)
	{
		fscanf(fp, "%s %s %d\n", studenti->ime, studenti->prezime, &studenti->bodovi);
		studenti++;
	}

	fclose(fp);
	return 0;
}

int PrintFromStruct(student* studenti, int br)
{
	int rel;
	for (int i = 0; i < br; i++)
	{
		rel = (((float)studenti->bodovi)/50)*100,0;
		printf("\nIme: %s Prezime: %s Bodovi: %d Relativni bodovi: %d %%", studenti->ime, studenti->prezime, studenti->bodovi,rel);
		studenti++;
	}
	return 0;
}
