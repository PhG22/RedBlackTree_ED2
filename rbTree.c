	#include <stdio.h>
	#include <stdlib.h>
        #include <assert.h>//usado para garantir a entrada de um ponteiro valido nas funcoes
	#include "rbTree.h"
        

        //difinindo constantes
	#define BLACK 0
	#define RED 1
	
        //funcao para retornar o no avo de um no qualquer
	rbNode* avo(rbNode* tree) {
		if ((tree != NULL) && (tree->pai != NULL))
			return (tree->pai)->pai;
		else
			return NULL;
	}
        
        //funcao para retornar o no tio de um no qualquer
	rbNode* tio(rbNode* tree) {
		rbNode* pAvo = avo(tree);
		if (pAvo == NULL) 
			return NULL;

		if (tree->pai == pAvo->esq)
			return pAvo->dir;
		else
			return pAvo->esq;

	}
	
        //funcao para retornar o no irmao de um no qualquer
	rbNode* irmao(rbNode* pai, rbNode* atual){
		if(pai == NULL) 
			return NULL;

		if(pai->dir->chave == atual->chave)
			return pai->esq;
		else
			return pai->dir;
	}
	
        //funcao que retorna o maior no da esquerda
	rbNode** maiorEsq(rbNode** pMaiorEsq){
		assert(pMaiorEsq);
		
		if (*pMaiorEsq == NULL) 
			return NULL;

		if ((*pMaiorEsq)->dir == NULL)
			return pMaiorEsq;
		else
			return maiorEsq(&((*pMaiorEsq)->dir));
	}

        //funcao que verifica se um no eh um filho da esquerda
	int filhoEsq(rbNode* tree){
		if(tree->pai->esq == tree)
			return 1;
		else
			return 0;
	}
	
        //rotacoes
	void rotacaoEsq(rbNode** node) {
		assert(node);

		if (*node == NULL) 
			return;

		rbNode* aux = *node;
		*node = aux->dir;
		aux->dir = (*node)->esq;
		(*node)->esq = aux;

		(*node)->pai = aux->pai;
		if (aux->esq != NULL)
			(aux->esq)->pai = aux;

		aux->pai = *node;
	 
		aux->cor = RED;
		(*node)->cor = BLACK;
	}
	
	void rotacaoDir(rbNode** node) {
		assert(node);

		if (*node == NULL) 
			return;

		rbNode *aux = *node;
		*node = aux->esq;
		aux->esq = (*node)->dir;
		(*node)->dir = aux;

		(*node)->pai = aux->pai;
		if(aux->dir != NULL)
			(aux->dir)->pai = aux;

		aux->pai = *node;

		aux->cor = RED;
		(*node)->cor = BLACK;

	}

	void rotacao_duplaEsq(rbNode** node) {
		assert(node);

		rotacaoDir(&((*node)->dir));
		rotacaoEsq(node);

	}

	void rotacao_duplaDir(rbNode** node) {
		assert(node);

		rotacaoEsq(&((*node)->esq));
		rotacaoDir(node);
	}
        

        //arruma a arvore, garantindo que nenhuma de suas propriedades seja violada
	void fixRb(rbNode** tree, rbNode** root) {
		assert(tree);

		rbNode* pAvo = NULL;
		rbNode* pTio = NULL;

		if((*tree)->pai != NULL) {
			if((*tree)->pai->cor == BLACK) return;

			if((*tree)->cor == RED) {
				pTio = tio(*tree); 
				if (pTio != NULL && pTio->cor == RED) {
					pAvo = avo(*tree);
					(*tree)->pai->cor = BLACK;
					pTio->cor = BLACK;
					if (pAvo->pai != NULL) {
						pAvo->cor = RED;
					} 
				} else {
					pAvo = avo(*tree);
					if (pAvo != NULL) {
						if ((*tree)->pai == pAvo->esq) { // filho esquerdo
							if ((*tree) == (pAvo->esq)->esq) {
								if (pAvo->pai != NULL) {
									if ((pAvo->pai)->esq == pAvo)
										rotacaoDir(&((pAvo->pai)->esq));
									else
										rotacaoDir(&((pAvo->pai)->dir));
								} else {
									rotacaoDir(root);
								}


						   } else {
							   if (pAvo->pai != NULL) {
								   if ((pAvo->pai)->esq == pAvo) {
										rotacao_duplaDir(&((pAvo->pai)->esq));
								   } else
									   rotacao_duplaDir(&((pAvo->pai)->dir));
							   } else { 
									rotacao_duplaDir(root);
							   }
						  }
					   } else { 
						   if ((*tree) == ((pAvo->dir)->dir)) {
							   if (pAvo->pai != NULL) {
								   if (((pAvo->pai)->esq) == pAvo) {
										rotacaoEsq(&((pAvo->pai)->esq));
								   } else
									   rotacaoEsq(&((pAvo->pai)->dir));
							   } else {
									rotacaoEsq(root);
							   }

						   } else {
							   if (pAvo->pai != NULL) {
								   if((pAvo->pai)->esq == pAvo) {
										rotacao_duplaEsq(&((pAvo->pai)->esq));
								   } else {
									   rotacao_duplaEsq(&((pAvo->pai)->dir));
								   }
							   } else {
										rotacao_duplaEsq(root);
							   }
						   }
					}
					}
				}
			}
		}
	}
	
        //funcoes auxiliares que ajudam a tratar dos diversos casos de remocao
	void nBlackIBlackFRed(rbNode* rmv, rbNode** tree){
		assert(tree);

		rbNode* paiRmv = rmv->pai;

		if(filhoEsq(rmv) == 1){
			rmv->pai->esq = NULL;
			free(rmv);
		} else {
			rmv->pai->dir = NULL;
			free(rmv);
		}

		if(paiRmv->esq == NULL){
			if(paiRmv->pai == NULL){
				if((paiRmv->dir)->dir == NULL){
					rotacaoDir(&((*tree)->dir));
				}
				rotacaoEsq(tree);
			} 
			else {
				if((paiRmv->dir)->dir == NULL){
					rotacaoDir(&(paiRmv->dir));
				}
				rotacaoEsq(&paiRmv);
			}
		} 
		else {
			if(paiRmv->pai == NULL){
				if((paiRmv->esq)->esq == NULL){
					rotacaoEsq(&((*tree)->esq));
				}
				rotacaoDir(tree);
			} else {
				if((paiRmv->dir)->dir == NULL){
					rotacaoEsq(&(paiRmv->esq));
				}
				rotacaoDir(&paiRmv);
			}
		}
		return;
	}

	void nBlackIBlackFBlack(rbNode* rmv, rbNode** tree){
		assert(tree);

		rbNode* paiRmv = rmv->pai;
		rbNode* pIrmao = irmao(paiRmv, rmv);

		nBlackIRed(rmv, tree);

		paiRmv->cor = BLACK;
		pIrmao->cor = RED;
	}

	void nBlackIRed(rbNode* rmv, rbNode** tree){
		assert(tree);

		rbNode* paiRmv = rmv->pai;

		nBlackIBlackFRed(rmv,tree);

		paiRmv->cor = BLACK;
		if(paiRmv->esq != NULL)
			(paiRmv->esq)->cor = RED;
		if(paiRmv->dir != NULL)
			(paiRmv->dir)->cor = RED;
	}
        
	void remover(rbNode** tree, int key){
		assert(tree);

		if((*tree) == NULL) 
			return;

		rbNode* rmv = *tree;

		rmv = buscar(rmv, key);

		if(rmv == NULL) 
			return;

		if(rmv->dir == NULL && rmv->esq == NULL){
			if(rmv->pai == NULL){
				free(rmv);
				*tree = NULL;
				return;
			} else {
				if(rmv->cor == RED && rmv->dir == NULL && rmv->esq == NULL){
					if(filhoEsq(rmv) == 1){
						rmv->pai->esq = NULL;
						free(rmv);
					} else {
						rmv->pai->dir = NULL;
						free(rmv);
					}
					return;
				} else {
					rbNode* pIrmao = irmao(rmv->pai,rmv);
						if(pIrmao == NULL) return;

					if(rmv->cor == BLACK && pIrmao->cor == BLACK){
						if(pIrmao->dir == NULL && pIrmao->esq == NULL){
							nBlackIBlackFBlack(rmv, tree);
							return;
						} else if(pIrmao->esq->cor == BLACK && pIrmao->dir->cor == BLACK){
							nBlackIBlackFBlack(rmv, tree);
							return;
						}
						else if(pIrmao->dir->cor == BLACK && pIrmao->esq == NULL){
							nBlackIBlackFBlack(rmv, tree);
							return;
						}
						else if(pIrmao->esq->cor == BLACK && pIrmao->dir == NULL){
							nBlackIBlackFBlack(rmv, tree);
							return;
						}
					} else if(rmv->cor == BLACK && pIrmao->cor == BLACK && (pIrmao->esq->cor == RED || pIrmao->dir->cor == RED)){
						if(pIrmao->esq != NULL){
							nBlackIBlackFRed(rmv, tree);
							return;
						} else if (pIrmao->dir != NULL){
							nBlackIBlackFRed(rmv, tree);
							return;
						}
					} else if(rmv->cor == BLACK && pIrmao->cor == RED){
						nBlackIRed(rmv, tree);
					}
				}
				return;
			}
		} else if (rmv->dir == NULL || rmv->esq == NULL){
			if(rmv->dir != NULL){
				rmv->chave = rmv->dir->chave;
				rmv->dir = NULL;
				free(rmv->dir);
			} else {
				rmv->chave = rmv->esq->chave;
				rmv->esq = NULL;
				free(rmv->esq);
			}
		} else {
			rbNode** subst = maiorEsq(&(rmv->esq));
			rbNode* aux = *subst;

			rmv->chave = (*subst)->chave;
			(*subst)->pai->esq = (*subst)->esq;


			if(rmv->cor == RED){
				if(rmv->esq == NULL && rmv == rmv->pai->esq && (rmv->dir->dir != NULL || rmv->dir->esq != NULL)){
					if(rmv->dir->dir != NULL){
						rotacaoDir(&(rmv->esq));
						rotacaoEsq(&rmv);
					}
					if(rmv->dir->esq != NULL){
						rotacaoDir(&(rmv->dir));
						rotacaoEsq(&rmv);
					}
				} else if(rmv->esq == NULL && rmv == rmv->pai->dir && (rmv->esq->dir != NULL || rmv->esq->esq != NULL)){
					if(rmv->esq->dir != NULL){
						rotacaoEsq(&(rmv->esq));
						rotacaoDir(&rmv);
					}
					if(rmv->esq->esq != NULL){
						rotacaoEsq(&(rmv->esq));
						rotacaoDir(&rmv);
					}
				}

				rmv->cor = BLACK;
				if(rmv->esq != NULL)
					rmv->esq->cor = RED;
				if(rmv->dir != NULL)
					rmv->dir->cor = RED;
			}
			free(aux);
		}
	}
	
	void inserir(rbNode** tree, rbNode* pPai, rbNode** root, int key) {
		assert(tree);

		if (*tree == NULL) {
			*tree = (rbNode*)malloc(sizeof(rbNode));
			if (*tree == NULL) 
				return;

			(*tree)->chave = key;
			(*tree)->cor = RED;
			
			(*tree)->pai = pPai;
			(*tree)->esq = NULL;
			(*tree)->dir = NULL;
			
		} else {

			if (key < (*tree)->chave) {
				inserir(&((*tree)->esq), *tree, root, key);
				fixRb(&((*tree)->esq), root);
			} else if (key > (*tree)->chave) {
				inserir(&((*tree)->dir), *tree, root, key);
				fixRb(&((*tree)->dir), root);
			}
		}
		
		if (*tree == *root)
				(*tree)->cor = BLACK;

	}

	rbNode* buscar(rbNode* tree, int key){
		if (tree == NULL) 
			return NULL;

		if (tree->chave == key) 
			return tree;

		if (key < tree->chave)
			return buscar(tree->esq, key);
		else
			return buscar(tree->dir, key);
	}
	
        //imprime os nos da arvore usando inOrder
	void printRbTree(rbNode* root, int op) {
		if (root == NULL) 
			return;

		if(op == 1){

		   printf("Chave: %d / Cor: %d\n\n", root->chave, root->cor);
		   printRbTree(root->esq,op);
		   printRbTree(root->dir,op);
		}

		else if(op == 2){
		   printRbTree(root->esq,op);
		   printf("Chave: %d / Cor: %d\n\n", root->chave, root->cor);
		   printRbTree(root->dir,op);
		}
		else
	 	   printf("Opcao invalida, voltando ao menu...");
	}

        //funcao que calcula a altura da arvore recursivamente
	int altura(rbNode* atual){
	   if(atual == NULL || (atual->esq == NULL && atual->dir == NULL))
	      return 0;
	   else{
	      if(altura(atual->esq) > altura(atual->dir)){
	         if(atual->cor == BLACK)
		    return (1 + altura(atual->esq));
		 else
		    return (altura(atual->esq));
	      }
	      else{
 	         if(atual->cor == BLACK)
		    return (1 + altura(atual->dir));
		 else
		    return(altura(atual->dir));
	      }
	   }
	}

