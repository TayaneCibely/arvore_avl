#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_avl(arvore *raiz) { *raiz = NULL; }

arvore inserir_avl(int valor, arvore raiz, int *cresceu) {
  if (raiz == NULL) {
    arvore novo_no = (arvore)malloc(sizeof(struct no_avl));
    novo_no->dado = valor;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    novo_no->fb = 0;
    *cresceu = 1;
    return novo_no;
  }

  if (valor > raiz->dado) {
    raiz->dir = inserir_avl(valor, raiz->dir, cresceu);

    if (*cresceu) {
      switch (raiz->fb) {
      case 0:
        raiz->fb = 1;
        *cresceu = 1;
        break;
      case -1:
        raiz->fb = 0;
        *cresceu = 0;
        break;
      case 1:
        raiz = rotacionar_avl(raiz);
        *cresceu = 0;
        break;
      }
    }
  } else {
     raiz->esq = inserir_avl(valor, raiz->esq, cresceu);
    if (*cresceu) {
      switch (raiz->fb) {
      case 0:
        raiz->fb = -1;
        *cresceu = 1;
        break;
      case -1:
        raiz->fb = 0;
        *cresceu = 0;
        break;
      case 1:
        raiz = rotacionar_avl(raiz);
        *cresceu = 0;
        break;
      }
    }
  }
  return raiz;
}

arvore rotacionar_avl(arvore raiz) {
  if (raiz->fb > 0) {
    switch (raiz->dir->fb) {
    case 0:
      return rotacao_simples_esquerda(raiz);
      break;
    case 1:
      return rotacao_simples_esquerda(raiz);
      break;
    case -1:
      return rotacao_dupla_esquerda(raiz);
      break;
    }
  } else {
    switch (raiz->esq->fb) {
    case 0:
      return rotacao_simples_esquerda(raiz);
      break;
    case 1:
      return rotacao_simples_direita(raiz);
        break;
    case -1:
      return rotacao_dupla_direita(raiz);
      break;
    }
  }
  return raiz;
}

arvore remover_avl(int valor, arvore raiz, int *diminuiu) {
  if (raiz == NULL) {
    return NULL;
  }
  if (raiz->dado == valor) {
    if (raiz->esq != NULL && raiz->dir != NULL) {
      raiz->dado = maior_elemento(raiz->esq);
      raiz->esq = remover_avl(raiz->dado, raiz->esq, diminuiu);
    } else if (raiz->esq == NULL) {
      *diminuiu = 1;
      return raiz->dir;
    } else if (raiz->dir == NULL) {
      return raiz->esq;
    }
    return raiz;
  }
  if (valor > raiz->dado) {
    raiz->dir = remover_avl(valor, raiz->dir, diminuiu);
    if (*diminuiu) {
      switch (raiz->fb) {
      case -1:
        raiz->fb = 0;
        *diminuiu = 0;
        break;
      case 0:
        raiz->fb = 1;
        break;
      case 1:
        raiz = rotacionar_avl(raiz);
        *diminuiu = 0;
        break;
      }
    }
  } else {
    raiz->esq = remover_avl(valor, raiz->esq, diminuiu);
    if (*diminuiu) {
      switch (raiz->fb) {
      case -1:
        raiz = rotacionar_avl(raiz);
        *diminuiu = 0;
        break;
      case 0:
        raiz->fb = -1;
        break;
      case 1:
        raiz->fb = 0;
        *diminuiu = 0;
        break;
      }
    }
  }
  return raiz;
}

arvore rotacao_simples_esquerda(arvore raiz) {
  arvore p, u, t1, t2, t3;
  // Inicial
  p = raiz;
  u = raiz->dir;
  t1 = p->esq;
  t2 = u->esq;
  t3= u->dir;

  // Final
  p->dir = t2;
  u->esq = p;

  if (u->fb == 1) {
    p->fb = 0;
    u->fb = 0;
  } else {
    p->fb = 1;
    u->fb = -1;
  }
  return u;
}

