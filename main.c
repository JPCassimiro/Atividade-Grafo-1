//João Pedro Silva Cassimiro - 2142600
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia {
  int vertice;
  TIPOPESO peso;
  struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
  ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
  int vertices;
  int arestas;
  VERTICE *adj;
} GRAFO;

GRAFO *criaGrafo(int v) {
  int i;
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
  for (i = 0; i < v; i++) {
    g->adj[i].cab = NULL;
  }
  return (g);
}

ADJACENCIA *criaAdj(int v, int peso) {
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;
  return (temp);
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
  if (!gr)
    return (false);
  if ((vf < 0) || (vf >= gr->vertices))
    return (false);
  if ((vf < 0) || (vf >= gr->vertices))
    return (false);
  ADJACENCIA *novo = criaAdj(vf, p);
  novo->prox = gr->adj[vi].cab;
  gr->adj[vi].cab = novo;
  gr->arestas++;
  return (true);
}

void imprimeLista(GRAFO *gr) {
  printf("Vértices: %d. Arestas: %d. \n", gr->vertices, gr->arestas);
  int i;
  for (i = 0; i < gr->vertices; i++) {
    printf("v%d: ", i);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad) {
      printf("v%d(%d)", ad->vertice, ad->peso);
      ad = ad->prox;
    }
    printf("\n");
  }
}

void imprimeMatriz(GRAFO *gr, int l, int c, int m[l][c]) {
  for (int i = 0; i < gr->vertices; i++) {
    for (int i2 = 0; i2 < gr->vertices; i2++) {
      m[i][i2] = 0; // inicia matriz em 0
    }
  }
  ADJACENCIA *ad;
  int i2 = gr->vertices - 1; // primeiros vertices são listados por ultimo
  for (int i = 0; i < gr->vertices; i++) {
    ad = gr->adj[i].cab; // linha
    while (ad) {
      while (i2 != ad->vertice) {
        i2--; // encontra coluna da matriz que coresponde ao vertice de
              // interesse
      }
      m[i][i2] = ad->peso; // atribui o peso a matriz
      ad = ad->prox;
      i2--;
    }
    i2 = gr->vertices - 1;
  }
  for (int i = 0; i < gr->vertices; i++) { // imprime
    for (int i2 = 0; i2 < gr->vertices; i2++) {
      printf("%d", m[i][i2]);
    }
    printf("\n");
  }
}

void somaMaiorCaminho(int origem,int fim,int v,int mGr2[v][v]){
  if(origem == fim){
    printf("valor total do caminho: 0");
    return;
  }
  int distancia = 0;
  int visitado[v];
  int dist[v];
  for(int i = 0; i < v; i++){
    dist[i] = 0;
    visitado[i] = 0;
  }
  int maior = 0;
  int prox = origem-1;
  while(prox!=fim-1){
    for(int i = 0;i<v;i++){
       if((maior < mGr2[prox][i])&&(i!=prox)){
         maior = mGr2[prox][i];
         dist[prox] = maior;
         prox = i;
         visitado[prox] = 1;
       }
      maior = 0;
     }
  }
  int resultado = 0;
  for(int i = 0;i < v;i++){
    resultado = resultado + dist[i];
  }
  printf("valor total do caminho: %d",resultado);
}

int main() {
  GRAFO *gr1 = criaGrafo(5);
  criaAresta(gr1, 0, 0, 4);
  criaAresta(gr1, 0, 2, 5);
  criaAresta(gr1, 2, 0, 5);
  criaAresta(gr1, 2, 1, 6);
  criaAresta(gr1, 1, 2, 6);
  criaAresta(gr1, 2, 3, 7);
  criaAresta(gr1, 3, 2, 7);
  criaAresta(gr1, 1, 4, 8);
  criaAresta(gr1, 4, 1, 8);
  criaAresta(gr1, 3, 4, 9);
  criaAresta(gr1, 4, 3, 9);
  printf("\nNão orientado(aresta pode acessada em qualquer direção)\n");
  imprimeLista(gr1);
  printf("\n\n");
  int mgr1[gr1->vertices][gr1->vertices];
  imprimeMatriz(gr1, 5, 5, mgr1);
  printf("\n\n");
  GRAFO *gr2 = criaGrafo(5);
  criaAresta(gr2, 0, 0, 4);
  criaAresta(gr2, 0, 2, 5);
  criaAresta(gr2, 2, 1, 6);
  criaAresta(gr2, 2, 3, 7);
  criaAresta(gr2, 1, 4, 8);
  criaAresta(gr2, 3, 4, 9);
  criaAresta(gr2, 3, 1, 3);
  printf("\nOrientado\n");
  imprimeLista(gr2);
  printf("\n\n");
  int mgr2[gr1->vertices][gr2->vertices];
  imprimeMatriz(gr2, 5, 5, mgr2);
  printf("\n\n");
  somaMaiorCaminho(1,5,5,mgr2);
  return 0;
}