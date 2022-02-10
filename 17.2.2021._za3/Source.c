#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable :4996 )
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _kafici;
typedef struct _kafici* KaficiPozicija;
struct _ljudi;
typedef struct _ljudi* LjudiPozicija;

typedef struct _kafici
{
	char kafic[max];
	LjudiPozicija ljudi;
	KaficiPozicija next;
}Kafici;

typedef struct _ljudi
{
	char ime[max], prezime[max];
	LjudiPozicija next;
}Ljudi;


KaficiPozicija Inic_kafici(KaficiPozicija p);
LjudiPozicija Inic_ljudi(LjudiPozicija p);
int ProcitajDatoteku(KaficiPozicija p, char* dat);
int UnesiKafice(KaficiPozicija p,char * ime, char* prezime, char* kafic);
int Ispis_kafici(KaficiPozicija p);
int Ispis_ljudi(LjudiPozicija p);
int Trazi(KaficiPozicija p, char* kafic);
KaficiPozicija TraziIstog(KaficiPozicija p, char* kafic);
LjudiPozicija UnesiLjude(LjudiPozicija p, char* ime, char* prezime);
int brisi_kafice(KaficiPozicija p);
int brisi_ljude(LjudiPozicija p);

int main()
{
	KaficiPozicija kafic_head = NULL;
	char dat[max] = "kafici.txt";

	kafic_head = Inic_kafici(kafic_head);

	ProcitajDatoteku(kafic_head, dat);
	Ispis_kafici(kafic_head->next);
	brisi_kafice(kafic_head);
	return 0;
}

KaficiPozicija Inic_kafici(KaficiPozicija p)
{
	p = (KaficiPozicija)malloc(sizeof(Kafici));
	if (p == NULL)
	{
		printf("Greska pri alokaciji kafica.\n");
		return NULL;
	}
	strcpy(p->kafic, "");
	p->ljudi = Inic_ljudi(p->ljudi);
	p->next = NULL;
	return p;
}
LjudiPozicija Inic_ljudi(LjudiPozicija p)
{
	p = (LjudiPozicija)malloc(sizeof(Ljudi));
	if (p == NULL)
	{
		printf("Greska pri alokaciji ljudi.\n");
		return NULL;
	}
	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->next = NULL;
	return p;
}

int Ispis_kafici(KaficiPozicija p)
{
	while (p != NULL)
	{
		printf("%s:\n", p->kafic);
		Ispis_ljudi(p->ljudi);
		p = p->next;
	}
	return 0;
}
int Ispis_ljudi(LjudiPozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s %s\n", p->ime, p->prezime);
		p = p->next;
	}
	return 0;
}

int ProcitajDatoteku(KaficiPozicija p, char* dat)
{
	FILE* file = NULL;
	KaficiPozicija pom = NULL;
	char ime[max] = { 0 }, prezime[max] = { 0 }, kafic[max] = { 0 };
	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s %s\n", ime, prezime, kafic);
		if(Trazi(p, kafic)==0)
			UnesiKafice(p, ime, prezime, kafic);
		else
		{
			pom = TraziIstog(p, kafic);
			UnesiLjude(pom->ljudi, ime, prezime);
		}
	}
	fclose(file);
	return 0;
}

int UnesiKafice(KaficiPozicija p, char* ime, char* prezime, char* kafic)
{
	KaficiPozicija q = NULL, pom=p;
	q = Inic_kafici(q);
	strcpy(q->kafic, kafic);
	q->ljudi = UnesiLjude(q->ljudi, ime, prezime);

	while (p->next != NULL)
	{
		if (strcmp(p->next->kafic, kafic) > 0 )
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	
	return 0;
}

LjudiPozicija UnesiLjude(LjudiPozicija p, char* ime, char* prezime)
{
	LjudiPozicija q = NULL;
	q = Inic_ljudi(q);
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);

	while (p->next != NULL)
	{
		if (strcmp(p->ime, ime) > 0)
			break;
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return p;
}

int Trazi(KaficiPozicija p, char* kafic)
{
	p = p->next;
	while (p != NULL)
	{
		if (strcmp(p->kafic, kafic) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}

KaficiPozicija TraziIstog(KaficiPozicija p, char* kafic)
{
	p = p->next;
	while (p != NULL)
	{
		if (strcmp(p->kafic, kafic) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

int brisi_kafice(KaficiPozicija p)
{
	KaficiPozicija q = NULL;
	while (p->next != NULL)
	{
		q = p->next;
		brisi_ljude(q->ljudi);
		p->next = p->next->next;
		free(q);
	}
	return 0;
}
int brisi_ljude(LjudiPozicija p)
{
	LjudiPozicija q = NULL;
	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return 0;
}