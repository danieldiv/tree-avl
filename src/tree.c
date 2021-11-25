#include "tree.h"

Tree* createTree() {
	return NULL;
}

void rotacaoSimplesDireita(Tree **t) {
	Tree *aux;

	printf("\nRSD\n");
	printf("t: %d\n", (*t)->reg.key);
	printf("t->esq: %d\n", (*t)->esq->reg.key);

	printf("1\n");
	aux = (*t)->esq;
	printf("2\n");
	(*t)->esq = aux->dir;
	printf("3\n");
	aux->dir = (*t);
	printf("4\n");
	(*t)->peso = getMaxPeso( getPeso( &(*t)->esq ), getPeso( &(*t)->dir ) ) + 1;
	printf("5\n");
	aux->peso = getMaxPeso( getPeso( &(*t)->esq ), (*t)->peso ) + 1;
	printf("6\n");
	(*t) = aux;
}

void rotacaoSimplesEsquerda(Tree **t) {
	Tree *aux;

	printf("\nRSE\n");
	printf("t: %d\n", (*t)->reg.key);
	printf("t->dir: %d\n", (*t)->dir->reg.key);

	aux = (*t)->dir;
	(*t)->dir = aux->esq;
	aux->esq = (*t);
	(*t)->peso = getMaxPeso( getPeso( &(*t)->esq ), getPeso( &(*t)->dir ) ) + 1;
	aux->peso = getMaxPeso( getPeso( &(*t)->esq ), (*t)->peso ) + 1;
	(*t) = aux;
}

void rotacaoDuplaDireita(Tree **t) {
	rotacaoSimplesEsquerda(&(*t)->esq);
	rotacaoSimplesDireita(t);
}

void rotacaoDuplaEsquerda(Tree **t) {
	rotacaoSimplesDireita(&(*t)->dir);
	rotacaoSimplesEsquerda(t);
}

void insertItem(Tree **t, Record r) {
	if(*t == NULL) {
		*t = (Tree*)malloc(sizeof(Tree));
		(*t)->esq = NULL;
		(*t)->dir = NULL;
		(*t)->reg = r;
		(*t)->peso = 0;
	} else {
		

		if(r.key < (*t)->reg.key) {
			printf("\ninsersao: %d\n", r.key);
			printf("lado esquerdo\n");
			printf("valor atual: %d", (*t)->reg.key);
			printf(" | peso: %d\n", (*t)->peso);

			insertItem(&(*t)->esq, r);

			printf("\n(%d:%d:%d) inserido E\n", r.key, (*t)->reg.key, (*t)->esq->reg.key);
			printf("esq: %d\n", getPeso( &(*t)->esq));
			printf("dir: %d\n", getPeso( &(*t)->dir));

			if(getPeso( &(*t)->esq) - getPeso(&(*t)->dir) == 2) {
				printf("rot D a\n");

				if(r.key < (*t)->esq->reg.key) {
					printf("rot S D b\n");
					rotacaoSimplesDireita(t);
				} else {
					printf("rot D D");
					rotacaoDuplaDireita(t);
				}
					
			}
		}
			

		if(r.key > (*t)->reg.key) {
			printf("\ninsersao: %d\n", r.key);
			printf("lado direito\n");
			printf("valor atual: %d", (*t)->reg.key);
			printf(" | peso: %d\n", (*t)->peso);

			insertItem(&(*t)->dir, r);

			printf("\n(%d:%d:%d) inserido D\n", r.key, (*t)->reg.key, (*t)->dir->reg.key);
			printf("esq: %d\n", getPeso( &(*t)->esq));
			printf("dir: %d\n", getPeso( &(*t)->dir));

			if(getPeso( &(*t)->dir) - getPeso(&(*t)->esq) == 2) {
				printf("rot E a\n");
				if(r.key > (*t)->dir->reg.key) {
					printf("rot S E b\n");
					rotacaoSimplesEsquerda(t);
				} else {
					printf("rot D E");
					rotacaoDuplaEsquerda(t);
				}
					
			}
		}
			
	}

	(*t)->peso = getMaxPeso( getPeso( &(*t)->esq ), getPeso( &(*t)->dir ) ) + 1;

}

