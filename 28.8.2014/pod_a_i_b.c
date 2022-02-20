#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
//Napisati program koji za tri različita predmeta čita ime i prezime studenta te njegovu ocjenu.Podaci o
//svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i
//ispisati je.
//a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri
//predmeta.
//b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena
//studenata, sadrži i njihovu prosječnu ocjenu iz ta tri predmeta.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	char ime[max], prezime[max];
	int ocjena;
	pozicija next;
}Lista;

pozicija Inicijalizacija(pozicija p);
int ProcitajDatoteku(pozicija p, char *dat);
int UnesiUListu(pozicija p, char* ime, char* prezime, int ocjena);
int Polozili(pozicija mat, pozicija fiz, pozicija elektro, pozicija nova);
int Prosjek(pozicija mat, pozicija fiz, pozicija elektro, pozicija nova);
int ispis(pozicija p);
int Brisi(pozicija p);

int main()
{
	pozicija mat_lista = NULL, fiz_lista = NULL, elektro_lista = NULL, polozili_sve=NULL, prosj_lista=NULL;
	char mat_dat[max] = "matematika.txt", fiz_dat[max] = "fizika.txt", elektro_dat[max] = "elektrotehnika.txt";

	mat_lista = Inicijalizacija(mat_lista);
	fiz_lista = Inicijalizacija(fiz_lista);
	elektro_lista = Inicijalizacija(elektro_lista);
	polozili_sve = Inicijalizacija(polozili_sve);
	prosj_lista= Inicijalizacija(prosj_lista);

	ProcitajDatoteku(mat_lista,mat_dat);
	ProcitajDatoteku(fiz_lista, fiz_dat);
	ProcitajDatoteku(elektro_lista, elektro_dat);

	printf("Lista 1:\n");
	ispis(mat_lista);
	printf("Lista 2:\n");
	ispis(fiz_lista);
	printf("Lista 3:\n");
	ispis(elektro_lista);

	Polozili(mat_lista, fiz_lista, elektro_lista, polozili_sve);
	printf("Studenti koji su polozili sve predmete:\n");
	ispis(polozili_sve);
	Prosjek(mat_lista, fiz_lista, elektro_lista, prosj_lista);
	printf("Prosjecne ocjene studenata iz sva tri predmeta:\n");
	ispis(prosj_lista);

	Brisi(mat_lista);
	Brisi(fiz_lista);
	Brisi(elektro_lista);
	Brisi(polozili_sve);
	Brisi(prosj_lista);

	return 0;
}

pozicija Inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri inicijalizaciji liste.\n");
		return NULL;
	}
	p->next = NULL;
	p->ocjena = NULL;
	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	return p;
}

int ProcitajDatoteku(pozicija p, char*dat)
{
	FILE* file = NULL;
	char ime[max] = { 0 }, prezime[max] = { 0 };
	int ocjena = 0;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s %d\n", ime, prezime, &ocjena);
		UnesiUListu(p, ime, prezime, ocjena);
	}
	fclose(file);
	return 0;
}

int UnesiUListu(pozicija p, char* ime, char* prezime, int ocjena)
{
	pozicija q = NULL;

	q = Inicijalizacija(q);
	q->ocjena = ocjena;
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);

	while (p->next != NULL)
	{
		if (strcmp(p->next->prezime, prezime) > 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int ispis(pozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->ocjena);
		p = p->next;
	}
	return 0;
}

int Polozili(pozicija mat, pozicija fiz, pozicija elektro, pozicija nova)
{
	pozicija q = NULL;

	mat = mat->next;
	fiz = fiz->next;
	elektro = elektro->next;

	while (mat != NULL)
	{
		if (mat->ocjena >= 50 && fiz->ocjena >= 50 && elektro->ocjena >= 50)
		{
			q = Inicijalizacija(q);    //NAPOMENA!! OVAMO MORA BIT INICIJALIZACIJA 
									  //jer ce se inace promjenit svaki element u novoj listi
			q->ocjena = 0;
			strcpy(q->ime, mat->ime);
			strcpy(q->prezime, mat->prezime);

			q->next =nova->next;
			nova->next = q;
		}
		mat = mat->next;
		fiz = fiz->next;
		elektro = elektro->next;
	}
	return 0;
}

int Brisi(pozicija p)
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

int Prosjek(pozicija mat, pozicija fiz, pozicija elektro, pozicija nova)
{
	pozicija q = NULL;
	int suma = 0;
	mat = mat->next;
	fiz = fiz->next;
	elektro = elektro->next;

	while (mat != NULL)
	{
		q = Inicijalizacija(q); 
		suma = (mat->ocjena + fiz->ocjena + elektro->ocjena)/3;
		q->ocjena = suma;
		strcpy(q->ime, mat->ime);
		strcpy(q->prezime, mat->prezime);

		q->next = nova->next;
		nova->next = q;

		mat = mat->next;
		fiz = fiz->next;
		elektro = elektro->next;
		suma = 0;
	}
	
}