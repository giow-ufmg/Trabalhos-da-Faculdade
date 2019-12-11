//
// Created by Giovanni Martinelli on 10/04/18.
//
#include "Grafo.h"

//Cria um no com Valor: X
no* criaNo(int x)
{
    no* noPt = (no*) malloc(sizeof(no));
    if(noPt == NULL)
    {
        perror("Node Malloc fail");
        exit(EXIT_FAILURE);
    }
    noPt->ID = x;
    noPt->prox = NULL;
    return noPt;
}

//Cria um grafo com V vertices
grafo* criaGrafo(int v)
{
    //Aloca grafo
    grafo* grafoPt = (grafo*) malloc(sizeof(grafo));
    if(grafoPt == NULL)
    {
        perror("Grafo Malloc fail\n");
        exit(EXIT_FAILURE);
    }

    grafoPt->vertices = v;

    //Aloca array de vertices
    grafoPt->array = (lista*) malloc(v * sizeof(lista));
    if(grafoPt->array == NULL)
    {
        perror("Grafo->array Malloc fail\n");
        exit(EXIT_FAILURE);
    }

    //Null em todos os ponteiros para as listas
    for(int i = 0; i < v; i++)
    {
        grafoPt->array[i].cabeca = NULL;
    }

    return grafoPt;
}

//Add Aresta ao Grafo
void addAresta(grafo* grafoPt, int ini, int fim)
{
    //add no ini -> fim
    no* temp = criaNo(fim);
    //Add Node no inicio da lista
    temp->prox = grafoPt->array[ini-1].cabeca;// [temp->prox] ->[cabeca]
    grafoPt->array[ini-1].cabeca = temp;//[cabeca]->[temp]->[old cabeca]
}

//Libera um grafo
void freeGrafo(grafo* grafoPt)
{
    for(int i = 0; i < grafoPt->vertices; i++)
    {
        //No para percorrer
        no* traversal =  grafoPt->array[i].cabeca;
        //No para ser libeador
        no* nodeToFree = traversal;

        //percorre lista
        while(traversal != NULL)
        {
            traversal = traversal->prox;
            //Desaloca Node
            free(nodeToFree);
            //Aponta para o proximo tbm
            nodeToFree = traversal;
        }
    }
    free(grafoPt->array);
    free(grafoPt);
}

//Libera um grafo
void printGrafo(grafo* grafoPt)
{
    for(int i = 0; i < grafoPt->vertices; i++)
    {
        //No para percorrer
        no* traversal =  grafoPt->array[i].cabeca;
        printf("%d", traversal->ID);
        //percorre lista
        while(traversal != NULL)
        {
            traversal = traversal->prox;
            printf("%d\n", traversal->ID);
        }
    }
}