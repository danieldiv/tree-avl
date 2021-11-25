#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Record Record;
typedef struct Tree Tree;

struct Record {
	int value;
	int key;
};

struct Tree {
	Record reg;
	Tree *esq, *dir;
	int peso;
};

Tree* createTree();
void insertItem(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);

void antecessor(Tree **t, Tree *aux);
void removeItem(Tree **t, Tree **f, Record r);
void rebalanceTree(Tree **t);

void preordem(Tree *t);
void central(Tree *t);
void posordem(Tree *t);

int getPeso(Tree **t);
int getMaxPeso(int left, int right);

void rotacaoSimplesDireita(Tree **t);
void rotacaoSimplesEsquerda(Tree **t);
void rotacaoDuplaDireita(Tree **t);
void rotacaoDuplaEsquerda(Tree **t);

#endif