int getPeso(Tree **t) {
	if(*t == NULL)
		return -1;
	return (*t)->peso;
}

int getMaxPeso(int left, int right) {
	if(left > right)
		return left;
	return right;
}

void pesquisa(Tree **t, Tree **aux, Record r) {
	if(*t == NULL) {
		printf("[ERRO]: Node not found!\n");
		return;
	}

	if((*t)->reg.key > r.key) { pesquisa(&(*t)->esq, aux, r); return; }
	if((*t)->reg.key < r.key) { pesquisa(&(*t)->dir, aux, r); return; }

	*aux = *t;
}

void antecessor(Tree **t, Tree *aux) {
	if((*t)->dir != NULL) {
		antecessor(&(*t)->dir, aux);
		return;
	}

	aux->reg = (*t)->reg;
	aux = *t;
	*t = (*t)->esq;
	free(aux);
}

void rebalanceTree(Tree **t) {

	if((*t) != NULL) {
		printf("O valor e %d\n", (*t)->reg.key);

		int balance;
		int left = 0;
		int right = 0;

		balance = getPeso(&(*t)->esq) - getPeso(&(*t)->dir);
		
		if((*t)->esq)
			left = getPeso(&(*t)->esq->esq) - getPeso(&(*t)->esq->dir);
		if((*t)->dir)
			right = getPeso(&(*t)->dir->esq) - getPeso(&(*t)->dir->dir);

		printf("\n============Valores balanceamento=========\n");
		printf("Raiz: %d, Filho esq: %d, Filho dir: %d\n", balance, left, right);
		printf("==========================================");

		if(balance == 2 && left >= 0) {
			printf("\n\nkey: %d\n", (*t)->reg.key);
			rotacaoSimplesDireita(t);
		}
			
		if(balance == 2 && left < 0)
			rotacaoDuplaDireita(t);

		if(balance == -2 && right >= 0)
			rotacaoDuplaEsquerda(t);
		if(balance == -2 && right < 0)
			rotacaoSimplesEsquerda(t);
	}
}

void removeItem(Tree **t, Tree **f, Record r) {
	Tree *aux;

	if(*t == NULL) {
		printf("[ERROR]: Record not found!!!\n");
		return;
	}

	if(r.key < (*t)->reg.key) { removeItem(&(*t)->esq, t, r); return; }
	if(r.key > (*t)->reg.key) { removeItem(&(*t)->dir, t, r); return; }

	if((*t)->dir == NULL) {
		aux = *t;
		*t = (*t)->esq;
		free(aux);

		// if((*f) != NULL)
			printf("valor de f: %d\n", (*f)->reg.key);
			printf("valor de f esq: %d\n", (*f)->esq->reg.key);
			printf("valor de f dir: %d\n", (*f)->dir->reg.key);
			rebalanceTree(f);
		// else
		// 	printf("ponteiro f eh nulo\n");

		// if((*t) != NULL)
			rebalanceTree(t);
		// else
		// 	printf("ponteiro t eh nulo\n");
		return;
	}

	if((*t)->esq != NULL) {
		antecessor(&(*t)->esq, *t);
		
		// if((*f) != NULL)
			rebalanceTree(f);
		// else
		// 	printf("ponteiro f eh nulo\n");

		// if((*t) != NULL)
			rebalanceTree(t);
		// else
		// 	printf("ponteiro t eh nulo\n");
		return;
	}

	aux = *t;
	*t = (*t)->dir;
	free(aux);
	
	// if((*f) != NULL)
		rebalanceTree(f);
	// else
	// 	printf("ponteiro f eh nulo\n");

	// if((*t) != NULL)
		rebalanceTree(t);
	// else
	// 	printf("ponteiro t eh nulo\n");
}

void preordem(Tree *t) {
	if(!(t == NULL)) {
		printf("%d ", t->reg.key);
		preordem(t->esq);
		preordem(t->dir);
	}
}

void central(Tree *t) {
	if(!(t == NULL)) {
		central(t->esq);
		printf("%d:%d ", t->reg.key, t->peso);
		central(t->dir);
	}
}

void posordem(Tree *t) {
	if(!(t == NULL)) {
		posordem(t->esq);
		posordem(t->dir);
		printf("%d ", t->reg.key);
	}
}