//André de Lima Michalsky

#include <stdio.h>
#include <stdlib.h>


typedef struct noArvore{
  int valor;
  struct noArvore* esq;
  struct noArvore* dir;
}no;


void buscarNo(no* n, int valor){ //Busca de forma recursiva pela esquerda e direita o No desejado
    if (n != NULL){
       if(valor == n->valor){
         printf("\n%d esta presenete na árvore\n", valor);
       } else if (valor < n -> valor){
          buscarNo(n->esq, valor);
       } else{
          buscarNo(n -> dir, valor);
       }
    } else{
       printf("\n%d não faz parte da árvore\n", valor);
    }
}


no* novoNo(int valor){ //Criação da estrutura base da árvore, com uma unica raiz
  no* novo = malloc(sizeof(no)); 
  novo -> valor = valor;
  novo -> esq = NULL;
  novo -> dir= NULL;
  return novo;
}

no* inserirNo(no* n, int novoValor){ // Função para que novos valores sejam inseridos, seguindo o conceito da arvore binaria
  if (n == NULL){
    n = novoNo(novoValor);
  } else if( n-> valor == novoValor){
      printf("Ja inserido");
  } else if(novoValor < n->valor){
    if(n-> esq == NULL) {
      n -> esq = novoNo(novoValor);
    } else{
        inserirNo(n -> esq, novoValor);
    }
  } else{
      if(n -> dir== NULL){
          n->dir= novoNo(novoValor);
      } else{
         inserirNo(n -> dir, novoValor);
      }
  }
  return n;
}

void exibirArvore(no* n, int nivel){
  //Os níveis são os espaços entre as linhas para deixar a arvore mais organizada
  
  if(n != NULL){
    
    exibirArvore(n -> dir, nivel + 1);
    
    for(int i = 0; i < nivel; i++){
      printf("     ");
    }
    printf("%d\n", n->valor);
    exibirArvore(n -> esq, nivel + 1);
  }
}

int calcularAltura(no *n){
    if(n == NULL){
      return 0;
    } else{
      int dir= calcularAltura(n -> dir);
      int esq = calcularAltura(n -> esq);
      return ((dir< esq) ? esq  : dir) + 1;
    }
}

no* removerNo(no* raiz, int valor) { // Dúvida!!!
    if (raiz == NULL) {
        return raiz; 
    }

    if (valor < raiz->valor) {
        raiz->esq = removerNo(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = removerNo(raiz->dir, valor);
    } else {
       
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
      
        else if (raiz->esq == NULL) {
            no* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            no* temp = raiz->esq;
            free(raiz);
            return temp;
        }
    
        else {
            no* temp = raiz->dir;
           
            while (temp && temp->esq != NULL) {
                temp = temp->esq;
            }
           
            raiz->valor = temp->valor;
            // Remove o nó que foi substituído
            raiz->dir = removerNo(raiz->dir, temp->valor);
        }
    }
    return raiz;
}



int main(void) {
  no* raizes = NULL;

  raizes = inserirNo(raizes, 12);
  raizes = inserirNo(raizes, 8);
  raizes= inserirNo(raizes, 15);
  raizes= inserirNo(raizes, 7);
  raizes= inserirNo(raizes, 4);
  raizes = inserirNo(raizes, 6);
  raizes = inserirNo(raizes, 13);
  raizes = inserirNo(raizes, 14);
  raizes= inserirNo(raizes, 11);
  raizes= inserirNo(raizes, 10);
  
  
  printf("Arvore 1: \n");
  exibirArvore(raizes, 4);
  buscarNo(raizes, 11); //Valor encontrado
  buscarNo(raizes, 100); // valor não existente

  
  printf("A altura da árvore 1 é %d\n", calcularAltura(raizes));
  printf("\n");
  printf("\n");
  printf("\n");

  no* n =  malloc(sizeof(no));
  no* n1 =  malloc(sizeof(no));
  no* n2 =  malloc(sizeof(no));
  no* n3 =  malloc(sizeof(no));
  no* n4 =  malloc(sizeof(no));
  no* n5 =  malloc(sizeof(no));

 

  //Criando outra árvore mas inserindo nos manualmente
  n-> valor = 10;       // Seguindo a regra: maior -> direita menor -> esq
  n -> esq = n1;
  n -> dir= n2;
  
  n1 -> valor = 20;
  n1 -> esq = n5;
  n1 -> dir= n3;

  n2 -> valor = 5;
  n2 -> esq = n4;
  n2 -> dir= n5;

  n3 -> valor = 25;
  n3 -> esq = NULL;
  n3 -> dir= NULL;

  n4 -> valor = 3;
  n4 -> esq = NULL;
  n4 -> dir= NULL;

  n5 -> valor = 7;
  n5 -> esq = NULL;
  n5 -> dir= NULL;

  printf("Arvore 2: \n");
  exibirArvore(n, 4);


  
  printf("A altura da árvore 2 é %d\n", calcularAltura(n));
  removerNo(n, 20);

  
  exibirArvore(n, 4);
  
  
  return 0;
}
