#define _CRT_SECURE_NO_WARNINGS
#pragma disable(warning :4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define velTab (11)
#define max (60)

struct _lista;
typedef struct _lista* ListaPozicija;
struct _stablo;
typedef struct _stablo* StabloPozicija;
struct _tablica;
typedef struct _tablica* TabPozicija;

typedef struct _lista
{
	char drzava[max];
	StabloPozicija stablo;
	ListaPozicija next;
}Lista;

typedef struct _stablo
{
	char grad[max];
	int stanovnici;
	StabloPozicija L;
	StabloPozicija D;
}Stablo;

typedef struct _tablica
{
	ListaPozicija* hashLista;
}Tablica;

ListaPozicija Inic_lista();
StabloPozicija Inic_stablo(StabloPozicija S);
StabloPozicija Brisi_stablo(StabloPozicija S);
TabPozicija Inic_tab(TabPozicija H);
int ProcitajDatDrzave(TabPozicija H, char* dat);
int DodajUTablicu(char* drzava_ime, char* drzava_dat, TabPozicija H);
int Funkcija(char* drzava_ime);
int UnosListe(ListaPozicija p, char* drzava_ime, char* drzava_dat);
StabloPozicija ProcitajDatGradovi(StabloPozicija S, char* drzava_dat);
StabloPozicija UnesiUStablo(StabloPozicija S,char* grad, int stanovnici);


int main()
{
	TabPozicija hash = NULL;
	hash = Inic_tab(hash);
	char ch = { 0 }, drzava[max] = { 0 }, dat[max]="drzave.txt";
	int stanovnici = 0, x = 1;

	ProcitajDatDrzave(hash, dat);
	/*while (x)
	{
		printf("Odaberi opciju 1)odabir 2)izlazak iz petlje:\n");
		scanf(" %c", &ch);
		switch (ch) 
		{
		case '1':
			printf("Odaberi drzavu: ");
			scanf(" %s", drzava);
			p=PronadiDrzavu(hash, )
		}
	}*/

	return 0;
}

ListaPozicija Inic_lista()
{
	ListaPozicija p = NULL;
	p= (ListaPozicija)malloc(sizeof(Lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije lise.\n");
		return NULL;
	}
	strcpy(p->drzava, "");
	p->next = NULL;
	//p->stablo=StabloPozicija(p->stablo);
	return p;
}

StabloPozicija Inic_stablo(StabloPozicija S)
{
	S = (StabloPozicija)malloc(sizeof(Stablo));
	if (S == NULL)
	{
		printf("Greska kod inicijalizacije stabla.\n");
		return NULL;
	}
	S->L = NULL;
	S->D = NULL;
	S->stanovnici = 0;
	strcpy(S->grad, "");

	return S;
}

StabloPozicija Brisi_stablo(StabloPozicija S)
{
	if (S != NULL)
	{
		Brisi_stablo(S->L);
		Brisi_stablo(S->D);
		free(S);
	}
	return NULL;
}

TabPozicija Inic_tab(TabPozicija H)
{
	int i = 0;
	H = (TabPozicija)malloc(sizeof(Tablica));
	if (H == NULL)
	{
		printf("Greska pri alokaciji hash tablice.");
		return NULL;
	}

	H->hashLista = (ListaPozicija*)malloc(velTab * sizeof(ListaPozicija));
	if (H->hashLista == NULL)
	{
		printf("Greska pri alokaciji hash tablice.");
		return NULL;
	}

	for (i = 0;i < velTab;i++)
		H->hashLista[i] = Inic_lista();

	return H;
}

int ProcitajDatDrzave(TabPozicija H, char* dat)
{
	FILE* file = NULL;
	char drzava_ime[max] = { 0 }, drzava_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava_ime, drzava_dat);
		DodajUTablicu(drzava_ime, drzava_dat, H);
	}

	fclose(file);
	return 0;
}

int DodajUTablicu(char* drzava_ime, char* drzava_dat, TabPozicija H)
{
	int indeks = 0;
	indeks = Funkcija(drzava_ime);

	UnosListe(H->hashLista[indeks], drzava_ime, drzava_dat);
	return 0;
}

int Funkcija(char* drzava_ime)
{
	int duljina = 0, i=0, suma=0, ostatak=0;
	duljina = strlen(drzava_ime);

	for (i = 0;i < duljina || i < 5;i++)
		suma += drzava_ime[i];

	ostatak = suma % velTab;
	return ostatak;
}
int UnosListe(ListaPozicija p, char* drzava_ime, char* drzava_dat)
{
	ListaPozicija q = NULL;
	q = Inic_lista();

	strcpy(q->drzava, drzava_ime);
	//q->stablo = ProcitajDatGradovi(q->stablo, drzava_dat);
	
	while (p->next != NULL)
	{
		if (strcmp(p->next->drzava, drzava_ime) < 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;

	return 0;
}

//StabloPozicija ProcitajDatGradovi(StabloPozicija S, char* dat)
//{
//	FILE* file = NULL;
//	char grad[max] = { 0 };
//	int stanovnici = 0;
//
//	file = fopen(dat, "r");
//	if (file == NULL)
//	{
//		printf("Greska pri otvaranju datoteke.");
//		return NULL;
//	}
//
//	while (!feof(file))
//	{
//		fscanf(file, " %s %d\n", grad, stanovnici);
//		//S = UnesiUStablo(S, grad, stanovnici);
//	}
//
//	fclose(file);
//	return S;
//}

//StabloPozicija UnesiUStablo(StabloPozicija S, char* grad, int stanovnici)
//{
//	if (S == NULL)
//	{
//		S = Inic_stablo(S);
//		S->stanovnici = stanovnici;
//		strcpy(S->grad, grad);
//	}
//	else if (stanovnici < S->stanovnici)
//		S->L = UnesiUStablo(S->L, grad, stanovnici);
//	else if (stanovnici > S->stanovnici)
//		S->D = UnesiUStablo(S->D, grad, stanovnici);
//	else if (S->stanovnici == stanovnici)
//	{
//		if (strcmp(grad, S->grad) < 0)
//			S->L = UnesiUStablo(S->L, grad, stanovnici);
//		if (strcmp(grad, S->grad) > 0)
//			S->D = UnesiUStablo(S->D, grad, stanovnici);
//	}
//
//	return S;
//}


