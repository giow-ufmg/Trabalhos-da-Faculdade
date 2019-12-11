//
// Created by Giovanni Martinelli on 10/04/18.
//
//Struct Pessoa
#include "Pessoa.h"

//Alloca e retorna uma struct Pessoa
pessoa* criaPessoa()
{
    pessoa* obj1 = (pessoa*) malloc(sizeof(pessoa));
    if(obj1 == NULL)
    {
        perror("Malloc fail");
        exit(EXIT_FAILURE);
    }
    return obj1;
}

//Cria uma lista de pessoas
pessoa** criaListaDePessoas(int n)
{
    pessoa** pPessoa = (pessoa**) malloc(n * sizeof(pessoa*));
    if(pPessoa == NULL)
    {
        perror("Malloc fail");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; i++)
    {
        pPessoa[i] = criaPessoa();
    }
    return pPessoa;
};

//Recebe e desaloca uma lista de pessoas
void freeListaDePessoas(pessoa** listaDePessoas, int n)
{
    for(int i = 0; i < n; i ++)
    {
        free(listaDePessoas[i]);
    }
    free(listaDePessoas);
}


