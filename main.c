#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

//menu para fins de teste das funcoes e da implementacao da arvore rubro negra

int main() {
    rbNode *arvore = NULL;

    int op = -1, aux = 1, pOp = -1, n, rm;
    

    do {
        printf("1) Inserir elemento.\n2) Remover elemento.\n3) Ver árvore.\n4) Ver Altura.\n5) Sair.\n\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Elemento a inserir:\n");
                scanf("%d", &n);
                inserir(&arvore, NULL, &arvore, n);
		system("clear");
                break;

            case 2:
                printf("Elemento a remover:\n");
                scanf("%d", &rm);
                remover(&arvore, rm);
		system("clear");
                break;

            case 3:
		system("clear");
            	printf("\n\n 1)Pre-Order\n 2)In-Order\n\nEscolha o metodo de mostragem: ");
		scanf("%d",&pOp);
                printRbTree(arvore, pOp);
                break;
	    
	    case 4:
		system("clear");
		printf("A Arvore tem altura %d.\n\n",altura(arvore));
		break;

            case 5:
                aux = 0;
                break;

            default:
                printf("Opção inválida.\n");
        }

        printf("=======================================================\n");
    } while (aux);
    
    system("clear");
    return 0;
}
