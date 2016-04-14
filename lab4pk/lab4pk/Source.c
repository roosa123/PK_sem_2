/*Zadanie 1 (unie)
Dana jest unia:
typedef union Rejestr_
{
unsignded char bajty[4];
unsignet short int slowa[2]; //16 bitowe
usigned int rejestr;//32 bitowy rejestr
} Rejestr;

Napisaæ funkcje implementuj¹ce:
1) Przesuniêcie cykliczne w lewo o 16 bitów;
2) Przesuniêcie cykliczne w lewo o 8 bitów;
3) Przesuniêcie cykliczne w prawo o 8 bitów;
4) Przesuniêcie w prawo o 1 bit;
5) Przesuniêcie w lewo o 1 bit;
6) Wyœwietla stan rejestru jako liczbê hex;
7) Wyœwietla najm³odzy bajt rejestru jako liczbê hex;
8) Wyœwietla starsze s³owo rejestru jako liczbê hex;
Wszystkie te funkcje przyjmuj¹ jako parametr wskaŸnik do Rejestr i nic nie zwracaj¹
Przetestowaæ wszystkie funkcje dla liczb szesnastkowych;

Zadanie 2 (struktury)
Dana jest struktura;
typedef Slownik_;
{ 
int ls; //liczba wszystkich unikalnych s³ów
int h; // wysokoœæ drzewa - liczba poziomów 
Slowo *korzen; 
Slowo *mf; // wskaŸnik na s³owo najczêsciej wystêpuj¹ce
Slowo **t; // realokowalna tablica wskaŸników do wszystkich nie powtarzaj¹cych siê s³ów w drzewie (realokacja co K=1000 elementów)
// pomocna przy sortowaniu (przestawiamy wskaŸniki) - funkcja nr 2 (dalsza czêœæ zadnia)

} Slownik;
typedef Slowo;
{ 
int lw; //liczba wyst¹pieñ s³owa
char *slowo;// slowo 
Slowo *prawy; //prawy i lewy potomek
Slowo *lewy; //
} Slownik;
1) Napisaæ funkcjê która tworzy slownik na podstwie pliku tekstowego.
(rozmiar minimum 300KB, np. ksi¹¿ka z projektu Gutenberg) -
funkcja powinna korzystaæ z pomocniczej funkcji:
Slowo * wstaw(Slownik *s,char *slowo); 
Funkcja zwraca adres nowo wstawionego slowa do drzewa, b¹dŸ NULL gdy slow jest ju¿ w drewie.
Adres ró¿ny od NULL wstawiamy do tablicy t. 
2) Napisaæ funkcjê która zapisuje do pliku wszystkie slowa od najczêœciej do najrzadziej wystêpuj¹cych
(skorzystaæ z tablicy t).
3) Napisaæ funkcjê która zwraca iloraz wysokoœci drzewa oraz wysokoœci tego drzewa 
w przypadku gdyby by³o ono idealnie zrównowa¿one.*/

#include<stdio.h>


typedef union Rejestr_
{
	unsigned char bajty[4];
	unsigned short int slowa[2];	//16 bitowe
	unsigned int rejestr;			//32 bitowy rejestr
} Rejestr;

void cykliczna_w_lewo_16(Rejestr *przesun)
{
	int n = 16;

	int rozmiar = sizeof(przesun->rejestr);

	(przesun->rejestr << n) | (przesun->rejestr >> (rozmiar - n));
}

void cyklicznie_w_lewo_8(Rejestr *przesun)
{
	int n = 8;

	int rozmiar = sizeof(przesun->rejestr);

	if (!przesun->rejestr)
		if(!przesun->bajty)
			if (przesun->slowa)
			{
				rozmiar = sizeof(przesun->slowa);
				(przesun->slowa << n) | (przesun->slowa >> (rozmiar - n));
			}
			else
			{
				printf("klops :(");
			}
		else
		{
			rozmiar = sizeof(przesun->slowa);
			(przesun->bajty << n) | (przesun->bajty >> (rozmiar - n));
		}
	else
	{
		rozmiar = sizeof(przesun->slowa);
		(przesun->rejestr << n) | (przesun->rejestr >> (rozmiar - n));
	}
}

void cykliczne_w_prawo_8(Rejestr *przesun)
{
	int n = 8;
	int rozmiar = sizeof(przesun->rejestr);

	(przesun->rejestr >> n) | (przesun->rejestr << (rozmiar - n));
}

void w_prawo_1(Rejestr *przesun)
{
	int n = 1;
	int rozmiar = sizeof(przesun->rejestr);

	przesun->rejestr >> n;
}

void w_lewo_1(Rejestr *przesun)
{
	int n = 1;
	int rozmiar = sizeof(przesun->rejestr);

	przesun->rejestr << n;
}

void stan_rejestru(Rejestr *pokaz)
{
	if (pokaz->bajty)
		printf("stan rejestru: %x", pokaz->bajty);
	else
		if (pokaz->rejestr)
			printf("stan rejestru: %x", pokaz->rejestr);
		else
			if (pokaz->slowa)
				printf("stan rejstru: %x", pokaz->slowa);
}

int main()
{

}