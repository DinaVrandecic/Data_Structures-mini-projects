#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* ListaP;
typedef struct _lista
{
	char ime[max], prezime[max];
	int ocjena;
	ListaP next;
}Lista;

ListaP Inic_listu(ListaP p);
int ProcitajDatoteku(ListaP p, char* dat);
int UnesiUListu(ListaP p, char* ime, char* prezime);
int Generiraj();
int ispis(ListaP p);
int Trazi(ListaP p,int ocjena);
int Brisi(ListaP p, int ocjena);
ListaP PronadiPrethodni(ListaP p, int ocjena);

int main()
{
	ListaP head = NULL;
	char dat[max] = "studenti.txt";
	int ocjena = 0, broj_ponavljanja = 0, i=0;
	srand(time(NULL));

	head = Inic_listu(head);
	ProcitajDatoteku(head, dat);
	ispis(head);

	ocjena = Generiraj();
	printf("\n%d\n", ocjena);
	broj_ponavljanja=Trazi(head, ocjena);

	for (i = 0;i < broj_ponavljanja;i++)
		Brisi(head, ocjena);
	ispis(head);

	return 0;
}

ListaP Inic_listu(ListaP p)
{
	p = (ListaP)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri inicijalizaciji liste.\n");
		return NULL;
	}
	p->next = NULL;
	p->ocjena = 0;
	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	return p;
}

int ProcitajDatoteku(ListaP p, char* dat)
{
	FILE* file = NULL;
	char ime[max] = { 0 }, prezime[max] = { 0 };

	file = fopen(dat, "r");
	if (p == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", ime, prezime);
		UnesiUListu(p, ime, prezime);
	}
	fclose(file);
	return 0;
}

int UnesiUListu(ListaP p, char* ime, char* prezime)
{
	ListaP q = NULL;
	q = Inic_listu(q);
	int ocjena = 0;

	ocjena = Generiraj();
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->ocjena = ocjena;

	while (p->next != NULL)
	{
		if (p->next->ocjena < ocjena)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int Generiraj()
{
	int broj = 0;

	broj = (rand() % (5 - 1 + 1)) + 1;
	return broj;
}

int ispis(ListaP p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}
	return 0;
}

int Trazi(ListaP p, int ocjena)
{
	int count = 0;
	p = p->next;
	while (p != NULL)
	{
		if (p->ocjena == ocjena)
			count++;
		p = p->next;
	}
	return count;
}

int Brisi(ListaP p, int ocjena)
{
	ListaP trenutni = NULL, prethodni = NULL;

	prethodni = PronadiPrethodni(p, ocjena);
	trenutni = prethodni->next;
	prethodni->next = prethodni->next->next;
	free(trenutni);
	return 0;
}

ListaP PronadiPrethodni(ListaP p,int ocjena)
{
	ListaP prethodni = NULL, trenutni = NULL;

	prethodni = p;
	trenutni = prethodni->next;

	while (trenutni !=NULL && trenutni->ocjena != ocjena)
	{
		prethodni = trenutni;
		trenutni = prethodni->next;
	}
	return prethodni;
}