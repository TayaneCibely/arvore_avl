#ifndef AVL_H
#define AVL_H

typedef int tipo_dado;

typedef struct no_avl {
  tipo_dado dado;
  int fb;
  struct no_avl *esq, *dir;
} no_avl;

typedef no_avl *arvore;

void inicializar_avl(arvore *raiz);
arvore inserir_avl(int valor, arvore raiz, int *cresceu);
int maior(int a, int b);
int altura(arvore raiz);
int maior_elemento(arvore raiz);
int menor_elemento(arvore raiz);
void imprimir_avl(arvore raiz);
void preorder_avl(arvore raiz);
void inorder_avl(arvore raiz);
void posorder_avl(arvore raiz);
arvore remover_avl(int valor, arvore raiz, int *diminuiu);
void imprimir_elemento(arvore raiz);
arvore rotacionar_avl(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);

#endif