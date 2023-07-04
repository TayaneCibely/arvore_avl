#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char* argv[]) {
  arvore a;
  int opcao;
  int controleFB;
  inicializar_avl(&a);

  while(1) {
    scanf("%d", &opcao);
    
    switch(opcao){
      int valor;      
      case 1:
        printf("%d\n", altura(a));   
        break;
      case 2:
        scanf("%d", &valor);
        a = inserir_avl(valor, a, &controleFB);
        break;
      case 3:
        printf("%d\n", maior_elemento(a));
        break;
      case 4:
        printf("%d\n", menor_elemento(a));
        break;
      case 5:
        preorder_avl(a);
        printf("\n");
        break;
      case 6:
        inorder_avl(a);
        printf("\n");
        break;
      case 7:
        posorder_avl(a);
        printf("\n");
        break;
      case 8:
        scanf("%d", &valor);
        a = remover_avl(valor, a, &controleFB);
      case 9:
        imprimir_avl(a);
        printf("\n");
        break;
      case 99:
          exit(0);
    }
  }
}