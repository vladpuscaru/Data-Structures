#include "Lista_Simplu_Inlantuita.h"
#include "Lista_Dublu_Inlantuita.h"

int main() {

	char numeFisier[20] = "produse.txt";

#pragma region Lista Simplu Inlantuita
	printf("\n\n----------------------------- Lista Simplu Inlantuita -----------------------------\n");
	nodls* cap = citireFisierLS(numeFisier);
	traversareLS(cap);
	dezalocareLS(cap);
#pragma endregion

#pragma region Lista Dublu Inlantuita
	printf("\n\n----------------------------- Lista Dublu Inlantuita -----------------------------\n");
	nodld* prim = NULL;
	nodld* ultim = NULL;
	citireFisierLD(numeFisier, &prim, &ultim);
	traversareLD(prim);
	printf("\n\n[][][] Traversare inversa [][][]\n");
	traversareLD_invers(ultim);
	dezalocareLD(prim);
#pragma endregion


	

	getchar();

	return 0;
}