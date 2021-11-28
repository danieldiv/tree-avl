#include "tree.h"

int menu();
void imprimir(Tree *raiz);
void inicializar(Tree **raiz);
void remover(Tree **raiz);
void pesquisar(Tree **raiz);

int main() {
	int op;
	Tree *raiz = createTree();

	do {
		system("clear");
		op = menu();

		switch(op) {
			case 1:
				inicializar(&raiz);
			break;
			case 2:
				imprimir(raiz);
			break;
			case 3:
				remover(&raiz);
			break;
			case 4:
				pesquisar(&raiz);
			break;
			case 0:
				printf("O programa sera finalizado!\n");
				return EXIT_SUCCESS;
			default:
				printf("Opcao invalida!\n");
		}

		system("read -p \"\nPressione enter para continuar\" saindo");
	} while (op != 0);

	return EXIT_SUCCESS;	
}

int menu() {
	int op;

	printf("====================\n");
	printf("   MENU DE OPCOES\n");
	printf("====================\n\n");
	
	printf("1 - Incializar arvore\n");
	printf("2 - Imprimir arvore\n");
	printf("3 - Remover elemento\n");
	printf("4 - Pesquisar\n");
	printf("0 - Sair\n\n");

	printf("Escolha uma opção: ");
	scanf("%d", &op);

	return op;
}

void pesquisar(Tree **raiz) {
	if(*raiz == NULL)
		printf("Arvore vazia!\n");
	else {
		Record r;
		Tree *aux, *aux2;

		aux = createTree();
		aux2 = *raiz;

		system("clear");
		printf("====================\n");
		printf("     PESQUISAR\n");
		printf("====================\n\n");

		printf("CENTRAL: { ");
		central(aux2);

		printf("}\n\nQual elemento deseja pesquisar? ");
		scanf("%d", &r.key);

		pesquisa(raiz, &aux, r);

		if(aux != NULL){
			printf("\nELEMENTOS ABAIXO DE (%d) EM\n", r.key);
			printf("PRE ORDEN: { ");
			preordem(aux);
			printf("}\n");
		}
	}
	
}

void imprimir(Tree *raiz) {
	if(raiz == NULL)
		printf("Arvore vazia!\n");
	else {
		printf("\nPRE ORDEN: { ");
		preordem(raiz);
		
		printf("}\nCENTRAL:   { ");
		central(raiz);
		
		printf("}\nPOS ORDEN: { ");
		posordem(raiz);
		printf("}\n");
	}
}

void inicializar(Tree **raiz) {
	int elemento, i, tam;
	Record r;

	int vetor1[] = {10,2,7,5,3,9,16,4,11,1,6,23,14};
	int vetor2[] = {78,44,67,92,22,110,16,54,23,32,37};

	system("clear");
	*raiz = createTree();

	printf("====================\n");
	printf("     ELEMENTOS\n");
	printf("====================\n\n");

	printf("1 - { 10,2,7,5,3,9,16,4,11,1,6,23,14 }\n");
	printf("2 - { 78,44,67,92,22,110,16,54,23,32,37 }\n\n");

	printf("Quais elementos deseja inserir: ");
	scanf("%d", &elemento);

	if(elemento == 1) {
		tam = sizeof(vetor1)/sizeof(vetor1[0]);

		for(i=0; i < tam; i++) {
			r.key = vetor1[i];
			insertItem(raiz, r);
		}
	} else if(elemento == 2) {
		tam = sizeof(vetor2)/sizeof(vetor2[0]);

		for(i=0; i < tam; i++) {
			r.key = vetor2[i];
			insertItem(raiz, r);
		}
	} else
		printf("Opcao invalida. A arvore sera reiniciada!\n");
}

void remover(Tree **raiz) {
	if(*raiz == NULL)
		printf("Arvore vazia!\n");
	else {
		Record r;
		Tree *aux;

		aux = *raiz;

		system("clear");
		printf("====================\n");
		printf("     REMOVER\n");
		printf("====================\n\n");

		printf("CENTRAL: { ");
		central(aux);

		printf("}\n\nQual elemento deseja remover? ");
		scanf("%d", &r.key);

		removeItem(raiz, raiz, r);
	}
}