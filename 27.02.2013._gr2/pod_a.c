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

int main()
{
	pozicija p = NULL;
	char dat[max] = "rijeci.txt";
	p = Inicijaliziraj(p);
	ProcitajListu(p, dat);
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