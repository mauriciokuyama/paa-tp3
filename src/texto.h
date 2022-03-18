#ifndef TEXTO_H
#define TEXTO_H

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
    char chave[TAMANHO_ALFABETO+1];
    frequencia lista_frequencia[TAMANHO_ALFABETO];
} texto;

void inicializaTexto(texto *textoinicial);
void estadoAtual(texto textoinicial);
void analiseFrequencia(texto *textoinicial);
void alteraChave(texto *textoinicial);
void buscaCripto(texto textoinicial);
void exportaResultado(texto textoinicial);
void buscaParcial(texto textoinicial);
void desalocaTexto(texto textoinicial);
texto leArqv(char* nomeArq);

#endif
