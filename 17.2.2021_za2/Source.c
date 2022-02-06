#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable :4996 )
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	char ime[max];
	char prezime[max];
	char kafic[max];
	pozicija next;
}lista;

pozicija Inicijalizacija(pozicija p);
int ProcitajDatoteku(pozicija p, char* dat);
int UnesiUListu(pozicija p, char* ime, char* prezime, char* kafic);
int Ispis(pozicija p);
int Pretraga(pozicija head, char *kafic);
int brisi(pozicija p);

int main()
{
	pozicija head = NULL;
	char dat[max] = { 0 }, ch = { 0 }, kafic[max] = { 0 };
	int x = 1;

	head = Inicijalizacija(head);

	printf("\nUpisi ime datoteke: ");
	scanf(" %s", dat);

	ProcitajDatoteku(head, dat);
	Ispis(head->next);
	printf("\nUpisi opciju 1)odaberi 2):");

	while (x)
	{
		scanf(" %c", &ch);
		switch (ch) 
		{
		case '1':
			printf("\nUpisi ime kafica: ");
			scanf(" %s", kafic);
			Pretraga(head, kafic);
			break;
		case '2':
			printf("\nIzlazak iz petlje\n");
			x = 0;
			break;
		}
	}
	brisi(head);
	return 0;
}

pozicija Inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("\nPogreska pri alokaciji memorije.");
		return NULL;
	}
	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	strcpy(p->kafic, "");
	p->next = NULL;
	return p;
}

int ProcitajDatoteku(pozicija p, char* dat)
{
	FILE* file = NULL;
	char ime[max] = { 0 },prezime[max] = { 0 },kafic[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("\nPogreska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s %s\n", ime, prezime, kafic);
		UnesiUListu(p, ime, prezime, kafic);
	}
	fclose(file);
	return 0;
}
int UnesiUListu(pozicija p, char* ime, char* prezime, char* kafic)
{
	pozicija q = NULL;
	q = Inicijalizacija(q);

	strcpy(q->prezime, prezime);
	strcpy(q->kafic, kafic);
	strcpy(q->ime, ime);

	while (p->next != NULL)
	{
		if (strcmp(p->next->kafic, kafic) < 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;

	return 0;
}

int Ispis(pozicija p)
{
	while (p != NULL)
	{
		printf("%s %s %s\n", p->ime, p->prezime, p->kafic);
		p = p->next;
	}
	return 0;
}
int Pretraga(pozicija p, char* kafic)
{
	int brojac = 0;

	while (p->next != NULL)
	{
		if (strcmp(p->kafic, kafic) == 0)
		{
			printf("%s %s\n", p->ime, p->prezime);
			brojac++;
		}
			p = p->next;
	}

	printf("\nBroj ljudi koji su bili u kaficu %s je %d.\n", kafic, brojac);
	return 0;
}

int brisi(pozicija p)
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