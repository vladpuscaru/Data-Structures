#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Produs.h"

struct nodCoada {
	nodCoada* prev;
	produs inf;
	nodCoada* next;
};

nodCoada* creareNodNouCoada(produs p) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.id = p.id;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.nrMagazine = p.nrMagazine;
	nou->inf.stocMagazine = (int*)malloc(nou->inf.nrMagazine * sizeof(int));
	for (int i = 0; i < nou->inf.nrMagazine; i++) {
		nou->inf.stocMagazine[i] = p.stocMagazine[i];
	}
	nou->next = NULL;
	nou->prev = NULL;

	return nou;
}

void enqueue(nodCoada** prim, nodCoada** ultim, produs p) {
	// creare nod nou
	nodCoada* nou = creareNodNouCoada(p);
	// caz in care coada e goala
	if (*prim == NULL && *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	// caz in care coada are elemente, adaugam la sfarsit
	else {
		(*ultim)->next = nou;
		nou->prev = *ultim;
		*ultim = nou;
	}
}

nodCoada* deque(nodCoada** prim, nodCoada** ultim) {
	// caz in care coada e goala
	if (*prim == NULL && *ultim == NULL) {
		return NULL;
	}

	nodCoada* nodReturnat = NULL;
	// caz in care coada are un singur element
	if (*prim == *ultim) {
		nodReturnat = *prim;
		*prim = NULL;
		*ultim = NULL;
	}
	// caz in care coada are elemente
	else {
		nodReturnat = *prim;
		*prim = (*prim)->next;
		(*prim)->prev = NULL;
	}

	return nodReturnat;
}

void traversareCoada(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp != NULL) {
		printf("\nAdresa prev: %p | Adresa nod: %p | Adresa next: %p ||-MD-|| ", temp->prev, temp, temp->next);
		afisareProdus(temp->inf);
		temp = temp->next;
	}
}

void dezalocareCoada(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp != NULL) {
		nodCoada* aux = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.stocMagazine);
		free(temp);
		temp = aux;
	}
}

// creare lista cu date din fisier
void citireFisierCoada(char* numeFisier, nodCoada** prim, nodCoada** ultim) {
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

		enqueue(prim, ultim, p);
	}

	// inchidere fisier
	fclose(file);
}