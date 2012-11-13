/**
Użycie: ./generuj ILOSCWYRAZOW ILOSCZNAKOW PoczatekAlfabetu KoniecAlfabetu >> nazwapliku.txt
Kompilacja: gcc generujStringi.c -o generuj
*/

#include<stdio.h>
#include<time.h>
int n=0,k=0;
int i,y;
int seed;

int main(int arc, char *argv[])
{
	n = atoi(argv[1]);
	k = atoi(argv[2]);
	char min_alphabet = *argv[3];
	char max_alphabet = *argv[4];
	srand(time(NULL));

	for (i=0;i<=n-1;i++)
	{
		unsigned int randomStr;
		randomStr = rand()%(1-k)+1;

		for (y=0;y<=randomStr-1;y++)
		{
			unsigned int randomizer;
			randomizer = rand();
			char ch = 'A' + randomizer % ((max_alphabet - min_alphabet) + 1);
			printf("%c",ch);
		}
		printf("\n");
	}
}
