#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactador_huffman.h"
#include "compactador_func.c"
int main(void){
	arvoreHead *arvHead;
	listHead *lstHead;/* code */

	int status=10;
	status=inicializaARV(&arvHead);
	status=inicializaLista(&lstHead);

	status=input_ARV(arvHead);
	//status=input_coderFileToFile(arvHead);

	imprime(arvHead->root);
	printf("status: %d\n", status);
	puts("FIM DO PROGRAMA!"); /* prints ... */
	return 0;
}

int input_ARV(arvoreHead* arvHead){
	FILE* fp;
	puts("-------------------------------------------------------");
	puts("input_ARV()...");
	int status=0;
	fp=fopen("arquivo_codificado.dat", "rb");
	if(fp==NULL){
		puts("Erro ao abrir arquivo_codificado.dat");
		status=1;
	}
	else{
		puts("input_ARV_REC_DAT()...");
		fread(arvHead, sizeof(arvoreHead), 1, fp);
		printf("arvHead->altura: %d\n", arvHead->altura);
		printf("arvHead->largura: %d\n", arvHead->largura);
		printf("arvHead->root: %p\n", arvHead->root);
		input_ARV_REC_DAT(&(arvHead->root), fp);
		fclose(fp);
		status=0;
	}
	return status;
}

void input_ARV_REC_DAT(arvore** noh, FILE* fp){
	if(fp==NULL)
		return;
	*noh=(arvore*)malloc(sizeof(arvore));
	nohChar* novo_char=(nohChar*)malloc(sizeof(nohChar));
	fread(*noh, sizeof(arvore), 1, fp);
	fread(novo_char, sizeof(nohChar), 1, fp);
	(*noh)->void_adress=novo_char;
	printf("input_ARV_REC_DAT() ... noh: %p\n", *noh);
	if(*noh){
		printf("	 (noh)->void_adress: %p\n", (*noh)->void_adress);
		if((*noh)->l)
			input_ARV_REC_DAT(&((*noh)->l), fp);
		if((*noh)->l)
			input_ARV_REC_DAT(&((*noh)->r), fp);
	}
}