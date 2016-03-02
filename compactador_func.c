#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactador_huffman.h"
#include <time.h>

int tabMaker_inicializa(tabCode** tab, arvoreHead* arvHead){
	puts("-------------------------------------------------------");
	puts("tabMaker_inicializa()...");
	int i;
	tabCode* novo_tab=(tabCode*)malloc(arvHead->largura*sizeof(tabCode));
	int* novo_i=(int*)malloc(sizeof(int));
	*novo_i=0;
	printf("%p\n", novo_tab->i);
	if (novo_tab && novo_i)
		puts("tabCode alocado em memoria!");
	else{
		puts("erro na alocação do tabCode...");
		return 1;
	}
	puts("Preenchimento do tabCode...");
	for(i=0; i<arvHead->largura; i++){
		(novo_tab+i)->code=NULL;
		(novo_tab+i)->code_size=0;
		(novo_tab+i)->caracter='*';
		(novo_tab+i)->i=novo_i;
	}
	puts("tabCode preenchido!");
	*tab=novo_tab;
	printf("%c\n", (*tab)->caracter);
	return 0;
}

int tabMaker_finalizar(tabCode* tab, arvoreHead* arvHead){
	puts("-------------------------------------------------------");
	puts("tabMaker_finalizar()...");
	int i, status=0;
	lista* code, *morto;
	for(i=0; i<arvHead->largura; i++){
		code=(tab+i)->code;
		if(code){
			while(code){
				morto=code;
				code=code->first;
				free(morto);
			}
		}
		else
			printf("%p", code);
	}
	free(tab->i);
	free(tab);
	puts("tab finalizada!");
	return status;
}


int output_listTofileEncoder(arvoreHead *arvHead, char* string){
	puts("-------------------------------------------------------");
	puts("output_listTofileEncoder()...");
	int status=0;
	//FILE* fp;
	tabCode* tab;
	tabMaker_inicializa(&tab, arvHead);
	tabMaker_imprime(tab, arvHead);

	tabMaker_ARVTotabEncoder(arvHead, tab);
	tabMaker_imprime(tab, arvHead);

	tabMaker_tabTofileEncoder(tab, arvHead, string);
	
	tabMaker_finalizar(tab, arvHead);
	removeSubARV(arvHead->root, arvHead);
	return status;
}
int tabMaker_ARVTotabEncoder(arvoreHead* arvHead, tabCode* tab){
	puts("-------------------------------------------------------");
	puts("tabMaker_ARVTotabEncoder()...");
	int status=0;
	lista *temp_code=NULL;
	tabMaker_ARVTotabEncoder_REC(arvHead, arvHead->root, tab, temp_code);
	return status;
}

void tabMaker_ARVTotabEncoder_REC(arvoreHead* arvHead, arvore* noh, tabCode* tab, lista* temp_code){
	puts("-------------------------------------------------------");
	printf("  !ehvazia()... return %d\n", !ehvazia(noh));
	if(!ehvazia(noh)){
		puts(">>>>");
		if(noh->l==NULL && noh->r==NULL){
			printf("%d\n", *(tab->i));
			puts("a");
			(tab+*(tab->i))->code=tabMaker_Salvar(tab+*(tab->i), temp_code, noh);
			puts("b");
			tabMaker_imprime(tab, arvHead);
			printf("*(tab->i): %d\n", *(tab->i));
		}
		else{
			temp_code=tabMaker_addList(0, temp_code);
		}
		tabMaker_ARVTotabEncoder_REC(arvHead, noh->l, tab, temp_code);
		if(noh->l || noh->r){
			temp_code=tabMaker_rmList(temp_code);
			temp_code=tabMaker_addList(1, temp_code);
		}
		tabMaker_ARVTotabEncoder_REC(arvHead, noh->r, tab, temp_code);
		if(noh->l || noh->r){
			temp_code=tabMaker_rmList(temp_code);
		}		
	}
}

int tabMaker_tabTofileEncoder(tabCode* tab, arvoreHead* arvHead, char *string){
	puts("-------------------------------------------------------");
	puts("tabMaker_tabTofileEncoder()...");
	int status=0;
	FILE* encodeFile_txt, *encodeFile_dat, *file;
	encodeFile_txt = fopen("arquivo_codificado.txt", "w");
	encodeFile_dat = fopen("arquivo_codificado.dat", "wb");
	if(encodeFile_dat==NULL)
		puts("erro ao abrir arquivo_codificado.txt");
	else
		puts("arquivo_codificado.txt Aberto!");
	file = fopen(string, "r");
	if (file==NULL)
		printf("erro ao abrir %s\n", string);
	else
		printf("%s Aberto!\n", string);
	tabMaker_tabTofileEncoder_ARV_DAT(arvHead, encodeFile_dat);

	printf("\n");
	tabMaker_tabTofileEncoder_TAB_TXT(tab, arvHead, encodeFile_txt, file);

	fclose(encodeFile_dat);
	fclose(encodeFile_txt);
	free(string);
	return status;
}



