#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _lista;
typedef struct _lista* pozicija;
typedef struct _lista
{
	int broj;
	pozicija next;
}Lista;

pozicija Inicijalizacija(pozicija p);
int Generiraj(pozicija parni, pozicija neparni);
int Unesi(pozicija neparni, int broj);
int Provjeri(pozicija neparni, int broj);
int Izbroji(pozicija p);
int ispis(pozicija p);

int main()
{
	pozicija parni = NULL, neparni = NULL;
	srand(time(NULL));

	parni = Inicijalizacija(parni);
	neparni = Inicijalizacija(neparni);

	printf("Generirani brojevi su:\n");
	Generiraj(parni, neparni);

	printf("\nParni:\n");
	ispis(parni);
	printf("\nNeparni:\n");
	ispis(neparni);
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
	p->broj = 0;
	p->next = NULL;
	return p;
}

int Generiraj(pozicija parni, pozicija neparni)
{
	int uneseni_p = 0, uneseni_n=0, broj=0;
	while (uneseni_p != 10 || uneseni_n != 10)
	{
		broj = (rand() % (80 - 50 + 1)) + 50;
		printf("%d ", broj);
		if (broj % 2 == 0)
		{
			if(uneseni_p <10)
				Unesi(parni, broj);
			uneseni_p = Izbroji(parni);
		}
		else
		{
			if (uneseni_n < 10)
				Unesi(neparni, broj);
			uneseni_n = Izbroji(neparni);
		}
	}
	return 0;
}

int Unesi(pozicija p, int broj)
{
	pozicija q = NULL;
	q = Inicijalizacija(q);
	q->broj = broj;

	if (Provjeri(p, broj) == 0)
	{
		while (p->next != NULL)
		{
			if (p->next->broj < broj)
				break;
			p = p->next;
		}
		q->next = p->next;
		p->next = q;
	}

	return 0;
}

int Provjeri(pozicija p, int broj)
{
	p = p->next;
	while (p != NULL)
	{
		if (p->broj == broj)
			return 1;
		p = p->next;
	}
	return 0;
}

int Izbroji(pozicija p)
{
	int suma = 0;
	p = p->next;
	while (p != NULL)
	{
		suma++;
		p = p->next;
	}
	return suma;
}

int ispis(pozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%d ", p->broj);
		p = p->next;
	}
	return 0;
}