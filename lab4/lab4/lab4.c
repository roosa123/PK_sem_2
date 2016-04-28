/*Napisaæ program który wczytuje pliki binarne  do tablicy dynamicznej tab:
Hex * tab;
typedef struct HexByte
 {
   char [2]; // reprezntacja bajtu w postaci 16-owej (ascii)
   unsigned char;// w postci binarnej
 } HexByte
 
Program wywo³uje siê z lini komend (cmd) z nastepuj¹cymi opcjami:
hex.exe plik.in -ot plik.txt // zapisuje wczytany plik w postaci tekstowej
hex.exe plik.in -ob plik.bin  // zapisuje wczytany plik w postaci binarne
hex.exe plik.in  -d FA36  // usuwa z pliku ci¹g bajtów 
hex.exe plik.in  -r  DB A908 FFAA33 // zastêpuje jeden ci¹g bajtów innym ci¹giem
Opcje -d i -r mog¹ wystêpowaæ z opcj¹ -ot albo -ob*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ROZMIAR 1024

typedef struct HexByte_
{
	char bajt_hex[2]; // reprezntacja bajtu w postaci 16-owej (ascii)
	unsigned char bajt_bin;// w postci binarnej
} HexByte;

enum PRZELACZNIKI
{
	TXT,
	BIN,
	USUN,
	ZASTAP
};

int czytaj_parametry(int ile_parametrow, char** przelaczniki)
{
	// flagi do porownywania parametrow

	char *zapisz_txt;
	char *zapisz_bin;
	char *usun_bajty;
	char *zastap_bajty;

	strncpy(zapisz_txt, "-ot", strlen("-ot"));
	strncpy(zapisz_bin, "-ob", strlen("-ob"));
	strncpy(usun_bajty, "-d", strlen("-d"));
	strncpy(zastap_bajty, "-r", strlen("-r"));

	int porownaj;

	int parametry[3];

	int ile_znaleziono = 0;

	// -d, -ob, -ot, -r

	for (int i = 2; i < ile_parametrow; ++i)
	{
		porownaj = strcmp(przelaczniki[i], zapisz_bin);

		if (porownaj > 0)
		{
			porownaj = strcmp(przelaczniki[i], zapisz_txt);
			if (porownaj == 0)
				parametry[ile_znaleziono] = TXT;
			else
				parametry[ile_znaleziono] = ZASTAP;
		}
		else
			if (porownaj < 0)
				parametry[ile_znaleziono] = USUN;
			else
				parametry[ile_znaleziono] = BIN;
	}

	return parametry;
}

void wczytaj_plik(char* nazwa_pliku)
{
	FILE *pliczek;
	pliczek = fopen(nazwa_pliku, "rb");

	char* bufor;
	bufor = (char*)malloc(ROZMIAR * sizeof(char));

	fread(bufor, sizeof(char), ROZMIAR, pliczek);
}

int main(int argc, char** argv)
{
	
}