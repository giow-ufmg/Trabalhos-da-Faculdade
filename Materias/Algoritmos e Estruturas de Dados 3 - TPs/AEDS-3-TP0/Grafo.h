//
// Created by Giovanni Martinelli on 10/04/18.
//

#ifndef TP0_GRAFO_H
#define TP0_GRAFO_H

#include "Pessoa.h"

//Struct do NO
typedef struct no {
    pessoa* objPessoa;
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
no* criaNo(int x, int y);
//Cria um grafo com V vertices
grafo* criaGrafo(int v);
//Add Aresta ao Grafo
void addAresta(grafo* grafoPt, int ini, int fim, pessoa** Pessoa);
//Libera um grafo
void freeGrafo(grafo* grafoPt);
//Subfuncao que itera sobre a lista de adjacencias
void percorreGrafo(const grafo *grafoPt, pessoa **Pessoas, int *estado, int like);
//Funcao para contar likes
void contaLikes(grafo *grafoPt, pessoa **Pessoas, int *estado, int ini);


#endif //TP0_GRAFO_H
