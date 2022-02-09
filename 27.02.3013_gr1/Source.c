//Napisati program kojim se
//a) Sluèajnim uzorkom generira 100 brojeva iz opsega od 300 do 700, te ih sprema u binarno stablo
//pretraživanja.Zatim ispišemo to stablo u preorder naèinu ispisa.
//b) Iz generiranog stabla pretraživanja izbrisati sve elemente koji su zapisani u proizvoljno
//definiranoj datoteci.
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define max (60)

struct _stablo;
typedef struct _stablo* pozicija;
typedef struct _stablo
{
	int broj;
	pozicija L, D;
}Stablo;

pozicija Inicijaliziraj(pozicija S);
pozicija generiraj(pozicija S);
pozicija UnesiUStablo(pozicija S,int broj);
int preorder(pozicija S);
int UnesiUDatoteku(pozicija dat, int broj);
pozicija ProcitajDat(pozicija S,char* dat);
pozicija BrisiBrojeve(pozicija S,int broj);
pozicija TraziMin(pozicija S);

int main()
{
	pozicija root = NULL;
	char dat[max] = { 0 }, ch = { 0 };
	int x = 1, broj=0;
	srand(time(NULL));
	root=generiraj(root);
	preorder(root);
	printf("Unesi ime datoteke: ");
	scanf(" %s", dat);
	printf("\nOdaberi 1)unesi broj 2)izlaz iz petlje.\n");
	while (x)
	{
		scanf(" %c", &ch);
		switch (ch)
		{
		case '1':
			printf("\nUpisi broj: ");
			scanf("%d", &broj);
			UnesiUDatoteku(dat, broj);
			break;
		case '2':
			printf("Izalzak iz petlje.\n");
			x = 0;
			break;
		}
	}
	root=ProcitajDat(root, dat);

	preorder(root);
	return 0;
}

pozicija Inicijaliziraj(pozicija S)
{
	S = (pozicija)malloc(sizeof(Stablo));
	if (S == NULL)
	{
		printf("Greska pri alokaciji memorije.\n");
		return NULL;
	}
	S->broj = 0;
	S->D = NULL;
	S->L = NULL;
	return S;
}

int preorder(pozicija S)
{
	if (S == NULL)
		return NULL;

	printf("%d   ", S->broj);
	preorder(S->L);
	preorder(S->D);

	return 0;
}

pozicija generiraj(pozicija S)
{
	int i = 0, broj=0;

	for (i = 0;i < 100;i++)
	{
		broj = (rand() % (700 - 300 + 1)) + 300;
		S = UnesiUStablo(S, broj);
	}
	return S;
}

pozicija UnesiUStablo(pozicija S, int broj)
{
	if (S == NULL)
	{
		S = Inicijaliziraj(S);
		S->broj = broj;
	}
	else if (broj < S->broj)
		S->L = UnesiUStablo(S->L, broj);
	else if (broj > S->broj)
		S->D = UnesiUStablo(S->D, broj);

	return S;
}

int UnesiUDatoteku(pozicija dat,int broj)
{
	FILE* file = NULL;
	
	file = fopen(dat, "a+");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	fprintf(file, "%d ", broj);
	fclose(file);
	return 0;
}

pozicija ProcitajDat(pozicija S, char* dat)
{
	FILE* file = NULL;
	int broj = 0;

	file = fopen(dat, "a+");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return NULL;
	}

	while (!feof(file))
	{
		fscanf(file, "%d ", broj);
		S = BrisiBrojeve(S, broj);
	}

	fclose(file);
	return S;
}

pozicija BrisiBrojeve(pozicija S, int broj)
{
	pozicija temp = NULL;
	if (S == NULL)
		printf("Nema ga.\n");
	else if (broj < S->broj)
		S->L = BrisiBrojeve(S->L, broj);
	else if (broj > S->broj)
		S->D = BrisiBrojeve(S->D, broj);
	else if (S->L != NULL && S->D != NULL)
	{
		temp = TraziMin(S->D);
		S->broj = temp->broj;
		S->D = BrisiBrojeve(S->D, S->broj);
	}
	else
	{
		temp = S;
		if (S->L == NULL)
			S = S->D;
		else
			S = S->L;
		free(temp);
	}
	return S;
}

pozicija TraziMin(pozicija S)
{
	if (S == NULL)
		return NULL;
	else if (S->L == NULL)
		return S;
	else
		return TraziMin(S->L);
}
