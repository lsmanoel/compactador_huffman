#include "compactador_huffman.h"

int main(void) {
	arvoreHead *arvHead;
	listHead *lstHead;

	int status=10;
	status=inicializaARV(&arvHead);
	status=inicializaLista(&lstHead);

	status=gerarLista_deNoh_ASCII(lstHead);


	status=insertionS_lista(lstHead);
	status=reordenadorLista_deNoh_ASCII(lstHead, arvHead);

	status=output_listTofileEncoder(arvHead);
	printf("status: %d\n", status);
	puts("FIM DO PROGRAMA!"); /* prints ... */
	return EXIT_SUCCESS;
}

int gerarLista_deNoh_ASCII(listHead *lstHead){
	int status=0;
	status=input_fileTolist(lstHead);
	return status;
}

int input_fileTolist(listHead *lstHead){
	int status=0;
	char temp_string[100], chr;
	lista* noh;
	printf("Digite o nome do arquivo para compactacao: ");
	scanf("%[^\n]s", temp_string);
	FILE* fp;
	int x;
	fp = fopen(temp_string, "r");
	if (fp==NULL) {
		printf("Erro ao abrir o arquivo!\n");
	    return -1;
	}
	else {
		puts("Arquivo aberto.");
		while(1){
			chr=fgetc(fp);
			if(chr==EOF)
				break;
			else {
				if(buscaLinear_lista(lstHead, chr, noh))
					((nohchar*)noh->adress_type)->peso++;
				else
					status=addLastList(lstHead, chr);
			}
		}
	}
	puts("Lista de noh Gerada!");
	fclose(fp);
	return status;
}

int addLastList(listHead *lstHead, char chr){
	puts("addLastList()...");
    lista* novo = (lista*) malloc(sizeof(lista));
    nohChar* novo_nohChar = (nohChar*) malloc(sizeof(nohChar));
	novo_nohChar->caracter=chr;
	novo_nohChar->peso=0;
    novo->adress_type=novo_nohChar;
	novo->next=NULL;
	if(lstHead->first==NULL){
		lstHead->first=novo;
	}

	if(lstHead->last!=NULL){
		(lstHead->last)->next=novo;
		novo->first=lstHead->last;
	}
	else{
		novo->first=NULL;
	}
	lstHead->last=novo;
	lstHead->size++;
	puts("List: elemento add.");
	return 0;

}