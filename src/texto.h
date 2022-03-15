#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ALFABETO 26

typedef struct Frequencia
{
    char letra;
    int qtd;
}frequencia;

typedef struct Texto
{
    char *criptografado;
    char *parcial;
    char chave[TAMANHO_ALFABETO];
    frequencia lista_frequencia[TAMANHO_ALFABETO];
} texto;

void inicializaTexto(texto *textoinicial);
void estadoAtual(texto textoinicial);
void analiseFrequencia(texto *textoinicial);
void desalocaTexto(texto textoinicial);
void buscaCripto(texto textoinicial);
void leArqv(char* nomeArq);
