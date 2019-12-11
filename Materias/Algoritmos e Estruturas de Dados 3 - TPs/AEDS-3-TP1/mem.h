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

#ifndef __MEM_H__
#define __MEM_H__

// ---------------------------------------
// --------- USAR ESSAS FUNÇÕES ----------
// ---------------------------------------
void* mathias_malloc(unsigned int size);
void mathias_free(void* ptr);
// ---------------------------------------
// ---------------------------------------

// NÃO USEM ESSA FUNÇÃO!!!
void _mathias_memory_init();
// Você também não precisa de nenhuma dessas duas!!!
unsigned int get_memory_peak();
unsigned int get_memory_using();

#endif
