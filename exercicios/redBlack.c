//André

#include <stdio.h>
#include <stdlib.h>

#define VER 0   // Definindo cor Vermelha
#define PRET 1  // Definindo cor Preta

// Estrutura do nó da árvore rubro-negra
struct No{
  int valor;        // Valor do nó
  int cor;          // Cor do nó (Vermelho ou Preto)
  struct No *esq, *dir, *pai;  // Ponteiros para os filhos e o pai do nó
};

typedef struct No No;

// Função para criar um novo nó na árvore
No *criarNovoNo(int valor){
  No *novo = (No *)malloc(sizeof(No));  // Aloca memória para o novo nó
  novo->valor = valor;    // Atribui o valor ao nó
  novo->cor = VER;        // Define a cor do nó como Vermelho inicialmente
  novo->esq = novo->dir = novo->pai = NULL;  // Inicializa ponteiros como NULL
  return novo;
}

// Função para realizar a rotação à esquerda
void rotaEsquerda(No **raiz, No *no){
  No *x = no->dir;           // Pega o filho direito do nó
  no->dir = x->esq;          // O filho esquerdo de x substitui a posição de x
  if (x->esq != NULL){
    x->esq->pai = no;
  }
  x->pai = no->pai;          // Ajusta o pai de x para ser o pai de no
  if (no->pai == NULL){
    *raiz = x;               // Se no for a raiz, x se torna a nova raiz
  } else if (no == no->pai->esq){
    no->pai->esq = x;        // Se no era o filho esquerdo, ajusta o ponteiro
  } else {
    no->pai->dir = x;
  }
  x->esq = no;               // Faz o no ser o filho esquerdo de x
  no->pai = x;
}

// Função para realizar a rotação à direita (simétrica à esquerda)
void rotaDireita(No **raiz, No *no){
  No *x = no->esq;           // Pega o filho esquerdo do nó
  no->esq = x->dir;
  if (x->dir != NULL){
    x->dir->pai = no;
  }
  x->pai = no->pai;
  if (no->pai == NULL){
    *raiz = x;
  } else if (no == no->pai->dir){
    no->pai->dir = x;
  } else {
    no->pai->esq = x;
  }
  x->dir = no;
  no->pai = x;
}

// Função para corrigir violações das regras da árvore rubro-negra após inserção
void violacao(No **raiz, No *no){
  while (no != *raiz && no->pai->cor == VER){  // Enquanto houver violações
    if (no->pai == no->pai->pai->esq) {        // Se o pai de no for filho esquerdo
      No *x = no->pai->pai->dir;               // Tio de no
      if (x != NULL && x->cor == VER){         // Caso 1: tio vermelho
        no->pai->cor = PRET;                   // Pai e tio ficam pretos
        x->cor = PRET;
        no->pai->pai->cor = VER;               // Avô fica vermelho
        no = no->pai->pai;                     // Sobe a árvore
      } else {
        if (no == no->pai->dir){               // Caso 2: no é filho direito
          no = no->pai;
          rotaEsquerda(raiz, no);              // Rotação à esquerda
        }
        no->pai->cor = PRET;                   // Caso 3: ajusta cores
        no->pai->pai->cor = VER;
        rotaDireita(raiz, no->pai->pai);       // Rotação à direita
      }
    } else {                                   // Mesma lógica para o lado direito
      No *x = no->pai->pai->esq;
      if (x != NULL && x->cor == VER){
        no->pai->cor = PRET;
        x->cor = PRET;
        no->pai->pai->cor = VER;
        no = no->pai->pai;
      } else {
        if (no == no->pai->esq){
          no = no->pai;
          rotaDireita(raiz, no);
        }
        no->pai->cor = PRET;
        no->pai->pai->cor = VER;
        rotaEsquerda(raiz, no->pai->pai);
      }
    }
  }
  (*raiz)->cor = PRET;                         // A raiz sempre deve ser preta
}

// Função para inserir um novo valor na árvore rubro-negra
void inserir(No **raiz, int valor){
  No *novo = criarNovoNo(valor);               // Cria um novo nó
  No *x = *raiz;
  No *y = NULL;

  while (x != NULL){                           // Encontra a posição correta na árvore
    y = x;
    if (novo->valor < x->valor){
      x = x->esq;
    } else {
      x = x->dir;
    }
  }
  novo->pai = y;                               // Define o pai do novo nó
  if (y == NULL){
    *raiz = novo;                              // Se a árvore estava vazia, novo nó vira raiz
  } else if (novo->valor < y->valor){
    y->esq = novo;                             // Define como filho esquerdo ou direito
  } else {
    y->dir = novo;
  }
  violacao(raiz, novo);                        // Corrige violações após a inserção
}

// Função para imprimir a árvore com identação
void imprimirArvore(No *raiz, int nivel){
  if (raiz == NULL)
    return;

  imprimirArvore(raiz->dir, nivel + 1);        // Imprime a subárvore direita

  for (int i = 0; i < nivel; i++)              // Identação
    printf("   ");

  printf("%d(%s)\n", raiz->valor, raiz->cor == VER ? "V" : "P");  // Imprime o valor e a cor

  imprimirArvore(raiz->esq, nivel + 1);        // Imprime a subárvore esquerda
}

// Função para buscar um valor na árvore
No* buscar(No *raiz, int valor) {
  if (raiz == NULL || raiz->valor == valor)    // Se o nó for NULL ou o valor foi encontrado
    return raiz;

  if (valor < raiz->valor)                     // Buscar na subárvore esquerda
    return buscar(raiz->esq, valor);
  else                                         // Buscar na subárvore direita
    return buscar(raiz->dir, valor);
}

int main() {
  No *raiz = NULL;

  // Inserindo valores na árvore
  inserir(&raiz, 10);
  inserir(&raiz, 20);
  inserir(&raiz, 30);
  inserir(&raiz, 15);
  inserir(&raiz, 25);
  inserir(&raiz, 5);

  // Imprime a árvore
  printf("Arvore Rubro-Negra:\n");
  imprimirArvore(raiz, 0);

  int valorBuscado = 25;
  No *resultado = buscar(raiz, valorBuscado);  // Busca um valor na árvore
  if (resultado != NULL) {
    printf("Valor %d encontrado, cor: %s\n", resultado->valor, resultado->cor == VER ? "Vermelho" : "Preto");
  } else {
    printf("Valor %d não encontrado.\n", valorBuscado);
  }

  int valorBuscado2 = 21;
  No *resultado2 = buscar(raiz, valorBuscado2);  // Busca um valor na árvore
  if (resultado2 != NULL) {
    printf("Valor %d encontrado, cor: %s\n", resultado2->valor, resultado2->cor == VER ? "Vermelho" : "Preto");
  } else {
    printf("Valor %d não encontrado.\n", valorBuscado2);
  }
  
  return 0;
}
