#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (50)

struct _stog;
typedef struct _stog* pozicija;
typedef struct _stog
{
	int broj;
	pozicija next;
}stog;

char* ProcitajFile(char* dat);
int StringUPostfix(char* buffer, double* rezultat);
pozicija Inicijaliziraj(pozicija p);
int PopIOperacija(pozicija p, char operacija, double* rezultat);
int UmetniNakon(pozicija head, pozicija el);
int Pop(pozicija head, double* rezultat);
pozicija StvoriElement(int broj);

int main()
{
	char dat[max] = "postfiks.txt";
	char* buffer = NULL;
	double rezultat = 0;

	buffer=ProcitajFile(dat);
	StringUPostfix(buffer, &rezultat);
	printf("\n%lf\n", rezultat);
	return 0;
}

char* ProcitajFile(char* dat)
{
	FILE* file = NULL;
	int duljina = 0;
	char* buffer = NULL;

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return NULL;
	}

	fseek(file, 0, SEEK_END); //postavljamo pokazivac na pocetak file-a
	duljina = ftell(file);  //trazimo duljinu file-a

	buffer = (char*)calloc(duljina + 1, sizeof(char));
	if (buffer == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return NULL;
	}

	rewind(file); 
	fread(buffer, sizeof(char), duljina, file);
	printf("%s \n", buffer);

	fclose(file);
	return buffer;
}
int StringUPostfix(char* buffer, double* rezultat)
{
	pozicija head = NULL, element = NULL;
	int status = 0, BrojBajtova=0;
	double broj = 0.0;
	char operacija = NULL;

	head = Inicijaliziraj(head);

	while (strlen(buffer) > 0)
	{
		status = sscanf(buffer, "%lf %n", &broj, &BrojBajtova); //vraca broj pohranjenih varijabli
		if (status != 1)  //ako smo dosli do operacije
		{
			sscanf(buffer, " %c %n", &operacija, &BrojBajtova);
			PopIOperacija(head, operacija, rezultat);
			broj = *rezultat;
		}
		element = StvoriElement(broj);

		buffer += BrojBajtova;
		printf("%s->", buffer);
		UmetniNakon(head, element);
	}
	Pop(head, rezultat);
	if (head->next)
	{
		printf("Nije valjan postfiks.");
		return -1;
	}
	return 0;
}
int UmetniNakon(pozicija head, pozicija el)
{
	el->next = head->next;
	head->next = el;

	return 0;
}


pozicija Inicijaliziraj(pozicija p)
{
	p = (pozicija)malloc(sizeof(stog));

	p->broj = 0;
	p->next = NULL;

	return p;
}

pozicija StvoriElement(int broj)
{
	pozicija q = NULL;
	
	q = (pozicija)malloc(sizeof(stog));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -2;
	}

	q->broj = broj;
	q->next = NULL;

	return q;
}
int PopIOperacija(pozicija head, char operacija, double* rezultat)
{
	double br1 = 0, br2 = 0;

	Pop(head, &br1);
	Pop(head, &br2);

	switch (operacija)
	{
	case '+':
		*rezultat = br2 + br1;  //mora ici prvo broj koji se drugi popa sa stoga (vidi u biljeznici)!!!!
		break;
	case '-':
		*rezultat = br2 - br1;
		break;
	case '*':
		*rezultat = br2 * br1;
		break;
	case '/':
		*rezultat = br2 /br1;
		break;
	default:
		printf("Ta operacija nije jos unesena.");
		return -2;
	}

	return 0;
}
int Pop(pozicija head, double* rezultat)
{
	pozicija izbrisi = NULL;
	izbrisi = Inicijaliziraj(izbrisi);

	izbrisi = head->next;
	
	head->next = izbrisi->next;
	*rezultat = izbrisi->broj;  //vraca broj sa stoga

	free(izbrisi);
	return 0;
}
