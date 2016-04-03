/*Napisac funkcje która tworzy listê jednokierunkow¹ na podstawie pliku
Nag³owek tej funkcji:
twórz(Lista *lista,char * nazwa_pliku)

Zastosowaæ nastêpuj¹ce struktury:
typedef struct Lista
{
 struct Element_ * lista;
 int le;//  

typedef struct Element_
{
 char * nazwisko;
 char * imie;
 int wiek
 } Element;
 
 format pliku: (pierwszy element liczba rekordow)
 2
 Kowalski
 Jan
 Nowak
 Andrzej*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>

#define MAX_SIZE 127

typedef struct Lista_
{
	struct Element* lista;
	int le;
} Lista;

typedef struct Element_
{
	char* nazwisko;
	char* imie;
	int wiek;
	struct Element_* nastepny;
} Element;

int tworz(Lista* lista, char* nazwa_pliku)
{
	// sprawdzenie, czy przekazana w parametrach lista jest pusta - do pelnej nie dodajemy

	if (lista->lista != NULL)
	{
		return -1;
	}
	
	// --- otwrcie pliku, sprawdzenie, czy sie otwarl ---

	FILE* plik;

	plik = fopen(nazwa_pliku, "r");

	if (plik == NULL)
	{
		return -2;
	}

	// deklarujemy zmienna buforowa do przechowywania danych odczytywanych z pliku - rozmiar zdefiniowany makrem, bo (podobno) C lubi makra

	char bufor[MAX_SIZE];

	// odcyztujemy ilosc elementow listy - 1 - szy wiersz pliku

	fgets(bufor, MAX_SIZE, plik);

	lista->le = atoi(bufor);

	// deklarujemy zmienne reprezentujace ogon listy i element tymczasowy - tzn. nowo dodawany; oba inicjalizujemy NULL - em.

	Element* ogon = NULL;
	Element* nowy = NULL;

	// odczytujemy linijka po linijce plik - najpierw do bufora, a ten nastepnie kopiujemy do listy

	while (feof(plik) == NULL)
	{
		nowy = (Element*)malloc(sizeof(Element));					// pamiec na nowy element

		fgets(bufor, MAX_SIZE, plik);								// odczyt kolejnej linijki pliku - imienia
		nowy->nazwisko = (char*)malloc(MAX_SIZE * sizeof(char));	// pamiec na pole struktury Element (bedace wskaznikiem na char, czyli de facto lancuch w stylu C)
		strcpy(nowy->nazwisko, bufor);							// kopiowanie zawartosci bufora do nowo tworzonego elementu listy

		fgets(bufor, MAX_SIZE, plik);
		nowy->imie = (char*)malloc(MAX_SIZE * sizeof(char));
		strcpy(nowy->imie, bufor);

		fgets(bufor, MAX_SIZE, plik);
		nowy->wiek = atoi(bufor);

		nowy->nastepny = NULL;										// wyzerowanie wskaznika na nastepny element po nowym

		if ((lista->lista) == NULL)										// czy lista jest pusta?
		{
			lista->lista = nowy;									// lista->lista pokazuje na wlasnie utworzony element...
			ogon = nowy;											// ... i jest to automatycznie takze ogon tworzonej listy
		}
		else
		{
			ogon->nastepny = nowy;									// doczepienie nowego elementu na koniec istniejacej listy
			ogon = ogon->nastepny;									// aktualizacja ogona
		}
	}

	// zamykamy plik

	fclose(plik);
	return 1;
}

void drukuj(Lista* lista)
{
	if (lista->lista == NULL)
	{
		printf("Lista jest pusta!");
		return;
	}

	Element* pom;

	pom = lista->lista;

	while (pom != NULL)
	{
		printf("Nazwisko: %s\n", pom->nazwisko);
		printf("Imie: %s\n", pom->imie);
		printf("Wiek: %d\n", pom->wiek);

		pom = pom->nastepny;
	}
}

void skasuj(Lista* lista)
{
	Element* smiec;
	Element* pom;

	pom = lista->lista;

	while (pom != NULL)
	{
		smiec = pom;				// jako smiecia przyjmujemy aktualnie przetwarzany element, wskazywany przez pom

		pom = pom->nastepny;		// przesuwamy wskaznik pom na nastepny element listy

		free(smiec->imie);			// zwalniamy pamiec zarezerwowana na imie
		free(smiec->nazwisko);		// zwalniamy pamiec zarezerwowana na nazwisko
		free(smiec);				// zwalniamy pamiec zarezerwowana na smiecia - czyli aktualnie przetwarzany
	}
}

int main()
{
	printf("Program odczytuje plik, a nastepnie tworzy z jego zawartosci liste jednokierunkowa.\nPo utworzeniu listy jej zawartosc jest wyswietlana na ekranie, a nastepnie kasowana.\n");

	char nazwa[MAX_SIZE];

	printf("Podaj nazwe pliku: ");
	scanf("%s", nazwa);

	// deklarujemy strukture typu Lista i ja inicjalizujemy - pole le zerem, a pole lista NULL - em
	
	Lista glowa;

	glowa.le = 0;
	glowa.lista = NULL;

	// wywolujemy funkcje tworzaca, a zwrocona przez nia wartosc zapisuje w zmiennej czy_utworzono

	int czy_utworzono = tworz(&glowa, nazwa);

	switch (czy_utworzono)
	{
	case -1:	printf("Lista nie jest pusta, nie dodajemy nowej zawartosci\n");
				break;
	case -2:	printf("Nie udalo sie otworzyc pliku!\n");
				break;
	case 1:		printf("Plik zostal otwarty, a lista utworzona. Oto ona:\n");
				drukuj(&glowa);
				skasuj(&glowa);
				break;
	default:	printf("Akcja defaultowa");
				break;
	}

	system("pause");
	return 0;
}