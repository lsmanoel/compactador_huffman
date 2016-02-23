#include <stdio.h>
#include <stdlib.h>
#include "compactador_huffman.h"

int main(void) {
	arvoreHead *arvHead;
	listHead *lstHead;

	int status=10;
	status=inicializaARV(&arvHead);
	status=inicializaLista(&lstHead);

	status=gerarLista_deNoh_ASCII(lstHead);

	mostrar_lista(lstHead->first);

	status=insertionS_lista(lstHead);

	mostrar_lista(lstHead->first);

	status=reordenadorLista_deNoh_ASCII(lstHead, arvHead);

	status=output_listTofileEncoder(arvHead);
	printf("status: %d\n", status);
	puts("FIM DO PROGRAMA!"); /* prints ... */
	return EXIT_SUCCESS;
}

void mostrar_lista(lista *lst){
	printf("%c ... peso: %d\n", ((nohChar*)((arvore*)lst->adress_type)->void_adress)->caracter, 
								((nohChar*)((arvore*)lst->adress_type)->void_adress)->peso);
	//printf("%p\n", lst->next);
	if(lst->next!=NULL)
		mostrar_lista(lst->next);
}

int output_listTofileEncoder(arvoreHead *arvHead){
	int status=0;
	return status;
}
int inicializaARV(arvoreHead **arvHead){
	arvoreHead* novo_head = (arvoreHead*) malloc(sizeof(arvoreHead));
	    if (novo_head==NULL){
    	puts("Erro na alocacao do arvHeader");
    	return 1;
    }
	novo_head->size=0;
	novo_head->root=NULL;
	*arvHead=novo_head;
	puts("arvHead inicializada.");
	return 0;
}

int inicializaLista(listHead **lstHead) {
    listHead *novo_head = (listHead*) malloc(sizeof (listHead));
    if (novo_head==NULL){
    	puts("Erro na alocacao do lstHead");
    	return 1;
    }
    novo_head->first=NULL;
    novo_head->last=NULL;
    novo_head->size=0;
    *lstHead=novo_head;
    puts("lstHead inicializada.");
	return 0;
};

int reordenadorLista_deNoh_ASCII(listHead* lstHead, arvoreHead* arvHead){
	int status=0;
	return status;
}

int gerarLista_deNoh_ASCII(listHead *lstHead){
	int status=0;
	status=input_fileTolist(lstHead);
	return status;
}

int input_fileTolist(listHead *lstHead){
	int status=0;
	char temp_string[31]/*="testefile.txt"*/, chr;
	lista* noh;
	printf("Digite o nome do arquivo para compactacao: ");
	__fpurge(stdin);
	scanf("%s", temp_string);
	FILE* fp;
	puts("...");
	fp = fopen(temp_string, "r");
	puts("...");
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
				if(buscaLinear_lista(lstHead, chr, &noh)){
					((nohChar*)((arvore*)noh->adress_type)->void_adress)->peso++;	
					printf("Pesso++ em %c\n", chr);				
				}
				else{
					status=addLastList(lstHead, chr);
					printf("Elemento add: %c\n", chr);					
				}
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
    arvore* novo_arv = (arvore*) malloc(sizeof(arvore));
    nohChar* novo_nohChar = (nohChar*) malloc(sizeof(nohChar));
	novo_nohChar->caracter=chr;
	novo_nohChar->peso=1;

    novo_arv->void_adress=novo_nohChar;
    novo_arv->r=NULL;
    novo_arv->l=NULL;

    novo->adress_type=novo_arv;
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

int buscaLinear_lista(listHead *lstHead, char chr, lista **noh){
	puts("buscaLinear_lista()...");
	lista* temp;
	temp=lstHead->first;
	while(temp){
		if(((nohChar*)((arvore*)temp->adress_type)->void_adress)->caracter == chr){
			puts("...");
			*noh=temp;
			puts(">>>caracter encontrado");
			return 1;
		}
		temp=temp->next;
	}
	puts("caracter nao encontrado");
	return 0;
}

int insertionS_lista(listHead *lstHead){
	clock_t clock_1, clock_2;
	clock_1=clock();
    lista *change, *lst_temp_i, *lst_temp_j;
	int  i, j, *k;
	puts("lista...");
	puts("insertionS");
	printf("%p\n", (lstHead->first)->next);
	printf("%p\n", lstHead->first);

	lst_temp_j=(lstHead->first)->next;
	lst_temp_i=lstHead->first;

	i=(int)((nohChar*)((arvore*)lst_temp_i->adress_type)->void_adress)->peso;
	j=(int)((nohChar*)((arvore*)lst_temp_j->adress_type)->void_adress)->peso;
	if(i > j){ //Verifica se os dois primeiros elementos estão ordenados, caso não, esses serão ordenados.
		k=lst_temp_i->adress_type;
		lst_temp_i->adress_type=lst_temp_j->adress_type;
		lst_temp_j->adress_type=k;
	}
	lst_temp_j=lst_temp_j->next;
	while(lst_temp_j!=NULL){
		//puts("change?");
	i=(int)((nohChar*)((arvore*)lst_temp_i->adress_type)->void_adress)->peso;
	j=(int)((nohChar*)((arvore*)lst_temp_j->adress_type)->void_adress)->peso;
		if(j < i ){
			//puts("_change!");
			change=lst_temp_j->next;

			(lst_temp_j->first)->next=lst_temp_j->next;
			if(lst_temp_j->next!=NULL)
				(lst_temp_j->next)->first=lst_temp_j->first;

			lst_temp_j->first=lst_temp_i->first;
			lst_temp_j->next=lst_temp_i;

			if(lst_temp_i->first!=NULL){
				(lst_temp_i->first)->next=lst_temp_j;
			}
			else
				lstHead->first=lst_temp_j;

			lst_temp_i->first=lst_temp_j;

			lst_temp_i=lstHead->first;
			lst_temp_j=change;
		}
		else{
			lst_temp_i=lst_temp_i->next;
			if(lst_temp_i==lst_temp_j){
				lst_temp_i=lstHead->first;
				lst_temp_j=lst_temp_j->next;
			}
		}
	}
	clock_2=clock();
	printf("tempo de ordenacao da lista: %d\n", clock_2 - clock_1);
	return 0;
}