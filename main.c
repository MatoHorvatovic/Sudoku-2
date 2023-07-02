#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"header.h"

#define MAX_ID 5



int main() {
	char ime[20], ID[MAX_ID];
	int izbor;
	int sudoku[9][9];
	Podaci podaci;
	printf("Dobrodošli u Sudoku program!\n");
	printf("Odaberite opciju:\n");
	printf("1. Novi korisnik\n");
	printf("2. Prijašnji korisnik\n");
	printf("Vaš odabir: ");
	scanf("%d", &izbor);
	ocistiUnos();
	if (izbor == 1) {
		printf("Unesite ime: ");
		scanf("%s",ime);

		// Generiranje ID-a
		generirajID(ID);

		// Pohrana imena i ID-a u datoteku
		FILE* datoteka;
		datoteka = fopen("podaci.txt", "a");
		if (datoteka == NULL) {
			printf("Greška pri otvaranju datoteke!\n");
			return;
		}

		fprintf(datoteka, "%s,%s\n", ime, ID);

		fclose(datoteka);

		printf("Podaci su pohranjeni u datoteku.\n");

	}
	else if (izbor == 2) {
		printf("Unesite ID: ");
		scanf("%s", ID);
		ocistiUnos();

		// Provjera ID-a u datoteci
		int pronaden = provjeriID(ID);
		if (pronaden) {
			printf("ID je pronađen u datoteci.\n");
		}
		else {
			printf("ID nije pronađen u datoteci.\n");
			return 0;
		}
	}
	else {
		printf("Pogrešan odabir. Izlaz iz programa.\n");
		return 0;
	}
	printf("Odaberite razinu težine\n");
	printf("1. lagano\n");
	printf("2. srednje\n");
	printf("3. teško\n");
	scanf("%d", &izbor);
	ocistiUnos();
	if (izbor == 1) {
		int lagano[9][9] = {
			{8, 2, 0, 4, 3, 9, 1, 6, 5},//7
			{1, 3, 6, 7, 0, 2, 9, 8, 4},//5
			{4, 5, 9, 8, 1, 6, 0, 7, 3},//2
			{6, 1, 4, 5, 9, 3, 7, 2, 0},//8
			{3, 0, 5, 2, 8, 7, 6, 4, 1},//9
			{7, 8, 2, 6, 4, 0, 3, 5, 9},//1
			{9, 0, 8, 3, 2, 5, 4, 1, 7},//6
			{2, 4, 1, 9, 7, 8, 5, 0, 6},//3
			{5, 7, 3, 1, 6, 0, 8, 9, 2}//4
		};
		memcpy(sudoku, lagano, sizeof(sudoku));
	}
	else if (izbor == 2) {
		int srednje[9][9] = {
			{0, 4, 0, 1, 5, 0, 0, 8, 0},
			{0, 0, 6, 0, 0, 7, 0, 0, 2},
			{0, 3, 2, 0, 0, 9, 0, 4, 7},
			{0, 5, 0, 0, 7, 3, 0, 2, 0},
			{4, 0, 7, 8, 0, 0, 3, 6, 0},
			{0, 2, 0, 0, 9, 6, 0, 7, 0},
			{0, 6, 5, 0, 0, 4, 0, 9, 8},
			{0, 1, 0, 2, 3, 0, 0, 5, 0}
			};
		memcpy(sudoku, srednje, sizeof(sudoku));
	}
	if (izbor == 3) {
		int tesko[9][9] = {
			{5, 3, 0, 0, 7, 0, 0, 0, 0},
			{6, 0, 0, 1, 9, 5, 0, 0, 0},
			{0, 9, 8, 0, 0, 0, 0, 6, 0},
			{8, 0, 0, 0, 6, 0, 0, 0, 3},
			{4, 0, 0, 8, 0, 3, 0, 0, 1},
			{7, 0, 0, 0, 2, 0, 0, 0, 6},
			{0, 6, 0, 0, 0, 0, 2, 8, 0},
			{0, 0, 0, 4, 1, 9, 0, 0, 5},
			{0, 0, 0, 0, 8, 0, 0, 7, 9}
		};
		memcpy(sudoku, tesko, sizeof(sudoku));
	}
	prikaziSudoku(sudoku);

	do {
		printf("\nOdaberite opciju:\n");
		printf("1. Prikazi Sudoku zadatak\n");
		printf("2. Automatski rjesi Sudoku\n");
		printf("3. Ručni unos brojeva\n");
		printf("4. Ispisi ID\n");
		printf("5. Izlaz iz programa\n");
		printf("Vaš odabir: ");
		scanf("%d", &izbor);
		ocistiUnos();

		switch (izbor) {
		case 1:
			prikaziSudoku(sudoku);
			break;
		case 2:
			rjesiSudoku(sudoku);
			printf("\nSudoku je riješen!\n");
			prikaziSudoku(sudoku);
			break;
		case 3:
			rucniUnosSudoku(sudoku);
			spremiVrijeme(podaci);
			break;
		case 4:
			ispisiID(podaci.id);
			break;
		case 5:
			printf("Hvala što ste koristili program. Doviđenja!\n");
				exit;
		default:
				printf("Pogrešan odabir. Molimo odaberite ponovno.\n");
				break;
		}

	} while (izbor != 7);

	return 0;
}
