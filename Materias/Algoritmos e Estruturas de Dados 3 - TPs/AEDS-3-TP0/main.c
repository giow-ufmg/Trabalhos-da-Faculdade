#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <zconf.h>
#include "Pessoa.h"
#include "Grafo.h"
#include <time.h>

#define BUFFERSIZE 100



int getTokenInt(const char *token) {
    //Ptr para caracteres adicionais
    char * ptrFim;

    //recebe o valor de strtol (que e long)
    int val = (int)strtol(token, &ptrFim, 10);

    //Testa Conversao para int
    if (ptrFim == token) {
        fprintf(stderr, "String Conversion Failed \n");
        exit(EXIT_FAILURE);
    }
    return val;
}

void iteraEPreenche(char *linha, char *token, int numeroPessoas, int numeroRelacoes,
                    pessoa **Pessoa, grafo *grafoPt) {

    int i;//indice token
    int n;//Indice da linha

    //Itera sobre as linhas que contem as pessoas
    for(n = 0; n < numeroPessoas; n++)
    {
        fgets(linha, BUFFERSIZE, stdin);
        i = 0;//indice token
        token = strtok(linha, " "); //Separa a linha por espaco

        while(token != NULL) //Enquanto Tiver tokens na linha
        {
            if (i == 0) // Primeiro Token == ID
            {
                Pessoa[n]->ID = getTokenInt(token);
            }
            else if (i == 1){ // Segundo Token == Idade
                Pessoa[n]->IDADE = getTokenInt(token);
            }
            token = strtok(NULL, " "); //Para o prox token
            i++;
        }
    }

    //Itera sobre as linhas que contem as arestas
    int ini = 0, dest = 0;
    for(n = 0; n < numeroRelacoes; n++)
    {
        fgets(linha, BUFFERSIZE, stdin);
        i = 0;
        token = strtok(linha, " "); //Separa a linha por espaco

        while(token != NULL) //Enquanto Tiver tokens na linha
        {
            if (i == 0) // Primeiro Token == Pessoa
            {
                ini = getTokenInt(token);
            }
            else if (i == 1){ // Segundo Token == Amigo da Pessoa
                dest = getTokenInt(token);
            }
            token = strtok(NULL, " "); //Para o prox token
            i++;
        }
        addAresta(grafoPt, ini, dest, Pessoa); //amizade ini -> fim
        addAresta(grafoPt, dest, ini, Pessoa); //amizade fim -> ini
    }
}

int main() {
    //Declaracoes
    char linha[BUFFERSIZE];
    char *token;
    int numeroPessoas;
    int numeroRelacoes;

    //Caso esteja sendo rodado em um terminal, abrir o arquivo no stdin
    if (isatty(fileno(stdin)))
    {
        freopen("../entradas/teste_3.txt","r",stdin);
    }

    //Recupera numero de pessoas (da primeira linha)
    fgets(linha, BUFFERSIZE, stdin);
    token = strtok(linha, " ");
    numeroPessoas = getTokenInt(token);

    //Lista de Estados
    //Estado, 0 = Nunca visitado, 2 = Visitado nao Gostou, 3 = Visitou e Gostou
    //int* estado = (int*) malloc(numeroPessoas * sizeof(int));
    int* estado = (int*) calloc((size_t)numeroPessoas, sizeof(int));

    //Aloca Lista de Pessoas e seus arrays
    pessoa** Pessoa = criaListaDePessoas(numeroPessoas);

    //Aloca grafo
    grafo* grafoPt = criaGrafo(numeroPessoas);

    //Recupera numero de Relacoes
    fgets(linha, BUFFERSIZE, stdin);
    token = strtok(linha, " ");
    numeroRelacoes = getTokenInt(token);

    //Analisa Arquivo e preenche o grafo e a lista de pessoas
    iteraEPreenche(linha, token, numeroPessoas, numeroRelacoes, Pessoa, grafoPt);

    //Recupera Informacao da primeira pessoa a compartilhar
    fgets(linha, BUFFERSIZE, stdin);
    token = strtok(linha, " ");
    int primeiraPessoa;
    primeiraPessoa = getTokenInt(token);

    //Conta as coisas
    contaLikes(grafoPt, Pessoa, estado, primeiraPessoa);

    //Frees & Closes
    free(estado);
    freeListaDePessoas(Pessoa, numeroPessoas);
    freeGrafo(grafoPt);
    fclose(stdin);
    return 0;
}