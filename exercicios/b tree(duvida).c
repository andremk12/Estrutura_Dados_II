// André de Lima Michalsky

#include <stdio.h>
#include <stdlib.h>

// Estrutura para os nós da árvore B
typedef struct No {
    int* chaves;                // Array para armazenar as chaves do nó
    int max_chaves;             // Número máximo de chaves que o nó pode armazenar
    struct No** filhos;         // Array de ponteiros para os nós filhos
    int qtd_chaves;             // Quantidade atual de chaves no nó
    int folha;                  // Indicador de folha (1 = sim, 0 = não)
} No;

// Função para criar um novo nó, definindo o máximo de chaves e se é folha
No* criarNo(int max_chaves, int folha) {
    No* no = (No*)malloc(sizeof(No));
    no->max_chaves = max_chaves;
    no->folha = folha;

    // Aloca memória para o array de chaves e para o array de filhos
    no->chaves = (int*)malloc((max_chaves - 1) * sizeof(int));
    no->filhos = (No**)malloc(max_chaves * sizeof(No*));
    no->qtd_chaves = 0;
    return no;
}

// Função para dividir um nó cheio em dois, reorganizando o nó pai
void dividirFilho(No* pai, int i, int max_chaves) {
    // Implementação futura
    // Esta função dividirá o nó cheio e ajustará o nó pai conforme necessário
}

// Função para inserir uma nova chave em um nó que não está cheio
void inserirNaoCheio(No* no, int chave, int max_chaves) {
    // Implementação futura
    // A função deve encontrar o local correto e inserir a chave no nó especificado
}

// Função para inserir uma nova chave na árvore B
void inserir(No** raiz, int chave, int max_chaves) {
    No* r = *raiz;

    // Caso a raiz esteja cheia, uma divisão é necessária
    if (r->qtd_chaves == max_chaves - 1) {
        // Cria uma nova raiz e define a antiga raiz como filha
        No* novaRaiz = criarNo(max_chaves, 0);
        novaRaiz->filhos[0] = r;

        // Divide o primeiro filho da nova raiz
        dividirFilho(novaRaiz, 0, max_chaves);

        // Decide em qual filho a nova chave será inserida
        int i = 0;
        if (novaRaiz->chaves[0] < chave)
            i++;
        
        // Insere a nova chave no filho apropriado
        inserirNaoCheio(novaRaiz->filhos[i], chave, max_chaves);
        
        // Atualiza a raiz para apontar para a nova raiz criada
        *raiz = novaRaiz;
    } else {
        // Caso a raiz não esteja cheia, a chave é inserida diretamente
        inserirNaoCheio(r, chave, max_chaves);
    }
}

int main(void) {
    int max_chaves = 3; // Quantidade máxima de chaves por nó (exemplo)
    No* raiz = criarNo(max_chaves, 1); // Inicializa a árvore com um nó raiz como folha
    inserir(&raiz, 10, max_chaves);    // Exemplo de inserção de chave
    inserir(&raiz, 20, max_chaves);
    inserir(&raiz, 5, max_chaves);
    
    return 0;
}
