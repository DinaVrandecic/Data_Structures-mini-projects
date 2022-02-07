#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* ListaPozicija;
typedef struct _lista
{
	char rijec[max];
	ListaPozicija next;
}Lista;

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	char rijec[max];
	ListaPozicija lista;
	pozicija L;
	pozicija D;
}stablo;

pozicija ProcitajDatoteku(pozicija S, char* dat);
pozicija Inicijaliziraj(pozicija root);
pozicija UnesiUStablo(pozicija S, char* rijec);
pozicija Brisi(pozicija S);
int UnesiUListu(ListaPozicija p, char* rijec);
ListaPozicija Inic_listu(ListaPozicija p);
int Inorder(pozicija S);
pozicija Pretraga(pozicija S, char* rijec);
int Ispis(ListaPozicija p);
int BrisiListu(ListaPozicija p);

int main()
{
	pozicija root = NULL, cvor=NULL;
	char dat[max] = "datoteka.txt", dat1[max] = "suglasnik.txt", dat2[max] = "samoglasnik.txt";
	char ch = { 0 }, rijec[max] = { 0 };
	int x = 1;

	//root = Inicijaliziraj(root);
	//cvor = Inicijaliziraj(cvor);
	root = ProcitajDatoteku(root, dat);
	Inorder(root);

	printf("\nOdaberi 1)unos rijeci 2)izlazak iz petlje: ");
	while (x)
	{
		scanf(" %c", &ch);
		switch (ch)
		{
		case '1':
			printf("Unesi rijec za koju zelis vidjeti koliko ima ponavljanja: ");
			scanf(" %s", rijec);
			cvor=Pretraga(root, rijec);
			Ispis(cvor->lista);
			break;
		case'2':
			printf("\nIzlazak iz petlje.\n");
			x = 0;
			break;
		}
	}
	Brisi(root);
	return 0;
}

pozicija ProcitajDatoteku(pozicija S, char* dat)
{
	FILE* file = NULL;
	char rijec[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return NULL;
	}

	while (!feof(file))
	{
		fscanf(file, " %s", rijec);
		S = UnesiUStablo(S, rijec);
	}
	fclose(file);
	return S;
}

pozicija Inicijaliziraj(pozicija S)
{
	S = (pozicija)malloc(sizeof(stablo));
	if (S == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return NULL;
	}

	strcpy(S->rijec, "");
	S->lista=Inic_listu(S->lista);
	S->L = NULL;
	S->D = NULL;

	return S;
}

ListaPozicija Inic_listu(ListaPozicija p)
{
	p = (ListaPozicija)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -1;
	}
	p->next = NULL;
	strcpy(p->rijec, "");
	return p;
}

pozicija UnesiUStablo(pozicija S, char* rijec)
{
	if (S == NULL)
	{
		S = Inicijaliziraj(S);
		strcpy(S->rijec, rijec);
	}
	else if (strcmp(S->rijec, rijec) > 0)
		S->L = UnesiUStablo(S->L, rijec);
	else if (strcmp(S->rijec, rijec) < 0)
		S->D = UnesiUStablo(S->D, rijec);
	else if (strcmp(S->rijec, rijec) == 0)
		 UnesiUListu(S->lista, rijec);

	return S;
}

int UnesiUListu(ListaPozicija p, char* rijec)
{
	ListaPozicija q = NULL;
	q=Inic_listu(q);
	strcpy(q->rijec, rijec);

	q->next = p->next;
	p->next = q;
	return 0;
}
pozicija Pretraga(pozicija S, char* rijec)
{
	if (S == NULL)
		return NULL;
	else if (strcmp(rijec, S->rijec) <0)
		return Pretraga(S->L, rijec);
	else if (strcmp(rijec, S->rijec) > 0)
		return Pretraga(S->D, rijec);

	return S;
}

int Ispis(ListaPozicija p)
{
	int brojac=0;
	while (p != NULL)
	{
		brojac++;
		p = p->next;
	}

	printf("\nIma %d trazene rijeci u tekstu.\n", brojac);
	return 0;
}

int Inorder(pozicija S)
{
	if (S == NULL)
		return 0;

	Inorder(S->L);
	printf(" %s", S->rijec);
	Inorder(S->D);
	return 0;
}

pozicija Brisi(pozicija S)
{
	if (S != NULL)
	{
		Brisi(S->L);
		Brisi(S->D);
		BrisiListu(S->lista);
		free(S);
	}
	return NULL;
}
int BrisiListu(ListaPozicija p)
{
	ListaPozicija pom = NULL;
	while (p->next != NULL)
	{
		pom = p->next;
		p->next = p->next->next;
		free(pom);
	}
	return 0;
}