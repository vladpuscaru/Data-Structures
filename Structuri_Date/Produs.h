#pragma once

struct produs {
	int id;
	char* denumire;
	float pret;
	int* stocMagazine;
	int nrMagazine;
};

void afisareProdus(produs p) {
	printf("%4d | %-15s | %5.2f LEI | aflat in %2d magazine ->  ", p.id, p.denumire, p.pret, p.nrMagazine);
	for (int i = 0; i < p.nrMagazine; i++) {
		printf("[%d]", p.stocMagazine[i]);
		if (i != p.nrMagazine - 1)
			printf(", ");
	}
}

void citireProdus(produs* p) {
	char buffer[50];

	printf("-> Id = ");
	scanf("%d", &p->id);
	printf("-> Denumire = ");
	scanf("%s", buffer);
	p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p->denumire, buffer);
	printf("-> Pret = ");
	scanf("%f", &p->pret);
	printf("-> Nr Magazine = ");
	scanf("%d", &p->nrMagazine);
	p->stocMagazine = (int*)malloc(p->nrMagazine * sizeof(int));
	for (int i = 0; i < p->nrMagazine; i++) {
		printf("--> Stoc magazin %d = ", i + 1);
		scanf("%d", &p->stocMagazine[i]);
	}
}