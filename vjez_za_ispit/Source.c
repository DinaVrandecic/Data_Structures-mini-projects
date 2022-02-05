#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max (60)

struct _stablo;
typedef struct _stablo* StabloPozicija;
typedef struct _stablo
{
	char gradovi[max];
	int broj;
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
ListaPozicija Inic_Lista(ListaPozicija p);
int ProcitajDrzave(ListaPozicija head, char *dat);
int UnesiListu(ListaPozicija head, char* drzava, char* drzava_dat);
StabloPozicija ProcitajGradove(StabloPozicija stablo, char *drzava_dat);
StabloPozicija UnesiStablo(StabloPozicija root, char *grad, int stanovnici);
StabloPozicija Inic_stablo(StabloPozicija S);
int print(ListaPozicija p);
int Inorder(StabloPozicija S);
ListaPozicija PronadiDrzavu(ListaPozicija head, char *drzava);
int InorderIspisVeceOd(StabloPozicija S, int broj);

int main()
{
	ListaPozicija head=NULL, p=NULL;
	char dat[max] = "drzave.txt";
	int x = 1, broj=0;
	char ch = { 0 }, drzava[max] = { 0 };

	head=Inic_Lista(head);
	p = Inic_Lista(head);

	ProcitajDrzave(head, dat);
	print(head->next);

	printf("\n1)Biraj drzavu\n2)Izlaz iz petlje\n");
	while (x)
	{
		scanf(" %c", &ch);
		switch (ch)
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
			printf("Izlaz iz petlje.");
			x = 0;
			break;
		}
	}
	return 0;
}

ListaPozicija PronadiDrzavu(ListaPozicija p, char* drzava)
{
	while (p->next != NULL && strcmp(p->drzava, drzava) != 0)
		p = p->next;

	return p;
}

ListaPozicija Inic_Lista(ListaPozicija p)
{
	p = (ListaPozicija)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska pri alokaciji memeorije.");
		return NULL;
	}
	strcpy(p->drzava, "");
	p->stablo = NULL;
	p->next = NULL;
	
	return p;
}

int ProcitajDrzave(ListaPozicija head, char* dat)
{
	FILE* file = NULL;
	char drzava[max] = { 0 }, drzava_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Neuspjesno otvaranje datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava, drzava_dat);
		UnesiListu(head, drzava, drzava_dat);
	}
	fclose(file);
	return 0;
}

int UnesiListu(ListaPozicija p, char* drzava, char* drzava_dat)
{
	ListaPozicija q=NULL;

	q=Inic_Lista(q);
	strcpy(q->drzava, drzava);
	q->stablo = ProcitajGradove(q->stablo, drzava_dat);

	while (p->next != NULL)
	{
		if (strcmp(q->drzava, p->drzava) < 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;

	return 0;
}

StabloPozicija ProcitajGradove(StabloPozicija root, char* drzava_dat)
{
	FILE* file = NULL;
	char grad[max] = { 0 };
	int stanovnici = 0;

	file = fopen(drzava_dat, "r");
	if (file == NULL)
	{
		printf("Neuspjesno otvaranje datoteke.");
		return NULL;
	}

	while(!feof(file))
	{
		fscanf(file, " %s %d\n", grad, &stanovnici);
		root = UnesiStablo(root, grad, stanovnici);
	}
	fclose(file);
	return root;
}

StabloPozicija UnesiStablo(StabloPozicija S, char* grad, int stanovnici)
{
	if (S == NULL)
	{
		S=Inic_stablo(S);
		strcpy(S->gradovi, grad);
		S->broj = stanovnici;
	}
	else if (strcmp(grad, S->gradovi) == 0)
	{
		if (stanovnici > S->broj)
			S->D = UnesiStablo(S->D, grad, stanovnici);
		if(stanovnici < S->broj)
			S->L= UnesiStablo(S->L, grad, stanovnici);
	}
	else
	{
		if (stanovnici > S->broj)
			S->D = UnesiStablo(S->D, grad, stanovnici);
		if (stanovnici < S->broj)
			S->L = UnesiStablo(S->L, grad, stanovnici);
	}
	return S;
}

StabloPozicija Inic_stablo(StabloPozicija S)
{
	S = (StabloPozicija)malloc(sizeof(stablo));
	if (S == NULL)
	{
		printf("Greska pri alokaciji memeorije.");
		return NULL;
	}
	strcpy(S->gradovi, "");
	S->broj = 0;
	S->D = NULL;
	S->L = NULL;

	return S;
}

int InorderIspisVeceOd(StabloPozicija S, int broj)
{
	if (S == NULL)
		return 0;

	InorderIspisVeceOd(S->L, broj);
	if( broj > S->broj)
		printf("%s-%d  ", S->gradovi, S->broj);
	InorderIspisVeceOd(S->D, broj);
	return 0;
}

int print(ListaPozicija p)
{
	while (p != NULL)
	{
		printf("\n%s:\n", p->drzava);
		Inorder(p->stablo);
		p = p->next;
	}
	return 0;
}

int Inorder(StabloPozicija S)
{
	if (S == NULL)
		return 0;

	Inorder(S -> L);
	printf("%s-%d  ", S->gradovi, S->broj);
	Inorder(S->D);

	return 0;
}
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdlib.h>
//#include<string.h>
//#include<stdlib.h>
//
//int main()
//{
//
//}