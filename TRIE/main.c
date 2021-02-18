#include "trie.h"

// DICA: Estude o arquivo trie.h antes de iniciar a sua implementacao!

no *criarNo(void) {
    // IMPLEMENTAR !!!
    // Dica: Aloca um no, atribua o tipo como 'I' e todos os filhos como NULL.

    int i;
    no *novo = (no *)malloc(sizeof(no));

    if (novo != NULL) {
        novo->tipo = 'I';

        for (i=0; i<TAMANHO_ALFABETO; i++)
            novo->filho[i] = NULL;
    }
    return novo;
}

void apagarArvore(no *raiz) {
    // IMPLEMENTAR !!!
    // Dica 1: Desaloque todos os nos filhos e depois desaloca o no atual.
    // Dica 2: Usar recursao facilita!
    int i;

    for (i = 0; i < TAMANHO_ALFABETO; i++) {
        if (raiz->filho[i] != NULL)
            apagarArvore(raiz->filho[i]);
    }
    free(raiz);
}

void adicionarPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Dica 1: Use um laco iterativo de 0 ate strlen(palavra)
    // Dica 2: Criar o no com a funcao criarNo (caso nao existir)
    // Dica 3: Utilize a macro CHAR_TO_INDEX (ver trie.h) para converter o caractere para o indice filho
    // Dica 4: Nao esqueca de mudar o tipo para 'P' no ultimo noh que representa o ultimo caractere
    int nivel, indice;
    no *tmp = raiz;

    for (nivel=0; nivel<strlen(palavra); nivel++) {
        indice = CHAR_TO_INDEX(palavra[nivel]);

        if (tmp->filho[indice] == NULL)
            tmp->filho[indice] = criarNo();
        tmp = tmp->filho[indice];
    }
    tmp->tipo = 'P';
}

int buscaPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Dica 1: Funcao similar ao adicionarPalavra
    // Dica 2: Se o ultimo noh que representa o ultimo caractere for do tipo 'I', a palavra nao existe
    // IMPORTANTE:
    //   retorne 0 se a palavra nao exite
    //   retorne 1 se a palavra existir
    int i, indice;
    no *tmp = raiz;

    for (i=0; i<strlen(palavra); i++) {
        indice = CHAR_TO_INDEX(palavra[i]);

        if (tmp->filho[indice] != NULL)
            tmp = tmp->filho[indice];
        else
            break;
    }

    if (palavra[i] == '\0' && tmp->tipo == 'P')
        return 1;
    else
        return 0;
}

int numeroDeNos(no *r) {
    // IMPLEMENTAR !!!
    // Dica: A funcao pode ser muito simples se utilizar recursao

    if (r == NULL)
        return 0;

    int i, count = 1;

    for (i=0; i<TAMANHO_ALFABETO; i++) {
        count += numeroDeNos(r->filho[i]);
    }

    return count;
}

int numeroDePalavras(no *r) {
    // IMPLEMENTAR !!!
    // Dica: Similar a funcao numeroDeNos, mas contabilize apenas os tipos 'P', que representa as palavras
    int i, count = 0;

    if (r->tipo == 'P') {
        count = 1;
    }

    for (i=0; i<TAMANHO_ALFABETO; i++) {
        if(r->filho[i])
            count += numeroDePalavras(r->filho[i]);
    }

    return count;
}

int alturaReal(no *r){
    int i, alturaMaxima = 0;

    for(i=0; i<TAMANHO_ALFABETO; i++){
        if (r->filho[i]) {
            int alturaAtual = alturaReal(r->filho[i]);

            if (alturaAtual > alturaMaxima)
                alturaMaxima = alturaAtual;
        }
    }
    return alturaMaxima + 1;
}

int altura(no *r) {
    return alturaReal(r) - 1;
}

int noSemFilho(no *raiz){
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (raiz->filho[i])
            return 0;
    }
    return 1;
}


no *removerNo(char *palavra, no *raiz, int i, int isRemover) {
    if (raiz) {
        int semFilho = noSemFilho(raiz);

        if (i == strlen(palavra)) {
            raiz->tipo = 'I';

            if(semFilho) {
                free(raiz);
                raiz = NULL;
            }
            return raiz;
        }

        int indice = CHAR_TO_INDEX(palavra[i]);

        raiz->filho[indice] = removerNo(palavra, raiz->filho[indice], i + 1, isRemover);

        semFilho = noSemFilho(raiz);
        if (semFilho && raiz->tipo == 'I') {
            free(raiz);
            raiz = NULL;
        }

        return raiz;

    }
}

void removerPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Nota: Esta funcao eh a mais elaborada. Recomendo criar funcoes auxiliares e utilizar recursao

    if (buscaPalavra(palavra, raiz))
        raiz = removerNo(palavra, raiz, 0, 1);
}

void imprimeArvore(no *raiz)
{
    int i;

    printf("(%c:", raiz->tipo);
    for (i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (raiz->filho[i] != NULL)
        {
            printf("%c", (int)'a' + (int)i);
            imprimeArvore(raiz->filho[i]);
        }
    }

    printf(")");
}