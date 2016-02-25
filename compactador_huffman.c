#include <stdio.h>
#include <stdlib.h>
#include "compactador_huffman.h"
#include <time.h>

int main(void) {
	arvoreHead *arvHead;
	listHead *lstHead;

	int status=10;
	status=inicializaARV(&arvHead);
	status=inicializaLista(&lstHead);

	status=gerarLista_deNoh_ASCII(lstHead);

	mostrar_lista((lista*)lstHead->first);

	status=insertionS_lista(lstHead);

	mostrar_lista((lista*)lstHead->first);

	status=reordenadorLista_deNoh_ASCII(lstHead, arvHead);
	status=main_altura_ARV(arvHead);
	status=main_largura_ARV(arvHead);

	imprime(arvHead->root);
	//status=output_listTofileEncoder(arvHead);
	printf("status: %d\n", status);
	puts("FIM DO PROGRAMA!"); /* prints ... */
	return EXIT_SUCCESS;
}

int main_largura_ARV(arvoreHead* arvHead){
	puts("main_largura_ARV()...");
	int status=0, *n_folhas=(int*)malloc(sizeof(int));
	*n_folhas=0;
	aux1_largura_ARV(arvHead->root, n_folhas);
	arvHead->largura=*n_folhas;
	free(n_folhas);
	printf("largura: %d\n", arvHead->largura);
	return status;
}

void aux1_largura_ARV(arvore* noh, int* n_folhas){
	if(!ehvazia(noh)){
		if(noh->l==NULL && noh->r==NULL)
			*n_folhas=1+*n_folhas;
		aux1_largura_ARV(noh->l, n_folhas);
		aux1_largura_ARV(noh->r, n_folhas);
	}
}

int main_altura_ARV(arvoreHead* arvHead){
	puts("main_altura_ARV()...");
	int status=0;
	int* altura= (int*) malloc(sizeof(int));
	*altura=0;
	aux1_altura_ARV(arvHead, arvHead->root, altura);
	printf("altura: %d\n", arvHead->altura);
	free(altura);
	return status;
}

void aux1_altura_ARV(arvoreHead* arvHead, arvore* noh, int* altura){
	if(!ehvazia(noh)){
		*altura=1+*altura;
		//printf("altura: %d\n", *altura);
		aux1_altura_ARV(arvHead, noh->l, altura);
		if(arvHead->altura < *altura)
			arvHead->altura=*altura;
		aux1_altura_ARV(arvHead, noh->r, altura);
		if(arvHead->altura<*altura)
			arvHead->altura=*altura;
		*altura=*altura-1;
	}
}


/*
int output_listTofileEncoder(arvoreHead *arvHead){
	int status=0;
	FILE* fp;
	int* altura= (int*) malloc(sizeof(int));
	int* way=(int*)malloc(arvHead->altura*sizeof(int));
	fp=fopen("arquivo_codificado.txt", "w");
	status=writer__listTofileEncoder(fp, arvHead->root);
	free(way);
	fclose(fp);
	free(altura);
	return status;
}

int tabMaker_listTofileEncoder(arvoreHead* arvHead, arvore* noh, int* altura, int* way){
	if(!ehvazia(noh)){
		*altura=1+*altura;
		//printf("altura: %d\n", *altura);
		aux1_altura_ARV(arvHead, noh->l, altura);
		if(arvHead->altura < *altura)
			arvHead->altura=*altura;
		aux1_altura_ARV(arvHead, noh->r, altura);
		if(arvHead->altura<*altura)
			arvHead->altura=*altura;
		*altura=*altura-1;
	}
}
int writer__listTofileEncoder(FILE* fp, arvore *noh){
	//fchar():
	if(!ehvazia(noh)){
		printf("imprime_adress(); noh adress: %p\n", noh);
		status=writer__listTofileEncoder(fp, noh->l);
		status=writer__listTofileEncoder(fp, noh->r);
	}
	return 0;
}
*/

