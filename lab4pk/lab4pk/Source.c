/*Zadanie 1 (unie)
Dana jest unia:
typedef union Rejestr_
{
unsignded char bajty[4];
unsignet short int slowa[2]; //16 bitowe
usigned int rejestr;//32 bitowy rejestr
} Rejestr;

Napisa� funkcje implementuj�ce:
1) Przesuni�cie cykliczne w lewo o 16 bit�w;
2) Przesuni�cie cykliczne w lewo o 8 bit�w;
3) Przesuni�cie cykliczne w prawo o 8 bit�w;
4) Przesuni�cie w prawo o 1 bit;
5) Przesuni�cie w lewo o 1 bit;
6) Wy�wietla stan rejestru jako liczb� hex;
7) Wy�wietla najm�odzy bajt rejestru jako liczb� hex;
8) Wy�wietla starsze s�owo rejestru jako liczb� hex;
Wszystkie te funkcje przyjmuj� jako parametr wska�nik do Rejestr i nic nie zwracaj�
Przetestowa� wszystkie funkcje dla liczb szesnastkowych;

Zadanie 2 (struktury)
Dana jest struktura;
typedef Slownik_;
{ 
int ls; //liczba wszystkich unikalnych s��w
int h; // wysoko�� drzewa - liczba poziom�w 
Slowo *korzen; 
Slowo *mf; // wska�nik na s�owo najcz�sciej wyst�puj�ce
Slowo **t; // realokowalna tablica wska�nik�w do wszystkich nie powtarzaj�cych si� s��w w drzewie (realokacja co K=1000 element�w)
// pomocna przy sortowaniu (przestawiamy wska�niki) - funkcja nr 2 (dalsza cz�� zadnia)

} Slownik;
typedef Slowo;
{ 
int lw; //liczba wyst�pie� s�owa
char *slowo;// slowo 
Slowo *prawy; //prawy i lewy potomek
Slowo *lewy; //
} Slownik;
1) Napisa� funkcj� kt�ra tworzy slownik na podstwie pliku tekstowego.
(rozmiar minimum 300KB, np. ksi��ka z projektu Gutenberg) -
funkcja powinna korzysta� z pomocniczej funkcji:
Slowo * wstaw(Slownik *s,char *slowo); 
Funkcja zwraca adres nowo wstawionego slowa do drzewa, b�d� NULL gdy slow jest ju� w drewie.
Adres r�ny od NULL wstawiamy do tablicy t. 
2) Napisa� funkcj� kt�ra zapisuje do pliku wszystkie slowa od najcz�ciej do najrzadziej wyst�puj�cych
(skorzysta� z tablicy t).
3) Napisa� funkcj� kt�ra zwraca iloraz wysoko�ci drzewa oraz wysoko�ci tego drzewa 
w przypadku gdyby by�o ono idealnie zr�wnowa�one.*/

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