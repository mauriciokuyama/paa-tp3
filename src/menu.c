#include "menu.h"
#include "texto.h"

#include <stdio.h>

#define VERMELHO "\x1b[31m"
#define CIANO    "\x1b[36m"
#define AMARELO  "\x1b[33m"
#define MAGENTA  "\x1b[35m"
#define RESET    "\x1b[0m"

void menu()
{
    texto textoinicial = escolhe_arquivo();
    int op = 0;
    char buffer[10];

    while (op != 7)
    {
        printf(CIANO "\n                                  -- Menu --                                 \n" RESET);
        printf(AMARELO "\n                1-Apresentar o estado atual da criptoanalise                 \n" RESET);
        printf(AMARELO "\n            2-Fazer analise de frequencia no texto criptografado             \n" RESET);
        printf(AMARELO "\n       3-Realizar casamento exato de caracteres no texto criptografado       \n" RESET);
        printf(AMARELO "\n4-Realizar casamento aproximado de caracteres no texto parcialmente decifrado\n" RESET);
        printf(AMARELO "\n                      5-Alterar chave de criptografia                        \n" RESET);
        printf(AMARELO "\n                6-Exportar resultado e encerrar o programa                   \n" RESET);
        printf(VERMELHO "\n                                   7-SAIR                                   \n" RESET);

        printf("Opcao Escolhida: ");
        fgets(buffer, 10, stdin);
        sscanf(buffer, "%d", &op);

        switch (op)
        {
        case 1:
            estadoAtual(textoinicial);
            para_execucao();
            break;
        case 2:
            analiseFrequencia(&textoinicial);
            para_execucao();
            break;
        case 3:
            buscaCripto(textoinicial);
            para_execucao();
            break;
        case 4:
            buscaParcial(textoinicial);
            para_execucao();
            break;
        case 5:
            alteraChave(&textoinicial);
            para_execucao();
            break;
        case 6:
            exportaResultado(textoinicial);
            para_execucao();
            break;
        case 7:
            printf(MAGENTA "\nSaindo...\n\n" RESET);
            break;
        default:
            printf(MAGENTA "Opcao Invalida!\n" RESET);
            break;
        }

    }
}

texto escolhe_arquivo()
{
    char caminho[100];
    char buffer[100];
    printf(VERMELHO "\n Digite o nome do arquivo para ser lido : " RESET);
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s", caminho);
    return leArqv(caminho);
}

void para_execucao(){
    char buffer[10];
    printf("\nDigite enter para continuar...\n");
    fgets(buffer, 10, stdin);
}
