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
	arvore *root;
};
typedef struct _arvoreHead arvoreHead;

struct _nohChar
{
	int peso;
	char caracter;
};
typedef struct _nohChar nohChar;

//funções proprietárias do compactador
int gerarLista_deNoh_ASCII(listHead *lstHead);
int reordenadorLista_deNoh_ASCII(listHead *lstHead, arvoreHead* arvHead);

//protótipos de operação com árvore
int inicializaARV(arvoreHead **avrHead);
int main_altura_ARV(arvoreHead* arvHead);
void aux1_altura_ARV(arvoreHead* arvHead, arvore* noh, int* altura);
int criarNohARV(void *elemento, int l_or_r, arvoreHead *head_temp);
arvore* removeSubARV(arvore *noh, arvoreHead *arvHead);
arvore* criarRamoARV(int* v, int *status, arvoreHead *avrHead);
arvore* criarNohRecursivo(void *elemento, arvore* l, arvore* r, arvoreHead *arvHead); 
int ehvazia(arvore* noh);

//protótipos I/O;
int input_fileTolist(listHead *lstHead);
int output_listTofileEncoder(arvoreHead *arvHead);
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