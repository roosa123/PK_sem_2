/*Napisac funkcje która tworzy listê jednokierunkow¹ na podstawie pliku
Nag³owek tej funkcji:
twórz(Lista *lista,char * nazwa_pliku)

Zastosowaæ nastêpuj¹ce struktury:
typedef struct Lista
{
struct Element_ *lista;
int le;//

typedef struct Element_
{
char *nazwisko;
char *imie;
int wiek
} Element;

format pliku: (pierwszy element liczba rekordow)
2
Kowalski
Jan
54
Nowak
Andrzej
12*/

#include<stdio.h>

typedef struct Lista_
{
	struct Element_ *lista;
	int le;
} Lista;

typedef struct Element_
{
	char *nazwisko;
	char *imie;
	int wiek;
	struct Element_ *nastepny;
} Element;

void tworz(Lista *glowa, char * nazwa_pliku)
{
	FILE *fp;
	fp = fopen(nazwa_pliku, "r");

	if (!fp)
	{
		printf("Nie mozna otworzyc pliku");
		return;
	}

	if (!glowa)
	{
		glowa = malloc(sizeof(Lista));
	}

	fscanf(fp, "%d", glowa->le);

	Element *ogon;

	while (!feof(fp))
	{
		if (!(glowa->lista))
		{
			glowa->lista = malloc(sizeof(Element));

			ogon = glowa->lista;
		}
		else
		{
			ogon->nastepny = malloc(sizeof(Element));
			ogon = ogon->nastepny;
		}

		ogon->nazwisko = gets(fp);
		ogon->imie = gets(fp);
		ogon->wiek = gets(fp);
	}
}

void drukuj(Lista *glowa)
{
	Element *pom;

	pom = glowa->lista;

	while (pom)
	{
		printf("Nazwisko: ", pom->nazwisko);
		printf("Imie: ", pom->imie);
		printf("Wiek: ", pom->wiek);

		pom = pom->nastepny;
	}
}

int main(int argc, char** argv[])
{
	char *nazwa_pliku[255];

	printf("Podaj nazwe pliku: ");
	scanf("%s", &nazwa_pliku);

	Lista *glowa;

	tworz(glowa, nazwa_pliku);

	if (glowa)
	{
		drukuj(glowa);
	}

	system("pause");
	return 0;
}
