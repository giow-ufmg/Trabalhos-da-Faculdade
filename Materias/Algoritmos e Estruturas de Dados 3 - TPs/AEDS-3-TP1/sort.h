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

#ifndef __SORT_H__
#define __SORT_H__

// Parâmetros:
//     - a: uma cadeia de caracteres de tamanho `len`;
//     - b: uma cadeia de caracteres de tamanho `len`;
//     - len: o tamanho (quantidade de bytes) de `a` e `b`.
// Essa função deve retornar 1, se `a` é menor que `b` (`a` deve vir antes de `b` no
// arquivo), e 0 caso contrário.
int a_menor_que_b(char* a, char* b, int len);

// Parâmetros:
//     - input_file: o nome do arquivo com os registros de entrada;
//     - output_file: o nome do arquivo com os registros de entrada ordenados;
//     - memory: o limite de memória a ser usado.
// Essa função deverá ler todos registros do arquivo `input_file`, ordená-los e
// escrevê-los em `output_file`, usando memória menor ou igual a `memory`. Lembre-se
// de fechar todos os arquivos que você usar por aqui!!
void external_sort(const char* input_file, const char* output_file, unsigned int memory);

#endif
