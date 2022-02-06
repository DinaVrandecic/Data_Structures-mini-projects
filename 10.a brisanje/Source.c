#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _stablo;
typedef struct _stablo* StabloPozicija;
typedef struct _stablo
{
	char grad[max];
	int stanovnici;
	StabloPozicija L;
	StabloPozicija D;

}stablo;

struct _lista;
typedef struct _lista* ListaPozicija;
typedef struct _lista
{
	char drzava[max];

	StabloPozicija stablo;
	ListaPozicija next;

}lista;


int ProcitajDatDrzave(ListaPozicija p, char* dat);
int SortiraniUnosListe(ListaPozicija p, char* drzava_ime, char* drzava_dat);
StabloPozicija NapraviStablo(StabloPozicija root, char* grad, int stanovnici);
int print(ListaPozicija p);
int inorder(StabloPozicija S);
int InorderIspisVeceOd(StabloPozicija p, int broj);
ListaPozicija StvoriElementListe(ListaPozicija p);
ListaPozicija PronadiDrzavu(ListaPozicija p, char* drzava);
StabloPozicija ProcitajDatGradovi(StabloPozicija root, char* drzava_dat);
int BrisiListu(ListaPozicija p);
StabloPozicija BrisiStablo(StabloPozicija S);

int main()
{
	ListaPozicija head = NULL, p = NULL;
	char dat[max] = "drzave.txt", c = { 0 }, drzava[max] = { 0 };
	int x = 1, broj = 0;

	head = StvoriElementListe(head);
	p = StvoriElementListe(p);

	ProcitajDatDrzave(head, dat);
	print(head->next);

	printf("\n1)Biraj drzavu\n2)Izlaz iz petlje\n");
	while (x)
	{
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Odaberi drzavu:");
			scanf(" %s", drzava);
			p = PronadiDrzavu(head, drzava);
			if (p == NULL)
			{
				printf("Odabrana drzava nije unesena u file.");
				return -5;
			}
			printf("\nPrikazat ce se gradovi s brojem stanovnika vecim nego uneseni.Unesi broj:");
			scanf("%d", &broj);
			InorderIspisVeceOd(p->stablo, broj);
			break;
		case '2':
			printf("Izlazak iz petlje.\n");
			x = 0;
			break;
		}
	}

	BrisiListu(head);
	return 0;
}

int BrisiListu(ListaPozicija p)
{
	ListaPozicija pom = NULL;
	while (p->next != NULL)
	{
		pom = p->next;
		BrisiStablo(p->stablo);
		p->next = p->next->next;
		free(pom);
	}
	return 0;
}

StabloPozicija BrisiStablo(StabloPozicija S)
{
	if (S != NULL)
	{
		BrisiStablo(S->L);
		BrisiStablo(S->D);
		free(S);
	}
	return NULL;
}

ListaPozicija StvoriElementListe(ListaPozicija p)
{
	p = (ListaPozicija)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memorije head elementa.");
		return -3;
	}
	strcpy(p->drzava, "");
	p->next = NULL;
	p->stablo = NULL;
}

int ProcitajDatDrzave(ListaPozicija p, char* dat)
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
		SortiraniUnosListe(p, drzava_ime, drzava_dat);
	}

	fclose(file);
	return 0;
}
int SortiraniUnosListe(ListaPozicija p, char* drzava_ime, char* drzava_dat)
{
	ListaPozicija q = NULL;
	char pom[max] = { 0 };

	q = (ListaPozicija)malloc(sizeof(lista));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -2;
	}


	strcpy(q->drzava, drzava_ime);
	q->stablo = NULL;
	q->stablo = ProcitajDatGradovi(q->stablo, drzava_dat);
	strcpy(pom, drzava_ime);

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
			break;
		}
		else if (strcmp(pom, p->next->drzava) < 0)
		{
			q->next = p->next;
			p->next = q;
			break;
		}
		p = p->next;
	}
	return 0;
}
StabloPozicija ProcitajDatGradovi(StabloPozicija root, char* drzava_dat)
{
	FILE* file = NULL;
	char grad[max] = { 0 };
	int stanovnici = 0;

	file = fopen(drzava_dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d\n", grad, &stanovnici);
		root = NapraviStablo(root, grad, stanovnici);
	}
	fclose(file);
	return root;
}
StabloPozicija NapraviStablo(StabloPozicija S, char* grad, int stanovnici)
{
	if (S == NULL)
	{
		S = (StabloPozicija)malloc(sizeof(stablo));
		if (S == NULL)
		{
			printf("Greska pri alokaciji memorije");
			return NULL;
		}
		strcpy(S->grad, grad);
		S->stanovnici = stanovnici;
		S->L = NULL;
		S->D = NULL;
	}
	else if (stanovnici == S->stanovnici)
	{
		if (strcmp(grad, S->grad) < 0)
			S->L = NapraviStablo(S->L, grad, stanovnici);
		else if (strcmp(grad, S->grad) > 0)
			S->D = NapraviStablo(S->D, grad, stanovnici);
	}
	else
	{
		if (stanovnici < S->stanovnici)
			S->L = NapraviStablo(S->L, grad, stanovnici);
		else if (stanovnici > S->stanovnici)
			S->D = NapraviStablo(S->D, grad, stanovnici);
	}
	return S;
}
int print(ListaPozicija p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->drzava);
		inorder(p->stablo);
		p = p->next;
	}
}
int inorder(StabloPozicija S)
{
	if (S == NULL)
		return 0;

	inorder(S->L);
	printf(" %s-%d ", S->grad, S->stanovnici);
	inorder(S->D);

	return 0;
}
ListaPozicija PronadiDrzavu(ListaPozicija p, char* drzava)
{
	while (p->next != NULL && strcmp(drzava, p->drzava) != 0)
		p = p->next;

	return p;
}
int InorderIspisVeceOd(StabloPozicija p, int broj)
{
	if (p == NULL)
		return 0;

	InorderIspisVeceOd(p->L, broj);

	if (broj < p->stanovnici)
		printf("%s %d\n", p->grad, p->stanovnici);

	InorderIspisVeceOd(p->D, broj);

	return 0;
}