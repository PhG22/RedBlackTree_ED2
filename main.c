#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

//menu para fins de teste das funcoes e da implementacao da arvore rubro negra

int main() {
    rbNode *arvore = NULL;

    int op = -1, aux = 1, n, rm;
    

    do {
        printf("1) Inserir elemento.\n2) Remover elemento.\n3) Ver árvore.\n4) Sair.\n");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Elemento a inserir:\n");
                scanf("%d", &n);
                inserir(&arvore, NULL, &arvore, n);
                break;

            case 2:
                printf("Elemento a remover:\n");
                scanf("%d", &rm);
                remover(&arvore, rm);
                break;

            case 3:
                printRbTree(arvore);
                break;

            case 4:
                aux = 0;
                break;

            default:
                printf("Opção inválida.\n");
        }

        printf("=======================================================\n");
    } while (aux);

    return 0;
}
