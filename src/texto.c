#include "texto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA        1000
#define MAX_TEXTO        10000
#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define TAM_ASCII        256


void inicializaTexto(texto *textoinicial) {
    int i;
    textoinicial->criptografado = calloc(MAX_TEXTO, sizeof(char));
    textoinicial->parcial = calloc(MAX_TEXTO, sizeof(char));
    for (i = 0; i < TAMANHO_ALFABETO; i++) {
        textoinicial->chave[i] = ' ';
    }
    textoinicial->chave[TAMANHO_ALFABETO] = '\0';
    for (i = 0; i < TAMANHO_ALFABETO; i++) {
        textoinicial->lista_frequencia[i].letra = 'A' + i;
        textoinicial->lista_frequencia[i].qtd = 0;
    }
}

void desalocaTexto(texto textoinicial) {
    free(textoinicial.criptografado);
    free(textoinicial.parcial);
}
void estadoAtual(texto textoinicial) {
    int i;
    printf("=== Texto criptografado ===\n");
    printf("%s", textoinicial.criptografado);
    printf("\n=== Chave ===\n");
    for (i = 0; i < TAMANHO_ALFABETO; i++) {
        printf("%c", i + 'A');
    }
    printf("\n");
    for (i = 0; i < TAMANHO_ALFABETO; i++) {
        printf("%c", textoinicial.chave[i]);
    }
    printf("\n");
    printf("=== Texto parcialmente decifrado ===\n");
    for (i = 0; i < strlen(textoinicial.criptografado); i++) {
        if (textoinicial.criptografado[i] == textoinicial.parcial[i]) {
            printf("%c", textoinicial.criptografado[i]);
        } else {
            printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, textoinicial.parcial[i]);
        }
    }
}

static int compare(const void *a, const void *b) {
    int arg1 = ((const frequencia *)a)->qtd;
    int arg2 = ((const frequencia *)b)->qtd;

    if (arg1 < arg2)
        return 1;
    if (arg1 > arg2)
        return -1;
    return 0;
}

void analiseFrequencia(texto *textoinicial) {
    int i;
    const char vetor_frequencia[TAMANHO_ALFABETO] = {'A', 'E', 'O', 'S', 'R', 'I', 'N', 'D', 'M',
                                                     'U', 'T', 'C', 'L', 'P', 'V', 'G', 'H', 'Q',
                                                     'B', 'F', 'Z', 'J', 'X', 'K', 'W', 'Y'};
    for (i = 0; i < strlen(textoinicial->criptografado); i++) {
        if (textoinicial->criptografado[i] >= 'A' && textoinicial->criptografado[i] <= 'Z') {
            textoinicial->lista_frequencia[textoinicial->criptografado[i] - 'A'].qtd++;
        }
    }
    qsort(textoinicial->lista_frequencia, TAMANHO_ALFABETO, sizeof(frequencia), compare);
    printf("Letra,  Cont.,  Freq. Alfabeto\n");
    for (i = 0; i < TAMANHO_ALFABETO; i++) {
        printf("%c\t%d\t%c\n", textoinicial->lista_frequencia[i].letra,
               textoinicial->lista_frequencia[i].qtd, vetor_frequencia[i]);
    }
    printf("\n");
}

static void shift_and_exato(char *texto, char *padrao) {
    //le o tamanho do texto e o tamanho do padrao
    int tamanhopadrao = strlen(padrao);
    int tamanhotexto = strlen(texto);
    int R = 0;
    int mascara[TAM_ASCII];
    int quantidade = 0;
    //inicializa o vetor mascara com 0
    for (int i = 0; i < TAM_ASCII; i++)
        mascara[i] = 0;
    //marca 1 na mascara do caractere de acordo com as posições de ocorrencia de cada caractere do padrão 
    for (int i = 1; i <= tamanhopadrao; i++)
        mascara[(int)padrao[i - 1]] |= 1 << (tamanhopadrao - i);

    for (int i = 0; i < tamanhotexto; i++) {
        //move R para a direita, adiciona 1 no inicio de R e faz and com a mascara do caractere atual no texto
        R = ((R >> 1) | (1 << (tamanhopadrao - 1))) & mascara[(int)texto[i]];
        //verifica se houve uma nova ocorrencia do padrão no texto 
        if (R & 1) {
            quantidade++;
        }
    }
    printf("Ocorrências: %d\n", quantidade);
}

