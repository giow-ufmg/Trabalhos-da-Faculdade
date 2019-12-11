// =----------------------------------------------------------=
// =                           AVISO:                         =
// =                   MODIFIQUE ESTE ARQUIVO!                =
// = Aqui, você deve implementar, obrigatoriamente, essas     =
// = duas funções:                                            =
// =     - `a_menor_que_b`: deve retornar quando uma string   =
// =        é menor que a outra (ambos com o mesmo tamanho);  =
// =     - `external_sort`: aqui, você deverá implementar o   =
// =        seu trabalho. Ordene os registros em `input_file` =
// =        e escreva-os em `output_file`, usando somente     =
// =        `memory` KB de memória.                           =
// =                                                          =
// = Instruções:                                              =
// =     - use a função `mathias_malloc` ao invés de          =
// =       `malloc`;                                          =
// =     - use a função `mathias_free` ao invés de `free`;    =
// =     - lembre-se que você tem somente `memory` KB de      =
// =       memória;                                           =
// =     - note que a sua implementação de `a_menor_que_b`    =
// =       afetará o resultado da verificação da resposta.    =
// =                                                          =
// = Dicas:                                                   =
// =     - você pode usar a sua função `a_menor_que_b` em     =
// =       sua implementação da função `external_sort`;       =
// =                                                          =
// =                      BOM TRABALHO!                       =
// =----------------------------------------------------------=


#include <math.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


#include "mem.h"
#include "heap.h"

int fTeto(float num) {
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}

// Parâmetros:
//     - a: uma cadeia de caracteres de tamanho `len`;
//     - b: uma cadeia de caracteres de tamanho `len`;
//     - len: o tamanho (quantidade de bytes) de `a` e `b`.
// Essa função deve retornar 1, se `a` é menor que `b` (`a` deve vir antes de `b` no
// arquivo), e 0 caso contrário.
// Ela também é usada para verificação da ordenação! Então, se você implementá-la
// erroneamente, a verificação também estará errada! 

int a_menor_que_b(char* a, char* b, int len) {
    if(strcmp(a,b)<0)
    {
        return 1;
    }
     else
    {
        return 0;
    }
}

FILE* openFile(const char* filename, char* mode)
{
    //Abre arquivo
    FILE *arquivo;
    arquivo = fopen(filename,mode);
    if(arquivo == NULL)
    {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }
    return arquivo;

}

int strCompare(const void *a, const void *b) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

void mergeFiles(const char *saida, int k, int tamLinhas)
{
    FILE* entrada[k];

    for(int i = 0; i < k; i++)
    {
        char filename[3];
        snprintf(filename, sizeof(filename), "%d", i);

        entrada[i] = openFile(filename, "r");
    }

    FILE *saidaFinal= openFile(saida, "w");
    fprintf(saidaFinal, "%d\n", tamLinhas-2);

    minHeap minHeap =  initMinHeap();
    int index;
    char linha[10000];
    for(index = 0; index < k; index ++)
    {
        if (fgets(linha, tamLinhas, entrada[index]) == NULL)
        {
            break;
        }
        insertNode(&minHeap, linha, index);//index do arquivo
    }

    int contador = 0;
    while(contador != index)
    {
        //Pega o menor elemento e poe na saida
        node cabeca = getMinHeap(&minHeap);
        fprintf(saidaFinal, "%s", cabeca.linha);

        if(fgets(cabeca.linha, tamLinhas,entrada[cabeca.index]) == NULL)
        {
            cabeca.linha = "~~~~~~~";
            contador++;
        }
        swap(&minHeap.elem[0], &cabeca);
        heapify(&minHeap, 0);
    }


    for(int i = 0; i < k; i++)
    {
        fclose(entrada[i]);
    }
    fclose(saidaFinal);
    deleteHeap(&minHeap);
}
// Parâmetros:
//     - input_file: o nome do arquivo com os registros de entrada;
//     - output_file: o nome do arquivo com os registros de entrada ordenados;
//     - memory: o limite de memória a ser usado.
// Essa função deverá ler todos registros do arquivo `input_file`, ordená-los e
// escrevê-los em `output_file`, usando memória menor ou igual a `memory`. Lembre-se
// de fechar todos os arquivos que você usar por aqui!!
void external_sort(const char* input_file, const char* output_file, unsigned int memory) {

    struct stat st;
    stat(input_file, &st);
    long tamanhoArq = st.st_size;
    memory *= 1000;

    FILE* entrada = openFile(input_file, "r");

    int tamLinhas;

    fflush(entrada);

    //Tamanho das linhas
    fscanf(entrada, "%d", &tamLinhas);
    //Pegar o \n e o \0
    tamLinhas+= 2;
    //printf("Tam Linhas + 2 = %d\n", tamLinhas);

    //Piso da memoria/linhas = numero maximo de linhas alocaveis
    int maxLinhasAlocaveis = memory/tamLinhas;

    long numFitas;

    if(tamanhoArq > memory) {
        numFitas = fTeto((float) tamanhoArq / memory)+1;
    }
    else{
        numFitas = 1;
    }

    //printf("Num Fitas:%ld\n", numFitas);


    FILE* saidas[numFitas];

    char nomeArq[3];

    for (int i = 0; i < numFitas; i++)
    {
        // converte i para string
        snprintf(nomeArq, sizeof(nomeArq), "%d", i);
        //printf("Nome arquivo[%d] = %s\n", i,nomeArq);

        // Abre arquivos para escrever
        saidas[i] = openFile(nomeArq, "w");
        //printf("Abrindo Saidas...\n");
    }

    //Aloco array de strings
    char **ptlinhas = (char**)malloc(maxLinhasAlocaveis * sizeof(char *));

    for(int i = 0; i < maxLinhasAlocaveis; i++)
    {
        //Alocar string com mathias malloc
        ptlinhas[i] = (char*) mathias_malloc(tamLinhas * sizeof(char));
        //printf("Alocando ptlinhas[%d]\n", i);
    }

    //Variaveis pra Preencher
    int i;
    bool more_input = true;
    int proximoArquivoSaida = 0;

    //pula \n
    fseek ( entrada , 1 , SEEK_CUR );

    //printf("Preenchendo vetor\n");
    //Preenche
    while (more_input)
    {
        //Prenche espaco disponivel na memoria
        for (i = 0; i < maxLinhasAlocaveis; i++)
        {
            //Copia string do arquivo para vetor de string
            if (fgets(ptlinhas[i], tamLinhas, entrada) == NULL) //Enquanto n for eof
            {
                more_input = false;
                break;
            }
        }
        //Ordena array de strings
        qsort(ptlinhas, i, sizeof(ptlinhas[0]), strCompare);

        if(proximoArquivoSaida >= numFitas) break;

        for (int j = 0; j < i; j++)
        {
            fprintf(saidas[proximoArquivoSaida], "%s", ptlinhas[j]);
        }
        proximoArquivoSaida++;
    }
    //printf("Desalocando linhas\n");
    for(int i = 0; i < maxLinhasAlocaveis; i++)
    {
        mathias_free(ptlinhas[i]);
    }
    free(ptlinhas);

    //printf("Fechando Arquivos\n");
    for(int i = 0; i < numFitas; i++)
    {
        fclose(saidas[i]);
    }
    fclose(entrada);

    //printf("Unindo Arquivos");
    mergeFiles(output_file, numFitas, tamLinhas);
}
