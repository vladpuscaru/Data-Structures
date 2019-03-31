#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Produs.h"
#include "Lista_Simplu_Inlantuita.h"

struct hashTable {
	nodls** vector;
	int dimensiune;
};

int functieHash(int cheie) {
	return cheie % 1001;
}

hashTable initializareHT(int dimensiune) {
	hashTable ht;
	ht.vector = (nodls**)malloc(dimensiune * sizeof(nodls*));
	ht.dimensiune = dimensiune;
	for (int i = 0; i < ht.dimensiune; i++) {
		ht.vector[i] = NULL;
	}
	return ht;
}

void inserareHT(hashTable* ht, produs p) {
	int poz = functieHash(p.id);
	inserareLS_sfarsit(&(ht->vector[poz]), p);
}

void stergereHT(hashTable* ht, produs p) {
	int poz = functieHash(p.id);
	stergereLS_dupaId(&ht->vector[poz], p.id);
}

void afisareHT(hashTable ht) {
	if (ht.vector != NULL) {
		for (int i = 0; i < ht.dimensiune; i++) {
			if (ht.vector[i] != NULL) {
				printf("\n [%d] = ", i);
				traversareLS(ht.vector[i]);
			}
		}
	}
}

void dezalocareHT(hashTable ht) {
	if (ht.vector != NULL) {
		for (int i = 0; i < ht.dimensiune; i++) {
			dezalocareLS(ht.vector[i]);
		}
	}
}

hashTable citireFisierHT(char* numeFisier, int dimensiune) {
	hashTable ht = initializareHT(dimensiune);
	produs p;
	int n;
	char buffer[50];

	// deschidere fisier
	FILE* file = fopen(numeFisier, "r");

	// citire numar produse
	fscanf(file, "%d", &n);
	for (int i = 0; i < n; i++) {
		// citire date produse
		fscanf(file, "%d", &p.id);
		fscanf(file, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(file, "%f", &p.pret);
		fscanf(file, "%d", &p.nrMagazine);
		p.stocMagazine = (int*)malloc(p.nrMagazine * sizeof(int));
		for (int j = 0; j < p.nrMagazine; j++) {
			fscanf(file, "%d", &p.stocMagazine[j]);
		}

		inserareHT(&ht, p);
	}

	// inchidere fisier
	fclose(file);

	return ht;
}
