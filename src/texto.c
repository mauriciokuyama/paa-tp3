#include "texto.h"

#define MAX_LINHA 1000

void inicializaTexto(texto *textoinicial) {
    
}

void desalocaTexto(texto textoinicial) {
    free(textoinicial.criptografado);
    free(textoinicial.parcial);
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
    while (!feof(arq)) {
        if(fgets(Linha, MAX_LINHA, arq) != NULL) {
            printf("%s", Linha);
        }
    }
    // desalocaTexto(textoinicial);
}