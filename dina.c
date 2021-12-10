#include<stdio.h>
#include<stdlib.h>

struct _stablo;
typedef struct _stablo *pozicija;
typedef struct _stablo{
	char ime[50];
	pozicija child;
	pozicija sibling;
}

pozicija umetni(pozicija trenutni, pozicija new);

int main(){
	int x=1, y=0;
	pozicija parent=NULL;


	while(x)
	{
		printf("1- md, 2 - cd dir, 3 - cd.., 4 - dir, 5 – izlaz"); //cd .. pomocu stoga push
		scanf("%d", &y);

		switch(y)
		{
		case '1':
				parent->child =umetni(parent->child, new);
				break;
		case ''5:
			x=0;
			break;
		}
	}

	return 0;
}

pozicija umetni(pozicija trenutni, pozicija new)
{
	if(trenutni == NULL)
		return new;
	
	if(strcmp(trenutni->ime, new->ime)<0)
	{
		trenutni->sibling=umetni(trenutni->sibling, new);
	}else if(strcmp(trenutni->ime, new->ime){
		new->sibling=trenutni;
		return new;
	}
	return trenutni;
}

