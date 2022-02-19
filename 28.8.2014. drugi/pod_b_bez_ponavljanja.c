#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable :4996 )
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	int random, redni;
	pozicija next;
}Lista;

pozicija Inicijalizacija(pozicija p);
int Generiraj(pozicija p);
int GenerirajRedni(pozicija p);
int UnesiUListu(pozicija p, int broj, int redni);
int NadiRedni(pozicija p,int broj, int i);
pozicija PronadiZadnji(pozicija p);
int ispis(pozicija p);
int BrisiListu(pozicija p);

int main()
{
	pozicija head = NULL;
	srand(time(NULL));
	head = Inicijalizacija(head);
	Generiraj(head);
	printf("Pocetna lista:\n");

	ispis(head);
	printf("Lista pod b):\n");
	GenerirajRedni(head);
	ispis(head);
	BrisiListu(head);
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
	p->random = 0;
	p->redni = 0;
	p->next = NULL;
	return p;
}

int Generiraj(pozicija p)
{
	pozicija pom = NULL;
	int i = 0, broj = 0;
	for (i = 0;i < 21;i++)
	{
		broj = (rand() % (150 - 100 + 1)) + 100;
		while (pom!= NULL)
		{
			if (pom->random == broj)
			{
				broj = (rand() % (150 - 100 + 1)) + 100;
				pom = p->next;
			}
			pom = pom->next;
		}
		UnesiUListu(p, broj, i);
		pom = p->next;
	}
	return 0;
}

int GenerirajRedni(pozicija p)
{
	pozicija pom = NULL;
	int i = 0,j=0, broj = 0;
	int niz[5] = { 0 };
	for (i = 0;i < 5;i++)
	{
		broj = (rand() % (19 + 1));
		for(j=0;j<5;j++)
		{
			if (niz[j] == broj)
			{
				broj = (rand() % (19 + 1));
				j = 0;
			}
		}
		niz[i] = broj;
		printf("%d\n", broj);
		NadiRedni(p, broj, i);
		pom = p->next;
	}
	return 0;
}

int UnesiUListu(pozicija p, int broj, int redni)
{
	pozicija q = NULL, zadnji=NULL;
	q = Inicijalizacija(q);
	zadnji = PronadiZadnji(p);
	q->random = broj;
	q->redni = redni;

	q->next = zadnji->next;
	zadnji->next = q;

	return 0;
}

pozicija PronadiZadnji(pozicija p)
{
	while (p->next != NULL)
		p = p->next;
	return p;
}

int ispis(pozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%d %d\n", p->redni, p->random);
		p = p->next;
	}
	return 0;
}

int NadiRedni(pozicija p, int broj, int mjesto)
{
	int i;
	pozicija head = p, q=NULL;
	p = p->next;

	while (p->next != NULL && p->next->redni !=broj)
		p = p->next;

	q = p->next;
	p->next = q->next;

	for (i = 0;i < mjesto;i++)  
		head = head->next;

	q->next = head->next;
	head->next = q;
	return 0;
}

int BrisiListu(pozicija p)
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
