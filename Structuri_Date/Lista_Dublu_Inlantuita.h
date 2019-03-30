#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Produs.h"

struct nodld {
	nodld* prev;
	produs inf;
	nodld* next;
};

// creare si initializare nod nou
nodld* creareNodNouLD(produs p) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));

	nou->prev = NULL;
	nou->next = NULL;

	nou->inf.id = p.id;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.nrMagazine = p.nrMagazine;
	nou->inf.stocMagazine = (int*)malloc(nou->inf.nrMagazine * sizeof(int));
	for (int i = 0; i < nou->inf.nrMagazine; i++) {
		nou->inf.stocMagazine[i] = p.stocMagazine[i];
	}

	return nou;
}

// calcul numar elemente din lista
int getNrElementeLD(nodld* prim) {
	int nrElemente = 0;
	nodld* temp = prim;
	while (temp != NULL) {
		nrElemente++;
		temp = temp->next;
	}

	return nrElemente;
}

// inserare la inceput
void inserareLD_inceput(nodld** prim, nodld** ultim, produs p) {
	// creare nod nou
	nodld* nou = creareNodNouLD(p);
	// caz in care lista e goala
	if (*prim == NULL && *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	// caz in care lista are elemente
	else {
		nou->next = *prim;
		(*prim)->prev = nou;
		*prim = nou;
	}
}

// inserare la sfarsit
void inserareLD_sfarsit(nodld** prim, nodld** ultim, produs p) {
	nodld* nou = creareNodNouLD(p);

	// caz in care lista este goala
	if (*prim == NULL && *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	// caz in care lista are elemente
	else {
		nou->prev = *ultim;
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

// stergere de la inceput [0 - a sters | -1 - nu a sters(lista goala)]
int stergereLD_inceput(nodld** prim, nodld** ultim) {
	return 0;

}

// stergere de la sfarsit [0 - a sters | -1 - nu a sters(lista goala)]
int stergereLD_sfarsit(nodld** prim, nodld** ultim) {
	return 0;

}

// stergere dupa id produs [0 - a sters | -1 - nu a sters(lista goala) | -2 - nu a sters(produsul nu exista)]
int stergereLD_dupaId(nodld** prim, nodld** ultim, int id) {
	return 0;

}

// stergere dupa pozitie [0 - a sters | -1 - nu a sters(lista goala) | -2 - nu a sters(pozitie in afara range-ului) | -3 - nu a sters(produsul nu exista)]
int stergereLD_dupaPozitie(nodld** prim, nodld** ultim, int poz) {
	return 0;
}

// traversare si afisare
void traversareLD(nodld* prim) {
	nodld* temp = prim;
	while (temp != NULL) {
		printf("\nAdresa prev: %p | Adresa nod: %p | Adresa next: %p ||-MD-|| ", temp->prev, temp, temp->next);
		afisareProdus(temp->inf);
		temp = temp->next;
	}
}

// traversare inversa si afisare
void traversareLD_invers(nodld* ultim) {
	nodld* temp = ultim;
	while (temp != NULL) {
		printf("\nAdresa prev: %p | Adresa nod: %p | Adresa next: %p ||-MD-|| ", temp->prev, temp, temp->next);
		afisareProdus(temp->inf);
		temp = temp->prev;
	}
}

// dezalocare memorie
void dezalocareLD(nodld* prim) {
	
}

// creare lista cu date din fisier
void citireFisierLD(char* numeFisier, nodld** prim, nodld** ultim) {
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

		inserareLD_sfarsit(prim, ultim, p);
	}

	// inchidere fisier
	fclose(file);
}