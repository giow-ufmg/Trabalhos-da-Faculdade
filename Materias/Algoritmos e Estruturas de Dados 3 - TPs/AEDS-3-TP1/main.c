// =----------------------------------------------------------=
// =                           AVISO:                         =
// =                NÃO MODIFIQUE ESTE ARQUIVO!               =
// = Ou modifique, não sou seu rei! Sou só um aviso...        =
// = Faça-o por sua conta e risco. Não poderei ajudar caso    =
// = você o faça.                                             =
// =                                                          =
// = Lembre-se que, na hora de compilar, usarei este arquivo  =
// = da forma como ele está agora!                            =
// =----------------------------------------------------------=

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.h"
#include "mem.h"


const char* INPUT_FILE;
const char* OUTPUT_FILE;
unsigned int MEMORY;

void print_usage(const char* prog) {
    fprintf(stderr, "Você deve informar 3 parâmetros na linha de comando:\n");
    fprintf(stderr, "\t- arquivo_de_entrada: arquivo contendo os registros.\n");
    fprintf(stderr, "\t- arquivo_de_saída: arquivo onde os registros ordenados deverão ser salvos.\n");
    fprintf(stderr, "\t- memoria_maxima: memória máxima a ser utilizada, em KB.\n");

    fprintf(stderr, "\n");

    fprintf(stderr, "Exemplo:\n");
    fprintf(stderr, "\t$ %s arquivo_de_entrada.txt arquivo_de_saida.txt 1024\n", prog);

    fprintf(stderr, "\n");
}

void print_error() {
    fprintf(stderr, "NÃO SE ESQUEÇA DE INFORMAR OS 3 PARÂMETROS!!\n");
}

void print_summary(double total_time, int ordered, int overused_memory) {
    printf("=------------- Resultados -------------=\n");

    if (ordered) printf("Ordenado: SIM\n");
    else printf("Ordenado: NAO\n");

    if (overused_memory) printf("Memoria: FAIL ");
    else printf("Memoria: OK ");
    printf("(%.4f kb)\n", (double) get_memory_peak() / 1024.0);

    printf("Tempo: %.4f milisegundos\n", total_time);

    printf("=--------------------------------------=\n");
}

void print_header() {
    fprintf(stderr, "=------------- Informações -------------=\n");
    fprintf(stderr, "Entrada: %s\n", INPUT_FILE);
    fprintf(stderr, "Saida: %s\n", OUTPUT_FILE);
    fprintf(stderr, "Memoria: %u\n", MEMORY);
    fprintf(stderr, "=---------------------------------------=\n");
}

int parse_args(int argc, const char** argv) {
    if (argc < 4) {
        print_usage(argv[0]);
        return 0;
    } else {
        INPUT_FILE = argv[1];
        OUTPUT_FILE = argv[2];
        MEMORY = atoi(argv[3]);
        return 1;
    }
}

int verify() {
    FILE* out = fopen(OUTPUT_FILE, "r");

    if (out == NULL) {
        fprintf(stderr, "NÃO FOI POSSÍVEL ABRIR O ARQUIVO `%s`.\n", OUTPUT_FILE);
        return 0;
    }

    unsigned int len;
    fscanf(out, "%u%*c", &len);
    char rec[2][len];

    int cur = 0, last = 1, number_of_records = 0;
    while (fscanf(out, "%[^\n]%*c", &rec[cur][0]) != EOF) {
        if (number_of_records != 0) {
            int chk = a_menor_que_b(&rec[last][0], &rec[cur][0], len);

            if (!chk) {
                fprintf(stderr, "ERROR: STRINGS EM ORDEM ERRADA:\n");
                fprintf(stderr, "%s\n", &rec[last][0]);
                fprintf(stderr, "%s\n", &rec[cur][0]);
                fclose(out);
                return 0;
            }
        }

        // Swap `cur` and `last`.
        int tmp = cur;
        cur = last;
        last = tmp;

        ++number_of_records;
    }

    fclose(out);
    return 1;
}

int main(int argc, const char** argv) {
    int ordered = 0;
    int overused_memory = 1;

    if (parse_args(argc, argv)) {
        struct timeval begin, end;

        print_header();

        // Inicializa o gerenciador de memória de Mathias.
        _mathias_memory_init();

        gettimeofday(&begin, NULL);
        external_sort(INPUT_FILE, OUTPUT_FILE, MEMORY);
        gettimeofday(&end, NULL);

        ordered = verify();

        double total_time = 0;
        total_time += (double) (end.tv_usec - begin.tv_usec) / 1000.0;
        total_time += (double) (end.tv_sec - begin.tv_sec) * 1000.0;

        unsigned int total_memory = get_memory_peak();
        overused_memory = total_memory > (MEMORY * 1024);
        print_summary(total_time, ordered, overused_memory);
    } else {
        print_error();
        return 0;
    }

    if (!ordered || overused_memory) {
        return 1;
    }
    return 0;
}
