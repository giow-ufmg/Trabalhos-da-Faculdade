#include "heap.h"


int meuAMenorqB(char *a, char *b) {
    if(strcmp(a,b)<0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
    Inicializa heap com valor 0
*/
minHeap initMinHeap() {
    minHeap hp ;
    hp.tamanho = 0 ;
    return hp ;
}


/*
    Funcao simples de troca de nos
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}


/*
    Manter Heap em ordem
*/
void heapify(minHeap *hp, int i) {
    int smallest;

    if(LCHILD(i) < hp->tamanho && meuAMenorqB(hp->elem[LCHILD(i)].linha, hp->elem[i].linha))
    {
       smallest = LCHILD(i);
    }
    else
    {
        smallest = i;
    }
    if(RCHILD(i) < hp->tamanho && meuAMenorqB(hp->elem[RCHILD(i)].linha, hp->elem[smallest].linha))
    {
        smallest = RCHILD(i) ;
    }
    if(smallest != i)
    {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}


/* Insere no no heal
*/
void insertNode(minHeap *heap, char* data, int index) {
    if(heap->tamanho) {
        heap->elem = realloc(heap->elem, (heap->tamanho + 1) * sizeof(node)) ;
    } else {
        heap->elem = malloc(sizeof(node)) ;
    }

    node no ;
    no.linha = (char*) malloc(strlen(data) * sizeof(char));
    strcpy(no.linha, data);
    no.index = index;

    int i = (heap->tamanho)++ ;
    while(i && meuAMenorqB(no.linha, heap->elem[PARENT(i)].linha)) {
        heap->elem[i] = heap->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    heap->elem[i] = no ;
}

node getMinHeap(minHeap *heap)
{
    return heap->elem[0];
}

/*
    Deleta No Heap
*/
void deleteNode(minHeap *hp) {
    if(hp->tamanho) {
        //printf("Deleting node %s\n\n", hp->elem[0].linha) ;
        hp->elem[0] = hp->elem[--(hp->tamanho)] ;
        hp->elem = realloc(hp->elem, hp->tamanho * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
        printf("\nMin Heap is empty!\n") ;
        free(hp->elem[0].linha);
        free(hp->elem) ;
    }
}


/*
    Deleta MinHeap
*/
void deleteMinHeap(minHeap *hp) {
    free(hp->elem) ;
}

/*
    Percorre Heap
 */
void deleteHeap(minHeap *hp) {
    int i ;
    for(i = 0; i < hp->tamanho; i++) {
        deleteNode(hp);
    }
}