void tabMaker_tabTofileEncoder_TAB_REC_DAT(tabCode* tab, FILE* encodeFile, FILE* file){
	if(tab && encodeFile && file){
	}
}

void tabMaker_tabTofileEncoder_TAB_TXT(tabCode* tab, arvoreHead* arvHead, FILE* encodeFile, FILE* file){
	int i;
	char chr;
	lista* list_temp;
	if(tab && encodeFile && file){
		puts("tabMaker_tabTofileEncoder_TAB_TXT(); Arquivo aberto.");
		while(1){
			chr=fgetc(file);
			if(chr==EOF)
				break;
			else {
				for(i=0; i<arvHead->largura; i++){
					if((tab+i)->caracter==chr){
						list_temp=(tab+i)->code;
						while(list_temp){
							if(list_temp->adress_type==NULL)
								fprintf(encodeFile, "0\n");
							else
								fprintf(encodeFile, "1\n");
							list_temp=list_temp->first;
						}
					}
				}
			}
		}
	}
	else {
		puts("Erro ao abrir arquivo!");
	}
}

void tabMaker_tabTofileEncoder_ARV_REC_TXT(arvore* noh, FILE* fp){
	printf("<");
	fprintf(fp, "<");
	if(!ehvazia(noh)){
		if(noh->l==NULL && noh->r==NULL){
			printf("%c", ((nohChar*)noh->void_adress)->caracter);
			fprintf(fp, "%c",((nohChar*)noh->void_adress)->caracter);
		}
		tabMaker_tabTofileEncoder_ARV_REC_TXT(noh->l, fp);
		tabMaker_tabTofileEncoder_ARV_REC_TXT(noh->r, fp);
		printf(">");
		fprintf(fp, ">");
	}
	else{
		printf(">");
		fprintf(fp, ">");
	}
}

int tabMaker_tabTofileEncoder_ARV_DAT(arvoreHead* arvHead, FILE* encodeFile_dat){
	puts("-------------------------------------------------------");
	puts("tabMaker_tabTofileEncoder_ARV_DAT()...");
	int status=0;
	fwrite(arvHead, sizeof(arvoreHead), 1, encodeFile_dat);
	tabMaker_tabTofileEncoder_ARV_REC_DAT(arvHead->root, encodeFile_dat);
	return status;
}

void tabMaker_tabTofileEncoder_ARV_REC_DAT(arvore* noh, FILE* encodeFile_dat){
	printf("%p\n", noh);
	if(!ehvazia(noh)){
		fwrite(noh, sizeof(arvore), 1, encodeFile_dat);
		fwrite(noh->void_adress, sizeof(nohChar), 1, encodeFile_dat);
		tabMaker_tabTofileEncoder_ARV_REC_DAT(noh->l, encodeFile_dat);
		tabMaker_tabTofileEncoder_ARV_REC_DAT(noh->r, encodeFile_dat);
	}
}

lista* tabMaker_Salvar(tabCode* tab, lista* lst_code, arvore* noh){
	printf("	tabMaker_Salvar()... \n");
	int n=0;
	lista* code=NULL, *temp_count=NULL;
	//lista* next_code = (tab+1)->code;
	if(lst_code){
		temp_count=lst_code;
		while(temp_count){
			n++;
			temp_count=temp_count->first;
		}
		puts("...");
		temp_count=lst_code;
		while(temp_count){
			if(temp_count->adress_type==NULL){
				printf("add 0 -->");
				code=tabMaker_addList(0, code);
			}
			else{
				printf("add 1 -->");
				code=tabMaker_addList(1, code);
			}
			temp_count=temp_count->first;
		}
		printf("code: ");
		temp_count=code;
		while(temp_count){
			if(temp_count->adress_type==NULL){
				printf("0 ");
			}
			else{
				printf("1 ");
			}
			temp_count=temp_count->first;
		}
		printf("%p %c\n", &(tab->caracter), ((nohChar*)noh->void_adress)->caracter);
		tab->caracter=((nohChar*)noh->void_adress)->caracter;
		tab->code_size=n;
		printf("		tab->code_size= %d\n", tab->code_size);
		printf("%d\n", *(tab->i));
		*(tab->i)=1+*(tab->i);
		printf("%c\n", tab->caracter);
	}
	printf("	tab->code: %p Ok!\n", code);
	return code;
}

