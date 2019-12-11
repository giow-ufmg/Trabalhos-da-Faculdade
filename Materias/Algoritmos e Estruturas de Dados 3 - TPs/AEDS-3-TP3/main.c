#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main() {
    printf("Hello, World!\n");
    int n,m;
    scanf("%d\n", &n);
    scanf("%d\n", &m);

    int* vetor = (int*) malloc(2 * m * sizeof(int));//Savar as conexoes

    for(int i = 0; i < n - 1; i += 2)
    {
        scanf("%d %d\n", &vetor[i], &vetor[i+1]);
    }

    grafo* grafo1 = criaGrafo(n);

    for(int i = 0; i < n - 1; i += 2)
    {
        addAresta(grafo1, vetor[i], vetor[i+1]);
    }

    for(int i = 0; i < n; i++)
    {

    }

    freeGrafo(grafo1);
    return 0;
}