int inicializaARV(arvoreHead **arvHead){
	arvoreHead* novo_head = (arvoreHead*) malloc(sizeof(arvoreHead));
	    if (novo_head==NULL){
    	puts("Erro na alocacao do arvHeader");
    	return 1;
    }
    novo_head->altura=0;
    novo_head->largura=0;
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
	puts("-------------------------------------------------------");
	puts("reordenadorLista_deNoh_ASCII()...");
	int status=0;
	lista* morto1=lstHead->first;
	lista* morto2=(lstHead->first)->next;
	lista* temp=((lista*)(lstHead->first)->next)->next;
	lista* novo = (lista*) malloc(sizeof(lista));
	arvore* novo_arv = (arvore*) malloc(sizeof(arvore));
    nohChar* novo_nohChar = (nohChar*) malloc(sizeof(nohChar));

	arvHead->root=novo_arv;
	arvHead->size++;

	novo_arv->l=(arvore*)(lstHead->first)->adress_type;
	novo_arv->r=(arvore*)((lstHead->first)->next)->adress_type;

	novo_nohChar->peso=((nohChar*)((arvore*)novo_arv->l)->void_adress)->peso+((nohChar*)((arvore*)novo_arv->r)->void_adress)->peso;
	novo_nohChar->caracter='>';
//******************************************************
	puts("addLastList()...");

    novo_arv->void_adress=novo_nohChar;
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
	lstHead->size--;
	puts("List: elemento add.");
//******************************************************
	printf("lstHead->size: %d\n", lstHead->size);
	if(lstHead->size>1){
		lstHead->first=temp;
		((lista*)lstHead->first)->first=NULL;
		free(morto1);
		free(morto2);
		mostrar_lista(lstHead->first);
		status=insertionS_lista(lstHead);
		mostrar_lista(lstHead->first);
		imprime(arvHead->root);
		status=reordenadorLista_deNoh_ASCII(lstHead, arvHead);
	}
	else{
		mostrar_lista(lstHead->first);
		printf("%p\n", lstHead->last);
		lstHead->first=lstHead->last;
		lstHead->last=NULL;
		(lstHead->first)->first=NULL;
		free(morto1);		
		free(morto2);
		printf("%p\n", lstHead->first);
		mostrar_lista(lstHead->first);
	}
	return status;
}

int insertionS_lista(listHead *lstHead){
	clock_t clock_1, clock_2;
	clock_1=clock();
    lista *change, *lst_temp_i, *lst_temp_j;
	int  i, j, *k;
	puts("lista...");
	puts("insertionS_lista()...");
	printf("lstHead->first: %p\n", lstHead->first);
	printf("(lstHead->first)->next: %p\n", (lstHead->first)->next);

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
		if(i > j){
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
	lst_temp_i=lstHead->first;
	while(lst_temp_i->next)
		lst_temp_i=lst_temp_i->next;
	lstHead->last=lst_temp_i;
	clock_2=clock();
	printf("tempo de ordenacao da lista: %d\n", (int)(clock_2 - clock_1));
	return 0;
}

int gerarLista_deNoh_ASCII(listHead *lstHead){
	int status=0;
	status=input_fileTolist(lstHead);
	return status;
}

int input_fileTolist(listHead *lstHead){
	int status=0;
	char chr;
	char temp_string[31]="testefile.txt";
	lista* noh;
	printf("Digite o nome do arquivo para compactacao: ");
	//__fpurge(stdin);
	//scanf("%s", temp_string);
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



/*imprime(); checa se a sub árvore não é vazia para uma função de impressão.
*/
void imprime(arvore* noh){
	puts("impressão...");
	if(ehvazia(noh))
		puts("Arvore vazia.");
	else{
		imprime_adress(noh);
		imprime_dado(noh);
	}
}

/*imprime_adress(); imprime recursivamente os adress dos nós de uma sub árvore*/
void imprime_adress(arvore* noh){
	if(!ehvazia(noh)){
		printf("imprime_adress(); noh adress: %p\n", noh);
		imprime_adress(noh->l);
		imprime_adress(noh->r);
	}
}

void imprime_dado(arvore* noh){
	if(!ehvazia(noh)){
		printf("imprime_dado(); peso: %d ... caracter: %c\n", ((nohChar*)noh->void_adress)->peso, ((nohChar*)noh->void_adress)->caracter);
		if(noh->l)
			puts("... ->l");
		imprime_dado(noh->l);
		if(noh->r)
			puts("... ->r");
		imprime_dado(noh->r);
	}	
}

void mostrar_lista(lista* lst){
	printf("%c ... peso: %d ... adress: %p\n", ((nohChar*)((arvore*)lst->adress_type)->void_adress)->caracter, 
											   ((nohChar*)((arvore*)lst->adress_type)->void_adress)->peso),
									           lst;
	//printf("%p\n", lst->next);
	if(lst->next!=NULL)
		mostrar_lista(lst->next);
}

/*ehvazia(); retorna 1 se a sub árvore for vazia.
*/
int ehvazia(arvore* noh){
	return noh==NULL;
}
