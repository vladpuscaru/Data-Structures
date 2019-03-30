#include "Lista_Dublu_Inlantuita.h"

int main() {

	char numeFisier[20] = "produse.txt";
	/*nodls* cap = citireFisierLS(numeFisier);

	traversareLS(cap);

	printf("\n\nDUPA STERGERE ID\n");
	int a = stergereLS_dupaId(&cap, 1019);
	int b = stergereLS_dupaId(&cap, 1007);
	int x = stergereLS_dupaPozitie(&cap, 2);
	traversareLS(cap);

	dezalocareLS(cap);*/

	nodld* prim = NULL;
	nodld* ultim = NULL;

	citireFisierLD(numeFisier, &prim, &ultim);
	traversareLD(prim);
	printf("\n\n-======================-\n");
	traversareLD_invers(ultim);

	return 0;
}