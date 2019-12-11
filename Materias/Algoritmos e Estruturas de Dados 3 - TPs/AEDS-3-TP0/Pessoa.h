//
// Created by Giovanni Martinelli on 10/04/18.
//

#ifndef TP0_PESSOAS_H
#define TP0_PESSOAS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int ID;
    int IDADE;
}pessoa;


//-----------Funcoes-------------
//Alloca e retorna uma struct Pessoa
pessoa* criaPessoa();
//Cria uma lista de pessoas
pessoa** criaListaDePessoas(int n);
//Recebe e desaloca uma lista de pessoas
void freeListaDePessoas(pessoa** listaDePessoas, int n);



#endif //TP0_PESSOAS_H
