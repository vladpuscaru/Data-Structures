#pragma once
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Produs.h"

struct nodls {
	produs inf;
	nodls* next;
};


// creare si initializare nod nou
nodls* creareNodNou(produs p) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.id = p.id;
	nou->inf.pret = p.pret;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.nrMagazine = p.nrMagazine;
	nou->inf.stocMagazine = (int*)malloc(nou->inf.nrMagazine * sizeof(int));
	for (int i = 0; i < nou->inf.nrMagazine; i++) {
		nou->inf.stocMagazine[i] = p.stocMagazine[i];
	}
	nou->next = NULL;

	return nou;
}

// calcul numar elemente din lista
int getNrElementeLS(nodls* cap) {
	int nrElemente = 0;
	nodls* temp = cap;
	while (temp != NULL) {
		nrElemente++;
		temp = temp->next;
	}

	return nrElemente;
}

// inserare la inceput
void inserareLS_inceput(nodls** cap, produs p) {
	// creare si initializare nod nou
	nodls* nou = creareNodNou(p);

	/// inserare nod in lista(la inceput)
	// caz in care lista este goala
	if (*cap == NULL) {
		*cap = nou;
	}
	// caz in care lista are elemente
	else {
		nou->next = *cap;
		*cap = nou;
	}
}

// inserare la sfarsit
void inserareLS_sfarsit(nodls** cap, produs p) {
	// creare si initializare nod nou
	nodls* nou = creareNodNou(p);

	/// inserare nod in lista(la sfarsit)
	// caz in care lista este goala

	if (*cap == NULL) {
		*cap = nou;
	}
	// caz in care lista are elemente
	else {
		nodls* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

// inserare dupa un anumit element [0 - a adaugat | -1 - nu a adaugat(lista goala) | -2 - nu a adaugat(produsul cu id X nu exista)]
int inserareLS_dupaId(nodls** cap, produs pAnterior, produs pNou) {
	int inserat = 0;

	// caz in care lista e goala
	if (*cap == NULL) {
		return -1;
	}
	// caz in care lista are elemente
	else {
		// verificare primul element
		if ((*cap)->inf.id == pAnterior.id) {
			// creare si initializare nod nou
			nodls* nou = creareNodNou(pNou);

			// adaugare nod in lista
			nou->next = (*cap)->next;
			(*cap)->next = nou;

			// setare flag
			inserat = 1;
		}
		// cautare element anterior
		nodls* temp = (*cap)->next;
		while (temp->next != NULL && !inserat) {
			if (temp->next->inf.id == pAnterior.id) {
				// creare si initializare nod nou
				nodls* nou = creareNodNou(pNou);

				// adaugare in lista
				nou->next = temp->next->next;
				temp->next->next = nou;

				// setare flag
				inserat = 1;
			}
			temp = temp->next;
		}
		// verificare ultimul element
		if (!inserat && temp->inf.id == pAnterior.id) {
			// adaugare in lista
			inserareLS_sfarsit(cap, pNou);

			// setare flag
			inserat = 1;
		}
	}

	return inserat == 1 ? 0 : -2;
}

// stergere de la inceput [0 - a sters | -1 - nu a sters(lista goala)]
int stergereLS_inceput(nodls** cap) {
	// caz in care lista este goala
	if (*cap == NULL)
		return -1;
	// caz in care lista are elemente
	else {
		nodls* nodDeSters = *cap;
		*cap = (*cap)->next;
		free(nodDeSters->inf.denumire);
		free(nodDeSters->inf.stocMagazine);
		free(nodDeSters);
	}

	return 0;
}

// stergere de la sfarsit [0 - a sters | -1 - nu a sters(lista goala)]
int stergereLS_sfarsit(nodls** cap) {
	// caz in care lista este goala
	if (*cap == NULL)
		return -1;
	// caz in care lista are un singur element
	else if ((*cap)->next == NULL)
		stergereLS_inceput(cap);
	// caz in care lista are mai multe elemente
	else {
		nodls* nodDeSters = *cap;
		nodls* anterior = nodDeSters;
		while (nodDeSters->next != NULL) {
			anterior = nodDeSters;
			nodDeSters = nodDeSters->next;
		}
		anterior->next = NULL;
		free(nodDeSters->inf.denumire);
		free(nodDeSters->inf.stocMagazine);
		free(nodDeSters);
	}

	return 0;
}

// stergere dupa id produs [0 - a sters | -1 - nu a sters(lista goala) | -2 - nu a sters(produsul nu exista)]
int stergereLS_dupaId(nodls** cap, int id) {
	int gasit = 0;
	// caz in care lista e goala
	if (*cap == NULL)
		return -1;
	// caz in care primul element este cel cautat
	else if ((*cap)->inf.id == id) {
		gasit = 1;
		stergereLS_inceput(cap);
	}
	// caz in care un element din interior este cel cautat
	else {
		nodls* nodDeSters = (*cap)->next;
		nodls* anterior = *cap;
		while (nodDeSters != NULL && !gasit) {
			if (nodDeSters->inf.id == id) {
				gasit = 1;
				anterior->next = nodDeSters->next;
				free(nodDeSters->inf.denumire);
				free(nodDeSters->inf.stocMagazine);
				free(nodDeSters);
				continue;
			}
			anterior = nodDeSters;
			nodDeSters = nodDeSters->next;
		}
	}

	return gasit == 1 ? 0 : -2;
}

// stergere dupa pozitie [0 - a sters | -1 - nu a sters(lista goala) | -2 - nu a sters(pozitie in afara range-ului) | -3 - nu a sters(produsul nu exista)]
int stergereLS_dupaPozitie(nodls** cap, int poz) {
	int gasit = 0;
	int nrElemente = getNrElementeLS(*cap);
	// caz in care lista e goala
	if (*cap == NULL)
		return -1;
	// caz in care pozitia este in afara listei
	else if (poz < 0 || poz >= nrElemente) {
		return -2;
	}
	// caz in care pozitia este 0
	else if (poz == 0) {
		gasit = 1;
		stergereLS_inceput(cap);
	}
	// caz in care se face cautarea
	else {
		int index = 1;
		nodls* nodDeSters = (*cap)->next;
		nodls* anterior = *cap;
		while (nodDeSters != NULL && !gasit) {
			if (index == poz) {
				gasit = 1;
				anterior->next = nodDeSters->next;
				free(nodDeSters->inf.denumire);
				free(nodDeSters->inf.stocMagazine);
				free(nodDeSters);
				continue;
			}
			index++;
			anterior = nodDeSters;
			nodDeSters = nodDeSters->next;
		}
	}

	return gasit == 1 ? 0 : -3;
}

// traversare si afisare
void traversareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp != NULL) {
		printf("\nAdresa nod: %p | Adresa next: %p ||-MD-|| ", temp, temp->next);
		afisareProdus(temp->inf);
		temp = temp->next;
	}
}

// dezalocare memorie
void dezalocareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp != NULL) {
		nodls* aux = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.stocMagazine);
		free(temp);
		temp = aux;
	}
}

// creare lista cu date din fisier
nodls* citireFisierLS(char* numeFisier) {
	nodls* cap = NULL;
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

		inserareLS_sfarsit(&cap, p);
	}

	// inchidere fisier
	fclose(file);

	return cap;
}