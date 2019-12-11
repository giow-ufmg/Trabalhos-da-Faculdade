#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strCompare(const void *a, const void *b) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}

//qsort(string_matrix[i], contador[distancia-1], sizeof(string_matrix[0][0]), strCompare);


static int distance (const char * word1,
                     int len1,
                     const char * word2,
                     int len2)
{
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

int main() {
    //Declaracoes
    int nEntradas;
    int nMudancas;
    char palavra[150];
    char pDict[10050];

    //Lendo valores
    scanf("%d", &nEntradas);
    scanf("%d", &nMudancas);
    scanf("%s", palavra);
    int tamPalavra =  strlen(palavra);

    char string_matrix[10][1000][200];

    //Abrindo Saida
    FILE* SAIDA = fopen("output.txt", "w");
    fprintf(SAIDA, "%s\n", palavra);


    int contador[10];
    memset(contador, 0, sizeof(contador));

    int distancia = 0;
    for(int i = 0; i < nEntradas; i++)
    {
        scanf("%s", pDict);
        //tentar alguma poda aqui
        distancia = distance(palavra, tamPalavra, pDict, strlen(pDict));
        printf("Distancia de %s: %d\n", pDict, distancia);
        if (distancia != 0 && distancia <= nMudancas)
        {
            strcpy(string_matrix[distancia-1][contador[distancia-1]],pDict);
            contador[distancia-1]++;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        qsort(string_matrix[i], contador[distancia-1], sizeof(string_matrix[0][0]), strCompare);
        for(int j = 0; j <= contador[distancia-1]; j++)
        {
            printf("%s\n", string_matrix[i][j]);
        }
    }

    fclose(SAIDA);
    return 0;
}