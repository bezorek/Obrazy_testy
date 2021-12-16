#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define DLUGOSC 500

struct Obraz {
	int width;
	int height;
	int depth;
	int** macierz;
	char nazwa_Pliku[100];
};


struct Obraz wczytaj_plik() {
	FILE* pgm;
	struct Obraz myImage;
	char bufor;
	char nazwa_pliku[100];
	int koniec = 0;
	int znak;
	printf("Podaj nazwe pliku do odczytania:");
	scanf("%s", &nazwa_pliku);
	if ((pgm = fopen(nazwa_pliku, "r")) == NULL) {
		printf("Brak takiej nazwy pliku!");
	}
	else {
		if (fscanf(pgm, "%c", &bufor) == NULL) {
			printf("Plik jest pusty!");
			koniec = 1;
		}
		if (bufor == 'P') {
			if (fscanf(pgm, "%c\n", &bufor) == '2') {
				printf("bufor: %c", bufor);
				printf("To nie jest transformacja P2!");
				koniec = 1;
			}
		}
		else {
			printf("To nie jest plik .PGM");
			koniec = 1;
		}
	}
	if (koniec == 0) {
		//myImage.nazwa_Pliku = nazwa_pliku;
		strcpy(myImage.nazwa_Pliku, nazwa_pliku);
		char pomocnicze;
		/*while (1) {
			if (fscanf(pgm, "%d", &znak) == 1)
				break;
			else
				continue;
		}*/
		fscanf(pgm, "%d %d", &myImage.width, &myImage.height);
		//fscanf(pgm, "%d\n", &myImage.height);
	}
	/*while (1) {
		if (fscanf(pgm, "%d", &znak) != 1)
			continue;
		else
			break;
	}*/
	fscanf(pgm, "%d\n", &myImage.depth);
	/*while (1) {
		if (fscanf(pgm, "%d", &znak) != 1)
			continue;
		else
			break;
	}*/


	int** piksele1 = malloc(myImage.height * sizeof(int*));
	int* piksele = malloc(myImage.height * myImage.width * sizeof(int));

	for (int i = 0; i < myImage.height; i++)
	{
		piksele1[i] = &piksele[i * myImage.width];
	}

	myImage.macierz = piksele1;
	for (int i = 0; i < myImage.height; i++)
		for (int j = 0; j < myImage.width; j++) {
			if (fscanf(pgm, "%d", &myImage.macierz[i][j]) != 1)
				printf("B³¹d z zapisanym zdjêciem ");
		}
	printf("Struktura:\nnazwa:%s\nwidth:%d\nheight:%d\ndepth:%d\npiksele nasze:%d\nte drugie:%d", myImage.nazwa_Pliku, myImage.width, myImage.height, myImage.depth, myImage.macierz, piksele1);
	return myImage;
	fclose(pgm);
}

void dodaj_baza(struct Obraz** baza, int* wielkosc, struct Obraz myImage) {
	struct Obraz* tmp;
	*wielkosc += 1;
	int resize = *wielkosc;
	tmp = (struct Obraz*)realloc(*baza, (resize * sizeof(struct Obraz)));
	if (tmp != NULL) {
		printf("\nUdana realokacja!\n");
		tmp[resize - 1] = myImage;
		*baza = tmp;
	}
	else
		printf("B³¹d realokacji!");

	printf("\nszerokosc z myimage:%d\n", myImage.width);
	//printf("\nszerokosc z bazy:%d\n", *(baza[0]).width);


}


int main() {
	int *tab;
	int wybor;
	int k;
	struct Obraz tmp;
	struct Obraz* baza;
	struct Obraz myImage;
	int wielkosc = 0;
	if (baza = (struct Obraz*)calloc(wielkosc, sizeof(struct Obraz))) {
		printf("Udana callocacja!\n");
	}

	for (;;)
	{
		printf("MENU GLOWNE\n");
		printf("-----------------\n");
		printf("1. Dodaj obraz\n");
		printf("2. Wybierz AKTYWNY obraz\n");
		printf("3. Wyœwietl liste obrazow\n");
		printf("4. Zapisz obraz\n");
		printf("5. Zrob negatyw\n");
		printf("6. Koniec programu\n");

		printf("Wybierz: \n");
		scanf("%d", &wybor);

		switch (wybor)
		{
		case 1:
		{
			myImage = wczytaj_plik();
			dodaj_baza(&baza, &wielkosc, myImage);
			printf("Obraz zostal dodany\n");
		}
		break;

		case 2:
		{
			printf("podaj ktory obraz:");
			scanf("%d", &k);
			tmp = baza[k];
			printf("Obraz %d zostal wybrany\n", k);
		}
		break;

		case 3:
		{
			for (int k = 0; k < wielkosc; k++)
				printf("\nNazwa pliku[%d]: %s\n", k, baza[k].nazwa_Pliku);
		}
		break;

		case 4:
		{

			char litery[20];
			FILE* plik;
			printf("Podaj nazwe pliku z rozszerzeniem .pgm:");
			scanf("%s", &litery);
			plik = fopen(litery, "w");

			fprintf(plik, "P2\n");
			fprintf(plik, "%d %d\n%d\n", baza[k].width, baza[k].height, baza[k].depth);
			for (int i = 0; i < baza[k].height; i++) {
				for (int j = 0; j < baza[k].width; j++) {
					fprintf(plik, "%d ", tmp.macierz[i][j]);
				}
				fprintf(plik, "\n");
			}
			fclose(plik);
		}
		break;

		case 5:
		{
			for (int i = 0; i < tmp.height; i++) {
				for (int j = 0; j < tmp.width; j++) {
					tmp.macierz[i][j] = tmp.depth - tmp.macierz[i][j];
					printf("%d ", tmp.macierz[i][j]);
				}
				printf("\n");
			}
			printf("Negatyw zostal wykonany\n");
		}
		break;

		case 6:
		{
			printf("Do widzenia\n");
			exit(0);
		}
		break;

		case 7:
		{
			int x;
			int count = 0;
			tab = calloc(tmp.depth, sizeof(int));
			for (x = 0; x < tmp.depth; x++)
			{
				tab[x] = 0;
				for (int i = 0; i < tmp.height; i++)
				{
					for (int j = 0; j < tmp.width; j++)
					{
						if (tmp.macierz[i][j] = x + 1)
						{
							count++;
						}
					}
				}
				tab[x] = count;
			}
			printf("Tablica histogramu\n");
			for (int i = 0; i < tmp.depth; i++)
			{
				printf("%d ", tab[x]);
			}
			printf("\n");
		}
		break;
		}
	}
}