lista* tabMaker_addList(int bit, lista* lst_bit){
	printf("	tabMaker_addList...\n");
	lista* novo_bit=(lista*)malloc(sizeof(lista));
	if(bit)
		novo_bit->adress_type=novo_bit;
	else
		novo_bit->adress_type=NULL;
	novo_bit->next=NULL;
	novo_bit->first=lst_bit;
	if(lst_bit)
		//lst_bit->next=novo_bit;
	printf("\nnovo_bit: %p Ok!\n", novo_bit);
	return novo_bit;
}

lista* tabMaker_rmList(lista* lst_bit){
	printf("	tabMaker_rmList... ");
	lista* first;
	if(lst_bit->first){
		first=lst_bit->first;
		first->next=NULL;
	}
	else
		first=NULL;
	free(lst_bit);
	printf("Ok!\n");
	return first;
}

void tabMaker_imprime(tabCode* tab, arvoreHead* arvHead){
	puts("-------------------------------------------------------");
	puts("tabMaker_imprime()...");
	int i;
	lista* code;
	for(i=0; i<arvHead->largura; i++){
		printf("%c: ", (tab+i)->caracter);
		code=(tab+i)->code;
		if(code){
			while(code){
			//printf("%p ", code);
			//printf("next%p first%p: ", code->next, code->first);
			if(code->adress_type==NULL)
				printf("0");
			else
				printf("1");
			code=code->first;
			}
		}
		else
			printf("%p", code);
		printf("\n");
	}
}





//#############################################################################

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

arvore* removeSubARV(arvore *noh, arvoreHead *arvHead){
	if(!ehvazia(noh)){
		removeSubARV(noh->l, arvHead);
		removeSubARV(noh->r, arvHead);
		//printf("removeRamoARV(); noh adress: %p\n", noh);
		arvHead->size--;
		free(noh->void_adress);
		free(noh);
		//printf("removeRamoARV(); noh adress: %p\n", noh);
	}
	return NULL;
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
		free(morto1);		
		free(morto2);
		printf("%p\n", lstHead->first);
		mostrar_lista(lstHead->first);
		free(lstHead->first);
	}
	return status;
}

int insertionS_lista(listHead *lstHead){
	clock_t clock_1, clock_2;
	clock_1=clock();
    lista *change, *lst_temp_i, *lst_temp_j;
	int  i, j, *k;
	puts("-------------------------------------------------------");
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

int gerarLista_deNoh_ASCII(listHead *lstHead, char** string){
	puts("-------------------------------------------------------");
	puts("gerarLista_deNoh_ASCII()...");
	int status=0;
	status=input_fileTolist(lstHead, string);
	return status;
}

int input_fileTolist(listHead *lstHead, char** string){
	puts("-------------------------------------------------------");
	puts("input_fileTolist()...");
	int status=0;
	char chr;
	char temp_string[31]="testefile.txt";
	lista* noh;
	printf("Digite o nome do arquivo para compactacao: ");
	//__fpurge(stdin);
	//scanf("%s", temp_string);
	*string=(char*)malloc(strlen(temp_string)*sizeof(char));
	*string=strcpy(*string, temp_string);
	if(strcmp(*string, temp_string)){
		puts("ERRO STRING!");
		exit(1);
	}
	FILE* fp;
	puts("...");
	fp = fopen(*string, "r");
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
	puts("-------------------------------------------------------");
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
	puts("-------------------------------------------------------");
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
	puts("-------------------------------------------------------");
	puts("imprime()...");
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
		printf("	imprime_adress(); noh adress: %p\n", noh);
		imprime_adress(noh->l);
		imprime_adress(noh->r);
	}
}

void imprime_dado(arvore* noh){
	if(!ehvazia(noh)){
		printf("	imprime_dado(); peso: %d ... caracter: %c\n", ((nohChar*)noh->void_adress)->peso, ((nohChar*)noh->void_adress)->caracter);
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
											   ((nohChar*)((arvore*)lst->adress_type)->void_adress)->peso,
									           lst);
	//printf("%p\n", lst->next);
	if(lst->next!=NULL)
		mostrar_lista(lst->next);
}

int main_largura_ARV(arvoreHead* arvHead){
	puts("-------------------------------------------------------");
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
	puts("-------------------------------------------------------");
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

/*ehvazia(); retorna 1 se a sub árvore for vazia.
*/
int ehvazia(arvore* noh){
	return noh==NULL;
}
