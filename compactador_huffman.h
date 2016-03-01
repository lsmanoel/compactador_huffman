/*
 ============================================================================
 Name        : compactador_hoffman.h
 Author      : Lucas Seara Manoel
 Version     : 1.0
 Copyright   : ...
 Description : Header do Compactador Huffman em C, Ansi-style.
 ============================================================================
 */
#ifndef COMPACTADOR_HUFFMAN_H_
#define COMPACTADOR_HUFFMAN_H_

struct _lista {
	void* adress_type;
	struct _lista *first;
	struct _lista *next;
};
typedef struct _lista lista;

struct _listHead {
    int size;
    struct _lista *last;
    struct _lista *first;
};
typedef struct _listHead listHead;

struct _vetorHead {
	int size;
	void* firstElement;
};
typedef struct _vetorHead vetorHead;

struct _arvore {
	void* void_adress;
	struct _arvore *r;
	struct _arvore *l;
};
typedef struct _arvore arvore;

struct _arvoreHead {
	int size;
	int altura;
	int largura;
	arvore *root;
};
typedef struct _arvoreHead arvoreHead;

struct _nohChar
{
	int peso;
	char caracter;
};
typedef struct _nohChar nohChar;

struct _tabCode
{
	char caracter;
	lista *code;
	int code_size;
	int *i;
};
typedef struct _tabCode tabCode;

//funções proprietárias do compactador
int gerarLista_deNoh_ASCII(listHead *lstHead, char** string);
int reordenadorLista_deNoh_ASCII(listHead *lstHead, arvoreHead* arvHead);

//protótipos de operação com árvore
int inicializaARV(arvoreHead **avrHead);
int main_altura_ARV(arvoreHead* arvHead);
void aux1_altura_ARV(arvoreHead* arvHead, arvore* noh, int* altura);
int main_largura_ARV(arvoreHead* arvHead);
void aux1_largura_ARV(arvore* noh, int* n_folhas);
int criarNohARV(void *elemento, int l_or_r, arvoreHead *head_temp);
arvore* removeSubARV(arvore *noh, arvoreHead *arvHead);
arvore* criarRamoARV(int* v, int *status, arvoreHead *avrHead);
arvore* criarNohRecursivo(void *elemento, arvore* l, arvore* r, arvoreHead *arvHead); 
int ehvazia(arvore* noh);

//protótipos I/O;
int input_fileTolist(listHead *lstHead, char** string);
int output_listTofileEncoder(arvoreHead *arvHead, char* string);

int tabMaker_inicializa(tabCode** tab, arvoreHead *arvHead);
int tabMaker_ARVTotabEncoder(arvoreHead* arvHead, tabCode* tab);
void tabMaker_ARVTotabEncoder_REC(arvoreHead* arvHead, arvore* noh, tabCode* tab, lista* temp_code);
lista* tabMaker_Salvar(tabCode* tab,lista* lst_code, arvore* noh);
lista* tabMaker_addList(int bit, lista* lst_bit);
lista* tabMaker_rmList(lista* lst_bit);
int tabMaker_tabTofileEncoder(tabCode* tab, arvoreHead* arvHead, char* string);
void tabMaker_tabTofileEncoder_ARV_REC_DAT(arvore* noh, FILE* fp);
void tabMaker_tabTofileEncoder_ARV_REC_TXT(arvore* noh, FILE* fp);
void tabMaker_tabTofileEncoder_TAB_REC_DAT(tabCode* tab, FILE* encodeFile, FILE* file);
void tabMaker_tabTofileEncoder_TAB_REC_TXT(tabCode* tab, FILE* encodeFile, FILE* file);
void tabMaker_imprime(tabCode* tab, arvoreHead* arvHead);
int tabMaker_finalizar(tabCode* tab, arvoreHead* arvHead);

void* input(void);
void imprime(arvore* noh);
void imprime_adress(arvore* noh);
void imprime_dado(arvore* noh);
void mostrar_lista(lista *lst);


//protótipos de operação com lista
int inicializaLista(listHead **lstHead);
int mostrarLista(listHead *lstHead);
int addLastList(listHead *lstHead, char chr);
int finalizaLista(listHead *lstHead);//para dados tipo int
int insertionS_lista(listHead *lstHead);
int buscaBin_lista(listHead *lstHead, int x);
int buscaLinear_lista(listHead *lstHead, char chr, lista **noh);

#endif /* COMPACTADOR_HUFFMAN_H_ */