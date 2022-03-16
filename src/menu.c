#include "menu.h"


#define VERMELHO    "\x1b[31m"
#define CIANO       "\x1b[36m"
#define AMARELO     "\x1b[33m"
#define MAGENTA     "\x1b[35m"
#define RESET       "\x1b[0m"

void menu()
{
    int op = 0;

    while (op != 7)
    {
        printf(CIANO "\n                                  -- Menu --                                 \n" CIANO);
        printf(AMARELO "\n                1-Apresentar o estado atual da criptoanálise                 \n" AMARELO);
        printf(AMARELO "\n            2-Fazer análise de frequência no texto criptografado             \n" AMARELO);
        printf(AMARELO "\n       3-Realizar casamento exato de caracteres no texto criptografado       \n" AMARELO);
        printf(AMARELO "\n4-Realizar casamento aproximado de caracteres no texto parcialmente decifrado\n" AMARELO);
        printf(AMARELO "\n                      5-Alterar chave de criptografia                        \n" AMARELO);
        printf(AMARELO "\n                6-Exportar resultado e encerrar o programa                   \n" AMARELO);
        printf(VERMELHO "\n                                   7-SAIR                                   \n" VERMELHO);

        printf(RESET"Opcao Escolhida: "RESET);
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                printf(MAGENTA"\nSaindo...\n\n"MAGENTA);
                break;
            default:
                printf(MAGENTA"Opcao Invalida!\n"MAGENTA);
                break;
        }
    }
}