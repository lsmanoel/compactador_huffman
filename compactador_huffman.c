#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactador_huffman.h"
#include "compactador_func.c"
#include <time.h>

int main(void) {
	arvoreHead *arvHead;
	listHead *lstHead;
	char* string;

	int status=10;
	status=inicializaARV(&arvHead);
	status=inicializaLista(&lstHead);

	status=gerarLista_deNoh_ASCII(lstHead, &string);

	mostrar_lista((lista*)lstHead->first);

	status=insertionS_lista(lstHead);

	mostrar_lista((lista*)lstHead->first);

	status=reordenadorLista_deNoh_ASCII(lstHead, arvHead);
	status=main_altura_ARV(arvHead);
	status=main_largura_ARV(arvHead);

	imprime(arvHead->root);
	status=output_listTofileEncoder(arvHead, string);
	free(arvHead);
	//free(lstHead);
	printf("status: %d\n", status);
	puts("FIM DO PROGRAMA!"); /* prints ... */
	return EXIT_SUCCESS;
}

