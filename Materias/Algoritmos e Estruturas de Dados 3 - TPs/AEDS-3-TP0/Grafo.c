//
// Created by Giovanni Martinelli on 10/04/18.
//
#include "Grafo.h"

//Cria um no com Valor: X
no* criaNo(int x, int y)
{
    no* noPt = (no*) malloc(sizeof(no));
    if(noPt == NULL) {
        perror("Node Malloc fail");
        exit(EXIT_FAILURE);
    }
    noPt->objPessoa = criaPessoa();
    noPt->objPessoa->ID = x;
    noPt->objPessoa->IDADE = y;
    noPt->prox = NULL;
    return noPt;
}

//Cria um grafo com V vertices
grafo* criaGrafo(int v)
{
    //Aloca grafo
    grafo* grafoPt = (grafo*) malloc(sizeof(grafo));
    if(grafoPt == NULL) {
        perror("Grafo Malloc fail\n");
        exit(EXIT_FAILURE);
    }

    grafoPt->vertices = v;

    //Aloca array de vertices
    grafoPt->array = (lista*) malloc(v * sizeof(lista));
    if(grafoPt->array == NULL) {
        perror("Grafo->array Malloc fail\n");
        exit(EXIT_FAILURE);
    }

    //Null em todos os ponteiros para as listas
    for(int i = 0; i < v; i++) {
        grafoPt->array[i].cabeca = NULL;
    }

    return grafoPt;
}

//Add Aresta ao Grafo
void addAresta(grafo* grafoPt, int ini, int fim, pessoa** Pessoa)
{
    //add no ini -> fim
    no* temp = criaNo(fim, Pessoa[fim-1]->IDADE);
    temp->objPessoa->ID = fim;
    //Add No no inicio da lista
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
            //Desaloca objPessoa
            free(nodeToFree->objPessoa);
            //Desaloca Node
            free(nodeToFree);
            //Aponta para o proximo tbm
            nodeToFree = traversal;
        }
    }
    free(grafoPt->array);
    free(grafoPt);
}
//Subfuncao que itera sobre a lista de adjacencias
void percorreGrafo(const grafo *grafoPt, pessoa **Pessoas, int *estado, int like) {
    int i;
    for(i = 0; i < grafoPt->vertices; i++)
    {
        //NO  tmp para percorrer array
        no* tmp =  grafoPt->array[i].cabeca;

        //Roda a lista
        while(tmp != NULL)
        {
            //Se o amigo[raiz] nao gostou (nao precisa olhar se os amigos gostaram)
            if(estado[i] == 2) break;

            //Se nao foi visitado
            if(estado[tmp->objPessoa->ID - 1] == 0)
            {
                //Tem idade para gostar
                if(tmp->objPessoa->IDADE < 35)
                {
                    //Seu amigo gostou e compartilhou
                    if(estado[i] == 3)
                    {
                        like++;
                        estado[tmp->objPessoa->ID - 1] = 3; //visitou e gostou
                    }
                    else//A mensagem nunca chegou ate vc
                    {
                        estado[tmp->objPessoa->ID - 1] = 0; // 0 = nao visitou
                    }
                }
                else//Amigo e mais velho, viu a publicacao e nao gostou
                {
                    estado[tmp->objPessoa->ID - 1] = 2; //visitou e nao gostou
                }
            }
                //Se o amigo for quem tiver curtido entao o no raiz curte tbm
            else if (estado[tmp->objPessoa->ID - 1] == 3)
            {
                if(estado[i] == 0 && Pessoas[i]->IDADE < 35)//Se o amigo de [i] tiver compartilhado entao [i] tbm ouviu
                {
                    like++;
                    estado[i] = 3;
                }
            }
            tmp = tmp->prox;
        }
    }
    printf("%d\n", like);
}

void contaLikes(grafo *grafoPt, pessoa **Pessoas, int *estado, int ini) {
    int like = 0;

    //Marca a Pessoa inicial como visitada
    estado[ini-1] = 3;

    //Se a pessoa incial for velha
    if (Pessoas[ini-1]->IDADE >= 35)
    {
        printf("0");
        return;
    }
    else
    {
        like++;
    }
    //Percorrer os nos
    //[i] -> [] -> [] -> []
    percorreGrafo(grafoPt, Pessoas, estado, like);

}
