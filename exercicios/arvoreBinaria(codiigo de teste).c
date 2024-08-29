//André de Lima Michalsky

#include <stdio.h>
#include <stdlib.h>


typedef struct noArvore{
  int valor;
  struct noArvore* esquerda;
  struct noArvore* direita;
}no;


void buscarNo(no* n, int valor){
    if (n != NULL){
       if(valor == n->valor){
         printf("\nValor encontrado\n");
       } else if (valor < n -> valor){
          buscarNo(n->esquerda, valor);
       } else{
          buscarNo(n -> direita, valor);
       }
    } else{
      printf("Não encontrado");
    }
}


no* novoNo(int valor){
  no* novo = malloc(sizeof(no));
  novo -> valor = valor;
  novo -> esquerda = NULL;
  novo -> direita = NULL;
  return novo;
}

no* inserirNo(no* n, int novoValor){
  if (n == NULL){
    n = novoNo(novoValor);
  } else if( n-> valor == novoValor){
      printf("Ja inserido");
  } else if(novoValor < n->valor){
    if(n-> esquerda == NULL) {
      n -> esquerda = novoNo(novoValor);
    } else{
        inserirNo(n -> esquerda, novoValor);
    }
  } else{
      if(n -> direita == NULL){
          n->direita = novoNo(novoValor);
      } else{
         inserirNo(n -> direita, novoValor);
      }
  }
  return n;
}

void imprimeOsNiveis(no* n, int nivel){
  if(n != NULL){
    
    imprimeOsNiveis(n -> direita, nivel + 1);
    
    for(int i = 0; i < nivel; i++){
      printf("     ");
    }
    printf("%d\n", n->valor);
    imprimeOsNiveis(n -> esquerda, nivel + 1);
  }
}

int alturaDaArvore(no *n){
    if(n == NULL){
      return 0;
    } else{
      int direita = alturaDaArvore(n -> direita);
      int esquerda = alturaDaArvore(n -> esquerda);
      return ((direita < esquerda) ? esquerda  : direita) + 1;
    }
}



int main(void) {
  no* n = NULL;

  n = inserirNo(n, 12);
  n = inserirNo(n, 8);
  n = inserirNo(n, 15);
  n = inserirNo(n, 7);
  n = inserirNo(n, 4);
  n = inserirNo(n, 6);
  n = inserirNo(n, 13);
  n = inserirNo(n, 14);
  n = inserirNo(n, 11);
  n = inserirNo(n, 10);
  printf("A altura é %d\n", alturaDaArvore(n));
  imprimeOsNiveis(n, 4);


  no* na =  malloc(sizeof(no));
  no* na1 =  malloc(sizeof(no));
  no* na2 =  malloc(sizeof(no));
  no* na3 =  malloc(sizeof(no));
  no* na4 =  malloc(sizeof(no));
  no* na5 =  malloc(sizeof(no));


  //Criando outra árvore mas inserindo nos manualmente
  na-> valor = 10;
  na -> esquerda = na1;
  na -> direita = na2;
  
  na1 -> valor = 20;
  na1 -> esquerda = na5;
  na1 -> direita = na3;

  na2 -> valor = 5;
  na2 -> esquerda = na4;
  na2 -> direita = na5;

  na3 -> valor = 25;
  na3 -> esquerda = NULL;
  na3 -> direita = NULL;

  na4 -> valor = 3;
  na4 -> esquerda = NULL;
  na4 -> direita = NULL;

  na5 -> valor = 7;
  na5 -> esquerda = NULL;
  na5 -> direita = NULL;

  imprimeOsNiveis(na, 4);
  
  
  return 0;
}
