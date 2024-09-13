//André de Lima Michalsky
#include <stdio.h>
#include <stdlib.h>

struct NoArvore {
    int valor;
    int altura;
    struct NoArvore *esq;
    struct NoArvore *dir;
};

struct NoArvore *criaNovoNo(int valor) {
    struct NoArvore *novoNo = (struct NoArvore *)malloc(sizeof(struct NoArvore));
    if (novoNo == NULL) {
        printf("Erro de memoria\n");
        return NULL;
    }

    novoNo->valor = valor;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 0;
    return novoNo;
}

int calcularAltura(struct NoArvore *no) {
    if (no == NULL) {
        return -1;
    }
    return no->altura;
}

int calcularFatorBalanceamento(struct NoArvore *no) {
    if (no == NULL) {
        return 0;
    }

    return calcularAltura(no->esq) - calcularAltura(no->dir);
}

struct NoArvore *rotacaoDireita(struct NoArvore *no) {
    struct NoArvore *novoNo = no->esq;
    struct NoArvore *subArvore = novoNo->dir;

    novoNo->dir = no;
    no->esq = subArvore;

    no->altura = 1 + (calcularAltura(no->esq) > calcularAltura(no->dir) ? calcularAltura(no->esq) : calcularAltura(no->dir));
    novoNo->altura = 1 + (calcularAltura(novoNo->esq) > calcularAltura(novoNo->dir) ? calcularAltura(novoNo->esq) : calcularAltura(novoNo->dir));

    return novoNo;
}

struct NoArvore *encontrarMinimo(struct NoArvore *no) {
    struct NoArvore *atual = no;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

struct NoArvore *rotacaoEsquerda(struct NoArvore *no) {
    struct NoArvore *novoNo = no->dir;
    struct NoArvore *subArvore = novoNo->esq;

    novoNo->esq = no;
    no->dir = subArvore;

    no->altura = 1 + (calcularAltura(no->esq) > calcularAltura(no->dir) ? calcularAltura(no->esq) : calcularAltura(no->dir));
    novoNo->altura = 1 + (calcularAltura(novoNo->esq) > calcularAltura(novoNo->dir) ? calcularAltura(novoNo->esq) : calcularAltura(novoNo->dir));

    return novoNo;
}

struct NoArvore *realizarBalanceamento(struct NoArvore *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + (calcularAltura(raiz->esq) > calcularAltura(raiz->dir) ? calcularAltura(raiz->esq) : calcularAltura(raiz->dir));

    int bal = calcularFatorBalanceamento(raiz);
    if (bal > 1 && valor < raiz->esq->valor) {
        return rotacaoDireita(raiz);
    }

    if (bal < -1 && valor > raiz->dir->valor) {
        return rotacaoEsquerda(raiz);
    }

    if (bal > 1 && valor > raiz->esq->valor) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (bal < -1 && valor < raiz->dir->valor) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

struct NoArvore *inserir(struct NoArvore *raiz, int valor) {
    if (raiz == NULL) {
        return criaNovoNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    } else {
        // Se o valor já existe, não realiza inserção nem balanceamento
        return raiz;
    }

    return realizarBalanceamento(raiz, valor);
}

struct NoArvore *remover(struct NoArvore *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Nó com apenas um filho ou sem filho
        if (raiz->esq == NULL || raiz->dir == NULL) {
            struct NoArvore *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp; // Cópia dos valores do filho
            }
            free(temp);
        } else {
            // Nó com dois filhos: Pegue o sucessor (menor valor na subárvore direita)
            struct NoArvore *temp = encontrarMinimo(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = remover(raiz->dir, temp->valor);
        }
    }

    // Se a árvore tiver apenas um nó
    if (raiz == NULL) {
        return raiz;
    }

    // Atualizar a altura do nó atual
    raiz->altura = 1 + (calcularAltura(raiz->esq) > calcularAltura(raiz->dir) ? calcularAltura(raiz->esq) : calcularAltura(raiz->dir));

    // Verificar o fator de balanceamento do nó
    int bal = calcularFatorBalanceamento(raiz);

    // Realizar as rotações necessárias
    if (bal > 1 && calcularFatorBalanceamento(raiz->esq) >= 0) {
        return rotacaoDireita(raiz);
    }

    if (bal > 1 && calcularFatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    if (bal < -1 && calcularFatorBalanceamento(raiz->dir) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    if (bal < -1 && calcularFatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void imprimeArvore(struct NoArvore *raiz, int espaco) {
    if (raiz == NULL) {
        return;
    }

    espaco += 5;  // Ajuste do espaçamento

    imprimeArvore(raiz->dir, espaco);

    printf("\n");
    for (int i = 5; i < espaco; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->valor);

    imprimeArvore(raiz->esq, espaco);
}


struct NoArvore* buscar(struct NoArvore* raiz, int valor) {
    if (raiz == NULL) {
        printf("Valor %d não encontrado.\n", valor);
        return NULL;
    }

    if (valor == raiz->valor) {
        printf("Valor %d encontrado.\n", valor);
        return raiz;
    }

    if (valor < raiz->valor) {
        return buscar(raiz->esq, valor);  // Buscar na subárvore esquerda
    } else {
        return buscar(raiz->dir, valor);  // Buscar na subárvore direita
    }
}


int main(void) {
    struct NoArvore *raiz = NULL;

    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 35);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 33);
    raiz = inserir(raiz, 3);


    buscar(raiz, 12);  // Valor presente
    buscar(raiz, 33);  // Valor presente
    buscar(raiz, 50);  // Valor ausente
    
    imprimeArvore(raiz, 0);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    raiz = remover(raiz, 35);
    imprimeArvore(raiz, 5);

    return 0;
}
