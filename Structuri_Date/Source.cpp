#include "Lista_Simplu_Inlantuita.h"
#include "Lista_Dublu_Inlantuita.h"
#include "Stiva.h"
#include "Coada.h"

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

#pragma region Coada
	printf("\n\n----------------------------- Coada -----------------------------\n");
	nodCoada* primCoada = NULL;
	nodCoada* ultimCoada = NULL;
	citireFisierCoada(numeFisier, &primCoada, &ultimCoada);
	traversareCoada(primCoada);
	nodCoada* top;
	int x = 0;
	while (x++ < 3) {
		top = deque(&primCoada, &ultimCoada);
		free(top->inf.denumire);
		free(top->inf.stocMagazine);
		free(top);
	}
	
	printf("\n\n");
	traversareCoada(primCoada);
	dezalocareCoada(primCoada);
#pragma endregion
	

	getchar();

	return 0;
}