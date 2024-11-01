//André de Lima Michalsky

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para os nós da árvore Treap
typedef struct No {
    int dado;
    int prioridade;
    struct No* direito;
    struct No* esquerdo;
} No;

// Funções de criação e liberação de memória
No* criar_no(int dado);
void liberar_arvore(No* raiz);

// Funções de rotação
No* rotacionar_direita(No* no);
No* rotacionar_esquerda(No* no);

// Funções de manipulação da árvore (inserção, exclusão, busca)
No* inserir_no(No* no, int dado);
No* deletar_no(No* no, int dado);
int buscar_no(No* no, int dado);

// Função para imprimir a árvore
void imprimir_arvore(No* raiz, int nivel);

// Função principal
int main() {
    srand(time(NULL));
    No* raiz = NULL;
    int dado, entrada = -1;

    while (entrada != 0) {
        printf("------------------------------ Árvore Treap ------------------------------\n");
        printf("Selecione sua opção:\n");
        printf("1- Inserir Valor\n2- Buscar Valor\n3- Deletar Valor\n4- Exibir Árvore\n5- Inserir Valores Aleatórios\n0- Sair\n");
        scanf("%d", &entrada);

        switch (entrada) {
            case 1:
                printf("Valor a ser inserido: ");
                scanf("%d", &dado);
                raiz = inserir_no(raiz, dado);
                break;
            case 2:
                printf("Valor a ser buscado: ");
                scanf("%d", &dado);
                if (buscar_no(raiz, dado)) {
                    printf("Valor %d encontrado na árvore.\n", dado);
                } else {
                    printf("Valor %d não encontrado.\n", dado);
                }
                break;
            case 3:
                printf("Valor a ser deletado: ");
                scanf("%d", &dado);
                raiz = deletar_no(raiz, dado);
                break;
            case 4:
                printf("--------------------------------------------------------------------------------------------------\n");
                imprimir_arvore(raiz, 0);
                printf("--------------------------------------------------------------------------------------------------\n");
                break;
            case 5:
                printf("Inserindo valores aleatórios...\n");
                for (int i = 0; i < 10; i++) {
                    dado = rand() % 101;
                    raiz = inserir_no(raiz, dado);
                }
                printf("Concluído!\n");
                break;
            default:
                if (entrada != 0) {
                    printf("Opção inválida!\n");
                }
                break;
        }
    }

    liberar_arvore(raiz);
    printf("Encerrando aplicação!\n");
    return 0;
}

// Implementação das funções

// Função para criar um novo nó com prioridade aleatória
No* criar_no(int dado) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(-1);
    }
    novo_no->dado = dado;
    novo_no->prioridade = rand() % 100;
    novo_no->direito = NULL;
    novo_no->esquerdo = NULL;
    return novo_no;
}

// Função para liberar a memória de toda a árvore
void liberar_arvore(No* raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esquerdo);
    liberar_arvore(raiz->direito);
    free(raiz);
}

// Rotações para manter a propriedade do heap
No* rotacionar_direita(No* no) {
    No* filho_esquerdo = no->esquerdo;
    no->esquerdo = filho_esquerdo->direito;
    filho_esquerdo->direito = no;
    return filho_esquerdo;
}

No* rotacionar_esquerda(No* no) {
    No* filho_direito = no->direito;
    no->direito = filho_direito->esquerdo;
    filho_direito->esquerdo = no;
    return filho_direito;
}

// Inserção de um novo nó na árvore Treap
No* inserir_no(No* no, int dado) {
    if (no == NULL) {
        return criar_no(dado);
    }

    if (dado == no->dado) {
        printf("Valor já inserido, não é possível duplicar.\n");
        return no;
    }

    if (dado < no->dado) {
        no->esquerdo = inserir_no(no->esquerdo, dado);
        if (no->esquerdo && no->esquerdo->prioridade > no->prioridade) {
            no = rotacionar_direita(no);
        }
    } else {
        no->direito = inserir_no(no->direito, dado);
        if (no->direito && no->direito->prioridade > no->prioridade) {
            no = rotacionar_esquerda(no);
        }
    }
    return no;
}

// Exclusão de um nó da árvore Treap
No* deletar_no(No* no, int dado) {
    if (no == NULL) {
        printf("Nó não encontrado!\n");
        return no;
    }

    if (dado < no->dado) {
        no->esquerdo = deletar_no(no->esquerdo, dado);
    } else if (dado > no->dado) {
        no->direito = deletar_no(no->direito, dado);
    } else {
        if (no->esquerdo && no->direito) {
            if (no->esquerdo->prioridade > no->direito->prioridade) {
                no = rotacionar_direita(no);
                no->direito = deletar_no(no->direito, dado);
            } else {
                no = rotacionar_esquerda(no);
                no->esquerdo = deletar_no(no->esquerdo, dado);
            }
        } else {
            No* temp = (no->esquerdo) ? no->esquerdo : no->direito;
            free(no);
            return temp;
        }
    }
    return no;
}

// Função para buscar um valor na árvore
int buscar_no(No* no, int dado) {
    if (no == NULL) return 0;
    if (no->dado == dado) return 1;
    if (dado < no->dado) return buscar_no(no->esquerdo, dado);
    return buscar_no(no->direito, dado);
}

// Função para imprimir a árvore em formato hierárquico
void imprimir_arvore(No* raiz, int nivel) {
    if (raiz == NULL) return;
    imprimir_arvore(raiz->direito, nivel + 1);
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("%d (p=%d)\n", raiz->dado, raiz->prioridade);
    imprimir_arvore(raiz->esquerdo, nivel + 1);
}
