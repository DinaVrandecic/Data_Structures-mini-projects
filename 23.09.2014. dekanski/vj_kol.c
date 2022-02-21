#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	char ime[max], prezime[max];
	float ocjena;
	pozicija next;
}Lista;

pozicija Inicijalizacija(pozicija p);
int ProcitajDatoteku(pozicija p, char *kol1);
int UnesiUListu(pozicija p, char* ime, char* prezime,float ocjena);
int UnesiUNovu(pozicija kol1_lista, pozicija kol2_lista, pozicija ispit);
int UnesiSortiranoNova(pozicija kol1, pozicija kol2, pozicija ispit);
int PretvoriUOcjenu(float ocjena);
int ispis(pozicija p);
int brisi(pozicija p);

int main()
{
	pozicija kol1_lista = NULL, kol2_lista=NULL, ispit=NULL;
	char kol1[max] = "kolokvij1.txt", kol2[max] = "kolokvij2.txt";

	kol1_lista = Inicijalizacija(kol1_lista);
	kol2_lista = Inicijalizacija(kol2_lista);
	ispit = Inicijalizacija(ispit);

	ProcitajDatoteku(kol1_lista, kol1);
	ProcitajDatoteku(kol2_lista, kol2);
	UnesiUNovu(kol1_lista, kol2_lista, ispit);

	printf("Prvi kolokvij:\n");
	ispis(kol1_lista);
	printf("\nDrugi kolokvij:\n");
	ispis(kol2_lista);
	printf("\nIspit:\n");
	ispis(ispit);

	brisi(kol1_lista);
	brisi(kol2_lista);
	brisi(ispit);
	return 0;
}

pozicija Inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}
	p->ocjena = 0.0;
	p->next = NULL;
	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	return p;
}

int ProcitajDatoteku(pozicija p, char* dat)
{
	FILE* file = NULL;
	char ime[max] = { 0 }, prezime[max] = { 0 };
	float ocjena = 0;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s %f\n", ime, prezime, &ocjena);
		UnesiUListu(p, ime, prezime, ocjena);
	}

	fclose(file);
	return 0;
}

int UnesiUListu(pozicija p, char* ime, char* prezime, float ocjena)
{
	pozicija q = NULL;
	q = Inicijalizacija(q);
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->ocjena = ocjena;

	while (p->next != NULL)
	{
		if (strcmp(p->next->prezime, prezime) <0 )
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int UnesiUNovu(pozicija kol1, pozicija kol2, pozicija ispit)
{
	kol1 = kol1->next;
	kol2 = kol2->next;

	while (kol1 != NULL)
	{
		if(kol1->ocjena >=50 && kol2->ocjena >=50)
			UnesiSortiranoNova(kol1, kol2, ispit);
		
		kol1 = kol1->next;
		kol2 = kol2->next;
	}
}

int UnesiSortiranoNova(pozicija kol1, pozicija kol2, pozicija ispit)
{
	pozicija q = NULL;
	float ocjena = 0;

	q = Inicijalizacija(q);
	strcpy(q->ime, kol1->ime);
	strcpy(q->prezime, kol1->prezime);
	ocjena = (kol1->ocjena + kol2->ocjena)/2;
	q->ocjena=PretvoriUOcjenu(ocjena);

	while (ispit->next != NULL)
	{
		if (ispit->next->ocjena < q->ocjena)
			break;
		ispit = ispit->next;
	}
	q->next = ispit->next;
	ispit->next = q;
	return 0;
}

int PretvoriUOcjenu(float ocjena)
{
	if (ocjena >=50 && ocjena<60)
		return 2;
	else if (ocjena >= 60 && ocjena < 74)
		return 3;
	else if (ocjena >= 74 && ocjena < 87)
		return 4;
	else if (ocjena >= 87 && ocjena < 100)
		return 5;
}

int ispis(pozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s %s %f\n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}
	return 0;
}

int brisi(pozicija p)
{
	pozicija q = NULL;
	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return 0;
}