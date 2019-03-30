#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Produs.h"

struct nodStiva {
	produs inf;
	nodStiva* next;
};

// creare si initializare nod nou
nodStiva* creareNodNouStiva(produs p) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
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

	return nou;
}

// inserare element (la sfarsit)
void push(nodStiva** varf, produs p) {
	// creare nod nou
	nodStiva* nou = creareNodNouStiva(p);
	// caz in care stiva e goala
	if (*varf == NULL) {
		*varf = nou;
	}
	// caz in care stiva are elemente -> adaugam la sfarsit
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

// stergere si returnare element (de la sfarsit)
nodStiva* pop(nodStiva** varf) {
	nodStiva* top = NULL;

	if (*varf != NULL) {
		top = *varf;
		*varf = (*varf)->next;
	}

	return top;
}

// traversare si afisare
void traversareStiva(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		printf("\n ---------------------------------------------");
		printf("\n | ");  afisareProdus(temp->inf);
		printf("\n | Adresa nod: %p | Adresa next: %p ", temp, temp->next);
		printf("\n ---------------------------------------------");
		temp = temp->next;
	}
}

void dezalocareStiva(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		nodStiva* aux = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.stocMagazine);
		free(temp);
		temp = aux;
	}
}

nodStiva* citireFisierStiva(char* numeFisier) {
	nodStiva* varf = NULL;
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

		push(&varf, p);
	}

	// inchidere fisier
	fclose(file);

	return varf;
}