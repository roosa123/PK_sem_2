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
W oparciu o funkcje biblioteczne strcmp i qsort napisaæ funkcjê ktora sortuje wszystkie wyrazy w tekœcie.
Nag³ówek funkcji:
Tekst * sortuj(Tekst *mt); //zwraca tekst posortowany.*/

#include<stdio.h>
#include<stdlib.h>
#include<cstring>

typedef struct Tekst_
{
 char *t;	//wskaŸnik na tekst
 int r;		// rozmiar tekstu w bajtach
 int lw;	// liczba wyrazów w tekœcie 
} Tekst;

typedef struct lista_
{
 char *tok;	// wskaŸnik na kolejny token
 lista *nast;
} lista;

// funkcja wczytujaca tekst z pliku i ustalajaca jego rozmiar

void czytaj(Tekst *mt, char *nazwa_pliku)
{
	FILE *pliczek;
	pliczek = fopen(nazwa_pliku, "r");

	if (!pliczek)
	{
		printf("Plik sie nie otwarl!");

		return;
	}

	fseek(pliczek, 0, SEEK_END);							// fseek ustawia wewnêtrzny wskaznik w pliku na wskazana pozycje. 0 (tu) to ilosc bajtow, o jaka ma byc przesuniety wskaznik wzgledem pozycji podanej jako trzeci argument, SEEK_END to pozycja koncowa w pliku (sa tez SEEK_CUR, czyli pozycja aktualna i SEEK_SET, czyli poczatek pliku)

	mt->r = ftell(pliczek);									// zwraca pozycje, na ktorej ustawiony jest wewnetrzny wskaznik pliku, tu bedzie to koniec, a wiec zarazem i rozmiar pliku

	fseek(pliczek, 0, SEEK_SET);							// powwrot wskaznikiem na poczatek

	mt->t = (char*)malloc(mt->r * sizeof(char) + 1);			// alokujemy pamiec o takim rozmiarze, aby wszedl caly plik (+ 1 jest na zero konczace lancuch

	char *zapis;

	zapis = fgets(mt->t, mt->r, pliczek);					// fgets zwraca wskaznik na mt->t (tak, to jest powtarzanie sie w koleczko), tzn. na "stringa", jaki zostal podany jako 1szy argument. Wczytuje tyle znakow, ile wynosi 2gi argument (czyli mt->r) z pliku (3 argument).

	if (!zapis)
		if (ferror(pliczek))
		{
			printf("wystapil blad w strumieniu!");

			fclose(pliczek);
			return;
		}
		
	fclose(pliczek);
}

// funkcja znajdujaca wzorzec we wczytanym tekscie

char* znajdz(Tekst *mt, char *wzorzec, int offset)
{
	// strstr zwraca ADRES na pierwsze wystapienie lancucha wzorcowego
	// czy zwiekszenie tego adresu o offset spowoduje rozpoczecie wyszukiwania od ostatniego miejsca wystapienia (jak w assemblerze?)

	
	char *znaleziony;									// wskaznik pomocniczy na lancuch, ktorego szukamy, bedziemy go nastepnie zwracac, chociaz w zasadzie mozna by te, trzecia i ostatnia linie sciac do zapisu return strstr(przeszukiwany, wzorzec); - ale bez przesady z robieniem funkcji skladajacej sie z 2 linii :D

	char *przeszukiwany = mt + offset;					// wykorzystujemy fakt, ze lancuch jest tablica, a zwiekszenie o pewna liczbe X wskaznika na poczatek tablicy (i jakiegokolwiek innego) skutkuje przesunieciem go na miejsce w pamieci oddalone o X * N bajtow, gdzie N to rozmiar typu, na jaki wskazuje zwiekszany wskaznik, np. int* ptr; ptr + 2 poskutkuje przesuniecem wskaznika ptr o 2 * sizeof(int) bajtow

	znaleziony = strstr(przeszukiwany, wzorzec);

	return znaleziony;
}

Tekst* sortuj(Tekst *mt)
{
	// 1. dzielimy tekst na slowa - zapisujemy najpierw do listy pomocniczej, a jak juz bedziemy wiedziec, ile ich jest - do tablicy

	int licznik = 1;

	lista *glowa;
	lista* pom;

	glowa = (lista*)malloc(sizeof(lista));

	glowa->tok = (char*)malloc(sizeof(char*));
	glowa->tok = strtok(mt->t, " ");
	glowa->nast = NULL;

	pom = glowa;

	while (pom->tok)
	{
		pom = pom->nast;
		pom = (lista*)malloc(sizeof(lista));
		pom->tok = (char*)malloc(sizeof(char*));
		pom->tok = strtok(mt->t, " ");
		pom->nast = NULL;

		++licznik;
	}

	// 2. tablica dynamiczna zawierajaca wskazniki na tokeny

	char** tablica_tokenow;

	tablica_tokenow = (char**)malloc(licznik * sizeof(char*));

	pom = glowa;

	for (int i = 0; i < licznik; ++i)
	{
		tablica_tokenow[i] = pom->tok;
		pom = pom->nast;
	}

	// 3. sortujemy :D

	qsort(tablica_tokenow, licznik, sizeof(char*), strcmp);


}

int main()
{

}