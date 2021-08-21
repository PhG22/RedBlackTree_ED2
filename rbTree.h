typedef struct _rbNode {
    int chave;
    int cor;
    struct _rbNode* pai;
    struct _rbNode* esq;
    struct _rbNode* dir;
} rbNode;

rbNode* avo(rbNode* tree);

rbNode* tio(rbNode* tree);

rbNode* irmao(rbNode* pai, rbNode* atual);

rbNode** maiorEsq(rbNode** pMaiorEsq);

int filhoEsq(rbNode* tree);

void rotacaoEsq(rbNode** node);

void rotacaoDir(rbNode** node);

void rotacao_duplaEsq(rbNode** node);

void rotacao_duplaDir(rbNode** node);

void fixRb(rbNode** tree, rbNode** root);

void nBlackIBlackFRed(rbNode* rmv, rbNode** tree);

void nBlackIBlackFBlack(rbNode* rmv, rbNode** tree);

void nBlackIRed(rbNode* rmv, rbNode** tree);

void remover(rbNode** tree, int key);

void inserir(rbNode** tree, rbNode* pPai, rbNode** root, int key);

rbNode *buscar(rbNode* tree, int key);

void printRbTree(rbNode* root, int op);

int altura(rbNode* atual);