void buscaCripto(texto textoinicial) {
    char padrao[100];
    printf("Qual o padrão utilizado?\n");
    scanf("%s", padrao);
    shift_and_exato(textoinicial.parcial, padrao);
}

void alteraChave(texto *textoinicial) {
    int i;
    char antigo, novo;
    printf("Informe a letra original, seguida da letra para a qual foi mapeada:\n");
    scanf("%c %c", &antigo, &novo);
    textoinicial->chave[(int)antigo - 'A'] = novo;
    printf("Registrado: %c -> %c\n", antigo, novo);

    for (i = 0; i < strlen(textoinicial->criptografado); i++) {
        if (textoinicial->parcial[i] == antigo)
            textoinicial->parcial[i] = novo;
    }
}

void exportaResultado(texto textoinicial) {
    char caminho[100];
    printf("Digite o caminho do arquivo de saida para a chave: \n");
    scanf("%s", caminho);
    FILE *arq = fopen(caminho, "w");
    if (!arq) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        fprintf(arq, "%c", i + 'A');
    }
    fprintf(arq, "\n%s", textoinicial.chave);
    fclose(arq);

    printf("Digite o caminho do arquivo de saida para o texto decifrado: \n");
    scanf("%s", caminho);
    arq = fopen(caminho, "w");
    if (!arq) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    fprintf(arq, "%s", textoinicial.parcial);
    fclose(arq);
}
void buscaParcial(texto textoinicial) { // shiftand aproximado
    int k,m,quantidade;
    long Masc[TAM_ASCII], i, j, Ri, Rant, Rnovo;
    quantidade = 0;

    char padrao[100];
    char buffer[100];
    printf("Qual o padrão e a tolerância utilizados?\n");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s %d", padrao, &k);
    long R[101];

    m = strlen(padrao);
    for (i = 0; i < TAM_ASCII; i++)
        Masc[i] = 0;
    for (i = 1; i <= m; i++) {
        Masc[padrao[i - 1] + 127] |= 1 << (m - i);
    }
    R[0] = 0;
    Ri = 1 << (m - 1);
    for (j = 1; j <= k; j++)
        R[j] = (1 << (m - j)) | R[j - 1];
    for (i = 0; i < strlen(textoinicial.parcial); i++) {
        Rant = R[0];
        Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[textoinicial.parcial[i] + 127];
        R[0] = Rnovo;
        for (j = 1; j <= k; j++) {
            Rnovo = ((((unsigned long)R[j]) >> 1) & Masc[textoinicial.parcial[i] + 127]
            | (unsigned long)(Rant >> 1));
            Rant = R[j];
            R[j] = Rnovo | Ri;
        }
        if ((Rnovo & 1) && evalido(textoinicial.parcial,m,i)){
            printf("@[%ld,%ld):",i-m+1,i+1);
            quantidade++;
            for (int z=i-m+1; z <= i; z++){
                printf("%c",textoinicial.parcial[z]);
            }
            printf("\n");
            // Ocorrências: 1
            // @[42,47): UEMDA
        }
    }
    printf("Ocorrências: %d\n", quantidade);
}
int evalido(char* string, int tampadrao,int i){
    int contador = 0;
    for (int z=i-tampadrao+1; z <= i; z++){
        if(string[z]>= 'A' && string[z] <= 'Z') contador++;
    }
    if(contador == tampadrao) return 1;
    return 0;
}
texto leArqv(char *nomeArq) {
    FILE *arq;
    texto textoinicial;
    char Linha[MAX_LINHA];
    arq = fopen(nomeArq, "rt");
    if (!arq) {
        printf("Problemas na abertura do arquivo\n");
        exit(1);
    }
    inicializaTexto(&textoinicial);
    while (!feof(arq)) {
        if (fgets(Linha, MAX_LINHA, arq) != NULL) {
            strcat(textoinicial.criptografado, Linha);
        }
    }
    strcpy(textoinicial.parcial, textoinicial.criptografado);
    fclose(arq);
    return textoinicial;
}
