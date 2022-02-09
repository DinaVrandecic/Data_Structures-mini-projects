//a) Iz datoteke èitaju rijeèi i spremaju u vezanu listu na naèin da se rijeèi slažu po abecednom redu
//obrnutom od abecednog reda.Zatim ispisati tu vezanu listu.
//b) Iz generirane liste ispisati samo one rijeèi koje se nalaze zapisane u drugoj proizvoljnoj datoteci.

#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	char rijec[max];
	pozicija next;
}Lista;

pozicija Inicijaliziraj(pozicija p);
int ProcitajListu(pozicija p, char* dat);
int UnesiUListu(pozicija p,char * rijec);
int print(pozicija p);
int ProcitajDatoteku(pozicija p,char * dat2);
int BrisiIzListe(pozicija p,char* rijec);
int BrisiSve(pozicija p);
pozicija PronadiPrethodni(pozicija p, char* rijec);

int main()
{
	pozicija p = NULL;
	char dat[max] = "rijeci.txt", dat2[max] = "dat2.txt";
	p = Inicijaliziraj(p);
	ProcitajListu(p, dat);
	print(p);
	ProcitajDatoteku(p, dat2);
	printf("\n\n");
	print(p);
	BrisiSve(p);
	print(p);
	return 0;
}

pozicija Inicijaliziraj(pozicija p)
{
	p = (pozicija)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}
	p->next = NULL;
	strcpy(p->rijec, "");
	return p;
}

int ProcitajListu(pozicija p, char* dat)
{
	FILE* file = NULL;
	char rijec[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s", rijec);
		UnesiUListu(p, rijec);
	}

	fclose(file);
	return 0;
}

int UnesiUListu(pozicija p, char* rijec)
{
	pozicija q = NULL;
	q = Inicijaliziraj(q);
	strcpy(q->rijec, rijec);

	while (p->next != NULL)
	{
		if (strcmp(p->next->rijec, rijec) < 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;

	return 0;
}

int print(pozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s ", p->rijec);
		p = p->next;
	}
	return 0;
}

int ProcitajDatoteku(pozicija p, char* dat2)
{
	FILE* file = NULL;
	char rijec[max] = { 0 };

	file = fopen(dat2, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s", rijec);
		BrisiIzListe(p, rijec);
	}

	fclose(file);
	return 0;
}

int BrisiIzListe(pozicija p, char* rijec)
{
	pozicija trenutni=NULL, prethodni=NULL;

	prethodni = PronadiPrethodni(p, rijec);
	if (prethodni == NULL)
		return -1;
	trenutni = prethodni->next;
	prethodni->next = prethodni->next->next;
	free(trenutni);
	return 0;
}

int BrisiSve(pozicija p)
{
	pozicija pom = NULL;
	while (p->next != NULL)
	{
		pom = p->next;
		p->next = p->next->next;
		free(pom);
	}
	return 0;
}

pozicija PronadiPrethodni(pozicija p, char*rijec)
{
	pozicija trenutni = NULL, prethodni = NULL;
	prethodni = p;
	trenutni = prethodni->next;

	while (trenutni != NULL && strcmp(trenutni->rijec, rijec) != 0)
	{
		prethodni = trenutni;
		trenutni = prethodni->next;
	}
	return prethodni;
}