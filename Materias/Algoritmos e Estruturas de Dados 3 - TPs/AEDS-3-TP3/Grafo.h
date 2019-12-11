//
// Created by Giovanni Martinelli on 10/04/18.
//

#ifndef TP0_GRAFO_H
#define TP0_GRAFO_H


#include <stdlib.h>
#include <stdio.h>

//Struct do NO
typedef struct no {
    int ID;
    struct no * prox;
}no;

//Struct Lista de NOs
typedef struct lista{
    struct no* cabeca;
}lista;

//Struct Grafo
typedef struct grafo{
    int vertices;
    struct lista* array;
}grafo;

//-----------Funcoes-------------
//Cria um no com Valor: X
no* criaNo(int x);
//Cria um grafo com V vertices
grafo* criaGrafo(int v);
//Add Aresta ao Grafo
void addAresta(grafo* grafoPt, int ini, int fim);
//Libera um grafo
void freeGrafo(grafo* grafoPt);

#endif //TP0_GRAFO_H
