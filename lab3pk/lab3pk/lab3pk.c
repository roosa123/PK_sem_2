/*Dana jest struktura:
typedef struct Tekst_
{
 char *t; //wskaŸnik na tekst
 int r;// rozmiar tekstu w bajtach
 int lw; // liczba wyrazów w tekœcie 
 
} Tekst;
 
Napisaæ funkcjê która wczytuje dowolny plik tekstowy do struktury powy¿ej ustawia pola s lw.
Nag³ówek funkcji:
void czytaj(Tekst *mt,char * nazwa_pliku)
W oparciu o funkcjê biblioteczn¹ strstr() napisaæ funkcjê która znajduje wzorzec w tekœcie i zwraca do niego
wskaŸnik.
Nag³ówek tej  funkcji:   char *  znajdz(Tekst *mt,char * wzorzec, int offset)
W oparciu o t¹ funkcje znaleŸæ wszystkie wyst¹pienia danego tekstu. Parametr offset wykorzystywany jest 
przy kontynuacji wyszukiwania (offset=0 przy pierwszym wywo³aniu funkcji znajdz)
W oparciu o funkcje biblioteczne strcmp i qsort napisaæ funkcjê ktora sortuje wszystkie wyraazy w tekœcie.
Nag³ówek funkcji:
Tekst * sortuj(Tekst *mt); //zwraca tekst posortowany.*/

#define _CRT_NO_SECURE_WARNINGS

#include<stdlib.h>
#include<stdio.h>

#define MAX_SIZE 255

typedef struct Tekst_
{
	char *t; //wskaŸnik na tekst
	int r;// rozmiar tekstu w bajtach
	int lw; // liczba wyrazów w tekœcie 

} Tekst;

void czytaj(Tekst *mt, char * nazwa_pliku)
{
	FILE* plik;

	plik = fopen(nazwa_pliku, "r");

	if (plik == NULL)
	{
		printf("Plik si enie otwarl!");
		return;
	}

	fseek(plik, 0, SEEK_END);

	mt->r = ftell(plik);

	/*
	while (feof(plik) != NULL)
	{
		++(mt->r);
	}
	*/

	mt->t = (char*)malloc(mt->r * sizeof(char));

	fseek(plik, 0, SEEK_SET);

	char* kolejny_wyraz[MAX_SIZE];

	mt->lw = 0;

	while (feof(plik) != NULL)
	{
		fscanf(plik, "%s", kolejny_wyraz);
		/*
		kolejny_znak = (char*)fgetc(plik);
		*/
		strcat(mt->t, kolejny_wyraz);
		++(mt->lw);
	}

	fclose(plik);
}

char* znajdz(Tekst* mt, char* wzorzec, int* offset)
{
	// offset - pozycja poczatku ostatniego wystapienia

	/*char* znaleziony;

	if (offset == 0)
	{
		znaleziony = strstr(wzorzec, mt->t);
	}
	else
		while (offset != 0 && offset != mt->r)
		{
			znaleziony = strstr(wzorzec, mt->t);
		}

	while (znaleziony == NULL)
	{

	}*/

	char* znaleziony;

	if (*offset != 0)
		znaleziony = &(mt->t[*offset]);
	else
		znaleziony = mt->t;

	znaleziony = strstr(++znaleziony, wzorzec);

	return znaleziony;
}

Tekst* sortuj(Tekst *mt)
{

}

int main()
{
	Tekst tekst_z_pliku;
	
}