#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _stablo;
typedef struct _stablo* StabloP;
typedef struct _stablo
{
	char rijec[max];
	int duljina;
	StabloP L;
	StabloP D;
}Stablo;

struct _lista;
typedef struct _lista* ListaP;
typedef struct _lista
{
	char rijec[max];
	int duljina;
	ListaP next;
}Lista;

StabloP Inic_stabla(StabloP S);
ListaP Inic_liste(ListaP p);
StabloP ProcitajDatoteku(StabloP root,char *dat);
StabloP UnesiUStablo(StabloP S, char* rijec);
int Inorder(StabloP S);
int Ispis_liste(ListaP p);
int Duljina(StabloP S);
StabloP Brisi(StabloP S);
int BrisiListu(ListaP p);
StabloP IspisiVeceOd(StabloP S, ListaP p, int duljina);
int UnesiUListu(ListaP p, char* rijec, int duljina);


int main()
{
	StabloP root = NULL;
	ListaP head = NULL;
	char dat[max] = "dat.txt";
	int prosj_duljina = 0;

	head = Inic_liste(head);
	root = ProcitajDatoteku(root, dat);
	Inorder(root);

	prosj_duljina = Duljina(root);
	printf("Prosjecna duljina je: %d\n", prosj_duljina);
	IspisiVeceOd(root,head, prosj_duljina);
	Ispis_liste(head);
	root=Brisi(root);
	BrisiListu(head);

	return 0;
}

StabloP Inic_stabla(StabloP S)
{
	S = (StabloP)malloc(sizeof(Stablo));
	if (S == NULL)
	{
		printf("Greska pri inicijalizaciji stabla.\n");
		return NULL;
	}
	S->L = NULL;
	S->D = NULL;
	S->duljina = 0;
	strcpy(S->rijec, "");
	return S;
}

ListaP Inic_liste(ListaP p)
{
	p = (ListaP)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri inicijalizaciji liste.\n");
		return NULL;
	}
	p->next = NULL;
	p->duljina = 0;
	strcpy(p->rijec, "");
	return p;
}

StabloP ProcitajDatoteku(StabloP S, char* dat)
{
	FILE* file = NULL;
	char rijec[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
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

StabloP UnesiUStablo(StabloP S, char* rijec)
{
	if (S == NULL)
	{
		S = Inic_stabla(S);
		strcpy(S->rijec, rijec);
		S->duljina = strlen(rijec);
	}
	else if (strcmp(S->rijec, rijec) > 0)
		S->L = UnesiUStablo(S->L, rijec);
	else if (strcmp(S->rijec, rijec) < 0)
		S->D = UnesiUStablo(S->D, rijec);

	return S;
}

int Inorder(StabloP S)
{
	if (S == NULL)
		return 1;

	Inorder(S->L);
	printf("%s %d\n", S->rijec, S->duljina);
	Inorder(S->D);

	return 0;
}

int Duljina(StabloP S)
{
	int duljina = 0, broj=0;

	if (S == NULL)
		return 0;

	Duljina(S->L);
	duljina += S->duljina;
	broj++;
	Duljina(S->D);

	return duljina /broj;
}

StabloP Brisi(StabloP S)
{
	if (S != NULL)
	{
		Brisi(S->L);
		Brisi(S->D);
		free(S);
	}
	return NULL;
}

StabloP IspisiVeceOd(StabloP S,ListaP p, int duljina)
{
	if (S == NULL)
		return 1;

	IspisiVeceOd(S->L,p, duljina);
	if(S->duljina >= duljina)
		UnesiUListu(p, S->rijec, S->duljina);
	IspisiVeceOd(S->D,p, duljina);

	return 0;
}

int UnesiUListu(ListaP p, char* rijec, int duljina)
{
	ListaP q = NULL;
	q = Inic_liste(q);

	q->duljina = duljina;
	strcpy(q->rijec, rijec);
	
	q->next = p->next;
	p->next = q;
	return 0;
}

int Ispis_liste(ListaP p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s %d\n", p->rijec, p->duljina);
		p = p->next;
	}
	return 0;
}

int BrisiListu(ListaP p)
{
	ListaP q = NULL;
	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return 0;
}