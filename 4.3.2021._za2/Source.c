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
	char kategorija[max];
	char proizvod[max];
	int kolicina;
	pozicija next;
}Lista;

pozicija Inicijalizacija(pozicija p);
int ProcitajDatoteku(pozicija head1, char* dat1);
int UnesiUListu(pozicija head, char* kategorija, char* proizvod, int kolicina);
int ProcitajRacun(pozicija head, char* dat2);
int PromjeniListu(pozicija head, char* kategorija, char* proizvod, int kolicina);
int PromjeniListu1(pozicija head, char* kategorija, char* proizvod, int kolicina);
int Ispis(pozicija head);
int Ispis1(pozicija head);
int Trazi(pozicija head, char* kategorija, char* proizvod, int kolicina);
int Brisi(pozicija p);

int main()
{
	char dat1[max] = { 0 }, dat2[max] = { 0 };
	pozicija head = NULL;

	head = Inicijalizacija(head);

	printf("Unesi ime datoteke skladista: ");
	scanf(" %s", dat1);
	printf("\nUnesi ime datoteke racuna: ");
	scanf(" %s", dat2);

	ProcitajDatoteku(head, dat1);
	ProcitajRacun(head, dat2);

	Ispis1(head->next);
	Ispis(head->next);
	Brisi(head);
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
	strcpy(p->kategorija, "");
	strcpy(p->proizvod, "");
	p->kolicina = 0;
	p->next = NULL;

	return p;
}

int ProcitajDatoteku(pozicija head, char* dat)
{
	FILE* file = NULL;
	char kategorija[max] = { 0 }, proizvod[max] = { 0 };
	int kolicina = 0;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s %d\n", kategorija, proizvod, &kolicina);
		if (Trazi(head, kategorija, proizvod, kolicina) == 1)
			PromjeniListu1(head, kategorija, proizvod, kolicina);
		else
			UnesiUListu(head, kategorija, proizvod, kolicina);
	}

	fclose(file);
	return 0;
}

int UnesiUListu(pozicija p, char* kategorija, char* proizvod, int kolicina)
{
	pozicija q = NULL;
	q = Inicijalizacija(q);


	strcpy(q->kategorija, kategorija);
	strcpy(q->proizvod, proizvod);
	q->kolicina = kolicina;

	while (p->next != NULL)
	{
		if (strcmp(p->next->kategorija, kategorija) < 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int ProcitajRacun(pozicija head, char* dat)
{
	FILE* file = NULL;
	char kategorija[max] = { 0 }, proizvod[max] = { 0 };
	int kolicina = 0;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return -1;
	}
	while (!feof(file))
	{
		fscanf(file, " %s %s %d\n", kategorija, proizvod, &kolicina);
		PromjeniListu(head, kategorija, proizvod, kolicina);
	}

	fclose(file);
	return 0;
}

int PromjeniListu(pozicija p, char* kategorija, char* proizvod, int kolicina)
{
	p = p->next;

	while (p != NULL)
	{
		if (strcmp(p->kategorija, kategorija) == 0 && strcmp(p->proizvod, proizvod) == 0)
			p->kolicina = p->kolicina - kolicina;
		p = p->next;
	}

	return 0;
}

int PromjeniListu1(pozicija p, char* kategorija, char* proizvod, int kolicina)
{
	p = p->next;

	while (p != NULL)
	{
		if (strcmp(p->kategorija, kategorija) == 0 && strcmp(p->proizvod, proizvod) == 0)
			p->kolicina = p->kolicina + kolicina;
		p = p->next;
	}

	return 0;
}

int Ispis(pozicija p)
{
	printf("\n");
	while (p != NULL)
	{
		if (p->kolicina < 5)
			printf(" %s %s %d\n", p->kategorija, p->proizvod, p->kolicina);
		p = p->next;
	}

	return 0;
}

int Ispis1(pozicija p)
{
	while (p != NULL)
	{
		printf(" %s %s %d\n", p->kategorija, p->proizvod, p->kolicina);
		p = p->next;
	}

	return 0;
}

int Trazi(pozicija p, char* kategorija, char* proizvod, int kolicina)
{
	p = p->next;
	while (p != NULL)
	{
		if (strcmp(p->kategorija, kategorija) == 0 && strcmp(p->proizvod, proizvod) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}
int Brisi(pozicija p)
{
	pozicija temp = NULL;
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
	return 0;
}