arvore rotacao_dupla_esquerda(arvore raiz) {
  arvore p, u, v, t1, t2, t3, t4;
  // Inicial
  p = raiz;
  u = p->dir;
  v = u->esq;
  t1 = p->esq;
  t2 = v->esq;
  t3 = v->dir;
  t4 = u->dir;
  // final
  v->esq = p;
  p->dir = t2;
  v->dir = u;
  u->esq = t3;

  switch (v->fb) {
  case 1:
    p->fb = 0;
    u->fb = 1;
    raiz = rotacao_simples_esquerda(raiz);
    break;
  case 0:
    p->fb = 0;
    u->fb = 0;
    break;
  case -1:
    p->fb = -1;
    u->fb = 0;
    raiz = rotacao_simples_direita(raiz);
    break;
  }
  v->fb = 0;

  return v;
}

arvore rotacao_simples_direita(arvore raiz) {
  arvore p, u, t1, t2, t3;
  // inicial
  p = raiz;
  u = raiz->esq;
  t1 = u->esq;
  t2 = u->dir;
  t3 = p->dir;
  // Final
  p->esq = t2;
  u->dir = p;

  if (u->fb == -1) {
    p->fb = 0;
    u->fb = 0;
  } else {
    p->fb = -1;
    u->fb = 1;
  }
  return u;
}

arvore rotacao_dupla_direita(arvore raiz) {
  arvore p, u, v, t1, t2, t3, t4;
  // Inicial
  p = raiz;
  u = raiz->esq;
  v = u->dir;
  t1 = u->esq;
  t2 = v->esq;
  t3 = v->dir;
  t4 = p->dir;
  // final
  v->esq = u;
  p->esq = t3;
  v->dir = p;
  u->dir = t2;

  // Atualizar fb
  switch (v->fb) {
  case -1:
    p->fb = -1;
    u->fb = 0;
    raiz = rotacao_simples_direita(raiz);
    break;
  case 0:
    u->fb = 0;
    p->fb = 0;
    break;
  case 1:
    p->fb = 1;
    u->fb = 0;
    raiz = rotacao_simples_esquerda(raiz);
  }
  v->fb = 0;
  return v;
}

int maior_elemento(arvore raiz) {
  if (raiz == NULL) {
    return -1;
  }
  if (raiz->dir == NULL) {
    return raiz->dado;
  } else {
    return maior_elemento(raiz->dir);
  }
}

int menor_elemento(arvore raiz) {
  if (raiz == NULL) {
    return -1;
  }
  if (raiz->esq == NULL) {
    return raiz->dado;
  } else {
    return menor_elemento(raiz->esq);
  }
}

void imprimir_avl(arvore raiz) {
  printf("(");
  if (raiz != NULL) {
    imprimir_elemento(raiz);
    imprimir_avl(raiz->esq);
    imprimir_avl(raiz->dir);
  }
  printf(")");
}
void imprimir_elemento(arvore raiz) { 
  printf("%d [%d]", raiz->dado, raiz->fb); 
}

int altura(arvore raiz){
  if(raiz == NULL){
    return 0;  
  }
  return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b){
  if(a>b)
    return a;
  else
    return b;
}

void preorder_avl(arvore raiz) {
  if (raiz != NULL) {
    imprimir_elemento(raiz);
    preorder_avl(raiz->esq);
    preorder_avl(raiz->dir);
  }
}

void inorder_avl(arvore raiz) {
  if (raiz != NULL) {
    inorder_avl(raiz->esq);
    imprimir_elemento(raiz);
    inorder_avl(raiz->dir);
  }
}

void posorder_avl(arvore raiz) {
  if (raiz != NULL) {
    posorder_avl(raiz->esq);
    posorder_avl(raiz->dir);
    imprimir_elemento(raiz);
  }
}