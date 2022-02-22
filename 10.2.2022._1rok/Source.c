#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define max (128)
#define velTab (7)

struct _client;
typedef struct _client* ClientP;
typedef struct _client
{
	char id[max];
	char firstName[max];
	char lastName[max];
}Client;

struct _date;
typedef struct _date* DateP;
typedef struct _date
{
	int year;
	int month;
	int day;
}Date;

struct _transaction;
typedef struct _transaction* TransactionP;
typedef struct _transaction {
	char description[max];
	float amount;
	char processed[max];
	ClientP client;
	DateP date;
	TransactionP next;
}Transaction;

struct _tablica;
typedef struct _tablica* TablicaP;
typedef struct _tablica
{
	TransactionP* lista;
}Tablica;

ClientP Inic_client(ClientP C);
DateP Inic_date(DateP D);
TransactionP Inic_transaction();
TablicaP Inic_hash(TablicaP H);
int ProcitajDatoteku(TablicaP H, char *dat);
int UnesiUTablicu(TablicaP H, char* description,float amount, char* processed, char* id, char* firstName, char* lastName, int year,int month,int day);
int UnesiUListu(TransactionP p, char* description, float amount, char* processed, char* id, char* firstName, char* lastName, int year, int month, int day);
int IspisiTablicu(TablicaP H);
int IspisiListu(TransactionP p);
int BrisiTablicu(TablicaP H);
int BrisiListu(TransactionP p);

int main()
{
	TablicaP H = NULL;
	char dat[max] = "transactions.txt";

	H = Inic_hash(H);
	ProcitajDatoteku(H, dat);
	IspisiTablicu(H);
	BrisiTablicu(H);

	return 0;
}

ClientP Inic_client(ClientP C)
{
	C = (ClientP)malloc(sizeof(Client));
	if (C == NULL)
	{
		printf("Greska pri inicijalizaciji clienta.");
		return NULL;
	}
	strcpy(C->id, "");
	strcpy(C->firstName, "");
	strcpy(C->lastName, "");
	return C;
}

DateP Inic_date(DateP D)
{
	D = (DateP)malloc(sizeof(Date));
	if (D == NULL)
	{
		printf("Greska pri inicijalizaciji datuma.");
		return NULL;
	}
	D->day = 0;
	D->month = 0;
	D->year = 0;
	return D;
}

TransactionP Inic_transaction()
{
	TransactionP p = NULL;
	p = (TransactionP)malloc(sizeof(Transaction));
	if (p == NULL)
	{
		printf("Greska pri inicijalizaciji liste.");
		return NULL;
	}
	p->amount = 0.00;
	strcpy(p->description, "");
	strcpy(p->processed, "");
	p->date=Inic_date(p->date);
	p->client=Inic_client(p->client);
	p->next = NULL;
	return p;
}

TablicaP Inic_hash(TablicaP H)
{
	int i;
	H = (TablicaP)malloc(sizeof(Tablica));
	if (H == NULL)
	{
		printf("Greska pri inicijalizaciji tablice.\n");
		return NULL;
	}

	H->lista = (TransactionP*)malloc(sizeof(TransactionP) * velTab);
	if (H->lista == NULL)
	{
		printf("Greska pri inicijalizaciji liste u tablici.\n");
		return NULL;
	}

	for (i = 0;i < velTab;i++)
		H->lista[i] = Inic_transaction();

	return H;
}

int ProcitajDatoteku(TablicaP H, char* dat)
{
	FILE* file = NULL;
	float amount=0.00;
	char description[max] = { 0 }, processed[max] = { 0 }, id[max] = { 0 }, firstName[max] = { 0 }, lastName[max] = { 0 };
	int year=0, month=0, day=0;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return 0;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %f %s %s %s %s %d-%d-%d\n", description, &amount, processed, id, firstName, lastName, &year, &month, &day);
		UnesiUTablicu(H, description, amount, processed, id, firstName, lastName, year, month, day);
	}
	fclose(file);
	return 0;
}

int UnesiUTablicu(TablicaP H, char* description, float amount, char* processed, char* id, char* firstName, char* lastName, int year, int month, int day)
{
	int indeks = 0;
	indeks = Funkcija(H, id);

	UnesiUListu(H->lista[indeks], description, amount, processed, id, firstName, lastName, year, month, day);
	return 0;
}

int Funkcija(TablicaP H, char* id)
{
	int i = 0, suma = 0, duljina = 0;
	duljina = strlen(id);

	for (i = 0;i < duljina;i++)
		suma += id[i];

	return suma % velTab;
}

int UnesiUListu(TransactionP p, char* description, float amount, char* processed, char* id, char* firstName, char* lastName, int year, int month, int day)
{
	TransactionP q = NULL;
	q = Inic_transaction(q);

	q->amount = amount;
	strcpy(q->description, description);
	strcpy(q->processed, processed);
	q->date->year = year;
	q->date->month = month;
	q->date->day = day;
	strcpy(q->client->id, id);
	strcpy(q->client->firstName, firstName);
	strcpy(q->client->lastName, lastName);

	while (p->next != NULL)
	{
		if (Sortiraj_datum(p->next->date, year, month, day) < 0)
			break;
		else if (Sortiraj_datum(p->next->date, year, month, day) == 0)
		{
			if (strcmp(p->next->client->lastName, lastName) < 0)
				break;
			else if (strcmp(p->next->client->lastName, lastName) == 0)
			{
				if (strcmp(p->next->client->firstName, firstName) < 0)
					break;
			}
		}
		p = p->next;
	}
	q->next = p->next;
	p->next=q;
	return 0;
}

Sortiraj_datum(DateP D, int year, int month,int day)
{
	int a = 0;

	a = D->year - year;
	if (a == 0)
	{
		a = D->month - month;
		if (a == 0)
			a = D->day - day;
	}
	return a;
}
int IspisiTablicu(TablicaP H)
{
	int i = 0;

	for (i = 0;i < velTab;i++)
	{
		printf("\n\nRed %d:\n\n", i);
		IspisiListu(H->lista[i]);
	}

	return 0;
}

int IspisiListu(TransactionP p)
{
	p = p->next;
	while (p != NULL)
	{
		printf(" %s %f %s %s %s %s %d-%d-%d\n", p->description, p->amount, p->processed, p->client->id, p->client->firstName, p->client->lastName, p->date->year, p->date->month, p->date->day);
		p = p->next;
	}
	return 0;
}

int BrisiTablicu(TablicaP H)
{
	int i = 0;

	for (i = 0;i < velTab;i++)
		BrisiListu(H->lista[i]);

	return 0;
}

int BrisiListu(TransactionP p)
{
	TransactionP q = NULL;
	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return 0;
}

