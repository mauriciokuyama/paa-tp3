#include <stdio.h>
#include <stdlib.h>

typedef struct Texto
{
    char *criptografado;
    char *parcial;
    char chave[26];
} texto;

void inicializaTexto(texto *textoinicial);
void desalocaTexto(texto textoinicial);
void leArqv(char* nomeArq);

