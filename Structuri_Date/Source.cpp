#include "Lista_Simplu_Inlantuita.h"
#include "Lista_Dublu_Inlantuita.h"
#include "Stiva.h"
#include "Coada.h"
#include "Hash_Table.h"

int main() {

	char numeFisier[20] = "produse.txt";

//#pragma region Lista Simplu Inlantuita
//	printf("\n\n----------------------------- Lista Simplu Inlantuita -----------------------------\n");
//	nodls* cap = citireFisierLS(numeFisier);
//	traversareLS(cap);
//	dezalocareLS(cap);
//#pragma endregion

//#pragma region Lista Dublu Inlantuita
//	printf("\n\n----------------------------- Lista Dublu Inlantuita -----------------------------\n");
//	nodld* prim = NULL;
//	nodld* ultim = NULL;
//	citireFisierLD(numeFisier, &prim, &ultim);
//	traversareLD(prim);
//	printf("\n\n[][][] Traversare inversa [][][]\n");
//	traversareLD_invers(ultim);
//	dezalocareLD(prim);
//#pragma endregion

//#pragma region Stiva
//	printf("\n\n----------------------------- Stiva -----------------------------\n");
//	nodStiva* varf = citireFisierStiva(numeFisier);
//	traversareStiva(varf);
//	dezalocareStiva(varf);
//#pragma endregion

//#pragma region Coada
//	printf("\n\n----------------------------- Coada -----------------------------\n");
//	nodCoada* primCoada = NULL;
//	nodCoada* ultimCoada = NULL;
//	citireFisierCoada(numeFisier, &primCoada, &ultimCoada);
//	traversareCoada(primCoada);
//	nodCoada* top;
//	int x = 0;
//	while (x++ < 3) {
//		top = deque(&primCoada, &ultimCoada);
//		free(top->inf.denumire);
//		free(top->inf.stocMagazine);
//		free(top);
//	}
//	
//	printf("\n\n");
//	traversareCoada(primCoada);
//	dezalocareCoada(primCoada);
//#pragma endregion

#pragma region Tabela de Dispersie - CHAINING
	printf("\n\n----------------------------- Tabela de dispersie (Chaining) -----------------------------\n");
	hashTable ht = citireFisierHT(numeFisier, 50);
	afisareHT(ht);
	printf("\n\n---- DUPA STERGERE (ID) ----\n");
	produs p;
	p.id = 4004;
	produs p2;
	p2.id = 2009;
	stergereHT(&ht, p);
	stergereHT(&ht, p2);
	afisareHT(ht);
	dezalocareHT(ht);
#pragma endregion
	

	getchar();

	return 0;
}