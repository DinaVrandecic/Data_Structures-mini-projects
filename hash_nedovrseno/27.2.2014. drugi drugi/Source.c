//Napisati program koji iz datoteke èita podatke o broju bodova koje je jedan student dobio na ispitu
//(struct _student {
//	char ime[128];char prezime[128];int broj_bodova; int relativni_broj_bodova;struct
//		_student* left; ;struct _student right;
//}) i sprema ih u binarno stablo pretraživanja. (Napomena : 0 <
//	broj_bodova <= 100).Ispisati binarno stablo na „inorder“ naèin.
//	U tako kreiranom binarnom stablu potrebno je za svakog od studenata izraèunati i relativan broj bodova
//	po formuli : relativan_broj_bodova = (broj_bodova / MAX(broj_bodova)).Ispisati binarno stablo na
//	„preorder“ naèin.
#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _stablo;
typedef struct _stablo* StabloPozicija;
typedef struct _stablo
{
	char ime[max], prezime[max];
	int bodovi;
	double bodovi_rel;
	StabloPozicija L, D;
}Stablo;

StabloPozicija Inicijalizacija(StabloPozicija S);
StabloPozicija ProcitajDatoteku(StabloPozicija S, char* dat);
StabloPozicija UnesiUStablo(StabloPozicija S, char* ime, char*  prezime,int bodovi);
StabloPozicija RelativniBodovi(StabloPozicija S, int *suma, StabloPozicija maks);
StabloPozicija IzracunSume(StabloPozicija S, int *suma);
StabloPozicija TraziMax(StabloPozicija S);
int inorder(StabloPozicija S);
int preorder(StabloPozicija S);

int main()
{
	char dat[max] = "tekst.txt";
	StabloPozicija root = NULL, maks=NULL;
	int suma = 0;

	root=ProcitajDatoteku(root, dat);
	inorder(root);
	IzracunSume(root, &suma);
	printf("\n%d\n", suma);
	maks = TraziMax(root);
	root=RelativniBodovi(root, &suma, maks);
	preorder(root);
	return 0;
}

StabloPozicija Inicijalizacija(StabloPozicija S)
{
	S = (StabloPozicija)malloc(sizeof(Stablo));
	if (S == NULL)
	{
		printf("Greska pri inicijalizaciji stabla.\n");
		return NULL;
	}
	S->D = NULL;
	S->L = NULL;
	strcpy(S->ime, "");
	strcpy(S->prezime, "");
	S->bodovi = 0;
	S->bodovi_rel = 0.0;

	return S;
}

StabloPozicija ProcitajDatoteku(StabloPozicija S, char* dat)
{
	FILE* file = NULL;
	char ime[max] = { 0 }, prezime[max] = { 0 };
	int bodovi = 0;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return NULL;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s %d\n", ime, prezime, &bodovi);
		S = UnesiUStablo(S, ime, prezime, bodovi);
	}

	fclose(file);
	return S;
}

StabloPozicija UnesiUStablo(StabloPozicija S, char* ime, char* prezime, int bodovi)
{
	if (S == NULL)
	{
		S = Inicijalizacija(S);
		S->bodovi = bodovi;
		strcpy(S->ime, ime);
		strcpy(S->prezime, prezime);
	}
	else if (bodovi < S->bodovi)
		S->L = UnesiUStablo(S->L, ime, prezime, bodovi);
	else if (bodovi > S->bodovi)
		S->D = UnesiUStablo(S->D, ime, prezime, bodovi);

	return S;
}

int inorder(StabloPozicija S)
{
	if (S == NULL)
		return NULL;

	inorder(S->L);
	printf("%s %s %d\n", S->ime, S->prezime, S->bodovi);
	inorder(S->D);
	return 0;
}

int preorder(StabloPozicija S)
{
	if (S == NULL)
		return NULL;

	printf("%s %s %d %lf\n", S->ime, S->prezime, S->bodovi, S->bodovi_rel);
	preorder(S->L);
	preorder(S->D);
	return 0;
}
StabloPozicija IzracunSume(StabloPozicija S, int *suma)
{
	if (S == NULL)
		return NULL;

	*suma += S->bodovi;
	S->L = IzracunSume(S->L, suma);
	S->D = IzracunSume(S->D, suma);

	return S;
}

StabloPozicija RelativniBodovi(StabloPozicija S, int *suma, StabloPozicija maks)
{
	if (S == NULL)
		return NULL;

	//S->bodovi_rel = ((float)S->bodovi / *suma);
	S->bodovi_rel = ((float)S->bodovi / maks->bodovi);
	S->L = RelativniBodovi(S->L, suma, maks);
	S->D = RelativniBodovi(S->D, suma, maks);

	return S;
}

StabloPozicija TraziMax(StabloPozicija S)
{
	if (S == NULL)
		return NULL;

	if (S->D == NULL)
		return S;
	else
		return TraziMax(S->D);
}