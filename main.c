#include <stdio.h>
#include <stdlib.h>
#include "rbTree.h"

//menu para fins de teste das funcoes e da implementacao da arvore rubro negra

int main() {
    rbNode *arvore = NULL;

    int op = -1, aux = 1, pOp = -1, test = -1, n, rm;

    //vetores para insercoes teste
    int ex1[10] = {13,8,17,1,11,15,25,6,22,27};
    int ex2[8] = {7,3,19,10,22,8,11,26};
    int ex3[13] = {61,52,85,20,55,76,93,16,71,81,90,101,65};
    

    do {
        printf("1) Inserir elemento.\n2) Remover elemento.\n3) Ver árvore.\n4) Ver Altura.\n5) Casos de Teste.\n6) Sair.\n\n");
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
                  system("clear");
		  printf("1) Caso de teste 1\n2) Caso de teste 2\n3) Caso de teste 3\n\n");
		  printf("digite o caso desejado: ");
		  scanf("%d",&test);

		  if(test == 1){
		     for(int i = 0; i < 10; i++)
                        inserir(&arvore,NULL,&arvore,ex1[i]);
		  }
		  else if(test == 2){
		     for(int i = 0; i < 8; i++)
			inserir(&arvore,NULL,&arvore,ex2[i]);
		  }
		  else if(test == 3){
		     for(int i = 0; i < 13; i++)
			inserir(&arvore,NULL,&arvore,ex3[i]);
		  }
		  else
		     printf("Opcao Invalida, retornando ao menu...");
		  break;

            case 6:
                aux = 0;
                break;

            default:
                printf("Opcao invalida.\n");
        }

        printf("=======================================================\n");
    } while (aux);
    
    system("clear");
    return 0;
}
