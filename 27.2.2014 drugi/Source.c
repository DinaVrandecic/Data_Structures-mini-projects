#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define max (1024)

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	char rijec[max];
	pozicija L;
	pozicija D;
}stablo;

pozicija ProcitajDatoteku(pozicija S, char* dat);
pozicija Inicijaliziraj(pozicija root);
pozicija UnesiUStablo(pozicija S, char* rijec);
pozicija UnesiUDatoteke(pozicija root, char* sugl, char* samogl);
int Unesi(pozicija S, char*samogl);
pozicija Brisi(pozicija S);


int main()
{
	pozicija root = NULL;
	char dat[max] = "datoteka.txt", dat1[max] = "suglasnik.txt", dat2[max] = "samoglasnik.txt";

	root = Inicijaliziraj(root);
	root = ProcitajDatoteku(root, dat);
	UnesiUDatoteke(root, dat1, dat2);
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
	S->L = NULL;
	S->D = NULL;

	return S;
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

	return S;
}

pozicija UnesiUDatoteke(pozicija S, char* sugl, char* samogl)
{
	if (S == NULL)
		return NULL;

	S->L = UnesiUDatoteke(S->L, sugl, samogl);

	if (S->rijec[0] == 'a' || S->rijec[0] == 'e' || S->rijec[0] == 'i' || S->rijec[0] == 'o' || S->rijec[0] == 'u')
	{
		Unesi(S,samogl);
	}
	else
	{
		Unesi(S, sugl);
	}

	S->D = UnesiUDatoteke(S->D, sugl, samogl);

	return S;
}

int Unesi(pozicija S, char* dat)
{
	FILE* file = NULL;
	file = fopen(dat, "a+");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}
	
	fprintf(file, " %s", S->rijec);

	return 0;
}

pozicija Brisi(pozicija S)
{
	if (S != NULL)
	{
		Brisi(S->L);
		Brisi(S->D);
		free(S);
	}
	return NULL;
}