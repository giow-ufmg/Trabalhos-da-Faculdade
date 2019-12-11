//
// Created by giow on 5/10/18.
//

#ifndef TP1_HEAP_H
#define TP1_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

typedef struct node {
    int index ;
    char* linha;
} node ;

typedef struct minHeap {
    int tamanho ;
    node *elem ;
} minHeap ;


int meuAMenorqB(char *a, char *b) ;


/*
    Funcao para inicializar o min heap with tamanho = 0
*/
minHeap initMinHeap() ;


/*
    Function to troca data within two nodes of the min heap using pointers
*/
void swap(node *n1, node *n2);


/*
    Heapify function is used to make sure that the heap property is never violated
    In case of deletion of a node, or creating a min heap from an array, heap property
    may be violated. In such cases, heapify function can be called to make sure that
    heap property is never violated
*/
void heapify(minHeap *hp, int i) ;


/*
    Build a Min Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMinHeap() function to build the heap in O(n) time
*/
void buildMinHeap(minHeap *hp, char **arr, int size) ;
/*
    Function to insert a node into the min heap, by allocating space for that node in the
    heap and also making sure that the heap property and shape propety are never violated.
*/
void insertNode(minHeap *heap, char* data, int index) ;

node getMinHeap(minHeap *heap);

/*
    Function to delete a node from the min heap
    It shall remove the root node, and place the last node in its place
    and then call heapify function to make sure that the heap property
    is never violated
*/
void deleteNode(minHeap *hp) ;

/*
    Function to clear the memory allocated for the min heap
*/
void deleteMinHeap(minHeap *hp) ;

/*
    Function to display all the nodes in the min heap by doing a inorder traversal
*/
void inorderTraversal(minHeap *hp, int i);


/*
    Function to display all the nodes in the min heap by doing a preorder traversal
*/
void preorderTraversal(minHeap *hp, int i);

/*
    Function to display all the nodes in the min heap by doing a post order traversal
*/
void postorderTraversal(minHeap *hp, int i);

/*
    Function to display all the nodes in the min heap by doing a level order traversal
*/
void deleteHeap(minHeap *hp);



#endif //TP1_HEAP_H
