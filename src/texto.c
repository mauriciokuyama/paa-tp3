#include "texto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1000
#define MAX_TEXTO 10000
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void inicializaTexto(texto *textoinicial) {
    int i;
    textoinicial->criptografado = malloc(MAX_TEXTO * sizeof(char));
    textoinicial->parcial = malloc(MAX_TEXTO * sizeof(char));
    for(i = 0; i < TAMANHO_ALFABETO; i++){
        textoinicial->chave[i] = ' ';
    }
    for(i = 0; i < TAMANHO_ALFABETO; i++){
        textoinicial->lista_frequencia[i].letra = 'A'+ i;
        textoinicial->lista_frequencia[i].qtd = 0;
    }
}

void desalocaTexto(texto textoinicial) {
    free(textoinicial.criptografado);
    free(textoinicial.parcial);
}
void estadoAtual(texto textoinicial){
    int i;
    printf("=== Texto criptografado ===\n");
    printf("%s",textoinicial.criptografado);
    printf("\n=== Chave ===\n");
    for (i=0; i<TAMANHO_ALFABETO; i++) {
        printf("%c", i + 'A');
    }
    printf("\n");
    for (i=0; i<TAMANHO_ALFABETO; i++) {
        printf("%c", textoinicial.chave[i]);
    }
    printf("\n");
    printf("=== Texto parcialmente decifrado ===\n");
    for(i=0; i< strlen(textoinicial.criptografado);i++) {
        if (textoinicial.criptografado[i] == textoinicial.parcial[i]) {
            printf("%c",textoinicial.criptografado[i]);
        } else{
            printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, textoinicial.parcial[i]);
        }
    }
 }

static int compare(const void* a, const void* b)
{
    int arg1 = ((const frequencia*)a)->qtd;
    int arg2 = ((const frequencia*)b)->qtd;

    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}

 void analiseFrequencia(texto *textoinicial) {
    int i;
    const char vetor_frequencia[TAMANHO_ALFABETO] = {'A','E','O','S','R','I','N','D','M','U','T','C','L','P','V','G','H','Q','B','F','Z','J','X','K','W','Y'};
    for (i=0; i< strlen(textoinicial->criptografado); i++) {
        if (textoinicial->criptografado[i] >= 'A' && textoinicial->criptografado[i] <= 'Z') {
            textoinicial->lista_frequencia[textoinicial->criptografado[i]-'A'].qtd++;
        }
    }
    qsort(textoinicial->lista_frequencia, TAMANHO_ALFABETO, sizeof(frequencia), compare);
    printf("Letra,  Cont.,  Freq. Alfabeto\n");
    for (i=0; i<TAMANHO_ALFABETO; i++) {
        printf("%c\t%d\t%c\n", textoinicial->lista_frequencia[i].letra,textoinicial->lista_frequencia[i].qtd, vetor_frequencia[i]);
    }
    printf("\n");
}

void leArqv(char* nomeArq) {
    FILE *arq;
    texto textoinicial;
    char Linha[MAX_LINHA];
    arq = fopen(nomeArq, "rt");
    if (!arq) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    inicializaTexto(&textoinicial);
    while (!feof(arq)) {
        if(fgets(Linha, MAX_LINHA, arq) != NULL){
            strcat(textoinicial.criptografado, Linha);
        }
    }
    strcpy(textoinicial.parcial, textoinicial.criptografado);
    analiseFrequencia(&textoinicial);
    estadoAtual(textoinicial);
    desalocaTexto(textoinicial);
    fclose(arq);
}
